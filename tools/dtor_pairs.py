#!/usr/bin/env python3
"""Find deleting destructors that an already-building source file emits unclaimed.

A class with a virtual destructor gets two functions: the destructor ??1X, and
the deleting stub ??_GX that calls it and then frees the object if the caller
asked for it. MSVC emits them together -- the stub comes with the vtable, and the
vtable comes with the translation unit that defines the destructor -- so wherever
??1X is claimed and verifying, ??_GX is already being compiled by that same file.

Those need no new C++ at all. They need a ledger row pointing at the stub, with
the source set to the file that already defines the destructor; add_match rebuilds
it and the symbol is either there and matching or it is not.

This is the opposite case from tools/vtable_owner.py, which finds stubs whose
destructor was trivial enough to inline into them. Those have no ??1 to pair with
and have to be written; these do not.

Usage: python tools/dtor_pairs.py [--limit N]
"""
import argparse
import bisect
import csv
import re
import struct
import sys

from vtable_gaps import EXE, IMAGE_BASE, ROOT, load_owners, sections


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--limit", type=int, default=40)
    args = ap.parse_args()

    data = EXE.read_bytes()
    secs = sections(data)
    tva, tvsz, troff, trsz = secs[".text"]
    text = data[troff:troff + trsz]

    rows = load_owners()
    taken = {r[2] for r in rows}
    starts = [r[0] for r in rows]

    def claimed_at(rva):
        k = bisect.bisect_right(starts, rva) - 1
        return k >= 0 and rva < rows[k][0] + rows[k][1]

    # Which source each destructor is defined in -- that is the file whose object
    # will also carry the stub, so it is what the new row has to point at.
    src = {}
    with (ROOT / "reverse" / "functions.csv").open(newline="", encoding="utf-8",
                                                   errors="replace") as fh:
        for r in csv.DictReader(fh):
            if not (r["name"] and r["source"] and r["status"] == "matched"):
                continue
            # An alias row's NAME is not what its source emits. The note records
            # the real object symbol, and reasoning from the name instead gives
            # nonsense: ??1AIUpdateModuleData is an alias for
            # ?releaseBuffer@?$StringBase@D@@AAEXXZ, so pairing a deleting stub
            # with it proposed a destructor for a class that has none in that
            # file. Under ICF a name and a body are many to many, and these rows
            # are where the two come apart.
            if "C++ alias" in (r["notes"] or "") or "object-symbol=" in (r["notes"] or ""):
                continue
            src[r["name"]] = r["source"]

    # Only virtual destructors have a deleting stub. UAE is the thiscall virtual
    # form; a QAE destructor is non-virtual and never gets one.
    DTOR = re.compile(r"^\?\?1(\w[\w@$?]*?)@@UAE@XZ$")
    wanted = {}
    for rva, size, nm in rows:
        m = DTOR.match(nm)
        if m and nm in src:
            wanted[rva] = (m.group(1), nm, src[nm])

    def off_of_text(rva):
        if tva <= rva < tva + tvsz and rva - tva < trsz:
            return troff + (rva - tva)
        return None

    def body(rva, cap=256):
        o = off_of_text(rva)
        if o is None:
            return b""
        j = o
        while j < o + cap and j < len(data) and data[j] != 0xCC:
            j += 1
        return data[o:j]

    # Every call site, resolved to its target, so a stub can be found by what it
    # calls rather than by where it sits.
    callers = {}
    for m in re.finditer(rb"\xe8", text):
        o = m.start()
        if o + 5 > len(text):
            break
        tgt = (tva + o + 5 + struct.unpack_from("<i", text, o + 1)[0]) & 0xFFFFFFFF
        if tgt in wanted:
            callers.setdefault(tgt, []).append(tva + o)

    def stub_start(call_rva):
        """Walk back to the int3 that precedes this call's function."""
        o = off_of_text(call_rva)
        j = o
        while j > troff and j > o - 64 and data[j - 1] != 0xCC:
            j -= 1
        return tva + (j - troff)

    findings = []
    for dtor_rva, (cls, dtor_nm, source) in sorted(wanted.items()):
        name = "??_G%s@@UAEPAXI@Z" % cls
        if name in taken:
            continue
        for call_rva in callers.get(dtor_rva, []):
            s = stub_start(call_rva)
            if claimed_at(s):
                continue
            b = body(s)
            # The stub tests bit 0 of its __flags argument and returns with
            # `ret 4` to clear it. Anything else that calls the destructor -- a
            # derived destructor, an array iterator -- has a different shape.
            if not re.search(rb"\xf6\x44\x24.\x01", b) or not b.endswith(b"\xc2\x04\x00"):
                continue
            findings.append((len(b), s, name, source))
            break

    findings.sort()
    print("%d unclaimed deleting stub(s) already emitted by a verifying source\n"
          % len(findings))
    for size, rva, name, source in findings[:args.limit]:
        print("0x%08X %3dB  %s" % (rva, size, name))
        print("            %s" % source)
    if len(findings) > args.limit:
        print("\n... %d more (--limit)" % (len(findings) - args.limit))

    # The other direction, which is where the yield actually is. A claimed stub
    # gives its destructor's address away for free, because it calls it. That
    # address is recorded nowhere else: an unmatched function has no ledger row,
    # and the source marker naming it carries no address, so the draft sitting in
    # the file has nothing to be compared against.
    STUB = re.compile(r"^\?\?_G(\w[\w@$?]*?)@@UAEPAXI@Z$")
    mirror = []
    for rva, size, nm in rows:
        m = STUB.match(nm)
        if not m or nm not in src:
            continue
        cls = m.group(1)
        if cls.startswith(("Gen_", "j_", "b_")):
            continue
        if "??1%s@@UAE@XZ" % cls in taken:
            continue
        b = body(rva, size)
        for c in re.finditer(rb"\xe8", b):
            p = c.start()
            if p + 5 > len(b):
                break
            t = (rva + p + 5 + struct.unpack_from("<i", b, p + 1)[0]) & 0xFFFFFFFF
            o = off_of_text(t)
            # A stub whose destructor was trivial enough to inline calls only
            # operator delete, and an ILT jump is the route to a destructor
            # rather than the destructor itself. Neither is an address to claim.
            if o is None or claimed_at(t) or data[o] == 0xE9:
                continue
            mirror.append((len(body(t, 4000)), t, "??1%s@@UAE@XZ" % cls, src[nm]))
            break

    mirror.sort()
    print("\n%d destructor(s) whose address is recoverable from a claimed stub\n"
          % len(mirror))
    for size, rva, name, source in mirror[:args.limit]:
        print("0x%08X %3dB  %s" % (rva, size, name))
        print("            %s" % source)


if __name__ == "__main__":
    sys.exit(main())
