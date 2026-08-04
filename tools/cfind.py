"""Locate C-linkage functions in retail by masked-body search.

harvest.py only looks at ?-mangled symbols that already appear in the export
table, so it cannot see a C library like Lua. This compiles a .c translation
unit and, for every function it defines, masks the relocation slots and hunts
the retail .text for a placement where every remaining byte agrees.
"""
import sys, csv, struct
sys.path.insert(0, 'tools')
import build
import importlib.util

spec = importlib.util.spec_from_file_location("harvest", "tools/harvest.py")
harvest = importlib.util.module_from_spec(spec)
spec.loader.exec_module(harvest)

TEXT_LO, TEXT_HI = 0x1000, 0x1000 + 13049856
data = open('baselines/bfme1/workshop-vanilla-1.03/files/lotrbfme.exe', 'rb').read()

claimed = {}
for r in csv.DictReader(open('reverse/functions.csv', newline='')):
    if r['status'] == 'matched':
        claimed[int(r['target_rva'], 16)] = r['name']

source = build.Path(sys.argv[1])
obj = harvest.compile_obj(source, [])
raw = obj.read_bytes()
names = sorted({s['name'] for s in build.read_object_symbols(raw)
                if s['section'] > 0 and (s['name'].startswith('_') or s['name'].startswith('?'))})

print(f"{source.name}: {len(names)} defined symbol(s)")
for name in names:
    try:
        body, relocs = build.read_object_symbol_bytes(obj, name)
    except Exception:
        continue
    n = len(body)
    if n < 12:
        continue
    mask = bytearray(n)          # 1 = ignore
    for off, rtype, sym in relocs:
        for k in range(off, min(off + 4, n)):
            mask[k] = 1
    # longest reloc-free run as the search needle
    best_len = best_start = 0
    cur = 0
    for i in range(n):
        if mask[i]:
            cur = 0
        else:
            cur += 1
            if cur > best_len:
                best_len, best_start = cur, i - cur + 1
    if best_len < 8:
        continue
    needle = bytes(body[best_start:best_start + best_len])
    hits = []
    i = TEXT_LO
    while True:
        j = data.find(needle, i, TEXT_HI)
        if j < 0:
            break
        start = j - best_start
        if start >= TEXT_LO and start + n <= TEXT_HI:
            if all(mask[k] or body[k] == data[start + k] for k in range(n)):
                hits.append(start)
        i = j + 1
    if len(hits) == 1:
        rva = hits[0]
        tag = f"  ALREADY {claimed[rva]}" if rva in claimed else ""
        print(f"  {name:34} {n:>5}B  ->  {rva:#010x}{tag}")
    elif len(hits) > 1:
        print(f"  {name:34} {n:>5}B  ->  ambiguous ({len(hits)} placements)")
