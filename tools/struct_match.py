#!/usr/bin/env python3
"""Match unclaimed retail bodies against an already-compiled source, STRUCTURALLY.

Why the obvious approach fails. When a class is relaid out, the natural sweep is
"find a compiled COMDAT of the same length as the retail row, then diff". That is
structurally blind here: BFME's offsets cross the disp8/disp32 boundary, so a
3-byte `mov ecx,[ecx+0x0C]` becomes a 6-byte `mov ecx,[ecx+0x188]`. THE RELAYOUT
CHANGES INSTRUCTION LENGTHS, NOT JUST CONSTANTS. Measured on Object.cpp: of 135
unclaimed rows in its range, only 13 have an equal-length candidate at all, and
121 have none.

So compare SHAPE, not bytes or length. Each instruction is normalised to its
mnemonic plus its operand form with every displacement and immediate erased:

    mov ecx,[ecx+0x0C]    ->   mov r,[r+K]
    mov ecx,[ecx+0x188]   ->   mov r,[r+K]        <- same shape, different length

Two bodies match when their whole normalised sequences are equal. That finds the
already-written body whose only defect is the layout constants, which is exactly
the situation in a file like Object.cpp where the source is present and correct
apart from the offsets.

WHAT THIS DOES NOT DO. A shape match is a CANDIDATE, never a claim: erasing the
constants erases real distinctions, so two genuinely different methods over the
same layout can share a shape. The byte gate still decides. Its output is a
worklist ranked by how few constants have to move.

Usage:
  python3 struct_match.py <source.cpp> <lo_rva> <hi_rva> [--max-diff N]
"""
import argparse
import collections
import csv
import io
import re
import sys
from pathlib import Path

sys.path.insert(0, "tools")
import build
import capstone

md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)

HEX = re.compile(r"\b0x[0-9a-f]+\b")
DEC = re.compile(r"(?<![\w.])\d+(?![\w.])")


def shape(body):
    """Normalised (mnemonic, operand-form) sequence, constants erased."""
    out, covered = [], 0
    for insn in md.disasm(body, 0):
        ops = HEX.sub("K", insn.op_str)
        ops = DEC.sub("K", ops)
        out.append(insn.mnemonic + " " + ops)
        covered += insn.size
    return (tuple(out), covered == len(body))


def constants(body):
    """The displacement/immediate values, in order -- what would have to move.

    RELATIVE BRANCH TARGETS ARE EXCLUDED. A call or jump displacement differs
    between the compiled object and retail by construction, because the two live
    at different addresses; counting them makes every candidate look like it
    needs half its constants moved and buries the one that actually matters. The
    interesting constants are member offsets and immediates.
    """
    vals = []
    for insn in md.disasm(body, 0):
        if insn.mnemonic in ("call", "jmp") or insn.mnemonic.startswith("j"):
            continue
        for m in HEX.finditer(insn.op_str):
            vals.append(int(m.group(0), 16))
    return vals


def object_bodies(source):
    """Every defined .text symbol in the compiled object for `source`."""
    path = build.obj_path(source)
    if not path.exists():
        sys.exit("no object for %s -- build it first with tools/build.py" % source)
    stat = path.stat()
    data, sections, symbols = build._object_layout(str(path), stat.st_mtime_ns, stat.st_size)
    out = {}
    for sym in symbols:
        if sym["section"] <= 0 or sym["name"].startswith("$L"):
            continue
        section = sections[sym["section"] - 1]
        if not section["name"].startswith(".text"):
            continue
        start = section["raw_pointer"] + sym["value"]
        end = section["raw_pointer"] + section["raw_size"]
        body = data[start:end].rstrip(b"\xcc")
        if 8 <= len(body) <= 4096:
            out.setdefault(sym["name"], body)
    return out


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("source")
    ap.add_argument("lo", type=lambda s: int(s, 16))
    ap.add_argument("hi", type=lambda s: int(s, 16))
    ap.add_argument("--max-diff", type=int, default=99)
    # Erasing constants erases distinctions, so a SHORT body shape-matches many
    # candidates and says nothing -- a 13-byte setter matches every setter in the
    # object, and an 8-byte getter matches every getter. Only bodies long enough
    # for the shape itself to be rare are worth a human's time.
    ap.add_argument("--min-size", type=int, default=24)
    args = ap.parse_args()

    compiled = object_bodies(args.source)
    by_shape = collections.defaultdict(list)
    undecodable = 0
    for name, body in compiled.items():
        sig, ok = shape(body)
        if ok:
            by_shape[sig].append((name, body))
        else:
            undecodable += 1
    print("compiled bodies in %s: %d (%d undecodable)"
          % (args.source, len(compiled), undecodable))

    rows = []
    with io.open("reverse/functions.csv", encoding="utf-8") as fh:
        for i, r in enumerate(csv.reader(fh)):
            if i == 0 or len(r) != 7:
                continue
            if not r[4].startswith("Code/gen_asm/"):
                continue
            rva = int(r[2], 16)
            if args.lo <= rva <= args.hi and args.min_size <= int(r[3]) <= 4096:
                rows.append((rva, int(r[3]), r[0]))
    rows.sort()
    print("unclaimed rows in range: %d\n" % len(rows))

    found = []
    for rva, size, rowname in rows:
        try:
            body = build.read_target_bytes(rva, size)
        except Exception:
            continue
        sig, ok = shape(body)
        if not ok:
            continue
        for name, cbody in by_shape.get(sig, []):
            rc, cc = constants(body), constants(cbody)
            moved = sum(1 for a, b in zip(rc, cc) if a != b)
            if moved <= args.max_diff:
                diffs = [(b, a) for a, b in zip(rc, cc) if a != b]
                found.append((size, -moved, rva, name, moved, len(rc), diffs))

    # Rank by body length first, then by how few constants have to move. A long
    # shape with one moved constant is close to a certainty; a short one with
    # several is noise. The reader should work down this list, not across it.
    found.sort(reverse=True)
    for size, _, rva, name, moved, total, diffs in found:
        print("0x%08X %4dB  <-  %s" % (rva, size, name[:78]))
        detail = (";  " + ", ".join("0x%X->0x%X" % d for d in diffs))[:150] \
            if moved else " -- BYTE-SHAPE IDENTICAL (an ICF twin, not a discovery)"
        print("           %d of %d constants differ%s" % (moved, total, detail))
    print("\n%d shape match(es) over %d distinct row(s)"
          % (len(found), len(set(f[2] for f in found))))


if __name__ == "__main__":
    main()
