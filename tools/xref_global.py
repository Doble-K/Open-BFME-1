#!/usr/bin/env python3
"""Name a global by finding which already-matched functions reference it.

build.py fills DIR32 slots from the target, so a one-line INI block parser like

    mov  eax, [0x12f4b70]        ; <- which global?
    push 0x110b984               ; <- which field table?
    call INI::initFromINI

byte-verifies no matter what our source calls those two addresses. Every
one-liner of that shape is interchangeable with every other, and the bytes will
never object. The name has to come from somewhere else.

This is that somewhere else, for globals: scan the image for absolute
references to an address and report which ledger rows own the referencing
instructions. A global read by ScienceStore::friend_parseScienceDefinition and
by nothing else is TheScienceStore -- that is how ?TheControlBar@@'s bad claim
in reverse/dir32_consistency_whitelist.txt was caught, by hand, before this
existed.

Naming strength, best first:
  * the address is already in reverse/symbols.csv -- reported and done;
  * several matched rows from one class touch it and nothing else does;
  * one matched row touches it -- a lead, not a name, since a function reads
    plenty of globals that are not its own store.

Usage:
  python3 tools/xref_global.py 0x012F4B70 [0x...]     # who references it
  python3 tools/xref_global.py --data 0x012F4B70      # also scan .data/.rdata
"""
import argparse
import bisect
import csv
import struct
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import build as B

IMAGE_BASE = 0x00400000


def load_ledger():
    """(sorted starts, rows) for containing-row lookup by rva."""
    rows = []
    with open(B.ROOT / "reverse/functions.csv", newline="", encoding="utf-8") as fh:
        for r in csv.DictReader(fh):
            try:
                rva = int(r["target_rva"], 16)
                size = int(r["target_size"])
            except (ValueError, KeyError):
                continue
            rows.append((rva, size, r["name"], r.get("source", "")))
    rows.sort()
    return [r[0] for r in rows], rows


def owner_of(starts, rows, rva):
    i = bisect.bisect_right(starts, rva) - 1
    if i < 0:
        return None
    start, size, name, source = rows[i]
    return (name, source) if start <= rva < start + size else None


def known_symbol(va):
    path = B.ROOT / "reverse/symbols.csv"
    if not path.exists():
        return None
    with open(path, newline="", encoding="utf-8") as fh:
        for r in csv.DictReader(fh):
            try:
                if int(r["address"], 16) == va:
                    return r["name"]
            except (ValueError, KeyError):
                continue
    return None


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("addrs", nargs="+", help="global virtual addresses, hex (0x...)")
    ap.add_argument("--data", action="store_true",
                    help="also scan non-executable sections (vtables, field tables)")
    args = ap.parse_args()

    data = open(B.EXE, "rb").read()
    secs = B.pe_sections(data)
    starts, rows = load_ledger()

    scan = []
    for s in secs:
        # .text is the only section with code; the rest only matter with --data.
        is_text = s["name"].startswith(".text")
        if is_text or args.data:
            body = data[s["raw_pointer"]:s["raw_pointer"] + s["size"]]
            scan.append((s["name"], s["rva"], body, is_text))

    for spec in args.addrs:
        va = int(spec, 16)
        print(f"0x{va:08X}")
        sym = known_symbol(va)
        if sym:
            print(f"  reverse/symbols.csv: {sym}")

        needle = struct.pack("<I", va)
        hits, unowned, data_hits = {}, 0, 0
        for name, rva0, body, is_text in scan:
            i = body.find(needle)
            while i != -1:
                if is_text:
                    hit = owner_of(starts, rows, rva0 + i)
                    if hit:
                        hits.setdefault(hit, 0)
                        hits[hit] += 1
                    else:
                        unowned += 1
                else:
                    data_hits += 1
                i = body.find(needle, i + 1)

        if not hits:
            print(f"  no matched row references it ({unowned} unclaimed-code refs)")
        for (name, source), n in sorted(hits.items(), key=lambda kv: -kv[1]):
            print(f"  {n:3d}x  {name}")
            if source:
                print(f"        {source}")
        if unowned:
            print(f"  ...and {unowned} references from code no ledger row covers")
        if data_hits:
            print(f"  ...and {data_hits} references from data sections")
        print()


if __name__ == "__main__":
    main()
