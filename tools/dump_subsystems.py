#!/usr/bin/env python3
"""Recover every subsystem global's name from GameEngine::init's own strings.

initSubsystem is a template:

    template<class T> void initSubsystem( T*& sysref, AsciiString name, T* sys,
                                          Xfer *pXfer, ... )

and retail's GameEngine::init calls it once per subsystem, passing the
subsystem's *name as a string literal* right before passing the address of the
global it initialises:

    push 0x1076494          ; "TheRankInfoStore"
    call AsciiString::AsciiString
    push 0x12f1014          ; &TheRankInfoStore   <-- named by the line above
    call initSubsystem<RankInfoStore>

That pairing is the only naming evidence in the image for most of these
globals, and it is decisive: a reference argument cannot bind through a
conversion, so the global's declared type IS T, and the string spells it.

Everything downstream depends on it. A one-line INI block parser such as

    mov ecx, [0x12ed740]
    push <ini>
    call <some member>

byte-verifies whatever we call 0x12ed740, because build.py fills the DIR32 slot
from the target (see tools/xref_global.py). Knowing 0x12ed740 is
ThePlayerAITypeSet is what turns that row from a guess into a match.

--boot additionally recovers the order the engine boots in, which is a separate
finding: BFME passes NULL for all three of initSubsystem's trailing const char*
path arguments at every one of the sites. Zero Hour hands the subsystem its
INI files there; BFME does not use them at all, and instead interleaves plain
INI::load calls between the registrations. So the boot-time INI order is not
readable from the initSubsystem arguments -- it has to be read from the calls
sitting between them, which is what --boot does.

Usage:
  python3 tools/dump_subsystems.py                    # table of name -> global
  python3 tools/dump_subsystems.py --csv              # append-ready for symbols.csv
  python3 tools/dump_subsystems.py --boot             # boot order -> docs/boot_order.md
"""
import argparse
import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import dump_ini_schema as S

# GameEngine::init, from its masm dump. Everything is disassembled forward from
# this exact start -- scanning for the push encoding instead finds hits inside
# other instructions' immediates and misaligns the rest of the listing.
INIT_RVA = 0x00079060
# 7123, and it really is 7123 even though tools/audit_short_rows.py flags a jcc
# branching 63 bytes past that end and Image.body_size measures 7322. Both are
# overruns: ??1GameEngine@@UAE@XZ starts at exactly 0x00079060 + 7123, so the
# branch target and the measured tail are inside the destructor, not inside init.
# Rescanning at 7322 finds no additional registrations, which confirms it.
INIT_SIZE = 7123
MIN_EXPECTED = 55

# INI::load(AsciiString, INILoadType, Xfer *). Not in the ledger yet -- ini.cpp
# still carries it present-unmatched -- so the address comes from the note on
# the matched ?prepFile@INI@@IAEXVAsciiString@@W4INILoadType@@@Z row. If it is
# ever wrong, --boot finds zero loads and MIN_EXPECTED_LOADS stops the run
# rather than quietly reporting a boot sequence with no INI in it.
INI_LOAD_RVA = 0x00853A20
MIN_EXPECTED_LOADS = 5

INI_LOAD_TYPE = {0: "INI_LOAD_INVALID", 1: "INI_LOAD_OVERWRITE",
                 2: "INI_LOAD_CREATE_OVERRIDES"}


def _initialized_ranges(img):
    """RVA ranges that actually have bytes in the file.

    .data's virtual size is larger than its raw size -- the tail is the zero-fill
    that holds every uninitialised global, and these singletons all live there.
    Reading it walks off the end of .data's file bytes and into the next section,
    so an uninitialised global decodes as whatever text happens to follow.

    That is not hypothetical: TheHouseColorSystem's global at 0x012F0FEC came
    back as the string "CloneImage", so collect() below classified the push as a
    name rather than as the &sysref argument and dropped the whole site.

    Sections are laid out contiguously in the file, so the next section's raw
    pointer is where this one's real bytes stop.
    """
    secs = sorted(img.secs, key=lambda s: s["raw_pointer"])
    out = []
    for i, s in enumerate(secs):
        nxt = secs[i + 1]["raw_pointer"] if i + 1 < len(secs) else len(img.data)
        raw_len = max(0, min(nxt - s["raw_pointer"], s["size"]))
        out.append((s["rva"], s["rva"] + raw_len))
    return out


