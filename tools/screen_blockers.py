#!/usr/bin/env python3
"""Rank naked-asm rows by whether their bytes show a known conversion blocker.

Every failed conversion this project has logged fell into a small number of
families, and each family has a byte signature that is visible before any build
time is spent. This reads each naked body, rejects the ones carrying a signature,
and ranks what is left so a tick can start from the cheapest candidate rather
than discovering the blocker after two or three builds.

The families, all recorded in docs/lessons.md and reverse/re_attempts.log:

  seh        __except/__finally prologue. The unwind funclets are separate
             symbols keyed by compiler-generated labels; nothing in the source
             steers them. 625 of ~972 naked rows, by far the largest group
  ebp-frame  a real frame pointer. Not fatal on its own, but frame layout has
             to be reproduced exactly and that is a whole extra axis
  esp-stash  `mov [esp+N],esp` -- a class stashed by value. No /EH setting
             reproduces it
  static-fn  a function-local static: byte guard load then `test al,cl`. The
             static's address is a compile-time constant, so MSVC folds it into
             every store where retail keeps it in a register. That one decision
             also suppresses the dead-store elimination retail performs, so the
             body diverges in two places at once
  x87        floating point. Constant materialisation direction differs per
             function and is not steerable from the source

Unpinned call targets are counted rather than treated as a blocker: a REL32 call
needs a name,address pin to resolve, so each unpinned target is one naming
problem standing between the row and a build.

Usage: python tools/screen_blockers.py [--limit N] [--max-bytes N]
"""
import argparse
import csv
import re
import struct
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
EXE = ROOT / "baselines" / "bfme1" / "workshop-vanilla-1.03" / "files" / "lotrbfme.exe"

# A row whose body contradicts its own decorated name is not a conversion
# candidate at all -- writing C++ for a name the bytes do not belong to cannot
# succeed. screen_identity.py already finds those, and this screener used to
# report them as clear, which is how ?Unregister@SimpleSceneClass@@ -- a row that
# pops 4 bytes under a name whose arguments size to 8 -- was picked as a
# candidate and read in full before the mismatch surfaced.
try:
    from screen_identity import arg_bytes, body_facts, split_name
except ImportError:                      # keep working if that tool is absent
    split_name = None


def rva2off(data, rva):
    lfanew = struct.unpack_from("<I", data, 0x3C)[0]
    coff = lfanew + 4
    nsec = struct.unpack_from("<H", data, coff + 2)[0]
    optsz = struct.unpack_from("<H", data, coff + 16)[0]
    base = coff + 20 + optsz
    for i in range(nsec):
        o = base + i * 40
        vsz, va, rsz, roff = struct.unpack_from("<IIII", data, o + 8)
        if va <= rva < va + max(vsz, rsz):
            return roff + (rva - va)
    return None


def _decoded_x87(body):
    """True only if an x87 escape opcode D8..DF starts an instruction.

    The loose byte test this replaces flagged 753 of the naked thunks where only
    150 really use x87 -- it was matching the opcode inside call displacements
    and immediates. Ranking on that buried hundreds of convertible functions
    under a blocker they did not have.
    """
    try:
        import capstone
    except ImportError:
        return any(0xD8 <= c <= 0xDF for c in body)
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    return any(0xD8 <= ins.bytes[0] <= 0xDF for ins in md.disasm(body, 0))


def blockers(body):
    """Byte signatures of the known families. Order is not significant."""
    found = []
    # SEH: `mov eax, fs:[0]` / `mov fs:[0], esp` appear in every MSVC 7.1
    # __except and __finally prologue and essentially nowhere else.
    if b"\x64\xa1\x00\x00\x00\x00" in body or b"\x64\x89\x25\x00\x00\x00\x00" in body:
        found.append("seh")
    if body.startswith(b"\x55\x8b\xec"):
        found.append("ebp-frame")
    # `mov [esp+disp8],esp` and `mov [esp],esp`
    if b"\x89\x64\x24" in body or b"\x89\x24\x24" in body:
        found.append("esp-stash")
    # Function-local static guard: load the guard byte, then test it. MSVC puts
    # the mask in a register in between (`mov eax,1`), so the test does not
    # follow the load directly -- matching them adjacently silently passes the
    # whole family through as clear, which is how this was first written.
    if re.search(rb"\x8a\x0d....[\s\S]{0,10}\x84[\xc0-\xff]", body, re.S):
        found.append("static-fn")
    # x87: the escape opcodes D8..DF. Checking the first byte of each
    # instruction properly needs a decoder, so this is deliberately loose and
    # only used to rank, never to reject outright.
    if _decoded_x87(body):
        found.append("x87")
    if _writes_an_offset_twice(body):
        found.append("vptr-sink")
    return found


