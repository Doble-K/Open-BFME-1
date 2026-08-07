#!/usr/bin/env python3
"""Find unclaimed functions sitting in vtables whose other slots are named.

An unnamed function is hard to identify in isolation. The same function sitting
at slot N of a vtable whose neighbours are named is often identifiable without a
single build: the slot order is the class's virtual declaration order, so a gap
between two known methods is bounded by them, and the reference headers give the
declaration order to compare against.

That is how SimpleSceneClass::Add_Render_Object, Register and Unregister were
identified -- by position and by their twins' behaviour, not by disassembling
them cold. This ranks every vtable in the image by how much of that leverage it
offers: how many named neighbours surround each gap.

A run of four or more consecutive .text pointers in .rdata is treated as a
vtable. That over-collects slightly (a static array of function pointers looks
the same) but never under-collects, and a wrong guess costs only a listing line.

Usage: python tools/vtable_gaps.py [--limit N] [--min-known-frac F]
"""
import argparse
import bisect
import csv
import re
import struct
import sys
from pathlib import Path

from screen_blockers import blockers, rva2off

ROOT = Path(__file__).resolve().parent.parent
EXE = ROOT / "baselines" / "bfme1" / "workshop-vanilla-1.03" / "files" / "lotrbfme.exe"
IMAGE_BASE = 0x00400000


def sections(data):
    lfanew = struct.unpack_from("<I", data, 0x3C)[0]
    coff = lfanew + 4
    nsec = struct.unpack_from("<H", data, coff + 2)[0]
    optsz = struct.unpack_from("<H", data, coff + 16)[0]
    base = coff + 20 + optsz
    out = {}
    for i in range(nsec):
        o = base + i * 40
        name = data[o:o + 8].rstrip(b"\0").decode("latin1") or "sec%d" % i
        vsz, va, rsz, roff = struct.unpack_from("<IIII", data, o + 8)
        out[name] = (va, vsz, roff, rsz)
    return out


def load_owners():
    """rva -> name, plus sorted starts/extents so an address can be attributed."""
    rows = []
    with (ROOT / "reverse" / "functions.csv").open(newline="", encoding="utf-8",
                                                   errors="replace") as fh:
        for r in csv.DictReader(fh):
            if not r["target_rva"] or not r["target_size"]:
                continue
            try:
                rows.append((int(r["target_rva"], 16), int(r["target_size"]), r["name"]))
            except ValueError:
                continue
    rows.sort()
    return rows


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--limit", type=int, default=20)
    ap.add_argument("--min-known-frac", type=float, default=0.5,
                    help="only report vtables at least this fraction named")
    ap.add_argument("--min-slots", type=int, default=4)
    args = ap.parse_args()

    data = EXE.read_bytes()
    secs = sections(data)
    tva, tvsz, _, _ = secs[".text"]
    rva0, _, rroff, rrsz = secs[".rdata"]
    rdata = data[rroff:rroff + rrsz]

    rows = load_owners()
    starts = [r[0] for r in rows]
    exact = {r[0]: r[2] for r in rows}

    def owner(rva):
        """Exact match first: a vtable slot points at a function's entry."""
        if rva in exact:
            return exact[rva]
        k = bisect.bisect_right(starts, rva) - 1
        if k >= 0 and rva < rows[k][0] + rows[k][1]:
            return rows[k][2] + " (interior)"
        return None

    def informative(name):
        """A generated placeholder names nothing, so it is no help as a neighbour.

        Most claimed rows in this image are gen-thunks carrying synthetic names
        like ?j_00035eb8@@YAXXZ. Counting those as "named" makes almost every
        vtable look fully identified and buries the handful of gaps that sit
        between real methods -- which are the only ones this tool is for.
        """
        return bool(name) and not re.match(r"\?[jb]_[0-9a-f]{6,8}@@YAXXZ", name)

    def is_text(off):
        if off < 0 or off + 4 > len(rdata):
            return False
        v = struct.unpack_from("<I", rdata, off)[0] - IMAGE_BASE
        return tva <= v < tva + tvsz

    # collect maximal runs of .text pointers
    tables, i = [], 0
    while i + 4 <= len(rdata):
        if i % 4 or not is_text(i):
            i += 4 if i % 4 == 0 else (4 - i % 4)
            continue
        j = i
        while is_text(j):
            j += 4
        if (j - i) // 4 >= args.min_slots:
            tables.append((i, (j - i) // 4))
        i = j

    def blocked(rva):
        """Reject candidates whose bytes already carry a known blocker.

        An identity found here still has to be written as C++ afterwards, so a
        slot sitting on an SEH prologue is not a lead worth following -- that
        family has no source-level fix. Sixteen bytes is enough: an SEH prologue
        is the first thing in a function, never buried in the middle.
        """
        off = rva2off(data, rva)
        if off is None:
            return ["unmapped"]
        return [b for b in blockers(data[off:off + 16]) if b in ("seh", "ebp-frame")]

    findings = []
    for off, n in tables:
        slots = [struct.unpack_from("<I", rdata, off + k * 4)[0] - IMAGE_BASE
                 for k in range(n)]
        names = [owner(s) for s in slots]
        names = [nm if informative(nm) else None for nm in names]
        known = sum(1 for nm in names if nm)
        if known < n * args.min_known_frac or known == n:
            continue
        for k, (s, nm) in enumerate(zip(slots, names)):
            if nm:
                continue
            before = next((names[p] for p in range(k - 1, -1, -1) if names[p]), None)
            after = next((names[p] for p in range(k + 1, n) if names[p]), None)
            if not before and not after:
                continue
            if blocked(s):
                continue
            findings.append((-(known / n), s, rva0 + off + IMAGE_BASE, k, n,
                             known, before, after))

    # dedupe: the same function can sit in many vtables
    findings.sort()
    seen, out = set(), []
    for f in findings:
        if f[1] in seen:
            continue
        seen.add(f[1])
        out.append(f)

    print("%d vtable-like run(s); %d distinct unclaimed slot(s) with named neighbours\n"
          % (len(tables), len(out)))
    for frac, rva, tbl, k, n, known, before, after in out[:args.limit]:
        print("0x%08X  slot %d/%d of vtable 0x%08X  (%d/%d named)"
              % (rva, k, n, tbl, known, n))
        if before:
            print("     after : " + before[:104])
        if after:
            print("     before: " + after[:104])
    if len(out) > args.limit:
        print("\n... %d more (--limit)" % (len(out) - args.limit))


if __name__ == "__main__":
    sys.exit(main())
