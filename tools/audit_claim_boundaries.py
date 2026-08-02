#!/usr/bin/env python3
"""Find ledger rows whose claimed address cannot be a function start.

A function begins on an instruction boundary. If a row's target_rva lands
*inside* an instruction of the function that contains it, the row is wrong --
there is no source you could write that would produce a body there.

This is the one ledger check that is worth running unattended, because it has
no judgement in it. Two earlier attempts at auditing rows (weakrows, conflicts)
were abandoned for flagging thousands of rows that were fine; this one flags a
row only when a clean, gap-free linear disassembly from the containing
function's start walks straight over the claimed address. Anything ambiguous --
a disassembly that desyncs, a claim in a gap between functions, a claim that is
itself a ghidra function start -- is passed over in silence.

MASM byte dumps are the reason this matters. A dump reproduces whatever bytes it
was cut from, so a dump cut from the middle of the wrong function byte-verifies
forever and the gate never notices. Worse, the bogus row's address range blocks
any honest claim on the function it was cut from.

Both instances found when this was written were exactly that:
  - ?notifyTargetOfProbe@NAT@@... claimed 0x006718BC, 28 bytes into
    sendMangledPortNumberToTarget, and blocked it;
  - ?setGameOptions@GameSpyInfo@@... claimed 0x00671686, 198 bytes into
    notifyUsersOfConnectionFailed and three bytes into one of its compares.

Exits 1 if anything is found, so it can gate.
"""
import bisect
import csv
import pathlib
import sys

ROOT = pathlib.Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "tools"))
import build

try:
    from capstone import CS_ARCH_X86, CS_MODE_32, Cs
except ImportError:
    print("audit_claim_boundaries: capstone not installed; nothing checked")
    raise SystemExit(0)

md = Cs(CS_ARCH_X86, CS_MODE_32)
data = build.EXE.read_bytes()
sections = build.pe_sections(data)

starts = {}
with (ROOT / "reverse/ghidra_functions.csv").open() as f:
    for row in csv.DictReader(f):
        starts[int(row["rva"], 16)] = int(row["size"])
keys = sorted(starts)


def boundaries_cover(owner, claim):
    """True/False if the claim is/isn't an instruction boundary; None if unsure."""
    try:
        off = build.rva_to_file_offset(sections, owner)
    except ValueError:
        return None
    blob = data[off : off + (claim - owner) + 16]
    pos = owner
    for insn in md.disasm(blob, owner):
        if insn.address != pos:
            return None  # linear decode desynced; say nothing
        if insn.address == claim:
            return True
        pos = insn.address + insn.size
        if pos > claim:
            return False  # walked straight over it
    return None


def main():
    bad = []
    with (ROOT / "reverse/functions.csv").open() as f:
        for row in csv.DictReader(f):
            try:
                rva = int(row["target_rva"], 16)
            except (ValueError, TypeError):
                continue
            if rva in starts:
                continue
            i = bisect.bisect_right(keys, rva) - 1
            if i < 0:
                continue
            owner = keys[i]
            if owner + starts[owner] <= rva:
                continue
            if boundaries_cover(owner, rva) is not False:
                continue
            try:
                size = int(row["target_size"])
            except (ValueError, TypeError):
                size = 0
            bad.append((row["name"], rva, size, owner, row["source"]))

    if not bad:
        print("audit_claim_boundaries: OK (no row claims a mid-instruction address)")
        return 0

    total = sum(b[2] for b in bad)
    print(
        f"audit_claim_boundaries: {len(bad)} row(s) claim an address that is not an "
        f"instruction boundary, covering {total} bytes that are not real\n"
    )
    for name, rva, size, owner, source in sorted(bad, key=lambda b: -b[2]):
        print(f"  {size:>5}B at 0x{rva:06X}  ({rva - owner} bytes into 0x{owner:06X})")
        print(f"        {name}")
        print(f"        {source}")
    return 1


if __name__ == "__main__":
    raise SystemExit(main())
