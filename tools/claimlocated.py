"""Turn thunk-located bodies into claims.

thunkchase gives (body address, calling wrapper). The callee usually lives in
the same translation unit as its caller, so compare every function that TU
compiles against the located address and land whatever agrees byte for byte.
"""
import sys, csv, struct, subprocess, importlib.util
sys.path.insert(0, 'tools')
import build
import capstone

spec = importlib.util.spec_from_file_location("harvest", "tools/harvest.py")
harvest = importlib.util.module_from_spec(spec)
spec.loader.exec_module(harvest)

data = open('baselines/bfme1/workshop-vanilla-1.03/files/lotrbfme.exe', 'rb').read()
md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
TEXT_LO, TEXT_HI = 0x1000, 0x1000 + 13049856

rows = []
claimed = {}
for r in csv.DictReader(open('reverse/functions.csv', newline='')):
    if r['status'] != 'matched':
        continue
    a = int(r['target_rva'], 16)
    claimed.setdefault(a, r['name'])
    rows.append((a, int(r['target_size']), r['name'], r['notes'], r['source']))

targets = []          # (body_rva, source_of_wrapper, wrapper_name)
for rva, size, name, notes, src in rows:
    if size > 64 or notes.startswith(('gen-thunk', 'gen-import', 'gen-shim')):
        continue
    if src.startswith('Code/masm_dumps/') or src.startswith('Code/gen_small/'):
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
    try:
        first = next(md.disasm(data[t:t + 8], t))
    except Exception:
        continue
    if first.mnemonic != 'jmp' or not first.op_str.startswith('0x'):
        continue
    hop = int(first.op_str, 16)
    if not (TEXT_LO <= hop < TEXT_HI) or hop in claimed:
        continue
    targets.append((hop, src, name))

print(f"located bodies to try: {len(targets)}", flush=True)

by_src = {}
for hop, src, name in targets:
    by_src.setdefault(src, []).append((hop, name))

landed = 0
for src, items in sorted(by_src.items()):
    try:
        obj = harvest.compile_obj(build.Path(src), [])
        syms = sorted({s['name'] for s in build.read_object_symbols(obj.read_bytes())
                       if s['section'] > 0 and s['name'].startswith(('?', '_'))})
    except Exception as e:
        continue
    for hop, wrapper in items:
        e = hop
        while e < len(data) - 3 and not (data[e] == 0xCC and data[e+1] == 0xCC and data[e+2] == 0xCC):
            e += 1
        size = e - hop
        if size < 8 or size > 4096:
            continue
        target = data[hop:hop + size]
        for nm in syms:
            # vtables and RTTI are pure relocation: every byte is masked, so they
            # "match" any run of the same length. Never claim them as code.
            if nm.startswith(('??_7', '??_R', '??_8')):
                continue
            try:
                body, rel = build.read_object_symbol_bytes(obj, nm)
            except Exception:
                continue
            if len(body) != size:
                continue
            mask = set()
            for off, t, x in rel:
                mask.update(range(off, off + 4))
            unmasked = size - len(mask & set(range(size)))
            if unmasked < 12:
                continue
            if all(i in mask or body[i] == target[i] for i in range(size)):
                p = subprocess.run([sys.executable, 'tools/add_match.py', nm, f"0x{hop:08X}",
                                    str(size), src, '--notes',
                                    'located through the ILT thunk its claimed caller tail-calls'],
                                   capture_output=True, text=True)
                ok = 'verified OK' in p.stdout
                print(f"  {'OK  ' if ok else 'FAIL'} {nm[:60]:62} {hop:#010x} {size:>4}B")
                if ok:
                    landed += 1
                break
print(f"\nlanded {landed}")
