#!/usr/bin/env python3
"""Predict whether a naked constructor's vptr store will land where retail has it.

MSVC sinks a constructor's vptr store to the end of the leading run of member
stores that share a value, and no further -- but only when that run is at least
two stores long; a single store is not enough to move it. Retail's placement
follows no rule recoverable from the bytes: sometimes ahead of every member
store, sometimes past all of them including differing values.

A constructor is convertible when the two coincide, and no arrangement of the
source can make them coincide when they do not, because C++ cannot say where the
vptr store goes. So this is a screen, not a diagnosis: it separates the ones
worth writing from the ones to leave alone.

Calibrated against every case measured so far -- AIMoveToState and
AIGuardRetaliateState (single member, both agree at 0), AIAttackSquadState and
DozerPrimaryIdleState and AIMoveAndTightenState and AIAttackAimAtTargetState (run
reaches retail's index, all matched), AIWanderState and AIIdleState and
AIMoveAndEvacuateState (disagree, all parked).

Known limitation, measured rather than assumed. The prediction reads retail's
register allocation, and MSVC does not always reproduce it. In
GarrisonContainModuleData retail holds 1.0f in ecx while the zero run is in eax,
so retail's run ends at eleven; the compile put both constants in eax, making
the run thirteen and carrying the vptr past two more stores. The screen called
it convertible and it was not.

So a 'convertible' verdict is a candidate, not a promise -- it means nothing in
retail's own bytes rules the function out. A 'parked' verdict is the stronger
one: those genuinely cannot agree whatever the allocator does, because retail
puts the store somewhere the compiler will never place it.

Usage: python tools/screen_vptr.py [--limit N] [--all]
"""
import argparse
import csv
import io
import pathlib
import re
import struct
import sys

sys.path.insert(0, str(pathlib.Path(__file__).resolve().parent))
import capstone

from vtable_gaps import EXE, IMAGE_BASE, sections

ROOT = pathlib.Path(__file__).resolve().parents[1]
NAKED = re.compile(r"__declspec\s*\(\s*naked\s*\)")
MD = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
MD.detail = True

# al/ax/eax all carry the same value for this purpose, so key on the register's
# root rather than its width -- retail zeroes a dword and a byte from one xor.
ROOT_REG = {}
for wide, parts in (("eax", "ax al ah"), ("ebx", "bx bl bh"),
                    ("ecx", "cx cl ch"), ("edx", "dx dl dh"),
                    ("esi", "si"), ("edi", "di")):
    ROOT_REG[wide] = wide
    for p in parts.split():
        ROOT_REG[p] = wide


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--limit", type=int, default=25)
    ap.add_argument("--all", action="store_true", help="also list the parked ones")
    args = ap.parse_args()

    data = EXE.read_bytes()
    secs = sections(data)
    tva, tvsz, troff, trsz = secs[".text"]
    rva0, rvsz, rroff, rrsz = secs[".rdata"]

    def is_vtable(va):
        a = va - IMAGE_BASE
        if not (rva0 <= a < rva0 + rvsz) or a - rva0 + 4 > rrsz:
            return False
        v = struct.unpack_from("<I", data, rroff + (a - rva0))[0] - IMAGE_BASE
        return tva <= v < tva + tvsz

    cache = {}

    def naked(src):
        if src not in cache:
            p = ROOT / src
            cache[src] = (p.suffix == ".cpp" and p.exists()
                          and bool(NAKED.search(p.read_text(encoding="utf-8", errors="replace"))))
        return cache[src]

    good, parked = [], []
    with (ROOT / "reverse" / "functions.csv").open(newline="", encoding="utf-8",
                                                   errors="replace") as fh:
        for r in csv.DictReader(fh):
            if r["status"] != "matched" or not r["target_rva"] or not r["source"]:
                continue
            if not r["name"].startswith("??0"):
                continue
            src = r["source"].replace("\\", "/")
            a, n = int(r["target_rva"], 16), int(r["target_size"])
            if n < 20 or n > 400:
                continue
            o = troff + (a - tva)
            if o < 1 or o + n > len(data) or data[o - 1] != 0xCC:
                continue
            if not naked(src):
                continue

            # Everything after the final call is the member-initialisation tail.
            ins = list(MD.disasm(data[o:o + n], a))
            last_call = max((i for i, x in enumerate(ins) if x.mnemonic == "call"),
                            default=-1)
            seq, vptr_idx, vptrs = [], None, 0
            for x in ins[last_call + 1:]:
                if x.mnemonic != "mov" or len(x.operands) != 2:
                    continue
                dst, srcop = x.operands
                if dst.type != capstone.x86.X86_OP_MEM:
                    continue
                if srcop.type == capstone.x86.X86_OP_IMM:
                    v = srcop.imm & 0xFFFFFFFF
                    if is_vtable(v):
                        vptrs += 1
                        if vptr_idx is None:
                            vptr_idx = len(seq)
                        continue
                    seq.append(("imm", v))
                elif srcop.type == capstone.x86.X86_OP_REG:
                    seq.append(("reg", ROOT_REG.get(x.reg_name(srcop.reg), "?")))
            if vptrs != 1 or vptr_idx is None:
                continue

            run = 0
            if seq:
                first = seq[0]
                while run < len(seq) and seq[run] == first:
                    run += 1
            predicted = run if run >= 2 else 0
            row = (n, a, r["name"], src, vptr_idx, predicted, len(seq))
            (good if predicted == vptr_idx else parked).append(row)

    good.sort()
    parked.sort()
    print("%d convertible (vptr agrees), %d parked (vptr disagrees)\n"
          % (len(good), len(parked)))
    for n, a, nm, src, vi, pr, ns in good[:args.limit]:
        print("0x%08X %4dB  vptr@%d of %d stores  %s" % (a, n, vi, ns, nm[:60]))
        print("            %s" % src.split("/")[-1])
    if args.all:
        print("\n-- parked --")
        for n, a, nm, src, vi, pr, ns in parked[:args.limit]:
            print("0x%08X %4dB  retail@%d predicted@%d of %d  %s"
                  % (a, n, vi, pr, ns, nm[:52]))


if __name__ == "__main__":
    sys.exit(main())
