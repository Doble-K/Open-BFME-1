#!/usr/bin/env python3
"""Flag naked-asm rows whose retail body contradicts the name they are filed under.

A __declspec(naked) body is a copy of the retail bytes, so the byte gate passes for
whatever name someone attached to it -- the identity on a naked row is unverified by
construction. This reads the body back against the decorated name and reports the
disagreements, so a candidate can be dropped before any build time goes into it.

Checks, all of them conservative -- they only fire on a direct contradiction:

  ret-arity    bytes the body pops vs the size of the decorated argument list.
               Argument lists that cannot be sized from the name alone -- a class
               passed by value, a template, varargs -- are skipped rather than
               guessed, because a half-right sizer reports noise, not findings
  bool/-1      name returns _N but the body returns -1
  void/eax     name returns X but the body loads eax right before returning
  wide/al      name returns something wider than a byte but every exit only sets al

Usage: python tools/screen_identity.py [--limit N]
"""
import argparse
import csv
import re
import struct
import sys
from pathlib import Path

from capstone import CS_ARCH_X86, CS_MODE_32, Cs

ROOT = Path(r"D:\Open-BFME-1")
EXE = ROOT / "baselines" / "bfme1" / "workshop-vanilla-1.03" / "files" / "lotrbfme.exe"


def rva2off(data, rva):
    lfanew = struct.unpack_from("<I", data, 0x3C)[0]
    coff = lfanew + 4
    nsec = struct.unpack_from("<H", data, coff + 2)[0]
    optsz = struct.unpack_from("<H", data, coff + 16)[0]
    base = coff + 20 + optsz
    for i in range(nsec):
        o = base + i * 40
        vsz, va, rsz, roff = struct.unpack_from("<IIII", data, o + 8)
        if va <= rva < va + max(vsz, rsz):
            return roff + (rva - va)
    return None


# ---- decorated-name reading -------------------------------------------------

def split_name(mangled):
    """-> (access_code, return_token, arg_string) or None.

    ?foo@Bar@@QAE_NXZ                        -> ('QAE', '_N', 'XZ')
    ?foo@Bar@@QAE?AW4Level@@XZ               -> ('QAE', '?A', 'XZ')
    ?foo@Bar@@QBEPBVDamageFX@@VAsciiString@@@Z -> ('QBE', 'PA', 'VAsciiString@@@Z')

    The return type has to be consumed whole, class name included, or everything
    after it is read as arguments and the arity check invents numbers.
    """
    m = re.search(r"@@([A-Z]{3})(.*)$", mangled)
    if not m:
        return None
    access, tail = m.group(1), m.group(2)
    if not tail:
        return None

    def after_class(s):
        # Same trap as the argument sizer: a return type like PAUFrameHashEntry@1@
        # ends at a scope backreference, not at `@@`. Scanning for `@@` returns
        # the empty string and the whole argument list vanishes.
        j = _skip_class(s, 1 if s[0] in "VUT" else 0)
        return s[j:] if j is not None else ""

    if tail.startswith("_"):
        return access, tail[:2], tail[2:]
    if tail.startswith("?A"):
        # ?AW4Foo@@ is an enum and comes back in eax; ?AVFoo@@ is a class and
        # comes back through a hidden pointer the callee pops. Same prefix,
        # opposite stack behaviour, so they must not share a token.
        kind = "?AW" if tail.startswith("?AW") else "?AV"
        j = _skip_class(tail, 4 if kind == "?AW" else 3)
        return access, kind, (tail[j:] if j is not None else "")
    if tail[0] in "VUT":
        return access, "V", after_class(tail)
    if tail[:2] in ("PA", "PB", "AA", "AB", "QA", "QB"):
        if len(tail) > 2 and tail[2] in "VUT":
            j = _skip_class(tail, 3)
            return access, "PA", (tail[j:] if j is not None else "")
        if len(tail) > 2 and tail[2] == "?":
            return access, "PA", after_class(tail)
        return access, "PA", tail[3:]
    return access, tail[0], tail[1:]


BYTE_RETURNS = {"_N", "D", "E", "C"}
WIDE_RETURNS = {"H", "I", "J", "K", "F", "G", "PA", "PB", "?AW", "?AV"}


