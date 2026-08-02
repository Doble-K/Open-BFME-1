#!/usr/bin/env python3
"""Try to NAME an unclaimed subsystem from the vtable its constructor installs.

`initSubsystem<T>` instantiations are byte-identical whatever T is called -- the
template only forms a `T*` and converts it to `SubsystemInterface*` -- so byte
matching one proves nothing about its name. Code/GameEngine/Source/Common/System/
game_engine_subsystems.h therefore admits a class only on real evidence:

  1. the constructor at its registration site already carries a decorated name in
     the ledger, or
  2. the vtable that constructor installs has a slot holding a function whose
     decorated name is class-specific.

Route 1 is a lookup. This tool does route 2: disassemble the constructor, find
the vptr store, walk the vtable, and report which slots the ledger can already
name. It reports evidence; it does not claim anything.

    tools/name_subsystem.py                 # every subsystem still unclaimed
    tools/name_subsystem.py TheVictorySystem

A name is only evidence if it is SPECIFIC. `??_GFileSystem@@` appearing in slot 0
of an unrelated class is ICF folding a trivial body, not a clue -- the tool marks
slots whose function is shared with other vtables so those can be discounted.
"""

import argparse
import collections
import csv
import io
import pathlib
import sys

import capstone

sys.path.insert(0, str(pathlib.Path(__file__).resolve().parent))
import build  # noqa: E402

ROOT = pathlib.Path(__file__).resolve().parent.parent
TSV = ROOT / "reverse" / "gameengine_init_subsystems.tsv"


def image_base():
    data = build.EXE.read_bytes()
    pe = build.u32(data, 0x3C)
    return build.u32(data, pe + 4 + 20 + 28)


def ledger():
    rows = list(csv.reader(io.StringIO(
        (ROOT / "reverse" / "functions.csv").read_bytes().decode("utf-8", "surrogateescape"))))
    out = {}
    for r in rows[1:]:
        if len(r) > 2:
            try:
                out.setdefault(int(r[2], 16), []).append(r[0])
            except ValueError:
                pass
    return out


def subsystems():
    for line in TSV.read_text().splitlines():
        if not line or line.startswith("#"):
            continue
        f = line.split("\t")
        if len(f) >= 5:
            yield {"name": f[0], "sizeof": f[1], "ctor": f[2], "via": f[3], "init": f[4]}


def find_vtable(ctor_rva, base):
    """The vptr store: `mov dword ptr [reg], imm32` with imm32 inside the image."""
    code = build.read_target_bytes(ctor_rva, 128)
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    md.detail = True
    for insn in md.disasm(code, ctor_rva):
        if insn.mnemonic != "mov" or len(insn.operands) != 2:
            continue
        dst, src = insn.operands
        if dst.type != capstone.x86.X86_OP_MEM or src.type != capstone.x86.X86_OP_IMM:
            continue
        if dst.mem.disp != 0:          # a vptr goes at offset 0
            continue
        va = src.imm
        if base <= va < base + 0x2000000:
            return va - base
    return None


def read_vtable(rva, base, limit=48):
    """Slots up to the first entry that is not a plausible .text pointer."""
    raw = build.read_target_bytes(rva, limit * 4)
    slots = []
    for i in range(limit):
        va = int.from_bytes(raw[i * 4:i * 4 + 4], "little")
        if not (base < va < base + 0x2000000):
            break
        slots.append(va - base)
    return slots


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("subsystem", nargs="?", help="e.g. TheVictorySystem")
    args = ap.parse_args()

    base = image_base()
    known = ledger()
    # A function sitting in many vtables is ICF-folded and names nothing.
    shared = collections.Counter()
    vtables = {}
    for s in subsystems():
        if s["via"] != "new":
            continue
        try:
            vt = find_vtable(int(s["ctor"], 16), base)
        except Exception:
            vt = None
        if vt is None:
            continue
        vtables[s["name"]] = (vt, read_vtable(vt, base))
        for f in vtables[s["name"]][1]:
            shared[f] += 1

    for s in subsystems():
        if args.subsystem and s["name"] != args.subsystem:
            continue
        claimed = int(s["init"], 16) in known
        if claimed and not args.subsystem:
            continue
        if s["via"] != "new":
            print("%-30s built by a factory -- no constructor to read" % s["name"])
            continue
        got = vtables.get(s["name"])
        if not got:
            print("%-30s ctor %s: no vptr store found in the first 128 bytes"
                  % (s["name"], s["ctor"]))
            continue
        vt, slots = got
        named = [(i, f, known[f]) for i, f in enumerate(slots) if f in known]
        specific = [n for i, f, n in named if shared[f] == 1]
        twins = [o for o, (ovt, _) in vtables.items()
                 if o != s["name"] and ovt == vt and vtables[o][0] == vt]
        print("%-30s ctor %s  vtable 0x%08X  %d slots, %d named, %d class-specific"
              % (s["name"], s["ctor"], vt, len(slots), len(named), len(specific)))
        for i, f, names in named:
            mark = "  (also in %d other vtables -- ICF, not evidence)" % (shared[f] - 1) \
                if shared[f] > 1 else "  <-- CLASS-SPECIFIC, this names it"
            print("    slot %-2d 0x%08X  %s%s" % (i, f, ", ".join(names)[:70], mark))
        if twins:
            # Same ctor and same vtable as another subsystem: there is no byte in
            # the image that tells the two apart, so route 2 can never work here.
            print("    UNNAMEABLE: shares this vtable with %s" % ", ".join(twins))
        elif not specific:
            # Only a slot unique to THIS vtable can name the class; one that
            # appears in several is shared or ICF-folded and names nothing, so
            # listing it as an unblock would send someone after a dead end.
            todo = [f for f in slots if f not in known and shared[f] == 1]
            print("    unblock by naming any one of: %s"
                  % (" ".join("0x%08X" % f for f in todo[:8]) + (" ..." if len(todo) > 8 else "")
                     if todo else "nothing -- every unnamed slot is shared with another vtable"))


if __name__ == "__main__":
    main()
