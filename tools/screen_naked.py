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
from vtable_gaps import EXE, IMAGE_BASE, load_owners, sections

ROOT = Path(__file__).resolve().parents[1]
SYNTHETIC = re.compile(r"^\?[jb]_[0-9a-f]{6,}@@|^Gen_[0-9a-f]+|^\?\w+@Gen_[0-9a-f]+")


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
        body = data[o:o + size]

        vptrs = 0
        for m in re.finditer(rb"\xc7[\x00-\xbf]", body):
            i = m.start()
            if i + 6 <= len(body):
                imm = struct.unpack_from("<I", body, i + 2)[0]
                if is_vtable(imm):
                    vptrs += 1

        unnamed = named = 0
        for m in re.finditer(rb"\xe8", body):
            i = m.start()
            if i + 5 > len(body):
                break
            t = (rva + i + 5 + struct.unpack_from("<i", body, i + 1)[0]) & 0xFFFFFFFF
            oo = troff + (t - tva)
            if 0 <= oo < len(data) and data[oo] == 0xE9:
                t = (t + 5 + struct.unpack_from("<i", data, oo + 1)[0]) & 0xFFFFFFFF
            nm = owner(t)
            if nm is None or SYNTHETIC.match(nm):
                unnamed += 1
            else:
                named += 1
        if unnamed:
            continue
        if vptrs > 1:
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