def _initialized(ranges, va):
    rva = va - S.IMAGE_BASE
    return any(lo <= rva < hi for lo, hi in ranges)


def _is_data(img, va):
    """True if va lands in a mapped, non-executable section."""
    return bool(img.read(va, 4)) and not img.in_text(va)


def collect(img, rva, size):
    """(name, global_va, call_rva) for each `push "TheX"` ... `push g` ... `call`."""
    o = rva - img.tbase
    ranges = _initialized_ranges(img)
    pending_name = None
    pending_global = None
    out = []
    for ins in S._MD.disasm(img.text[o:o + size], rva):
        if ins.mnemonic == "push" and ins.op_str.startswith("0x"):
            imm = int(ins.op_str, 16)
            # Only bytes that exist in the file can be a string literal.
            text = img.cstr(imm) if _initialized(ranges, imm) else None
            if text and text.startswith("The") and len(text) > 4:
                pending_name = text
                pending_global = None
            elif pending_name and not text and _is_data(img, imm):
                # A mapped, non-code address pushed after the name: &sysref.
                # The mapping test is what keeps `push 0x14; call operator new`
                # -- which precedes most of these sites -- from being read as a
                # global; 0x14 is simply not an address in this image.
                pending_global = imm
        elif ins.mnemonic == "call" and pending_name and pending_global:
            # Retail links incrementally: the call goes to a 5-byte E9 thunk,
            # not the instantiation. Ledger rows claim the body, so follow it.
            target = (img.deref_thunk(int(ins.op_str, 16))
                      if ins.op_str.startswith("0x") else None)
            out.append((pending_name, pending_global, target))
            pending_name = pending_global = None
    return out


# ??$initSubsystem@VScienceStore@@@@YAXAAPAVScienceStore@@...  -> ScienceStore
_T_RE = re.compile(r"^\?\?\$initSubsystem@[VU]([^@]+)@@")


def type_of(row_name):
    """T from a matched initSubsystem<T> row, or None if nothing proves it.

    The string literal at the call site names the *variable*; only the mangled
    instantiation names the *type*, and the two differ often enough to matter --
    TheWritableGlobalData is a GlobalData*, TheAudio an AudioManager*. Deriving
    the class by chopping "The" off the variable would be wrong for both.
    """
    if not row_name:
        return None
    m = _T_RE.match(row_name)
    return m.group(1) if m else None


def _cstring(img, va):
    """The C string at va, or None. Longer limit than Image.cstr: INI paths run
    past the 64 chars that heuristic caps names at."""
    if va is None:
        return None
    raw = bytes(img.read(va, 256))
    if not raw:
        return None
    s = raw.split(b"\x00")[0]
    return s.decode("latin1") if s and all(32 <= c < 127 for c in s) else None


def collect_boot(img, subs):
    """Ordered ('subsystem', name) / ('load', path, loadtype) events in init."""
    o = INIT_RVA - img.tbase
    pushes, seq = [], []
    for ins in S._MD.disasm(img.text[o:o + INIT_SIZE], INIT_RVA):
        if ins.mnemonic == "push":
            # int(x, 0) rather than a 0x prefix test: capstone prints small
            # immediates in decimal, and INI_LOAD_OVERWRITE is `push 1`.
            try:
                pushes.append(int(ins.op_str, 0))
            except ValueError:
                pushes.append(None)          # a register, so not an argument we can read
        elif ins.mnemonic == "call":
            if not ins.op_str.startswith("0x"):
                continue
            target = img.deref_thunk(int(ins.op_str, 16))
            if target in subs and len(pushes) >= 8:
                # (&sysref, name, sys, xfer, a, b, c) pushed right to left, with
                # the by-value AsciiString built in place in a reserved slot.
                name = _cstring(img, pushes[-2])
                if name and name.startswith("The"):
                    seq.append(("subsystem", name, None))
                    pushes = []
            elif target == INI_LOAD_RVA and len(pushes) >= 4:
                _xfer, load_type, _slot, path = pushes[-4:]
                path = _cstring(img, path)
                if path:
                    seq.append(("load", path,
                                INI_LOAD_TYPE.get(load_type, str(load_type))))
                    pushes = []
    return seq