def _skip_class(body, i):
    """Index just past a V/U/T/W4 qualified name, or None if it is a template.

    A qualified name is `@`-separated segments ending either at `@@` (an empty
    segment) or at a single-digit segment, which is a backreference to an
    enclosing scope -- `FrameHashEntry@1@` is Debug::FrameHashEntry and ends at
    the `@` after the 1, with no `@@` anywhere. Scanning only for `@@` runs off
    the end of such a name and swallows the whole argument list, which reads as
    "sizes to 0" and would condemn a perfectly good row.

    Template names embed their own `@@`, so they are refused outright.
    """
    j = i
    while j < len(body):
        k = body.find("@", j)
        if k == -1:
            return None
        seg = body[j:k]
        if "?$" in seg or "$$" in seg:
            return None
        if seg == "":                     # `@@` terminator
            return k + 1
        if len(seg) == 1 and seg.isdigit():   # scope backreference ends the name
            return k + 1
        j = k + 1
    return None


SCALAR4 = set("DEFGHIJKM")          # char..float, one stack slot each
SCALAR8 = set("NO")                 # double, long double


def arg_bytes(argstr):
    """Stack bytes a callee-cleaned function pops for its arguments, or None.

    None means "cannot be sized safely" -- a class passed by value (whose size
    is not in the name), a template, or varargs. Callers must treat None as
    "no opinion" rather than as a mismatch.
    """
    if argstr.startswith("XZ"):
        return 0
    body = argstr
    if body.endswith("@Z"):
        body = body[:-2]
    elif body.endswith("Z"):
        body = body[:-1]

    total = 0
    seen = []                        # slot size of each composite type, in order
    i = 0
    while i < len(body):
        c = body[i]
        if c == "@":
            break
        if c == "Z":                 # varargs: the caller cleans up, not the callee
            return None
        pair = body[i:i + 2]
        if pair in ("_N", "_W"):
            total += 4
            i += 2
            continue
        if pair in ("_J", "_K"):
            total += 8
            i += 2
            continue
        if pair == "W4":             # enum by value: one slot
            j = _skip_class(body, i + 2)
            if j is None:
                return None
            seen.append(4)
            total += 4
            i = j
            continue
        if pair in ("PA", "PB", "PC", "QA", "QB", "AA", "AB"):
            j = i + 2
            if j >= len(body):
                return None
            if body[j] in "VUT" or body[j] == "W":
                # step past the V/U/T (or W4) tag: _skip_class segments on `@`,
                # and leaving the tag in makes the first segment "V1" rather
                # than the lone "1" that marks a name backreference, so
                # PAV1@ is mis-sized and a correct row is condemned.
                nxt = _skip_class(body, j + (2 if body[j] == "W" else 1))
                if nxt is None:
                    return None
                i = nxt
            elif body[j] == "?":     # pointer to template/function
                return None
            else:
                i = j + 1            # pointer to a scalar
            seen.append(4)
            total += 4
            continue
        if c.isdigit():              # backreference to an earlier composite type
            idx = int(c)
            if idx >= len(seen) or seen[idx] is None:
                return None
            total += seen[idx]
            i += 1
            continue
        if c in SCALAR4:
            total += 4
            i += 1
            continue
        if c in SCALAR8:
            total += 8
            i += 1
            continue
        if c in "VUT":               # class by value: size is not in the name
            return None
        return None                  # anything unrecognised: no opinion
    return total


# ---- body reading -----------------------------------------------------------

def body_facts(blob, rva):
    md = Cs(CS_ARCH_X86, CS_MODE_32)
    md.skipdata = True
    ins = list(md.disasm(blob, rva))
    if not ins:
        return None
    rets = [i for i in ins if i.mnemonic == "ret"]
    pops = set()
    for r in rets:
        pops.add(int(r.op_str, 16) if r.op_str else 0)
    facts = {
        "ret_pops": pops,
        "returns_minus_one": any(i.mnemonic == "or" and i.op_str in
                                 ("eax, 0xffffffff", "eax, -1") for i in ins),
        "sets_al_only": False,
        "loads_eax_before_ret": False,
    }
    # writes to eax vs al across the whole body
    wide = byte_only = False
    for i in ins:
        if i.mnemonic in ("mov", "or", "xor", "add", "sub", "lea", "movzx", "movsx", "and"):
            dst = i.op_str.split(",")[0].strip()
            if dst == "eax":
                wide = True
            elif dst == "al":
                byte_only = True
    facts["sets_al_only"] = byte_only and not wide
    # last eax-defining instruction before any ret
    for idx, i in enumerate(ins):
        if i.mnemonic == "ret" and idx > 0:
            prev = ins[idx - 1]
            if prev.op_str.split(",")[0].strip() in ("eax", "al") or prev.mnemonic == "call":
                facts["loads_eax_before_ret"] = True
    return facts


