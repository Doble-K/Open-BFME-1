#!/usr/bin/env python3
"""Split ONE gen-dump scaffold PROC into adjacent PROCs at a byte boundary.

This is an EXTENSION of tools/gen_dump.py's --asm emission path, not a hand
edit of its output: it reuses gen_dump's own ASM_PROC template and asm_db
byte-formatter to re-render exactly one PROC block as several PROCs, byte for
byte identical in aggregate, just relabelled at the cut point(s). Everything
else in the .asm file is untouched (verified by diff before/after).

Why this exists: `add_match --replace-rva` retires a scaffold only on an EXACT
start-address match, and a gen_asm .asm file defines exactly one object
symbol per scaffold row spanning that row's whole byte range. A twin sitting
at a sub-range inside a scaffold can never satisfy an exact match as long as
only one symbol covers the whole range. Hand-splitting the LEDGER row alone
(tried previously) is unsound -- the tail row names a symbol the .asm never
emits, and byte-verify fails with "symbol not found in object". The fix has
to happen at the SOURCE: regenerate the .asm so the object actually contains
a symbol starting at the twin's address.

Usage:
  python3 tools/split_scaffold.py <old_rva_hex> <cut_rva_hex>[,<cut_rva_hex>...]

<old_rva_hex> must be the target_rva of exactly one gen-dump scaffold row
(status=matched, notes starts with "gen-dump", source under Code/gen_asm/).
Each <cut_rva_hex> must fall strictly inside (old_rva, old_rva+size) and cuts
are applied in address order, producing len(cuts)+1 adjacent scaffold rows.
The FIRST piece keeps the original row's name (same start RVA); later pieces
mint new `?d_<rva>@@YAXXZ` names the normal gen-dump way.

A split does not RETIRE the head row: nothing about the piece starting at
old_rva is deleted, so nothing is tombstoned in reverse/deleted_rows.csv (left
untouched) and the row is never dropped. Its ledger line is rewritten IN
PLACE, byte-identical except the size field narrows to the head piece's own
width -- same name (`?d_<old_rva>@@YAXXZ`), same rva, same source/status, and
notes preserved VERBATIM. Every later piece (tail, and a middle piece too, if
the twin lands inside the scaffold rather than at either edge) is a brand new
row, appended binary/CRLF, named `?d_<piece_rva>@@YAXXZ` from ITS OWN address
the normal gen-dump way, with plain `gen-dump;ghidra=<name>` notes -- exactly
what gen_dump.py itself would have written had it dumped that address as its
own row to begin with.

This does not verify anything itself. Run tools/build.py on the touched .asm
file afterward -- compile-and-byte-verify is the only real judge.
"""
import csv
import io
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))

import build
import gen_dump
import ledger_io
from portable_lock import lock

ROOT = gen_dump.ROOT
FUNCTIONS = gen_dump.FUNCTIONS


def parse_rows(raw):
    rows = []
    for i, r in enumerate(csv.reader(io.StringIO(raw.decode("utf-8"))), start=1):
        if i == 1 or not r or (len(r) == 1 and not r[0]):
            continue
        if len(r) != 7:
            raise SystemExit(f"functions.csv line {i} has {len(r)} fields, not 7 -- "
                             "ledger looks corrupt, fix it first")
        name, export_rva, target_rva, target_size, source, status, notes = r
        rows.append({"line": i, "name": name, "export_rva": export_rva,
                     "rva": int(target_rva, 16), "size": int(target_size or 0),
                     "source": source, "status": status, "notes": notes})
    return rows


