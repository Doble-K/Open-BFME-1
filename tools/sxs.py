#!/usr/bin/env python3
"""Side-by-side disassembly of retail vs compiled for one source file.

Byte diffs say *where* two bodies disagree; they do not say what either side is
doing, and for x86 a one-byte change can be a different register or a different
vtable slot -- categorically different problems.  Reading them as instructions
separates the two, which is most of the work in getting a body from
close-to-matching to matching.

    tools/sxs.py Code/.../Foo.cpp             # everything
    tools/sxs.py Code/.../Foo.cpp --diff      # only rows that differ
    tools/sxs.py Code/.../Foo.cpp --at 0x4e   # a window around one offset

Alignment is by offset, not by instruction index: the two sides are decoded
independently and rows are paired where their offsets agree, so an inserted or
deleted instruction shows as an unpaired row rather than shifting everything
after it.
"""

import argparse
import re
import subprocess
import sys
from pathlib import Path

import capstone

ROOT = Path(__file__).resolve().parent.parent


FAIL_BLOCK = re.compile(
    r"^\s*FAIL (\S+).*?\n\s*target:\s*([0-9a-f ]+)\n\s*compiled:\s*([0-9a-f ]+)$",
    re.M,
)


def build(source, symbol=None):
    """Return (symbol, target, compiled) for the one function under test.

    A TU can fail on several symbols at once.  Picking one silently would make
    every measurement taken afterwards a measurement of an unknown function, so
    an ambiguous result is an error and the caller has to say which it means.
    """
    out = subprocess.run(
        [str(ROOT / "build.sh"), source],
        cwd=ROOT, capture_output=True, text=True,
    )
    blob = out.stdout + out.stderr
    found = [
        (name, bytes.fromhex(t.replace(" ", "")), bytes.fromhex(c.replace(" ", "")))
        for name, t, c in FAIL_BLOCK.findall(blob)
    ]
    if symbol:
        found = [f for f in found if symbol in f[0]]
        if not found:
            sys.exit("no failing symbol matches %r" % symbol)
    if not found:
        if "compile failed" in blob or "error" in blob.lower():
            sys.exit(blob.strip()[-3000:])
        sys.exit("all functions in this TU match -- nothing to compare")
    if len(found) > 1:
        sys.exit(
            "%d symbols failed; pass --symbol to choose one:\n  %s"
            % (len(found), "\n  ".join(f[0] for f in found))
        )
    return found[0]


def decode(code):
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    rows = {}
    for i in md.disasm(code, 0):
        text = i.mnemonic + (" " + i.op_str if i.op_str else "")
        rows[i.address] = (text, i.bytes.hex())
    return rows


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("source")
    ap.add_argument("--diff", action="store_true", help="only differing rows")
    ap.add_argument("--at", help="hex offset to window around")
    ap.add_argument("--window", type=int, default=12, help="rows either side of --at")
    ap.add_argument("--symbol", help="substring of the mangled name, when several fail")
    args = ap.parse_args()

    name, target, compiled = build(args.source, args.symbol)
    print("%s\ntarget %d bytes, compiled %d bytes, %d differing\n"
          % (name, len(target), len(compiled),
             sum(a != b for a, b in zip(target, compiled))
             + abs(len(target) - len(compiled))))

    t, c = decode(target), decode(compiled)
    offsets = sorted(set(t) | set(c))

    if args.at is not None:
        want = int(args.at, 0)
        near = min(offsets, key=lambda o: abs(o - want))
        i = offsets.index(near)
        offsets = offsets[max(0, i - args.window):i + args.window + 1]

    blank = ("", "")
    for off in offsets:
        tt, tb = t.get(off, blank)
        ct, cb = c.get(off, blank)
        same = tb == cb
        if args.diff and same:
            continue
        # A row present on one side only is the interesting case, so mark it
        # distinctly from a row that merely decodes differently.
        mark = "  " if same else ("<<" if not ct else (">>" if not tt else "!!"))
        print("%04x %s %-14s %-32s | %-14s %s"
              % (off, mark, tb, tt, cb, ct))


if __name__ == "__main__":
    main()
