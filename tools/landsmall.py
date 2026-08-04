"""Masked-body sweep: compile a TU, mask relocation slots, hunt .text, land it.

For each function the object file defines, blank out every relocated operand and
search the section for the one placement where all remaining bytes agree. Where
exactly one exists and the placement sits on a 16-byte boundary or right after
int3 padding, add_match it.

Guards that must stay: vtables and RTTI (??_7 / ??_R / ??_8) are pure relocation
and are refused outright, and a body needs at least 12 unmasked bytes before a
unique hit means anything. Without the boundary rule the search once "found" an
8-byte body inside the immediate of a mov.

Historically produced ~90 functions; as of 2026-08-04 it is essentially
exhausted -- see docs/lessons.md. Worth re-running only after a class layout
changes, which reopens whatever that class blocked.

Run from the repo root: python3 tools/landsmall.py <files...>   (LANDS what it finds)
"""
import sys, csv, subprocess, importlib.util
sys.path.insert(0, 'tools')
import build

spec = importlib.util.spec_from_file_location("harvest", "tools/harvest.py")
harvest = importlib.util.module_from_spec(spec)
spec.loader.exec_module(harvest)

TEXT_LO, TEXT_HI = 0x1000, 0x1000 + 13049856
data = open('baselines/bfme1/workshop-vanilla-1.03/files/lotrbfme.exe', 'rb').read()


def claimed_rvas():
    s = {}
    for r in csv.DictReader(open('reverse/functions.csv', newline='')):
        if r['status'] == 'matched':
            s[int(r['target_rva'], 16)] = r['name']
    return s


def find(source):
    obj = harvest.compile_obj(build.Path(source), [])
    raw = obj.read_bytes()
    names = sorted({s['name'] for s in build.read_object_symbols(raw)
                    if s['section'] > 0 and s['name'].startswith(('_', '?'))})
    out = []
    for name in names:
        # vtables and RTTI are pure relocation: nothing is left to verify
        if name.startswith(('??_7', '??_R', '??_8')):
            continue
        try:
            body, relocs = build.read_object_symbol_bytes(obj, name)
        except Exception:
            continue
        n = len(body)
        if n < 8:
            continue
        mask = bytearray(n)
        for off, rtype, sym in relocs:
            for k in range(off, min(off + 4, n)):
                mask[k] = 1
        best_len = best_start = cur = 0
        for i in range(n):
            if mask[i]:
                cur = 0
            else:
                cur += 1
                if cur > best_len:
                    best_len, best_start = cur, i - cur + 1
        if best_len < 6:
            continue
        if n - sum(mask) < 12:      # too few bytes actually checked
            continue
        needle = bytes(body[best_start:best_start + best_len])
        hits = []
        i = TEXT_LO
        while True:
            j = data.find(needle, i, TEXT_HI)
            if j < 0:
                break
            st = j - best_start
            # a real function starts on a 16-byte boundary or right after int3
            # padding; without this an 8-byte body of mostly zero immediates
            # matches happily in the middle of someone else's instruction
            boundary = (st % 16 == 0) or (data[st-1] == 0xCC and data[st-2] == 0xCC and data[st-3] == 0xCC)
            if boundary and st >= TEXT_LO and st + n <= TEXT_HI and all(
                    mask[k] or body[k] == data[st + k] for k in range(n)):
                hits.append(st)
            i = j + 1
        if len(hits) == 1:
            out.append((name, hits[0], n))
    return out


landed = failed = 0
for source in sys.argv[1:]:
    cl = claimed_rvas()
    for name, rva, size in find(source):
        if rva in cl:
            continue
        p = subprocess.run([sys.executable, 'tools/add_match.py', name, f"0x{rva:08X}",
                            str(size), source, '--notes',
                            'pristine Lua 4.0.1 upstream source; located by masked-body search'],
                           capture_output=True, text=True)
        ok = 'verified OK' in p.stdout
        print(f"  {'OK  ' if ok else 'FAIL'} {name:26} {rva:#010x} {size:>4}B  {source.split('/')[-1]}")
        if ok:
            landed += 1
        else:
            failed += 1
            for line in (p.stdout + p.stderr).splitlines():
                if 'unresolved' in line or 'already' in line or 'Functions: FAIL' in line:
                    print("        ", line.strip()[:130])
                    break
print(f"\nlanded {landed}, failed {failed}")
