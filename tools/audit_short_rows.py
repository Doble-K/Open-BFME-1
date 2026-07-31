#!/usr/bin/env python3
"""Find ledger rows whose target_size is SHORTER than the function it claims.

A short row still passes ./build.sh, because the gate only compares the bytes a
row claims -- so a truncated claim hides the tail of a function (and, for a MASM
dump, means the dump does not reproduce the whole body). INI::parseBitString32
was recorded as 297B against a 472-byte body this way.

The test is a conditional branch (jcc) whose target lands past the row's end.
An unconditional jmp can legitimately leave a function (tail call), but a jcc
cannot: both of its successors belong to the same function. Targets that are the
start of another claimed row are ignored, since those are real tail positions.

Branch targets that land inside ANY claimed row are ignored, not just row
starts: those are a neighbour's code, since retail packs functions back to back
with no padding in places.

Candidates, not verdicts: capstone can desync on embedded data or jump tables
and invent a branch. Confirm by hand -- disassemble from target_rva and check
whether the byte at target_rva+size is int3 padding or the start of the next
claimed function.

Usage:
  python3 tools/audit_short_rows.py [--masm-only] [--min-gap N] [--limit N]
"""
import argparse
import csv
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import build as B
import capstone

JCC = {
    "je", "jne", "jg", "jge", "jl", "jle", "ja", "jae", "jb", "jbe",
    "js", "jns", "jo", "jno", "jp", "jnp", "jecxz",
}


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--masm-only", action="store_true", help="only rows backed by a MASM dump")
    ap.add_argument("--min-gap", type=int, default=1, help="ignore branches this close past the end")
    ap.add_argument("--limit", type=int, default=40)
    args = ap.parse_args()

    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    data = open(B.EXE, "rb").read()
    sec = next(s for s in B.pe_sections(data) if s["name"] == ".text")
    blob = data[sec["raw_pointer"]:sec["raw_pointer"] + sec["size"]]
    base = sec["rva"]

    rows = []
    with open(B.ROOT / "reverse/functions.csv", newline="", encoding="utf-8") as fh:
        for r in csv.DictReader(fh):
            try:
                rows.append((int(r["target_rva"], 16), int(r["target_size"]), r["name"], r["source"]))
            except ValueError:
                pass
    starts = {a for a, _, _, _ in rows}
    # every byte any row already claims -- a branch landing in one of those is a
    # neighbour's code (or a desync), not evidence that this row is short
    claimed = set()
    for a, n, _, _ in rows:
        claimed.update(range(a, a + n))

    hits = []
    for addr, size, name, source in rows:
        if size <= 8 or size > 8192:
            continue
        if args.masm_only and not source.endswith(".asm"):
            continue
        off = addr - base
        if off < 0 or off + size > len(blob):
            continue
        for ins in md.disasm(bytes(blob[off:off + size]), addr):
            if ins.mnemonic not in JCC or not ins.op_str.startswith("0x"):
                continue
            target = int(ins.op_str, 16)
            gap = target - (addr + size)
            if args.min_gap <= gap < 4096 and target not in starts and target not in claimed:
                hits.append((gap, addr, size, name, source))
                break

    hits.sort(reverse=True)
    print(f"{len(hits)} row(s) with a conditional branch past their claimed end")
    for gap, addr, size, name, source in hits[:args.limit]:
        kind = "MASM" if source.endswith(".asm") else "C++ "
        print(f"  {kind} 0x{addr:08X} claim={size:6d}  jcc +{gap:5d} past end  {name[:56]}")


if __name__ == "__main__":
    main()
