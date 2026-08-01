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

Usage:
  python3 tools/dump_subsystems.py                    # table of name -> global
  python3 tools/dump_subsystems.py --csv              # append-ready for symbols.csv
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
INIT_SIZE = 7123
MIN_EXPECTED = 40


def _is_data(img, va):
    """True if va lands in a mapped, non-executable section."""
    return bool(img.read(va, 4)) and not img.in_text(va)


def collect(img, rva, size):
    """(name, global_va, call_rva) for each `push "TheX"` ... `push g` ... `call`."""
    o = rva - img.tbase
    pending_name = None
    pending_global = None
    out = []
    for ins in S._MD.disasm(img.text[o:o + size], rva):
        if ins.mnemonic == "push" and ins.op_str.startswith("0x"):
            imm = int(ins.op_str, 16)
            text = img.cstr(imm)
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


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--csv", action="store_true", help="emit reverse/symbols.csv rows")
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