def main():
    if len(sys.argv) != 3:
        raise SystemExit(__doc__)
    old_rva = int(sys.argv[1], 16)
    cuts = sorted(int(x, 16) for x in sys.argv[2].split(","))

    # Other agents share this checkout and append to functions.csv concurrently
    # (add_match.py, gen_dump.py). Take the same exclusive lock add_match uses,
    # and re-read the ledger fresh once held, to close the read-modify-write race.
    lock_file = (ROOT / "reverse" / ".add_match.lock").open("a")
    lock(lock_file, exclusive=True,
         wait_notice="split_scaffold: waiting for ledger lock...")

    raw = FUNCTIONS.read_bytes()
    rows = parse_rows(raw)
    hits = [r for r in rows if r["rva"] == old_rva]
    if len(hits) != 1:
        raise SystemExit(f"0x{old_rva:08X}: {len(hits)} ledger rows at this address, need 1")
    row = hits[0]
    if row["status"] != "matched" or not row["notes"].lstrip().startswith("gen-dump"):
        raise SystemExit(f"0x{old_rva:08X} ({row['name']}) is not a gen-dump scaffold row: "
                         f"status={row['status']} notes={row['notes']!r}")
    if not row["source"].startswith("Code/gen_asm/"):
        raise SystemExit(f"0x{old_rva:08X} source is {row['source']!r}, not Code/gen_asm/* "
                         "-- this tool only splits .asm-emitted scaffolds")
    end = row["rva"] + row["size"]
    for c in cuts:
        if not (row["rva"] < c < end):
            raise SystemExit(f"cut 0x{c:08X} is not strictly inside "
                             f"[0x{row['rva']:08X}, 0x{end:08X})")
    bounds = [row["rva"]] + cuts + [end]
    pieces = list(zip(bounds, bounds[1:]))

    asm_path = ROOT / row["source"]
    raw_asm = asm_path.read_bytes()
    # Work in BYTES and reuse whatever line ending this file already has on
    # disk (checkout may be CRLF under core.autocrlf even though the blob
    # gen_dump.py committed is LF) -- a text-mode round-trip would silently
    # renormalize every untouched line and make the diff look like a full
    # rewrite instead of the one PROC that actually changed.
    nl = b"\r\n" if b"\r\n" in raw_asm else b"\n"
    old_name = row["name"]
    old_name_b = old_name.encode("ascii")
    proc_start_marker = b"public " + old_name_b + nl + old_name_b + b" PROC" + nl
    proc_end_marker = nl + old_name_b + b" ENDP" + nl
    start_of_public = raw_asm.index(proc_start_marker)
    # Walk back to the start of this PROC's own comment line (the line above
    # "public ..."), stopping at the previous ENDP/blank boundary so we never
    # eat a neighbour's block.
    comment_start = raw_asm.rfind(nl + b"; ghidra:", 0, start_of_public)
    if comment_start == -1:
        raise SystemExit(f"{asm_path}: no '; ghidra:' comment found above {old_name}'s PROC "
                         "-- refusing to guess the block boundary")
    comment_start += len(nl)  # skip the newline that terminates the previous block
    ghidra_line_end = raw_asm.index(nl, comment_start)
    ghidra_comment = raw_asm[comment_start:ghidra_line_end].decode("ascii")
    # "; ghidra: NAME  retail @ 0xXXXXXXXX size N" -> just NAME
    ghidra_name = ghidra_comment.split("ghidra:", 1)[1].split("retail @", 1)[0].strip()

    end_of_endp = raw_asm.index(proc_end_marker, start_of_public) + len(proc_end_marker)

    exe = build.EXE.read_bytes()
    text_section = next(s for s in build.pe_sections(exe) if s["name"] == ".text")

    def read(rva, size):
        offset = text_section["raw_pointer"] + (rva - text_section["rva"])
        return exe[offset:offset + size]

    new_block_parts = []
    new_rows = []
    for piece_start, piece_end in pieces:
        piece_size = piece_end - piece_start
        body = read(piece_start, piece_size)
        rendered = gen_dump.ASM_PROC.format(
            ghidra=ghidra_name, rva=piece_start, size=piece_size,
            db=gen_dump.asm_db(body))
        # Every piece, including the head, uses gen_dump's own naming rule --
        # named from its OWN start address. For the head that is old_name
        # itself (asserted below), so nothing here needs suffixing to dodge a
        # collision: the head's ledger row is narrowed in place, never
        # dropped, so there is no tombstoned occurrence for a live row to
        # collide with.
        piece_name = f"?d_{piece_start:08x}@@YAXXZ"
        piece_bytes = rendered.encode("ascii").replace(b"\n", nl)
        new_block_parts.append(piece_bytes)
        new_rows.append((piece_name, piece_start, piece_size))

    head_name, head_rva, head_size = new_rows[0]
    if head_name != old_name:
        raise SystemExit(f"head piece minted {head_name!r} but the row being narrowed is "
                         f"{old_name!r} -- naming mismatch, refusing to write")

    new_block = b"".join(new_block_parts)
    while new_block.startswith(nl):
        new_block = new_block[len(nl):]
    # old_block ran from the comment line through the final ENDP+nl; the
    # emitted pieces already carry their own leading blank line (ASM_PROC
    # starts with "\n"), so splice like-for-like.
    new_raw_asm = raw_asm[:comment_start] + new_block + raw_asm[end_of_endp:]
    ghidra_marker = nl + b"; ghidra:"
    if new_raw_asm.count(ghidra_marker) != raw_asm.count(ghidra_marker) - 1 + len(pieces):
        raise SystemExit("block-count sanity check failed -- refusing to write")

    # Ledger: narrow the head row IN PLACE (byte-identical apart from the size
    # field -- same name/rva/source/status, notes untouched verbatim), then
    # append the later pieces as brand-new plain gen-dump rows. Nothing is
    # dropped, so reverse/deleted_rows.csv is never touched.
    old_rva_field = f"0x{old_rva:08X}".encode("ascii")
    old_name_b = old_name.encode("ascii")
    new_size_field = str(head_size).encode("ascii")
    rewritten, matched = [], 0
    for payload, term in ledger_io.split_records(raw):
        # 7 fields, comma-joined; notes (the last field) is the only one that
        # could in principle contain a literal comma, but the earlier len==7
        # csv-parse check already proved it doesn't for this row, so a plain
        # bytes split-on-comma round-trips every untouched field exactly.
        parts = payload.split(b",", 6)
        if (len(parts) == 7 and parts[0] == old_name_b and parts[2] == old_rva_field):
            parts[3] = new_size_field
            payload = b",".join(parts)
            matched += 1
        rewritten.append(payload + term)
    if matched != 1:
        raise SystemExit(f"expected to narrow exactly 1 row, matched {matched} -- aborting, "
                         "no files written")
    narrowed = b"".join(rewritten)

    # Later pieces carry the SPLIT ROW'S OWN NOTES VERBATIM, exactly as the
    # narrowed head does. Synthesising `gen-dump;ghidra=<name>` from the .asm's
    # "; ghidra:" comment instead is wrong, and was caught corrupting provenance:
    # a scaffold whose notes read `gen-dump;bounds=high` has a comment reading
    # "; ghidra: bounds-high", so the synthesised form emitted
    # `gen-dump;ghidra=bounds-high` -- asserting that Ghidra named a function
    # "bounds-high" when it had named nothing at all. 62 rows were minted that
    # way in a single run. A split changes an EXTENT, never provenance: every
    # piece came out of the same dump and inherits the same claim about where it
    # came from.
    new_ledger_rows = "".join(
        f"{name},{row['export_rva']},0x{rva:08X},{size},{row['source']},matched,"
        f"{row['notes']}\r\n"
        for name, rva, size in new_rows[1:]
    ).encode("ascii")

    # Write .asm first (cheap to redo), then the ledger (narrowed+appended,
    # atomic per file). No tombstone -- nothing was deleted.
    asm_path.write_bytes(new_raw_asm)
    FUNCTIONS.write_bytes(narrowed + new_ledger_rows)

    print(f"split {old_name} @ 0x{old_rva:08X} size {row['size']} into {len(pieces)} piece(s):")
    for name, rva, size in new_rows:
        print(f"  {name} @ 0x{rva:08X} size {size}")
    print(f"asm: {asm_path.relative_to(ROOT)}")
    print(f"verify: python3 tools/build.py {row['source']}")


if __name__ == "__main__":
    main()
