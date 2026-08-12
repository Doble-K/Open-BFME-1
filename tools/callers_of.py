"""Name anonymous dumps from the call graph instead of from their bytes.

`tools/locate.py` places a function by matching its compiled bytes. When it
reports `unlocated (drifted or not in this binary)` the bytes no longer agree, so
byte-scanning can never find that function and the 5.0 MB sitting in
`?d_xxxxxxxx@@YAXXZ` dumps stays anonymous.

The call graph does not care about drift. A dump called from exactly one named
function is pinned by that caller: open the caller's Zero Hour source, read what it
calls at that point, and the dump has a name. That is how `?d_000efe10@@YAXXZ` was
identified as `TeamFactory::findTeamPrototype` - two named callers agreed.

Usage:
    python3 tools/callers_of.py 0x000efe10        # who calls this address
    python3 tools/callers_of.py --report [N]      # best N naming candidates

`--report` lists anonymous dumps that have exactly one distinct named caller,
largest first, which are the ones a single source read can settle.

Direct `E8`/`E9` displacements are followed through one level of link thunk, and a
target only counts when it is a known function start, which is what keeps stray
matches inside instruction operands out of the results.
"""
import csv
import re
import struct
import sys
import collections

EXE = 'baselines/bfme1/workshop-vanilla-1.03/files/lotrbfme.exe'
ANON = re.compile(r'^\?[dj]i?_[0-9a-f]{8}@@YAXXZ$')


def load_image():
    data = open(EXE, 'rb').read()
    pe = data.index(b'PE\0\0')
    nsec = struct.unpack_from('<H', data, pe + 6)[0]
    optsz = struct.unpack_from('<H', data, pe + 20)[0]
    tab = pe + 24 + optsz
    secs = []
    for i in range(nsec):
        s = tab + 40 * i
        va = struct.unpack_from('<I', data, s + 12)[0]
        vsz = struct.unpack_from('<I', data, s + 16)[0]
        raw = struct.unpack_from('<I', data, s + 20)[0]
        secs.append((va, vsz, raw))
    return data, secs


def make_off(secs):
    def off(rva):
        for va, vsz, raw in secs:
            if va <= rva < va + vsz:
                return raw + (rva - va)
        return None
    return off


def load_rows():
    """Return (starts, sized, anon, named) keyed by RVA."""
    starts, sized, anon, named = set(), {}, {}, {}
    for r in csv.DictReader(open('reverse/functions.csv', newline='')):
        try:
            rva = int(r['target_rva'], 16)
            size = int(r['target_size'] or 0)
        except (ValueError, KeyError):
            continue
        starts.add(rva)
        sized[rva] = size
        if ANON.match(r['name']):
            anon[rva] = (size, r['name'])
        else:
            named[rva] = r['name']
    return starts, sized, anon, named


def build_edges(data, off, starts, sized, named):
    """caller RVA -> set of callee RVAs, following one level of link thunk."""
    thunk = {}

    def resolve(rva):
        if rva in thunk:
            return thunk[rva]
        o = off(rva)
        out = rva
        if o is not None and data[o] == 0xE9 and rva not in starts:
            out = rva + 5 + struct.unpack_from('<i', data, o + 1)[0]
        elif o is not None and data[o] == 0xE9:
            tgt = rva + 5 + struct.unpack_from('<i', data, o + 1)[0]
            if sized.get(rva, 0) <= 5:
                out = tgt
        thunk[rva] = out
        return out

    edges = collections.defaultdict(set)
    for rva in named:
        size = sized.get(rva, 0)
        if size < 5:
            continue
        o = off(rva)
        if o is None:
            continue
        body = data[o:o + size]
        i = 0
        end = len(body) - 4
        while i < end:
            if body[i] in (0xE8, 0xE9):
                tgt = rva + i + 5 + struct.unpack_from('<i', body, i + 1)[0]
                tgt = resolve(tgt)
                if tgt in starts and tgt != rva:
                    edges[rva].add(tgt)
                i += 5
                continue
            i += 1
    return edges


def main():
    data, secs = load_image()
    off = make_off(secs)
    starts, sized, anon, named = load_rows()

    args = sys.argv[1:]
    if not args:
        print(__doc__)
        return 2

    if args[0] == '--report':
        limit = int(args[1]) if len(args) > 1 else 40
        edges = build_edges(data, off, starts, sized, named)
        callers = collections.defaultdict(set)
        for src, tgts in edges.items():
            for t in tgts:
                if t in anon:
                    callers[t].add(src)
        single = [(anon[t][0], t, next(iter(cs)))
                  for t, cs in callers.items() if len(cs) == 1]
        single.sort(reverse=True)
        print('anonymous dumps with exactly one named caller: %d' % len(single))
        print('%8s  %-10s  %s' % ('size', 'dump', 'sole caller'))
        for size, t, c in single[:limit]:
            print('%8d  0x%08x  %s' % (size, t, named[c][:88]))
        return 0

    target = int(args[0], 16)
    edges = build_edges(data, off, starts, sized, named)
    hits = sorted(src for src, tgts in edges.items() if target in tgts)
    label = named.get(target) or (anon[target][1] if target in anon else '?')
    print('0x%08x  %s  (%d bytes)' % (target, label, sized.get(target, 0)))
    if not hits:
        print('  no named caller reaches it directly')
        return 0
    for h in hits:
        print('  <- 0x%08x  %s' % (h, named[h]))
    return 0


if __name__ == '__main__':
    sys.exit(main())
