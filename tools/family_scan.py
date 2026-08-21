#!/usr/bin/env python3
"""Group unclaimed retail bodies into families that ONE conversion can pay for.

A family is a set of addresses whose bodies are the same function differing
only in constants. Converting one member proves the shape; the rest land in a
single add_match_batch pass. The whole question is what "the same" means, and
this tool offers three progressively looser normal forms:

  --exact   raw bytes. Finds only families with no relocations and no varying
            field at all.

  --disp    REL32 branch displacements zeroed. A call to a FIXED target encodes
            a DIFFERENT displacement from every address, so exact grouping
            structurally cannot see relocation-bearing families -- every member
            is its own singleton. When this was first measured, on a much
            earlier ledger, masking took the queue from 11 families and 51 rows
            to 161 families and 1,614 rows.

  --operand (default) every immediate AND displacement field zeroed, using
            capstone byte offsets so opcodes, modrm register selection and
            instruction lengths stay intact. `sub ecx,0x58` and `sub ecx,0x08`
            are one shape with one varying axis, but they are not byte-identical
            and --disp leaves each a singleton -- masking displacements does not
            mask IMMEDIATES.

All three measured on the same ledger (7,183 bodies passing the filters below,
at commit 31cb443bf), so the three rows are directly comparable:

              mode        families    rows    remaining singletons
              --exact          162     348                   6,731
              --disp           384   1,017                   6,062
              --operand        727   3,280                   3,799

Looser grouping trades precision for reach and WILL produce some false
families, because an immediate can be load-bearing in the source: a 0 and a 1
need different C++. That is acceptable and not a defect. This decides only what
is worth LOOKING at; the byte gate still decides every member individually.

FILTERS, each of which exists because omitting it cost a run:
  * only unclaimed Code/gen_asm/ dump rows -- gen_small and gen_uw own theirs;
  * drop rows whose address carries a REAL (not address-derived) symbols.csv
    pin: those are tgrid territory;
  * drop ghidra=Unwind@ rows: compiler unwind residue, not function bodies;
  * require the byte AFTER the row to be 0xCC, so a PREFIX of a longer function
    cannot pass as a whole one;
  * require the body to end in a ret or a jmp, which excludes padding-terminated
    dead code;
  * EXCLUDE PREVIOUSLY-ATTEMPTED ADDRESSES ONLY AFTER GROUPING. Excluding them
    first splits a partially-attempted family into two apparently distinct
    groups -- that is exactly how 0x001EEAE0 and 0x001F35C0 were reported as
    two families of 6 and 7 when they were one family of 7.

Usage:
  python3 tools/family_scan.py [--exact|--disp|--operand] [--min-members 2]
                              [--min-size 8] [--max-size 160] [--out FILE]
"""
import argparse
import collections
import csv
import io
import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))

import build

ROOT = Path(__file__).resolve().parent.parent
ADDRESS_DERIVED = re.compile(
    r"Gen_?[0-9A-Fa-f]{8}|gen_?[0-9A-Fa-f]{8}|Rva_?[0-9A-Fa-f]{8}|\?[bdj]_", re.I)


def mask_disp(body):
    """Zero the 4-byte displacement of every E8/E9 near branch."""
    out = bytearray(body)
    i = 0
    while i < len(out) - 4:
        if out[i] in (0xE8, 0xE9):
            out[i + 1:i + 5] = b"\0" * 4
            i += 5
        else:
            i += 1
    return bytes(out)


def mask_operands(body, md):
    """Zero every immediate and displacement field. None if it does not decode
    cleanly end to end -- a body we cannot decode is one we cannot group."""
    out = bytearray(body)
    covered = 0
    for insn in md.disasm(body, 0):
        enc = insn.encoding
        if enc.imm_size:
            lo = insn.address + enc.imm_offset
            out[lo:lo + enc.imm_size] = b"\0" * enc.imm_size
        if enc.disp_size:
            lo = insn.address + enc.disp_offset
            out[lo:lo + enc.disp_size] = b"\0" * enc.disp_size
        covered += insn.size
    return bytes(out) if covered == len(body) else None


def load_real_pins():
    pins = set()
    with io.open(ROOT / "reverse" / "symbols.csv", encoding="utf-8",
                 errors="replace") as fh:
        for i, row in enumerate(csv.reader(fh)):
            if i == 0 or len(row) < 2 or ADDRESS_DERIVED.search(row[0]):
                continue
            try:
                pins.add(int(row[1], 16))
            except ValueError:
                pass
    return pins