def _writes_an_offset_twice(body):
    """True if some destination takes two different `mov [reg+disp],imm32`.

    That is the inline-base signature: a base constructed in place writes its own
    vtable and the derived class overwrites it at the same offset. Wherever it
    appears, the derived vtable stores have to sit between the base constructors
    and the member initialisation -- and MSVC sinks them past the members
    instead, which no source spelling or available flag corrects. Rows carrying
    it are blocked before any build, so they are worth rejecting up front.
    """
    seen = {}
    i = 0
    while i < len(body) - 1:
        if body[i] != 0xC7:
            i += 1
            continue
        modrm = body[i + 1]
        if (modrm >> 3) & 7:            # /0 only: this is MOV r/m32, imm32
            i += 1
            continue
        mod, rm = modrm >> 6, modrm & 7
        if mod == 3:                    # register destination, not a store
            i += 1
            continue
        if rm == 4:                     # SIB byte; skip rather than mis-decode
            i += 1
            continue
        if mod == 0:
            disp_len = 4 if rm == 5 else 0
        elif mod == 1:
            disp_len = 1
        else:
            disp_len = 4
        start = i + 2 + disp_len
        if start + 4 > len(body):
            break
        key = body[i + 1:start]
        imm = body[start:start + 4]
        if key in seen and seen[key] != imm:
            return True
        seen[key] = imm
        i = start + 4
    return False


def _name_contradicts_body(name, body, rva):
    """True when the bytes pop a different amount than the name's arguments need.

    Only the stack-cleanup check is reused here, because it is the one that never
    fires on a merely-unusual function: a callee-cleaned function pops exactly
    its argument list, so a disagreement means the name is on the wrong bytes.
    arg_bytes returns None whenever the list cannot be sized from the name alone,
    and None must stay "no opinion" rather than becoming a finding.
    """
    if split_name is None:
        return False
    parts = split_name(name)
    if not parts:
        return False
    access, ret, argstr = parts
    if argstr.startswith("Z") or access[2] == "A":       # varargs: caller cleans
        return False
    if access[2] not in "EIM":                            # not callee-cleaned
        return False
    want = arg_bytes(argstr)
    if want is None:
        return False
    facts = body_facts(body, rva)
    if not facts or not facts["ret_pops"]:
        return False
    if ret in ("?AV", "V"):                               # hidden return pointer
        want += 4
    return want not in facts["ret_pops"]


def call_targets(body, rva):
    """REL32 call destinations. e8 is the only direct-call encoding used here."""
    out = []
    i = 0
    while True:
        i = body.find(b"\xe8", i)
        if i == -1 or i + 5 > len(body):
            break
        disp = struct.unpack_from("<i", body, i + 1)[0]
        out.append((rva + i + 5 + disp) & 0xFFFFFFFF)
        i += 1
    return out


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--limit", type=int, default=25)
    ap.add_argument("--max-bytes", type=int, default=200)
    ap.add_argument("--show-blocked", action="store_true",
                    help="also print rows that carry a blocker signature")
    args = ap.parse_args()

    data = EXE.read_bytes()

    naked = {}
    for path in (ROOT / "Code").rglob("*.cpp"):
        try:
            text = path.read_text(encoding="utf-8", errors="replace")
        except OSError:
            continue
        if "__declspec(naked)" not in text:
            continue
        for m in re.finditer(r"//\s*(\?[^\s]+)\s*\n__declspec\(naked\)", text):
            naked[m.group(1)] = path

    pinned = set()
    with (ROOT / "reverse" / "symbols.csv").open(newline="", encoding="utf-8",
                                                 errors="replace") as fh:
        for row in fh:
            parts = row.split(",")
            if len(parts) >= 2 and parts[1].strip().startswith("0x"):
                try:
                    pinned.add(int(parts[1], 16))
                except ValueError:
                    pass

    rows = []
    with (ROOT / "reverse" / "functions.csv").open(newline="", encoding="utf-8",
                                                   errors="replace") as fh:
        for row in csv.DictReader(fh):
            name = row["name"]
            if name not in naked or not row["target_rva"]:
                continue
            size = int(row["target_size"] or 0)
            if not 6 <= size <= args.max_bytes:
                continue
            rva = int(row["target_rva"], 16)
            off = rva2off(data, rva)
            if off is None:
                continue
            body = data[off:off + size]
            found = blockers(body)
            if _name_contradicts_body(name, body, rva):
                found.append("identity")
            if found and not args.show_blocked:
                continue
            calls = call_targets(body, rva)
            unpinned = [c for c in calls if c not in pinned]
            pinned.add(rva)
            # cheapest first: unresolved names dominate, then size
            score = len(unpinned) * 1000 + size
            rows.append((score, name, rva, size, len(calls), len(unpinned),
                         found, naked[name]))

    rows.sort()
    clean = [r for r in rows if not r[6]]
    print("%d naked row(s) in range; %d with no blocker signature\n"
          % (len(rows), len(clean)))
    for score, name, rva, size, ncalls, nunp, found, path in rows[:args.limit]:
        tag = ("BLOCKED[" + ",".join(found) + "]") if found else "clear"
        print("0x%08X %4dB  %d call(s) %d unpinned  %s" % (rva, size, ncalls, nunp, tag))
        print("     " + name[:110])
        print("     " + path.relative_to(ROOT).as_posix())
    if len(rows) > args.limit:
        print("\n... %d more not shown (--limit)" % (len(rows) - args.limit))


if __name__ == "__main__":
    sys.exit(main())
