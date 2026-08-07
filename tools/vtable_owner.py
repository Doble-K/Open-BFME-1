#!/usr/bin/env python3
"""Name a vtable from the code that installs it, and claim its deleting destructor.

vtable_gaps identifies a slot from its named neighbours. That stops working at a
table's first slot, which has no neighbour above it -- and after runs were split
into real vtables, every scalar deleting destructor became a first slot and left
the listing entirely. They are the cheapest bodies in the image and they dropped
out exactly when the partitioning got correct.

They do not need a neighbour. A constructor installs the vptr of its own class,
so the code that stores a table's address names the class outright, and slot 0 of
that table is that class's scalar deleting destructor. That is how CullLinkClass
was identified: 0x0113780C is installed by ??0GridLinkClass, so the table below
it belongs to GridLinkClass's base.

Two things keep this honest. The installer has to be a constructor or destructor
of a real class, not a synthetic ?j_/?b_ placeholder, and slot 0 has to actually
carry the deleting-stub shape -- a class whose destructor is not virtual puts an
ordinary method there instead, and then the name would be wrong.

Usage: python tools/vtable_owner.py [--limit N] [--all]
"""
import argparse
import bisect
import csv
import re
import struct
import sys

from vtable_gaps import EXE, IMAGE_BASE, load_owners, sections


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--limit", type=int, default=25)
    ap.add_argument("--all", action="store_true",
                    help="also list tables whose slot 0 is already claimed")
    args = ap.parse_args()

    data = EXE.read_bytes()
    secs = sections(data)
    tva, tvsz, troff, trsz = secs[".text"]
    rva0, _, rroff, rrsz = secs[".rdata"]
    rdata = data[rroff:rroff + rrsz]
    text = data[troff:troff + trsz]

    rows = load_owners()
    starts = [r[0] for r in rows]
    exact = {r[0]: r[2] for r in rows}
    taken = {r[2] for r in rows}

    def owner(rva):
        k = bisect.bisect_right(starts, rva) - 1
        if k >= 0 and rva < rows[k][0] + rows[k][1]:
            return rows[k][2]
        return None

    def off_of_text(rva):
        if tva <= rva < tva + tvsz and rva - tva < trsz:
            return troff + (rva - tva)
        return None

    def body(rva, cap=128):
        o = off_of_text(rva)
        if o is None:
            return b""
        j = o
        while j < o + cap and j < len(data) and data[j] != 0xCC:
            j += 1
        return data[o:j]

    def is_deleting_dtor(rva):
        b = body(rva)
        return bool(re.search(rb"\xf6\x44\x24.\x01", b)) and b.endswith(b"\xc2\x04\x00")

    def is_text(off):
        if off < 0 or off + 4 > len(rdata):
            return False
        v = struct.unpack_from("<I", rdata, off)[0] - IMAGE_BASE
        return tva <= v < tva + tvsz

    # Every address in .rdata that a run of code pointers starts at, plus every
    # address inside one where a body installs its own slot -- the same two
    # boundary rules vtable_gaps partitions with, applied here to enumerate the
    # tables rather than the gaps between their slots.
    heads, i = [], 0
    while i + 4 <= len(rdata):
        if i % 4 or not is_text(i):
            i += 4 if i % 4 == 0 else (4 - i % 4)
            continue
        j = i
        while is_text(j):
            j += 4
        if (j - i) // 4 >= 1:
            for k in range((j - i) // 4):
                slot_va = rva0 + i + k * 4 + IMAGE_BASE
                slot = struct.unpack_from("<I", rdata, i + k * 4)[0] - IMAGE_BASE
                if k == 0 or struct.pack("<I", slot_va) in body(slot, 256):
                    heads.append((slot_va, slot))
        i = j

    # Where each table address is stored from. A constructor writing it names
    # the class; anything else is not evidence and is dropped.
    CTOR = re.compile(r"^\?\?[01](\w[\w@]*?)@@")

    findings = []
    for slot_va, slot0 in heads:
        claimed = exact.get(slot0)
        if claimed and not args.all:
            continue
        names = set()
        for m in re.finditer(re.escape(struct.pack("<I", slot_va)), text):
            nm = owner(tva + m.start())
            if not nm:
                continue
            g = CTOR.match(nm)
            if g:
                names.add(g.group(1))
        if len(names) != 1:
            continue
        cls = names.pop()
        if not is_deleting_dtor(slot0):
            continue
        # The name may already be claimed somewhere else. Both 31-byte
        # candidates this first produced were like that:
        # ??_GWin32LocalFileSystem is held at 0x009CDE30 as slot 0 of
        # 0x01143B98, while the table here is 0x01143B78 twenty bytes below it.
        # One of the two anchors is wrong and finding out which is a ledger
        # question, not a conversion -- offering it as work to write invites
        # claiming a name the image already spends elsewhere.
        if "??_G%s@@UAEPAXI@Z" % cls in taken:
            continue
        findings.append((len(body(slot0, 4000)), slot0, slot_va, cls, claimed))

    findings.sort()
    print("%d table(s) named by their installer with an unclaimed deleting destructor\n"
          % len(findings))
    for size, slot0, slot_va, cls, claimed in findings[:args.limit]:
        print("0x%08X ~%-4dB  vtable 0x%08X  ??_G%s@@UAEPAXI@Z%s"
              % (slot0, size, slot_va, cls, "   [claimed: %s]" % claimed if claimed else ""))
    if len(findings) > args.limit:
        print("\n... %d more (--limit)" % (len(findings) - args.limit))


if __name__ == "__main__":
    sys.exit(main())
