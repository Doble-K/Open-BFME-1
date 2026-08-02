#!/usr/bin/env python3
"""Find destructor rows that share one address under several class names.

WHY THESE SURVIVE THE GATE. A destructor is made of exactly the two things the
byte comparison cannot see:

  ??1<C>   installs the vptr -- `mov [ecx], offset <C>'s vtable` -- and that is
           a DIR32, which build.py fills in from the target. Two destructors for
           different classes therefore byte-match after masking.
  ??_G<C>  calls the scalar destructor -- a REL32, likewise filled in from the
           target. Every deleting destructor of the standard 30-byte shape
           matches every other one.

So for destructors the verifier tests the shape and nothing else, and a wrong
class name is never contradicted. That is how 205 different class names came to
be claimed on 0x005BF290, and how ??1RAMFile@@ and ??1SaveLoadSubSystemClass@@
both came to sit on 0x009D19A0. It is the same unfalsifiable-size problem as a
5-byte ILT thunk (tools/audit_thunk_rows.py) and a 1-byte bare ret
(tools/audit_short_rows.py), but it bites at any size and in bulk.

THE PART THAT NEEDS NO JUDGEMENT. Identical function bodies really are folded by
the linker, and folding really does put several correct names on one address --
that is why most output from the thunk audit is legitimate. But folding cannot
join two bodies that install DIFFERENT vtable pointers, because those bodies
differ before masking, and a vtable belongs to exactly one class. So:

    n distinct class names on one body that installs a vtable
      =>  at least n-1 of those rows are wrong.

That count is printed first and does not depend on deciding which name is right.

THE PART THAT DOES NEED JUDGEMENT. To say WHICH name survives, read the vptr
back out of the image and ask who owns that vtable. A claimed constructor
installing the same pointer names it outright: ??0RAMFile@@ installs 0x01143C58,
so the body at 0x009D19A0 that also installs 0x01143C58 is ~RAMFile, and the
SaveLoadSubSystemClass row is the wrong one.

That attribution is only as good as the constructor row it leans on. A false ??0
propagates straight through, so confirm the owner independently before editing
-- the strongest confirmation is a vtable pinned by a byte-matched caller, the
way FileSystem's three matched callers pin 0x01143B98 to Win32LocalFileSystem.
`unexplained` means no claimed constructor installs that vtable: the address is
unproven, not proven wrong.

Usage:
  python3 tools/audit_dtor_aliases.py
  python3 tools/audit_dtor_aliases.py --address 0x009D19A0
  python3 tools/audit_dtor_aliases.py --only-contradicted
"""
import argparse
import csv
import re
import struct
import sys
from collections import defaultdict
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import dump_ini_schema as S

_DTOR_RE = re.compile(r"^\?\?1(.+?)@@[A-Z]")
_DG_RE = re.compile(r"^\?\?_G(.+?)@@[A-Z]")
_CTOR_RE = re.compile(r"^\?\?0(.+?)@@[A-Z]")

# mov dword ptr [reg], imm32 for the registers MSVC uses to hold `this`.
_VPTR_PREFIXES = (b"\xc7\x01", b"\xc7\x06", b"\xc7\x07", b"\xc7\x03")

# .rdata and .data, as virtual addresses -- dump_ini_schema's section table is
# already based, so do NOT add IMAGE_BASE again here.
_VT_LO, _VT_HI = 0x01073000, 0x012A5000


def vptr_installed(img, rva, size):
    """The FIRST vtable pointer this body installs, or None.

    First, not any: a derived destructor under multiple inheritance installs
    several, and the one that identifies the class is the one it writes at the
    top of the body."""
    off = rva - img.tbase
    body = bytes(img.text[off:off + size])
    best = None
    for pre in _VPTR_PREFIXES:
        i = body.find(pre)
        while i != -1:
            if i + 6 <= len(body):
                v = struct.unpack("<I", body[i + 2:i + 6])[0]
                if _VT_LO <= v < _VT_HI and (best is None or i < best[0]):
                    best = (i, v)
            i = body.find(pre, i + 1)
    return best[1] if best else None


