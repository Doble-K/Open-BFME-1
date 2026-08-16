#!/usr/bin/env python3
"""Find unmatched bodies of a known-good TU by COMPILED SIZE.

locate.py places a compiled function by masked byte-scan. Its needle is the
longest relocation-free run in the body, so a function that is dense with
pointer stores -- a constructor, a mapper Apply -- has no needle long enough to
be unique and comes back "unlocated" even though the function is in the image.

What locate.py does print for those is the compiled size. This tool takes that
list, bounds the search to the address span the translation unit already owns,
and offers every unclaimed byte dump of exactly that size as a candidate. Each
candidate costs one explain_mismatch call to accept or reject.

A size match is a candidate and NOT a result. On mapper.cpp this found
?Apply@GridTextureMapperClass@@UAEXH@Z at 863 bytes; on vertmaterial.cpp it
found both remaining constructors; and on part_ldr.cpp the one candidate it
offered disagreed at its first byte.

WHAT IT REFUSES TO OFFER
------------------------
A hit is only reported as landable when it is 1:1 -- this symbol matched exactly
one address AND that address was matched by exactly one symbol. Everything else
is identical-code folding and is printed separately as a fold group.

That filter matters more than the search does. Four mapper classes compile Apply
to the same 860 bytes, and hanim.cpp's template vector destructors are
instantiated dozens of times across the image; on hanim.cpp this tool finds 108
"exact" matches and offers none of them, which is the correct answer. Naming a
folded body from the bytes is a coin flip. Break the tie with evidence that is
not the bytes -- scan .rdata for the address as a VA (rva + 0x400000) and read
the vtable it lands in, or follow a deleting destructor's call to the scalar
destructor it names. Do not break it by elimination.

Usage:
  python3 tools/prospect_by_size.py <source.cpp> [--window 0x8000]
"""
import argparse
import collections
import csv
import json
import os
import re
import subprocess
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
FUNCTIONS = os.path.join(ROOT, 'reverse', 'functions.csv')
SWEEP = os.path.join(ROOT, 'build', 'zh_sweep', 'match.json')


def unclaimed_dumps():
    """Byte dumps nothing has converted yet, as (rva, size).

    gen_asm only. A gen_small row is already real C++ under a placeholder name,
    so taking one over is a rename rather than a conversion, and add_match
    requires that retraction be its own commit.
    """
    out = []
    with open(FUNCTIONS, encoding='utf-8', newline='') as f:
        r = csv.reader(f)
        next(r)
        for row in r:
            if len(row) > 5 and row[2].startswith('0x') and 'gen_asm' in row[4]:
                try:
                    out.append((int(row[2], 16), int(row[3])))
                except ValueError:
                    pass
    return out


def owned_span(src):
    """Address range the TU already owns.

    Ledger rows first. A TU with no ledger row can still be bounded by the
    placements the sweep already made for it, which is how this works on
    sources that have never been landed from.
    """
    lo = hi = None
    with open(FUNCTIONS, encoding='utf-8', newline='') as f:
        r = csv.reader(f)
        next(r)
        for row in r:
            if len(row) > 5 and row[4] == src and row[2].startswith('0x'):
                a = int(row[2], 16)
                lo = a if lo is None else min(lo, a)
                hi = a if hi is None else max(hi, a)
    if lo is None and os.path.exists(SWEEP):
        for e in json.load(open(SWEEP)):
            if e.get('source') == src and e.get('rva') and e['bucket'].startswith('exact-unique'):
                a = e['rva']
                lo = a if lo is None else min(lo, a)
                hi = a if hi is None else max(hi, a)
    return lo, hi


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('source')
    ap.add_argument('--window', default='0x8000',
                    help='how far outside the owned span to look (default 0x8000)')
    ap.add_argument('--min-size', default='24')
    args = ap.parse_args()

    src = args.source.replace('\\', '/')
    window = int(args.window, 0)

    p = subprocess.run([sys.executable, 'tools/locate.py', src, '--min-size', args.min_size],
                       cwd=ROOT, capture_output=True, text=True)
    m = re.search(r'unlocated \(drifted or not in this binary\): (.*)', p.stdout + p.stderr)
    if not m:
        print('locate.py reported no unlocated symbols for this source')
        return 0
    syms = [(n, int(s)) for n, s in re.findall(r'([^\s,]+)\((\d+)B\)', m.group(1))]

    lo, hi = owned_span(src)
    if lo is None:
        print('this source owns no addresses yet, in the ledger or the sweep cache;')
        print('there is nothing to bound the search with, so every size would match')
        return 1

    by_size = collections.defaultdict(list)
    for a, s in unclaimed_dumps():
        if lo - window <= a <= hi + window:
            by_size[s].append(a)

    pairs = [(n, s, a) for n, s in syms for a in by_size.get(s, [])]
    print(f'{len(syms)} unlocated symbol(s); span 0x{lo:08X}..0x{hi:08X} '
          f'(+/-0x{window:X}); {len(pairs)} size-matched pair(s)')
    if hi - lo > 0x200000:
        print('  NOTE: that span is very wide, so the size filter is doing most of the')
        print('        work and the fold rate will be high')

    hits = []
    for name, size, addr in pairs:
        q = subprocess.run([sys.executable, 'tools/explain_mismatch.py', name,
                            '--rva', hex(addr), '--size', str(size), '--source', src],
                           cwd=ROOT, capture_output=True, text=True)
        if 'classification: exact match' in q.stdout:
            hits.append((name, addr, size))

    by_name = collections.Counter(n for n, _, _ in hits)
    by_addr = collections.Counter(a for _, a, _ in hits)
    unique = [h for h in hits if by_name[h[0]] == 1 and by_addr[h[1]] == 1]
    folded = [h for h in hits if h not in unique]

    print(f'{len(unique)} unambiguous, {len(folded)} in fold groups (not landable by name)')
    for name, addr, size in unique:
        print(f"python3 tools/add_match.py '{name}' 0x{addr:08X} {size} {src} "
              f"--replace-rva 0x{addr:08X}")
    if folded:
        groups = collections.defaultdict(set)
        for n, a, _ in folded:
            groups[a].add(n)
        print('\nfold groups -- the bytes cannot name these, the vtable can:')
        for a in sorted(groups):
            print(f'  0x{a:08X}: {len(groups[a])} name(s)')
    return 0


if __name__ == '__main__':
    sys.exit(main())
