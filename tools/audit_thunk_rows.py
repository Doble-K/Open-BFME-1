#!/usr/bin/env python3
"""Find 5-byte thunk rows whose body is already claimed under a different name.

A ledger row of size 5 over an incremental-link thunk cannot fail. Every ILT
entry in the image is E9 xx xx xx xx, and the displacement is a REL32 the
verifier fills in from the target, so such a row byte-verifies against ANY thunk
and its name is never tested. That is the same unfalsifiable-size problem as an
over-long MASM dump (which is the retail bytes, so it matches at any length) and
a 1-byte row (a bare ret, which matches every empty function).

Two such rows were provably wrong when this was written:

  ?showBuildTooltipLayout@ControlBar@@  claimed 0x00017503, whose body is the
                                        matched ScienceStore::friend_lookupScience
  ?undoNamedMapReveal@ScriptEngine@@    claimed 0x0001019A, whose body is the
                                        matched ScriptEngine::removeNamedMapReveal

The first is what let commandButtonTooltip resolve its callee through the wrong
function, which in turn is what put ?TheControlBar@@ in the DIR32 whitelist.

READ THE OUTPUT WITH JUDGEMENT. Most hits are legitimate, because identical
function bodies are folded by the linker and a folded body has exactly one
address that several names all legitimately reach:

  * template instantiations -- the ConcreteModuleTemplate::getClass and
    ConcreteModuleClass::getInstance pairs are dozens of hits and all real;
  * trivial forwarders -- StringBase<char>::clear and AsciiString::~AsciiString
    both fold onto releaseBuffer, because that is all they do.

A hit is worth investigating when the two names could NOT have identical bodies.
That is a question about the source, not the address: look the two functions up
in the Zero Hour tree and compare them. undoNamedMapReveal does a lookup and then
more work while removeNamedMapReveal only erases, so those two cannot fold and
the row was wrong. Do that check before removing anything.

--same-class narrows it, but not by much and not for templates: a name like
??$_Construct@UEvaSideSounds@@... has no plain class to extract, so both sides
come back unknown and the hit is kept. Template instantiations are also where
most of the folding happens, so the filter removes the least interesting third
and leaves the rest. Treat the output as a worklist, not a defect list.

Usage:
  python3 tools/audit_thunk_rows.py
  python3 tools/audit_thunk_rows.py --same-class   # drops cross-class hits
"""
import argparse
import csv
import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import dump_ini_schema as S

# ??0X@@...  -> X   (constructor/destructor/operator)
# ?method@X@@... -> X
_CTOR_RE = re.compile(r"^\?\?[0-9A-Z_]([A-Za-z_][A-Za-z0-9_]*)@@")
_METH_RE = re.compile(r"^\?[A-Za-z_][A-Za-z0-9_]*@([A-Za-z_][A-Za-z0-9_]*)@@")


def class_of(name):
    """The owning class, taken from the FRONT of the decorated name.

    Searching anywhere for @word@@ finds the first parameter type instead --
    ??0AutoHealBehavior@@QAE@PAVThing@@... yields PAVThing, which then compares
    equal for every module constructor and defeats the filter entirely."""
    for rx in (_CTOR_RE, _METH_RE):
        m = rx.match(name)
        if m:
            return m.group(1)
    return None


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--same-class", action="store_true",
                    help="only report hits where both names name the same class")
    args = ap.parse_args()

    img = S.Image()
    owner = S.load_ledger()

    rows = []
    with open(S.B.ROOT / "reverse/functions.csv", newline="", encoding="utf-8") as fh:
        for r in csv.DictReader(fh):
            try:
                addr, size = int(r["target_rva"], 16), int(r["target_size"])
            except (ValueError, KeyError):
                continue
            if size == 5:
                rows.append((addr, r["name"], r.get("source", "")))

    hits = []
    for addr, name, src in rows:
        off = addr - img.tbase
        if not (0 <= off < len(img.text)) or img.text[off] != 0xE9:
            continue                       # a real 5-byte function, not a thunk
        body_name = owner(img.deref_thunk(addr))
        if not body_name or body_name == name:
            continue
        if args.same_class and class_of(name) != class_of(body_name):
            continue
        hits.append((addr, name, body_name, src))

    print(f"{len(rows)} five-byte rows; {len(hits)} whose body is claimed under "
          f"another name\n")
    for addr, name, body_name, src in hits:
        print(f"  0x{addr:08X}  row:  {name}")
        print(f"              body: {body_name}")
        if src:
            print(f"              src:  {src}")
    print("\nMost of these are linker-folded identical bodies and are correct. "
          "Before touching one, compare the two functions in the Zero Hour tree: "
          "if they could not compile to the same bytes, the row is wrong.")


if __name__ == "__main__":
    main()
