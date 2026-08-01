#!/usr/bin/env python3
"""Choose one MASM 5-byte jump thunk to convert to clean C++.

The default randomly chooses among the best-ranked distinct classes. Use
``--ranked`` to inspect the full class ranking.

Usage: python3 tools/list_thunk_dumps.py [--ranked] [--limit N]
"""
import argparse
import re
import struct
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import build
from work_selection import choose_ranked


def klass(name):
    # ctor/dtor/operator special names (??0Class@@, ??1Class@@, ??_GClass@@):
    # the owning class follows the ??<code> prefix, NOT the first @Ident@@ (which
    # is a parameter type — grouping ctors under their arg types was a real bug).
    m = re.match(r"^\?\?(?:[0-9]|_[A-Za-z])([A-Za-z][A-Za-z0-9_]*)@@", name)
    if m:
        return m.group(1)
    # normal method ?method@Class@@sig
    m = re.match(r"^\?[A-Za-z0-9_]+@([A-Za-z0-9_]+)@@", name)
    if m:
        return m.group(1)
    m = re.search(r"@([A-Za-z0-9_]+)@@", name)
    return m.group(1) if m else "(free function)"


def collect_thunks():
    thunks = []
    seen = set()
    for row in build.load_all_function_rows():
        source = row.get("source", "")
        if "masm_dumps" not in source or row.get("status") != "matched":
            continue
        if not (build.ROOT / source).is_file():
            continue
        try:
            rva, size = int(row["target_rva"], 16), int(row["target_size"])
        except (ValueError, KeyError, TypeError):
            continue
        if size != 5:
            continue
        try:
            body = build.read_target_bytes(rva, 5)
        except Exception:
            continue
        if body[0] != 0xE9:
            continue
        dest = (rva + 5 + struct.unpack_from("<i", body, 1)[0]) & 0xFFFFFFFF
        identity = (row["name"], rva, source)
        if identity in seen:
            continue
        seen.add(identity)
        thunks.append({"class": klass(row["name"]), "name": row["name"],
                       "source": source, "rva": rva, "dest": dest})
    return thunks


def ranked_thunks(thunks):
    by_class = {}
    for item in thunks:
        by_class.setdefault(item["class"], []).append(item)
    for items in by_class.values():
        items.sort(key=lambda item: (item["name"], item["rva"], item["source"]))
    groups = sorted(by_class.items(), key=lambda pair: (-len(pair[1]), pair[0]))
    return [item for _, items in groups for item in items], groups


def select_thunk(thunks, root=build.ROOT):
    ranked, _ = ranked_thunks(thunks)
    return choose_ranked(
        ranked, lambda item: item["class"],
        lambda item: (item["name"], item["rva"], item["source"]),
        "thunk-dumps", root)


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--ranked", action="store_true",
                    help="show the complete class ranking for humans/debugging")
    ap.add_argument("--limit", type=int, default=40,
                    help="max classes with --ranked (default 40)")
    args = ap.parse_args()

    thunks = collect_thunks()
    _, groups = ranked_thunks(thunks)
    if not args.ranked:
        selected, meta = select_thunk(thunks)
        if selected is None:
            print("No validated convertible thunk-dumps remain.")
            return
        class_size = sum(1 for item in thunks if item["class"] == selected["class"])
        print("== selected convertible thunk ==")
        print(f"  randomized across {meta['pool_groups']} top-ranked class group(s)")
        print(f"  class:       {selected['class']} ({class_size} thunk(s) remain)")
        print(f"  symbol:      {selected['name']}")
        print(f"  dump:        {selected['source']}")
        print(f"  retail:      0x{selected['rva']:06X} -> body 0x{selected['dest']:06X}")
        print("  action: write this body's C++, repoint this row, delete this dump, "
              "then byte-verify its source file")
        return

    print(f"{len(thunks)} convertible thunk-dumps across {len(groups)} classes "
          f"(body = the jump target clean C++ must reproduce):\n")
    for cls, items in groups[:args.limit]:
        example = items[0]
        print(f"  {cls:32} {len(items):3}  e.g. {example['name'][:48]} "
              f"-> 0x{example['dest']:06X}")
    if thunks:
        print("\nConvert one: write its body's C++, repoint the row to your .cpp, "
              "delete the .asm, then `./build.sh <file>` to byte-verify.")


if __name__ == "__main__":
    main()
