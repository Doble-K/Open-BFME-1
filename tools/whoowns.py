"""Which compiled COMDATs reproduce the retail bytes at a given RVA?"""
import sys, csv
sys.path.insert(0, 'tools')
import build
from pathlib import Path

rva = int(sys.argv[1], 16)
size = int(sys.argv[2])
data = open('baselines/bfme1/workshop-vanilla-1.03/files/lotrbfme.exe', 'rb').read()
target = data[rva:rva + size]

src_of = {}
for r in csv.DictReader(open('reverse/functions.csv', newline='')):
    s = r['source']
    if s not in src_of:
        try:
            src_of[str(build.obj_path(build.ROOT / s))] = s
        except Exception:
            pass

hits = []
scanned = 0
for o in Path('build/match').rglob('*.obj'):
    try:
        raw = o.read_bytes()
    except Exception:
        continue
    scanned += 1
    try:
        syms = build.read_object_symbols(raw)
    except Exception:
        continue
    for nm in sorted({s['name'] for s in syms if s['name'].startswith(('?', '_'))}):
        try:
            body, rel = build.read_object_symbol_bytes(o, nm)
        except Exception:
            continue
        if len(body) != size:
            continue
        mask = set()
        for off, t, x in rel:
            mask.update(range(off, off + 4))
        if all(i in mask or body[i] == target[i] for i in range(size)):
            hits.append((nm, src_of.get(str(o), o.name)))

print(f"scanned {scanned} objects; {len(hits)} COMDAT(s) reproduce {rva:#x} ({size}B)")
for nm, s in hits[:30]:
    print(f"  {nm[:88]}")
    print(f"      {s}")