def scalar_target(img, rva, size):
    """For a deleting destructor, the scalar destructor it calls.

    The bound is the .text extent in RVA terms. Bounding by 0x00401000 instead
    skips the low ILT region, where these calls very often land, and picks up
    the `call operator delete` two instructions later -- which is the same for
    every class and so distinguishes nothing."""
    off = rva - img.tbase
    body = bytes(img.text[off:off + size])
    i = body.find(b"\xe8")
    while i != -1 and i + 5 <= len(body):
        disp = struct.unpack("<i", body[i + 1:i + 5])[0]
        t = rva + i + 5 + disp
        if img.tbase <= t < img.tbase + len(img.text):
            return img.deref_thunk(t)
        i = body.find(b"\xe8", i + 1)
    return None


def load_rows():
    rows = []
    with open(S.B.ROOT / "reverse/functions.csv", newline="", encoding="utf-8") as fh:
        for r in csv.DictReader(fh):
            try:
                rows.append((r["name"], int(r["target_rva"], 16),
                             int(r["target_size"]), r.get("source", "")))
            except (ValueError, KeyError):
                continue
    return rows


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--address", help="only this RVA (hex)")
    ap.add_argument("--only-contradicted", action="store_true")
    args = ap.parse_args()
    only = int(args.address, 16) if args.address else None

    img = S.Image()
    rows = load_rows()
    size_at = {}
    for _n, a, s, _src in rows:
        size_at[a] = max(size_at.get(a, 0), s)

    # Who owns each vtable? A claimed constructor installing it says so.
    vtable_owner = defaultdict(set)
    for name, rva, size, _src in rows:
        m = _CTOR_RE.match(name)
        if m:
            v = vptr_installed(img, rva, size)
            if v is not None:
                vtable_owner[v].add(m.group(1))

    by_addr = defaultdict(list)
    for name, rva, size, src in rows:
        if (_DTOR_RE.match(name) or _DG_RE.match(name)) and \
                (only is None or rva == only):
            by_addr[rva].append((name, size, src))

    # The judgement-free count, over scalar destructors only: ??_G bodies are
    # near-identical by construction, so counting them here would overstate.
    must_be_wrong = shared = 0
    for rva, entries in by_addr.items():
        classes = {_DTOR_RE.match(n).group(1) for n, _, _ in entries
                   if _DTOR_RE.match(n)}
        if len(classes) > 1:
            shared += 1
            if vptr_installed(img, rva, size_at[rva]) is not None:
                must_be_wrong += len(classes) - 1

    print(f"{shared} scalar-destructor address(es) claimed by more than one "
          f"class.\nAt least {must_be_wrong} of those rows are wrong: the body "
          f"installs one vtable,\nand a vtable belongs to one class.\n")

    n_bad = n_group = 0
    for rva, entries in sorted(by_addr.items()):
        if len({n for n, _, _ in entries}) < 2 and only is None:
            continue
        n_group += 1

        size = size_at[rva]
        v = vptr_installed(img, rva, size)
        via = "installs"
        if v is None:
            tgt = scalar_target(img, rva, size)
            if tgt is not None:
                v = vptr_installed(img, tgt, size_at.get(tgt, 64))
                via = f"scalar dtor 0x{tgt:08X} installs"
        if v is None:
            continue

        owners = vtable_owner.get(v)
        print(f"0x{rva:08X}  {via} vtable 0x{v:08X}  "
              f"owner={'/'.join(sorted(owners)) if owners else '(no claimed ctor)'}")
        for name, _s, src in sorted(entries):
            cls = (_DTOR_RE.match(name) or _DG_RE.match(name)).group(1)
            if not owners:
                verdict = "unexplained"
            elif cls in owners:
                verdict = "agrees"
            else:
                verdict = "CONTRADICTED"
                n_bad += 1
            if args.only_contradicted and verdict != "CONTRADICTED":
                continue
            print(f"      {verdict:<13} {name}")
            if verdict == "CONTRADICTED" and src:
                print(f"                    src: {src}")
        print()

    print(f"{n_group} aliased destructor address(es); "
          f"{n_bad} contradicted by their own vtable")


if __name__ == "__main__":
    main()
