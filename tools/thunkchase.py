"""Locate unclaimed function bodies through claimed wrappers.

A claimed wrapper that tail-calls an ILT thunk gives away the address of the
body behind it. Where that body is still unclaimed, the wrapper's own name is
strong evidence for what lives there.
"""
import sys, csv, struct
sys.path.insert(0, 'tools')
import capstone

data = open('baselines/bfme1/workshop-vanilla-1.03/files/lotrbfme.exe', 'rb').read()
md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
TEXT_LO, TEXT_HI = 0x1000, 0x1000 + 13049856

claimed = {}
rows = []
for r in csv.DictReader(open('reverse/functions.csv', newline='')):
    if r['status'] != 'matched':
        continue
    a = int(r['target_rva'], 16)
    claimed.setdefault(a, r['name'])
    rows.append((a, int(r['target_size']), r['name'], r['notes']))

# only walk small wrappers: big functions call many things and prove nothing
found = []
for rva, size, name, notes in rows:
    if size > 64 or notes.startswith(('gen-thunk', 'gen-import', 'gen-shim')):
        continue
    try:
        ins = list(md.disasm(data[rva:rva + size], rva))
    except Exception:
        continue
    calls = [i for i in ins if i.mnemonic in ('call', 'jmp') and i.op_str.startswith('0x')]
    if len(calls) != 1:
        continue
    t = int(calls[0].op_str, 16)
    if not (TEXT_LO <= t < TEXT_HI):
        continue
    # follow one jmp hop (ILT thunk)
    hop = None
    try:
        first = next(md.disasm(data[t:t + 8], t))
        if first.mnemonic == 'jmp' and first.op_str.startswith('0x'):
            hop = int(first.op_str, 16)
    except Exception:
        pass
    if hop is None or not (TEXT_LO <= hop < TEXT_HI):
        continue
    if hop in claimed:
        continue
    found.append((hop, t, rva, name))

print(f"wrappers examined: {len(rows)}")
print(f"unclaimed bodies located behind a thunk: {len(found)}\n")
seen = set()
for hop, thunk, rva, name in sorted(found)[:60]:
    if hop in seen:
        continue
    seen.add(hop)
    # size of the body from int3 padding
    e = hop
    while e < len(data) - 3 and not (data[e] == 0xCC and data[e + 1] == 0xCC and data[e + 2] == 0xCC):
        e += 1
    print(f"  body {hop:#010x} ({e-hop:>5}B)  thunk {thunk:#08x}  <- {name[:64]}")
print(f"\ndistinct bodies: {len(seen)}")
