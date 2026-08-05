#!/usr/bin/env python3
"""Matched rows whose claimed range contains int3 padding strictly inside it.

MSVC pads *between* functions with 0xCC and never inside one, so a long run of
0xCC in the middle of a claimed range means the claim spans a function
boundary. That makes this the cheapest decisive test in the toolbox: it needs
no disassembler, no Ghidra inventory and no second opinion -- the retail bytes
say it outright.

It matters because the rows it finds are exactly the ones the byte gate can
never object to. A MASM dump is the retail bytes and matches at whatever length
it is given; a `__declspec(naked)` body transcribed from those bytes is the
same thing spelled in inline asm. Both verify forever while covering two, three
or more real functions -- and every function inside the overhang becomes
unclaimable, because its address already belongs to somebody else's row.

Trailing padding is ignored on purpose: a row that merely runs into the pad
after its own body is over-long but is not standing on anything.

What the tool does NOT tell you is where the claim should have started. Check
that separately -- a real function start is 16-byte aligned or sits directly
after a padding run. `??0AIAttackMoveStateMachine@@` was wrong on both counts:
it began 129 bytes inside the function at 0x002C0FE0 and ran 340 past its end.

Usage:
  python3 tools/audit_internal_padding.py            # runs >= 8 int3
  python3 tools/audit_internal_padding.py --min-run 16
"""
import argparse
import csv
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import build

PADDING = 0xCC


def main():
    parser = argparse.ArgumentParser(description=__doc__,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--min-run", type=int, default=8,
                        help="shortest run of 0xCC treated as padding")
    args = parser.parse_args()

    data = build.EXE.read_bytes()
    hits = []
    for row in build.load_all_function_rows():
        if row["status"] != "matched":
            continue
        try:
            rva = int(row["target_rva"], 16)
            size = int(row["target_size"])
        except (ValueError, TypeError):
            continue
        if size < args.min_run + 2:
            continue
        core = data[rva:rva + size].rstrip(bytes([PADDING]))
        if len(core) < args.min_run:
            continue

        run = longest = 0
        offset = -1
        for i, byte in enumerate(core):
            if byte == PADDING:
                run += 1
                if run > longest:
                    longest, offset = run, i - run + 1
            else:
                run = 0
        if longest >= args.min_run:
            hits.append((longest, rva, size, offset, row["name"], row["source"]))

    hits.sort(reverse=True)
    if not hits:
        print("audit_internal_padding: OK (no claimed range contains interior padding)")
        return 0

    print("matched rows with a run of >=%d int3 inside the body: %d\n" % (args.min_run, len(hits)))
    for longest, rva, size, offset, name, source in hits:
        print("  0x%06X %6dB  body really ends at +0x%X, then %d int3  %s"
              % (rva, size, offset, longest, name[:58]))
        print("        %s" % source)
    return 1


if __name__ == "__main__":
    raise SystemExit(main())
