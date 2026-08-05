#!/usr/bin/env python3
"""Diff our class layout against retail's, field by field, for any INI block.

Retail and our source both carry the *same* `FieldParse` table for a block --
the same tokens in the same order, each paired with an `offsetof` into the class.
Retail's copy is plain data and `docs/ini_schema.md` already has it decoded.
Ours is a COMDAT in the compiled object. Line the two up by token and the
result is an exact per-member layout diff, which is what class reconstruction
has otherwise been doing by hand: one offset read off one instruction, a pad,
and a walk-back when the pad breaks a matched row.

The offsets come out of the object rather than the source because the source
only says `offsetof(WeaponTemplate, m_attackRange)` -- the number is whatever
the headers in force at compile time produce, shims included, which is exactly
the number worth comparing. Tokens come from the source, because in an object
file the token slot of every live entry is a zeroed pointer with a relocation
over it. That also gives the terminator test: the NULL entry ending the table
is the first one with no relocation on its token.

What a difference means, and what it does not. A field the table places at a
different offset is a real defect in our layout -- but the fix is not
necessarily "grow the member before it". The table only names fields the INI
parser writes, so runtime-only members between them are unconstrained, and the
existing matched rows still decide between an insert, a pad and a relocation
(see the CommandButton and Object entries in docs/lessons.md).

Usage:
  python3 tools/ini_layout_diff.py Code/.../Weapon.cpp Weapon
  python3 tools/ini_layout_diff.py Code/.../Weapon.cpp Weapon --table '?The...@@'
"""
import argparse
import importlib.util
import re
import struct
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import build

_spec = importlib.util.spec_from_file_location("harvest", str(Path(__file__).resolve().parent / "harvest.py"))
harvest = importlib.util.module_from_spec(_spec)
_spec.loader.exec_module(harvest)

ENTRY = 16          # { const char *token; proc; const void *userData; Int offset; }
OFFSET_IN_ENTRY = 12
SCHEMA = build.ROOT / "docs" / "ini_schema.md"


def retail_offsets(block):
    """token -> offset, from the decoded retail FieldParse table."""
    text = SCHEMA.read_text(encoding="utf-8", errors="replace")
    match = re.search(r"^### `" + re.escape(block) + r"`$(.*?)(?=^### `|\Z)",
                      text, re.MULTILINE | re.DOTALL)
    if not match:
        raise SystemExit(f"no `### \\`{block}\\`` section in docs/ini_schema.md")
    found = {}
    for token, offset in re.findall(r"^\|\s*`([^`]+)`\s*\|\s*`(0x[0-9A-Fa-f]+)`\s*\|",
                                    match.group(1), re.MULTILINE):
        found[token] = int(offset, 16)
    return found


def source_tokens(source, table_symbol):
    """The table's tokens in declaration order, read from the .cpp."""
    text = Path(source).read_text(encoding="utf-8", errors="replace")
    # the table's own name as it appears in the source, e.g. TheWeaponTemplateFieldParseTable
    bare = re.search(r"\?([A-Za-z_][A-Za-z0-9_]*)@", table_symbol)
    name = bare.group(1) if bare else "FieldParseTable"
    start = text.find(name)
    while start != -1 and "[]" not in text[start:start + 200]:
        start = text.find(name, start + 1)
    if start == -1:
        raise SystemExit(f"could not find the {name} array in {source}")
    brace = text.find("{", start)
    depth, i = 0, brace
    while i < len(text):
        if text[i] == "{":
            depth += 1
        elif text[i] == "}":
            depth -= 1
            if depth == 0:
                break
        i += 1
    return re.findall(r'\{\s*"([^"]+)"', text[brace:i])


def main():
    parser = argparse.ArgumentParser(description=__doc__,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("source")
    parser.add_argument("block", help="the INI block name as docs/ini_schema.md spells it")
    parser.add_argument("--table", help="field-table symbol, if the source has more than one")
    args = parser.parse_args()

    retail = retail_offsets(args.block)

    obj = harvest.compile_obj(build.Path(args.source), [])
    # The table is sometimes a class static and sometimes a function-local one,
    # so match on the data symbol rather than on a naming convention, and drop
    # the accessor and the INI entry point that share the substring.
    symbols = [s["name"] for s in build.read_object_symbols(obj.read_bytes())
               if "FieldParse" in s["name"] and s["section"] > 0
               and not s["name"].startswith(("?getFieldParse@", "?initFromINI@"))]
    if args.table:
        symbols = [s for s in symbols if args.table in s]
    if len(symbols) != 1:
        raise SystemExit("expected one field table, found: " + (", ".join(symbols) or "none")
                         + "\nnarrow it with --table")
    table_symbol = symbols[0]

    body, relocs = build.read_object_symbol_bytes(obj, table_symbol)
    relocated = {off: name for off, _, name in relocs}
    ours = []
    for index in range(len(body) // ENTRY):
        base = index * ENTRY
        if base not in relocated:        # NULL token: end of table
            break
        ours.append((relocated[base],
                     struct.unpack_from("<i", body, base + OFFSET_IN_ENTRY)[0]))

    # Take each entry's token from the string the token slot relocates to, not from
    # the source. Any table with a conditional entry has fewer live entries in the
    # object than tokens in the .cpp, and lining the two up by position then pairs
    # every field after the gap with the wrong offset -- silently, which is worse
    # than refusing. The object is self-describing here, so use it.
    pairs = []
    for literal, offset in ours:
        try:
            text, _ = build.read_object_symbol_bytes(obj, literal)
        except ValueError:
            pairs = []
            break
        pairs.append((text.split(b"\0")[0].decode("ascii", "replace"), offset))

    if pairs:
        tokens_ours = pairs
    else:
        # No usable string symbols (some toolchains emit the literals unnamed);
        # fall back to the source order, which is only safe when the counts agree.
        tokens = source_tokens(args.source, table_symbol)
        if len(tokens) != len(ours):
            raise SystemExit(f"{len(tokens)} tokens in the source but {len(ours)} live entries "
                             "in the object, and the token strings could not be read back from "
                             "the object either -- nothing safe to line up on")
        tokens_ours = list(zip(tokens, (offset for _, offset in ours)))

    print(f"{args.block}: {len(tokens_ours)} fields in our table, {len(retail)} in retail's\n")
    agree = missing = 0
    diffs = []
    for token, offset in tokens_ours:
        if token not in retail:
            missing += 1
            continue
        if retail[token] == offset:
            agree += 1
        else:
            diffs.append((token, offset, retail[token]))

    if diffs:
        print("%-38s %8s %8s %8s" % ("field", "ours", "retail", "delta"))
        for token, mine, theirs in sorted(diffs, key=lambda d: d[1]):
            print("%-38s %8s %8s %+8d" % (token, hex(mine), hex(theirs), theirs - mine))
    extra = sorted(set(retail) - {t for t, _ in tokens_ours}, key=lambda t: retail[t])
    if extra:
        print(f"\nfields retail parses that our table does not ({len(extra)}) -- "
              "these are the BFME additions, and where the offsets above came from:")
        for token in extra:
            print("  %-38s %s" % (token, hex(retail[token])))

    print(f"\nagree: {agree}   differ: {len(diffs)}   "
          f"not in retail's table: {missing}   only in retail's: {len(extra)}")
    return 1 if diffs else 0


if __name__ == "__main__":
    raise SystemExit(main())