# Cases worked out by hand from the MSVC mangling rules. Two bugs have already
# shipped here, both from scanning a qualified name for `@@` when it can end at
# a backreference instead, and both would have condemned correct rows. Anything
# touching _skip_class or arg_bytes should run --selftest.
SELFTEST = [
    ("XZ", 0),                              # no arguments
    ("PBDH@Z", 8),                          # const char*, int
    ("ABVAsciiString@@0@Z", 8),             # const ref, then a type backreference
    ("PAVTextureClass@@0@Z", 8),            # pointer to class, then a backreference
    ("PAV1@W4CrushSquishTestType@@@Z", 8),  # pointer via name backref, then an enum
    ("IIPBDH@Z", 16),                       # two uints, const char*, int
    ("_N@Z", 4),                            # bool
    ("N@Z", 8),                             # double takes two slots
    ("VAsciiString@@@Z", None),             # class by value: size not in the name
    ("ZZ", None),                           # varargs: caller-cleaned
]


def selftest():
    bad = 0
    for argstr, want in SELFTEST:
        got = arg_bytes(argstr)
        ok = got == want
        bad += not ok
        print(f"  {'ok  ' if ok else 'FAIL'} {argstr:34} -> {got!r:6} expected {want!r}")
    print("selftest:", "OK" if not bad else f"{bad} FAILURE(S)")
    return 1 if bad else 0


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--limit", type=int, default=40)
    ap.add_argument("--selftest", action="store_true",
                    help="check the argument sizer against hand-computed cases and exit")
    args = ap.parse_args()

    if args.selftest:
        return selftest()

    data = EXE.read_bytes()

    naked = {}
    for path in (ROOT / "Code").rglob("*.cpp"):
        try:
            text = path.read_text(encoding="utf-8", errors="replace")
        except OSError:
            continue
        if "__declspec(naked)" not in text:
            continue
        for m in re.finditer(r"//\s*(\?[^\s]+)\s*\n__declspec\(naked\)", text):
            naked[m.group(1)] = path

    flagged = []
    checked = 0
    with (ROOT / "reverse" / "functions.csv").open(newline="", encoding="utf-8",
                                                   errors="replace") as fh:
        for row in csv.DictReader(fh):
            name = row["name"]
            if name not in naked or not row["target_rva"]:
                continue
            size = int(row["target_size"] or 0)
            if size < 6:
                continue
            parts = split_name(name)
            if not parts:
                continue
            access, ret, argstr = parts
            rva = int(row["target_rva"], 16)
            off = rva2off(data, rva)
            if off is None:
                continue
            facts = body_facts(data[off:off + size], rva)
            if not facts:
                continue
            checked += 1

            why = []
            if ret == "_N" and facts["returns_minus_one"]:
                why.append("returns _N but body returns -1")
            if ret == "X" and facts["loads_eax_before_ret"]:
                why.append("returns void but body sets eax at a return")
            if ret in WIDE_RETURNS and facts["sets_al_only"]:
                why.append(f"returns {ret} but body only ever writes al")
            # ret-arity. arg_bytes returns None whenever the list cannot be
            # sized from the name alone, and None means no opinion -- never a
            # finding. A class returned by value also pops its hidden return
            # pointer; an enum comes back in eax and pops nothing.
            varargs = argstr.startswith("Z") or access[2] == "A"
            want = arg_bytes(argstr)
            if want is not None and not varargs and access[2] in "EIM" and facts["ret_pops"]:
                if ret in ("?AV", "V"):
                    want += 4
                if want not in facts["ret_pops"]:
                    why.append(f"pops {sorted(facts['ret_pops'])} but the argument list "
                               f"sizes to {want}")

            if why:
                flagged.append((name, rva, size, naked[name], why))

    print(f"screened {checked} naked row(s) >=6B; {len(flagged)} contradicted\n")
    for name, rva, size, path, why in flagged[:args.limit]:
        print(f"0x{rva:08X}  {size:>4}B  {'; '.join(why)}")
        print(f"     {name[:110]}")
        print(f"     {path.relative_to(ROOT).as_posix()}")
    if len(flagged) > args.limit:
        print(f"\n... {len(flagged) - args.limit} more not shown (--limit)")


if __name__ == "__main__":
    sys.exit(main())
