#!/usr/bin/env python3
"""Re-key object-symbol=$L rows positionally after an edit renumbers them.

A row keyed to a compiler-generated label finds its body by that label, and the
number depends on how much code precedes it in the translation unit. So any
edit that adds or removes code renumbers it and build.py stops with

    ValueError: symbol not found in object: $L64293

which reads like a broken checkout and is really a layout change doing its job.
There are 1,367 such rows across 503 translation units, so this is the standing
obstacle in front of every header and shim change.

`tools/relabel.py` repairs the easy case by matching bytes, and correctly gives
up on the rest: funclets share a prologue and their one distinguishing operand
is a masked rel32, so several candidates match and it reports AMBIGUOUS.

Position survives renumbering even when bytes cannot tell the labels apart. The
compiler emits them in a fixed order, so the nth $L symbol of a given size
before the edit is the nth of that size after it. Snapshot the label set before
the edit, apply the edit, and map across.

The corroboration to look for is a *uniform* shift: if every row moves by the
same delta, the mapping is almost certainly right. A ragged one means code was
added between the funclets and the result needs checking by hand -- and either
way `./build.sh <source>` is the thing that decides, since a wrong label either
fails to resolve or fails the byte comparison.

Usage:
  # 1. before the edit
  python3 tools/rekey_funclets.py --snapshot <source.cpp> /tmp/before.json
  # 2. make the header or shim change
  # 3. after
  python3 tools/rekey_funclets.py <source.cpp> /tmp/before.json   # EDITS the ledger
  python3 tools/rekey_funclets.py <source.cpp> /tmp/before.json --dry-run
"""
import argparse
import csv
import importlib.util
import json
import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import build

_spec = importlib.util.spec_from_file_location(
    "harvest", str(Path(__file__).resolve().parent / "harvest.py"))
harvest = importlib.util.module_from_spec(_spec)
_spec.loader.exec_module(harvest)

LEDGER = build.ROOT / "reverse" / "functions.csv"


def label_sizes(source):
    """{label: body size}, in the order the compiler numbered them."""
    obj = harvest.compile_obj(build.Path(source), [])
    names = {s["name"] for s in build.read_object_symbols(obj.read_bytes())
             if s["name"].startswith("$L")}
    sizes = {}
    for name in sorted(names, key=lambda n: int(n[2:])):
        try:
            body, _ = build.read_object_symbol_bytes(obj, name)
        except Exception:
            continue
        sizes[name] = len(body)
    return sizes


def by_position(sizes):
    """(size, rank among labels of that size) -> label."""
    seen = {}
    out = {}
    for name in sorted(sizes, key=lambda n: int(n[2:])):
        size = sizes[name]
        rank = seen.get(size, 0)
        out[(size, rank)] = name
        seen[size] = rank + 1
    return out


def keyed_rows(source):
    rows = []
    for row in csv.DictReader(LEDGER.open(newline="", encoding="utf-8", errors="replace")):
        if row["source"].replace("\\", "/") != source:
            continue
        match = re.search(r"object-symbol=(\$L\d+)", row["notes"] or "")
        if match:
            rows.append((row["name"], match.group(1)))
    return rows


def main():
    parser = argparse.ArgumentParser(description=__doc__,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("source")
    parser.add_argument("snapshot", help="path to the before-edit label set")
    parser.add_argument("--snapshot", dest="record", action="store_true",
                        help="record the current label set instead of re-keying")
    parser.add_argument("--dry-run", action="store_true")
    args = parser.parse_args()

    source = args.source.replace("\\", "/")
    if args.record:
        sizes = label_sizes(source)
        Path(args.snapshot).write_text(json.dumps(sizes), encoding="utf-8")
        print("recorded %d labels for %s" % (len(sizes), source))
        return 0

    before = json.loads(Path(args.snapshot).read_text(encoding="utf-8"))
    after = label_sizes(source)
    old_slot, new_slot = by_position(before), by_position(after)
    mapping = {old: new_slot[key] for key, old in old_slot.items() if key in new_slot}

    rows = keyed_rows(source)
    print("labels before %d, after %d, positionally mapped %d; %d keyed row(s)"
          % (len(before), len(after), len(mapping), len(rows)))

    deltas = set()
    plan = []
    for name, old in rows:
        new = mapping.get(old)
        print("  %-16s %s -> %s" % (name, old, new or "NO MAPPING"))
        if new and new != old:
            deltas.add(int(new[2:]) - int(old[2:]))
            plan.append((name, old, new))
    if deltas:
        print("shift: " + ("uniform %+d" % deltas.pop() if len(deltas) == 1
                           else "RAGGED %s -- check by hand" % sorted(deltas)))
    if args.dry_run or not plan:
        return 0

    raw = LEDGER.read_bytes()
    for name, old, new in plan:
        needle = name.encode() + b","
        index = raw.find(needle)
        if index < 0:
            raise SystemExit("row vanished from the ledger: " + name)
        end = raw.find(b"\n", index)
        line = raw[index:end]
        if b"object-symbol=" + old.encode() not in line:
            raise SystemExit("row no longer carries %s: %s" % (old, name))
        raw = raw[:index] + line.replace(b"object-symbol=" + old.encode(),
                                         b"object-symbol=" + new.encode()) + raw[end:]
    LEDGER.write_bytes(raw)
    print("rewrote %d row(s) -- now run ./build.sh %s" % (len(plan), source))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
