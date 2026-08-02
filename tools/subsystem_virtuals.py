#!/usr/bin/env python3
"""Name a subsystem's init/reset/update from its vtable, using the class its
deleting destructor already names.

Every SubsystemInterface vtable is identifiable: BFME inserted
?loadIniFilesFromLegend@SubsystemInterface@@UAE_NXZ into the base class, and it
lands at slot 2 in all 147 of them. Slot 0 is the deleting destructor, whose
decorated name is ??_G<Class>@@UAEPAXI@Z -- so wherever that slot is already
matched, the vtable tells you the class outright.

The remaining question is which slot is which, and Zero Hour's header cannot
answer it because loadIniFilesFromLegend was inserted into the middle of the
base class's virtuals, shifting everything after it. The image answers instead:
SubsystemLegend's own vtable has ?init@SubsystemLegend@@, ?reset@SubsystemLegend@@
and ?update@SubsystemLegend@@ already matched at slots 1, 4 and 5, and PlayerList
and TeamFactory independently put reset at slot 4.

So for any vtable whose slot 0 names a class, slots 1, 4 and 5 are that class's
init, reset and update. That is a name derived from two matched rows rather than
from a guess.

Two targets are dropped rather than reported. Anything reached from more than
two different classes is a shared stub rather than a per-class virtual --
_purecall at 0x0088C500 is the clear case, sitting at slots 1, 4 and 5 of every
abstract subsystem's vtable at once.

A caution the output makes explicit: many of these are one byte, a bare ret. A
one-byte row byte-verifies against every empty function in the image, so it
proves the address and nothing else -- fine when the vtable slot is the evidence,
worthless as independent confirmation. Sizes are printed so you can tell which
is which.

Usage:
  python3 tools/subsystem_virtuals.py            # unclaimed slots, by size
  python3 tools/subsystem_virtuals.py --all      # include already-claimed
"""
import argparse
import re
import struct
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import dump_ini_schema as S

# The base-class virtual that identifies a SubsystemInterface vtable, and the
# slot it occupies in every one of them.
LEGEND_RVA = 0x009A1A50
LEGEND_SLOT = 2
MIN_EXPECTED_VTABLES = 100

# Proven from SubsystemLegend's own vtable; see the module docstring.
SLOT_NAMES = {1: "init", 4: "reset", 5: "update"}

_DTOR_RE = re.compile(r"^\?\?_G([A-Za-z_][A-Za-z0-9_]*)@@")


def find_vtables(img):
    """Every VA whose slot 2 is loadIniFilesFromLegend."""
    needle = struct.pack("<I", LEGEND_RVA + S.IMAGE_BASE)
    out = []
    for sec in img.secs:
        body = img.data[sec["raw_pointer"]:sec["raw_pointer"] + sec["size"]]
        i = body.find(needle)
        while i != -1:
            out.append(S.IMAGE_BASE + sec["rva"] + i - LEGEND_SLOT * 4)
            i = body.find(needle, i + 1)
    return out


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--all", action="store_true", help="include already-claimed slots")
    args = ap.parse_args()

    img = S.Image()
    owner = S.load_ledger()
    vtables = find_vtables(img)
    if len(vtables) < MIN_EXPECTED_VTABLES:
        raise SystemExit(
            f"subsystem_virtuals: found only {len(vtables)} SubsystemInterface "
            f"vtables, expected >= {MIN_EXPECTED_VTABLES}. Either "
            f"loadIniFilesFromLegend moved off 0x{LEGEND_RVA:08X} or it is no "
            "longer at slot 2 -- fix this before trusting any output.")

    rows = []
    for vt in vtables:
        dtor = img.deref_thunk(
            struct.unpack("<I", bytes(img.read(vt, 4)))[0] - S.IMAGE_BASE)
        m = _DTOR_RE.match(owner(dtor) or "")
        if not m:
            continue                     # slot 0 unclaimed: nothing names the class
        cls = m.group(1)
        for slot, method in SLOT_NAMES.items():
            target = img.deref_thunk(
                struct.unpack("<I", bytes(img.read(vt + slot * 4, 4)))[0] - S.IMAGE_BASE)
            have = owner(target)
            if have and not args.all:
                continue
            rows.append((img.body_size(target) or 0, cls, method, target, have))

    # A target reached from several different classes' slots is a shared stub,
    # not any one class's virtual. 0x0088C500 is the clear case: it is _purecall
    # -- it calls the terminate handler -- and it sits at slots 1, 4 AND 5 of
    # every abstract subsystem's vtable. Naming it ?init@GameTextInterface@@ and
    # ?reset@CDManagerInterface@@ and so on would be three wrong claims from one
    # reading, so anything used by more than two classes is dropped.
    users = {}
    for _size, cls, _method, target, _have in rows:
        users.setdefault(target, set()).add(cls)
    shared = {t for t, c in users.items() if len(c) > 2}
    rows = [r for r in rows if r[3] not in shared]

    rows.sort(reverse=True)
    print(f"{len(vtables)} SubsystemInterface vtables; "
          f"{len(rows)} slots to report\n")
    print(f"{'size':>6}  {'address':<12} symbol")
    for size, cls, method, target, have in rows:
        mark = "  (claimed)" if have else ""
        print(f"{size:>6}  0x{target:08X}   ?{method}@{cls}@@UAEXXZ{mark}")
    trivial = sum(1 for r in rows if r[0] <= 1)
    print(f"\n{trivial} of {len(rows)} are one byte or less -- a bare ret, which "
          "matches every empty function in the image, so the vtable slot is the "
          "only evidence for those.")


if __name__ == "__main__":
    main()