def load_attempted():
    seen = set()
    with io.open(ROOT / "reverse" / "re_attempts.log", encoding="utf-8",
                 errors="replace") as fh:
        for line in fh:
            for m in re.finditer(r"0x([0-9A-Fa-f]{8})", line):
                seen.add(int(m.group(1), 16))
    return seen


def candidates(min_size, max_size, real_pins):
    with io.open(ROOT / "reverse" / "functions.csv", encoding="utf-8") as fh:
        for i, row in enumerate(csv.reader(fh)):
            if i == 0 or len(row) != 7:
                continue
            name, _, rva_s, size_s, src, _, notes = row
            if not src.startswith("Code/gen_asm/"):
                continue
            size = int(size_s)
            if not (min_size <= size <= max_size) or "Unwind@" in notes:
                continue
            rva = int(rva_s, 16)
            if rva not in real_pins:
                yield name, rva, size


def main():
    ap = argparse.ArgumentParser(
        description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    g = ap.add_mutually_exclusive_group()
    g.add_argument("--exact", action="store_const", dest="mode", const="exact")
    g.add_argument("--disp", action="store_const", dest="mode", const="disp")
    g.add_argument("--operand", action="store_const", dest="mode", const="operand")
    ap.add_argument("--min-members", type=int, default=2)
    ap.add_argument("--min-size", type=int, default=8)
    ap.add_argument("--max-size", type=int, default=160)
    ap.add_argument("--out", type=Path)
    ap.add_argument("--top", type=int, default=30)
    ap.set_defaults(mode="operand")
    args = ap.parse_args()

    md = None
    if args.mode == "operand":
        import capstone
        md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
        md.detail = True

    real_pins = load_real_pins()
    attempted = load_attempted()

    groups = collections.defaultdict(list)
    scanned = undecoded = 0
    for name, rva, size in candidates(args.min_size, args.max_size, real_pins):
        try:
            window = build.read_target_bytes(rva, size + 1)
        except Exception:
            continue
        if len(window) != size + 1 or window[size] != 0xCC:
            continue                       # must END at padding
        body = window[:size]
        if body[-1] not in (0xC3, 0xC2, 0xE9, 0xEB) and body[-2:-1] != b"\xff":
            continue                       # must end in a ret or a jmp
        scanned += 1
        if args.mode == "exact":
            key = body
        elif args.mode == "disp":
            key = mask_disp(body)
        else:
            key = mask_operands(body, md)
            if key is None:
                undecoded += 1
                continue
        groups[key].append((rva, size, name))

    families = []
    for key, members in groups.items():
        if len(members) < args.min_members:
            continue
        fresh = [m for m in members if m[0] not in attempted]   # AFTER grouping
        if fresh:
            families.append((len(members), len(fresh), key, members, fresh))
    families.sort(reverse=True, key=lambda f: f[1])
    singletons = sum(1 for m in groups.values()
                     if len(m) == 1 and m[0][0] not in attempted)

    print("mode=%s  bodies scanned: %d%s" % (
        args.mode, scanned,
        "  (undecodable, skipped: %d)" % undecoded if undecoded else ""))
    print("families >= %d with unattempted members: %d"
          % (args.min_members, len(families)))
    print("unattempted rows reachable: %d" % sum(f[1] for f in families))
    print("unattempted singletons (regex-sweep territory): %d" % singletons)

    if args.out:
        with io.open(args.out, "w", encoding="utf-8") as out:
            for total, fresh_n, key, members, fresh in families:
                out.write("=== %d members (%d unattempted), %dB, anchor 0x%08X\n"
                          "normal: %s\nmembers: %s\n\n"
                          % (total, fresh_n, members[0][1], fresh[0][0], key.hex(),
                             " ".join("0x%08X" % a for a, _, _ in fresh)))
        print("written: %s" % args.out)

    print("\nTOP %d:" % args.top)
    for total, fresh_n, _, members, fresh in families[:args.top]:
        print("  0x%08X  %3dB  %4d fresh / %4d total"
              % (fresh[0][0], members[0][1], fresh_n, total))


if __name__ == "__main__":
    main()
