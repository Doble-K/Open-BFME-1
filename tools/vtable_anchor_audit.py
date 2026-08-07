#!/usr/bin/env python3
"""Find virtual-method rows anchored to a copy no vtable dispatches to.

MSVC emits a class's inline virtuals into every translation unit that needs
them, and the linker keeps more than one copy when it cannot fold them all away.
Only one copy ends up in the vtable; the others are dead weight that nothing ever
calls. Both are genuinely that function's code, so claiming either verifies
byte-exactly and the gate cannot tell them apart.

That matters because the dead copy is the wrong anchor. Its address carries no
dispatch evidence, so nothing later can confirm or refute the attribution from
the vtable it should have been in -- and the live copy stays unclaimed, looking
like an unexplored gap when it is really the same function claimed elsewhere.

This reports rows whose name is a virtual (U.E in the decorated name) whose
address appears in no vtable, while a byte-identical body elsewhere does appear
in one. It reports; it does not repoint. Deciding between two real copies of the
same function is a judgement about which the ledger should record, not something
to automate.

Usage: python tools/vtable_anchor_audit.py [--limit N]
"""
import argparse
import csv
import re
import struct
import sys
from collections import defaultdict
from pathlib import Path

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


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--limit", type=int, default=25)
    ap.add_argument("--min-bytes", type=int, default=16,
                    help="ignore bodies too short to be distinctive; at 3 bytes
                          this reports 209 rows and means nothing, at 16 it reports 5")
    ap.add_argument("--max-bytes", type=int, default=64,
                    help="only compare bodies this small; large ones rarely duplicate")
    args = ap.parse_args()

    data = EXE.read_bytes()
    secs = sections(data)
    tva, tvsz, troff, trsz = secs[".text"]
    rva0, _, rroff, rrsz = secs[".rdata"]
    rdata = data[rroff:rroff + rrsz]

    def off_of(rva):
        if tva <= rva < tva + trsz:
            return troff + (rva - tva)
        return None

    # every address any vtable-looking slot points at
    dispatched = set()
    for i in range(0, len(rdata) - 4, 4):
        v = struct.unpack_from("<I", rdata, i)[0] - IMAGE_BASE
        if tva <= v < tva + tvsz:
            dispatched.add(v)

    rows = []
    with (ROOT / "reverse" / "functions.csv").open(newline="", encoding="utf-8",
                                                   errors="replace") as fh:
        for r in csv.DictReader(fh):
            if not r["target_rva"] or not r["target_size"]:
                continue
            try:
                rva, size = int(r["target_rva"], 16), int(r["target_size"])
            except ValueError:
                continue
            if not args.min_bytes <= size <= args.max_bytes:
                continue
            rows.append((rva, size, r["name"], r["source"]))

    # index small bodies by their exact bytes
    by_bytes = defaultdict(list)
    claimed = set()
    for rva, size, name, src in rows:
        o = off_of(rva)
        if o is None:
            continue
        by_bytes[data[o:o + size]].append((rva, name))
        claimed.add(rva)

    # A short body says nothing. `xor eax,eax; ret` is three bytes and is the
    # whole of dozens of unrelated virtuals, so ICF folds them onto one
    # address and 'no vtable points here' stops being evidence of anything.
    # Only bodies long enough to be distinctive are worth comparing.
    # scan .text for other copies of those same bodies
    findings = []
    for rva, size, name, src in rows:
        if not re.search(r"@@U[A-Z]E", name):        # virtual methods only
            continue
        if rva in dispatched:
            continue
        o = off_of(rva)
        if o is None:
            continue
        body = data[o:o + size]
        twins = []
        i = 0
        while True:
            i = data.find(body, troff, troff + trsz) if i == 0 else data.find(body, i, troff + trsz)
            if i == -1:
                break
            cand = tva + (i - troff)
            if cand != rva and cand in dispatched and cand not in claimed:
                twins.append(cand)
            i += 1
            if len(twins) > 3:
                break
        if twins:
            findings.append((name, rva, size, twins, src))

    print("%d small claimed virtual row(s) examined; %d anchored to an undispatched copy\n"
          % (sum(1 for r in rows if re.search(r"@@U[A-Z]E", r[2])), len(findings)))
    for name, rva, size, twins, src in findings[:args.limit]:
        print("0x%08X %3dB  claimed here but no vtable points at it" % (rva, size))
        print("     %s" % name[:104])
        print("     dispatched twin(s): %s" % ", ".join("0x%08X" % t for t in twins))
    if len(findings) > args.limit:
        print("\n... %d more (--limit)" % (len(findings) - args.limit))


if __name__ == "__main__":
    sys.exit(main())
