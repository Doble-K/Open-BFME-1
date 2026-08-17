#!/usr/bin/env python3
"""Name naked dumps by the string literals they push.

A body that does `push offset "SomeLiteral"` carries its own identity. Read the
DIR32 immediate as a virtual address, read the C string there, and look the
string up in the vendored Zero Hour tree: when it appears in exactly one
reference source, that source is the body's compiland, and the function
enclosing the string is the first candidate for its name.

This is a different anchor from the ones already in the tree. locate.py needs a
relocation-free run long enough to be unique; reloc_names.csv needs a byte-true
call site; the ZH packet sweep needs a reference body that already nearly
matches. A string needs none of those -- it works on bodies whose code has
drifted far enough that nothing else votes.

    python3 tools/string_anchors.py [--min 24] [--max 4000] [--csv out.csv]

Output is a worklist, not a claim: a string proves which compiland the body
belongs to, not which function. Verify with tools/add_match.py, which reverts on
failure, and read its whole output -- a source that needs a shim to compile the
body may regress a row the file already owns.
"""
import argparse
import collections
import os
import re
import subprocess
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import build  # noqa: E402

REF = 'reference/CnC_Generals_Zero_Hour/GeneralsMD/Code'
IMAGE_BASE = 0x400000

# push imm32 whose high byte is 0x01 -- the .rdata window BFME's literals live in
PUSH_LITERAL = re.compile(rb'\x68(.[\x00-\xff]{2}\x01)', re.S)

# A function definition line: a name, an argument list, no trailing semicolon.
DEFINITION = re.compile(
    r'^[A-Za-z_][\w:<>,\*&\s]*?\b((?:\w+::)?\w+)\s*\([^;{]*\)\s*(?:const\s*)?\{?\s*$')


def unclaimed_dumps(lo, hi):
    """gen dumps in [lo,hi] whose address no real C++ row claims."""
    claimed = set()
    dumps = []
    for line in open('reverse/functions.csv', encoding='utf-8', errors='replace'):
        p = line.rstrip('\r\n').split(',')
        if len(p) < 6:
            continue
        try:
            rva, size = int(p[2], 16), int(p[3])
        except ValueError:
            continue
        if p[4].startswith('Code/gen_') or p[4].endswith('.asm'):
            if p[0].startswith('?d_') and lo <= size <= hi:
                dumps.append((rva, size))
        else:
            claimed.add(rva)
    return [(rva, size) for rva, size in dumps if rva not in claimed]


def read_cstring(va, limit=120):
    try:
        raw = bytes(build.read_target_bytes(va - IMAGE_BASE, limit))
    except Exception:
        return None
    end = raw.find(b'\x00')
    if end < 6:
        return None
    text = raw[:end]
    if not all(32 <= c < 127 for c in text):
        return None
    return text.decode('ascii')


def strings_in(rva, size):
    try:
        data = bytes(build.read_target_bytes(rva, size))
    except Exception:
        return []
    out = []
    for m in PUSH_LITERAL.finditer(data):
        s = read_cstring(int.from_bytes(m.group(1), 'little'))
        # backslashes are source paths from DEBUG macros: they name the file
        # directly and never need this lookup
        if s and 6 <= len(s) <= 60 and '\\' not in s:
            out.append(s)
    return out


def sole_reference_file(text):
    r = subprocess.run(['grep', '-rl', '--include=*.cpp', '--include=*.h', text, REF],
                       capture_output=True, text=True)
    files = [f for f in r.stdout.split('\n') if f.strip()]
    return files[0] if len(files) == 1 else None


def enclosing_function(path, text):
    try:
        lines = open(path, encoding='utf-8', errors='replace').read().splitlines()
    except OSError:
        return None
    hit = next((i for i, l in enumerate(lines) if text in l), None)
    if hit is None:
        return None
    for j in range(hit, max(0, hit - 200), -1):
        line = lines[j].rstrip()
        if line.lstrip().startswith(('if', 'for', 'while', 'switch', 'return', '//', '*')):
            continue
        m = DEFINITION.match(line)
        if m and '(' in line:
            return m.group(1)
    return None


def ports_by_basename():
    index = collections.defaultdict(list)
    for root, _dirs, files in os.walk('Code'):
        if 'gen_' in root:
            continue
        for f in files:
            if f.endswith(('.cpp', '.c')):
                index[f.lower()].append(os.path.join(root, f).replace(os.sep, '/'))
    return index


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--min', type=int, default=24)
    ap.add_argument('--max', type=int, default=4000)
    ap.add_argument('--csv')
    args = ap.parse_args()

    ports = ports_by_basename()
    rows = []
    for rva, size in unclaimed_dumps(args.min, args.max):
        for text in strings_in(rva, size)[:3]:
            ref = sole_reference_file(text)
            if not ref:
                continue
            fn = enclosing_function(ref, text)
            if not fn:
                continue
            port = ports.get(os.path.basename(ref).lower(), [])
            rows.append((size, rva, text, ref[len(REF) + 1:], fn,
                         port[0] if len(port) == 1 else ''))
            break

    rows.sort(reverse=True)
    print('%d dump(s) in [%d,%d] anchored to one reference source'
          % (len(rows), args.min, args.max))
    for size, rva, text, ref, fn, port in rows:
        print('%6d 0x%08X %-34s %-40s %s' % (size, rva, text[:34], fn[:40], port))
    if args.csv:
        with open(args.csv, 'w', encoding='utf-8', newline='') as handle:
            handle.write('target_rva,size,literal,reference_source,candidate_function,port\n')
            for size, rva, text, ref, fn, port in rows:
                if ',' in text or '"' in text:
                    continue
                handle.write('0x%08X,%d,%s,%s,%s,%s\n' % (rva, size, text, ref, fn, port))


if __name__ == '__main__':
    main()
