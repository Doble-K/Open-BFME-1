"""Repair rows keyed to a compiler-generated label after codegen shifts.

A gen-funclet row names its body through object-symbol=$L<n>. The number is
assigned by the compiler and moves whenever anything upstream changes, so the
lookup fails even though the funclet itself is untouched. Find it by its bytes
and rewrite the note.
"""
import sys, csv, re
sys.path.insert(0, 'tools')
import build

data = open('baselines/bfme1/workshop-vanilla-1.03/files/lotrbfme.exe', 'rb').read()
rows = list(csv.DictReader(open('reverse/functions.csv', newline='')))

fixes = []
broken = []
for r in rows:
    m = re.search(r'object-symbol=(\$L\d+)', r['notes'])
    if not m:
        continue
    label = m.group(1)
    o = build.obj_path(build.ROOT / r['source'])
    if not o.exists():
        continue
    try:
        syms = {s['name'] for s in build.read_object_symbols(o.read_bytes())}
    except Exception:
        continue
    if label in syms:
        continue                      # still fine
    rva, size = int(r['target_rva'], 16), int(r['target_size'])
    target = data[rva:rva + size]
    cands = []
    for nm in sorted(s for s in syms if s.startswith('$L')):
        try:
            body, rel = build.read_object_symbol_bytes(o, nm)
        except Exception:
            continue
        if len(body) < size:
            continue
        mask = set()
        for off, t, x in rel:
            mask.update(range(off, off + 4))
        if all(i in mask or body[i] == target[i] for i in range(size)):
            cands.append(nm)
    if len(cands) == 1:
        fixes.append((r, label, cands[0]))
    else:
        broken.append((r, label, cands))

print(f"rows whose label vanished: {len(fixes) + len(broken)}")
for r, old, new in fixes:
    print(f"  {old} -> {new}   {r['name'][:40]:42} {r['source'].split('/')[-1]}")
for r, old, cands in broken:
    print(f"  {old} -> AMBIGUOUS ({len(cands)})  {r['name'][:40]:42} {r['source'].split('/')[-1]}")

if fixes:
    from pathlib import Path
    p = Path('reverse/functions.csv')
    raw = p.read_bytes()
    for r, old, new in fixes:
        needle = (r['name'] + ',').encode('utf-8')
        i = raw.find(needle)
        assert i >= 0, r['name']
        j = raw.find(b'\r\n', i)
        line = raw[i:j]
        assert (b'object-symbol=' + old.encode()) in line
        raw = raw[:i] + line.replace(b'object-symbol=' + old.encode(),
                                     b'object-symbol=' + new.encode()) + raw[j:]
    p.write_bytes(raw)
    print(f"\nrewrote {len(fixes)} note(s)")
