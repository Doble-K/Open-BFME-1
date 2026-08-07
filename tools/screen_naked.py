#!/usr/bin/env python3
"""Rank naked-asm candidates by what actually decides whether they convert.

Three ticks of picking uniformly at random hit three different walls, and every
one of them was visible in the bytes before any C++ was written:

  * QueueProductionExitUpdate stored six vptrs -- multiple inheritance with six
    vtables, which the established idioms do not model.
  * SupplyTruckAIUpdateModuleData called a constructor whose only name is the
    synthetic ?b_000b2cc0, so landing it would have meant inventing a signature
    to pin.
  * ConcreteModuleClass::getInstance lives in a bulk file that verifies 560 rows
    on every build, which makes a three-build experiment cost three long builds.

So screen on those three properties up front. The ranking is deliberately
conservative: it prefers bodies that store at most one vtable, call only
functions that already have real names, and sit in a source file whose build is
cheap.

Usage: python tools/screen_naked.py [--limit N] [--max-rows N]
"""
import argparse
import bisect
import csv
import io
import re
import struct
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import capstone

from vtable_gaps import EXE, IMAGE_BASE, load_owners, sections

MD = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
MD.detail = True

ROOT = Path(__file__).resolve().parents[1]
SYNTHETIC = re.compile(
    r"^\?[jb]_[0-9a-f]{6,}@@|^Gen_[0-9a-f]+|^\?\w+@Gen_[0-9a-f]+|^tg_[0-9a-f]+")


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--limit", type=int, default=20)
    ap.add_argument("--max-rows", type=int, default=120,
                    help="skip sources carrying more matched rows than this")
    args = ap.parse_args()

    data = EXE.read_bytes()
    secs = sections(data)
    tva, tvsz, troff, trsz = secs[".text"]
    rva0, rvsz, rroff, rrsz = secs[".rdata"]

    rows = load_owners()
    starts = [r[0] for r in rows]

    def owner(a):
        k = bisect.bisect_right(starts, a) - 1
        if k >= 0 and a < rows[k][0] + rows[k][1]:
            return rows[k][2]
        return None

    # Every matched row, plus how many rows each source carries -- that count is
    # the build cost, because the gate verifies the whole file on every attempt.
    per_source = {}
    entries = []
    with (ROOT / "reverse" / "functions.csv").open(newline="", encoding="utf-8",
                                                   errors="replace") as fh:
        for r in csv.DictReader(fh):
            if r["status"] != "matched" or not r["source"]:
                continue
            src = r["source"].replace("\\", "/")
            per_source[src] = per_source.get(src, 0) + 1
            entries.append((r["name"], int(r["target_rva"], 16),
                            int(r["target_size"]), src))

    naked = set()
    for src in set(per_source):
        p = ROOT / src
        if p.suffix != ".cpp" or not p.exists():
            continue
        try:
            text = p.read_text(encoding="utf-8", errors="replace")
        except OSError:
            continue
        if "__declspec(naked)" not in text:
            continue
        for m in re.finditer(r"//\s*(\?\S+)", text):
            naked.add((src, m.group(1)))

    def is_vtable(va):
        a = va - IMAGE_BASE
        if not (rva0 <= a < rva0 + rvsz) or a - rva0 + 4 > rrsz:
            return False
        v = struct.unpack_from("<I", data, rroff + (a - rva0))[0] - IMAGE_BASE
        return tva <= v < tva + tvsz

    out = []
    for name, rva, size, src in entries:
        if (src, name) not in naked:
            continue
        cost = per_source[src]
        if cost > args.max_rows:
            continue
        o = troff + (rva - tva)
        if o < 0 or o + size > len(data):
            continue
        # Every real entry in this image is preceded by int3 padding. A row
        # anchored anywhere else is not at a function start, and no amount of
        # C++ will match it -- ?xfer@GarrisonContain is claimed at a byte
        # preceded by 00, and its body returns this with a bare ret, so it is a
        # constructor rather than the xfer the name promises.
        if o == 0 or data[o - 1] != 0xCC:
            continue
        body = data[o:o + size]

        # Decode. The first version of this counted vtable stores by matching
        # c7 and reading the immediate at a fixed offset, which ignores the
        # ModRM displacement -- `mov [esi+0x38], imm32` encodes as c7 46 38
        # and the immediate starts a byte later. DeflectSpecialPower stores six
        # vtables and the regex reported one, which is the same mistake the x87
        # screen made before it was changed to decode.
        vptrs = indirect = unnamed = named = 0
        unoptimised = False
        for ins in MD.disasm(body, rva):
            if ins.mnemonic == "mov" and len(ins.operands) == 2:
                dst_op, src_op = ins.operands
                if (dst_op.type == capstone.x86.X86_OP_MEM
                        and src_op.type == capstone.x86.X86_OP_IMM
                        and is_vtable(src_op.imm & 0xFFFFFFFF)):
                    vptrs += 1
            elif ins.mnemonic == "call":
                op = ins.operands[0]
                if op.type != capstone.x86.X86_OP_IMM:
                    indirect += 1
                    continue
                t = op.imm & 0xFFFFFFFF
                oo = troff + (t - tva)
                if 0 <= oo < len(data) and data[oo] == 0xE9:
                    t = (t + 5 + struct.unpack_from("<i", data, oo + 1)[0]) & 0xFFFFFFFF
                nm = owner(t)
                if nm is None or SYNTHETIC.match(nm):
                    unnamed += 1
                else:
                    named += 1
        # A frame pointer and a stack frame in a body this small means the
        # translation unit was not built with the project's -O2, so matching it
        # is a different job from the rest of the queue.
        if body[:3] == bytes((0x55, 0x8B, 0xEC)) and bytes((0x83, 0xEC)) in body[:8]:
            unoptimised = True
        if unnamed or indirect or unoptimised or vptrs > 1:
            continue
        out.append((cost, size, vptrs, named, rva, name, src))

    out.sort()
    print("%d candidate(s) with <=1 vtable, no unnamed callee, source <=%d rows\n"
          % (len(out), args.max_rows))
    for cost, size, vptrs, named, rva, name, src in out[:args.limit]:
        print("0x%08X %4dB  vptr=%d calls=%d  file-rows=%d" % (rva, size, vptrs, named, cost))
        print("   %s" % name)
        print("   %s" % src)


if __name__ == "__main__":
    sys.exit(main())
