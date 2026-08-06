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
    if any(0xD8 <= c <= 0xDF for c in body):
        found.append("x87?")
    return found


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