def emit_boot(seq, path):
    loads = sum(1 for k, _, _ in seq if k == "load")
    subs = sum(1 for k, _, _ in seq if k == "subsystem")
    with open(path, "w", encoding="utf-8") as fh:
        fh.write("# BFME 1.03 engine boot order\n\n")
        fh.write(
            "Generated by `tools/dump_subsystems.py --boot`, read straight out of\n"
            "`GameEngine::init` at 0x00079060. This is the order the engine brings\n"
            "its subsystems up in, so it is also the order a mod's overrides take\n"
            "effect in: anything parsed later wins.\n\n"
            "Two things worth knowing before reading it.\n\n"
            "Zero Hour hands each subsystem its INI files through `initSubsystem`'s\n"
            "three trailing `const char *` arguments. BFME passes NULL for all three\n"
            "at all %d sites and calls `INI::load` separately instead, so the loads\n"
            "below are their own statements sitting between the registrations, not\n"
            "properties of the subsystem above them.\n\n"
            "Only %d INI files are loaded here. Every other INI in the game is loaded\n"
            "later, by the subsystem's own `init()` -- `Eva::init` reaches for\n"
            "`Data\\INI\\Eva.ini` itself, for instance. So this is the boot order, not\n"
            "the full INI load order.\n\n"
            % (subs, loads))
        fh.write("| # | step | detail |\n|--:|:--|:--|\n")
        n = 0
        for kind, a, b in seq:
            n += 1
            if kind == "subsystem":
                fh.write(f"| {n} | `initSubsystem` | **{a}** |\n")
            else:
                fh.write(f"| {n} | `INI::load` | `{a}` — {b} |\n")
    print(f"{subs} subsystems, {loads} INI loads -> {path}")


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--csv", action="store_true", help="emit reverse/symbols.csv rows")
    ap.add_argument("--boot", action="store_true",
                    help="write the boot order to docs/boot_order.md")
    args = ap.parse_args()

    img = S.Image()
    owner = S.load_ledger()
    found = collect(img, INIT_RVA, INIT_SIZE)
    if len(found) < MIN_EXPECTED:
        raise SystemExit(
            f"dump_subsystems: recovered only {len(found)} name/global pairs from "
            f"GameEngine::init, expected >= {MIN_EXPECTED}. The call shape has "
            "changed -- fix this before trusting any output."
        )

    if args.boot:
        seq = collect_boot(img, {t for _, _, t in found})
        loads = sum(1 for k, _, _ in seq if k == "load")
        if loads < MIN_EXPECTED_LOADS:
            raise SystemExit(
                f"dump_subsystems: found only {loads} INI::load calls in "
                f"GameEngine::init, expected >= {MIN_EXPECTED_LOADS}. Either "
                f"INI_LOAD_RVA (0x{INI_LOAD_RVA:08X}) is no longer INI::load or "
                "the call shape changed -- fix this before trusting the output.")
        emit_boot(seq, S.B.ROOT / "docs/boot_order.md")
        return

    rows = [(n, g, t, type_of(owner(t) if t else None)) for n, g, t in found]

    if args.csv:
        for name, g, _, cls in rows:
            if not cls:
                continue          # no ledger row proves T; guessing it is how
                                  # a wrong name gets into the ledger unnoticed
            print(f"?{name}@@3PAV{cls}@@A,0x{g:08X},"
                  f"initSubsystem<{cls}> site in GameEngine::init names it")
        return

    print(f"{len(found)} subsystems initialised by GameEngine::init\n")
    print(f"  {'global':<12} {'instantiation':<13} {'T':<28} name")
    for name, g, target, cls in rows:
        print(f"  0x{g:08X}   0x{target:08X}    {cls or '?':<28} {name}")
    known = sum(1 for r in rows if r[3])
    print(f"\n{known}/{len(found)} have T proven by a matched initSubsystem row")


if __name__ == "__main__":
    main()
