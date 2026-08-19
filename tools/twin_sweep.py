#!/usr/bin/env python3
"""ICF-twin candidate sweep -- corpus-wide.

A twin is an ALREADY-MATCHED body whose exact bytes ALSO occur at an address
nothing has claimed (or that holds only a gen-dump scaffold). The second
address is claimable as a gen-alias row via tools/add_match.py. This tool
finds every such occurrence in one deterministic pass and persists the
candidate list to disk so it survives between agent runs -- a previous sweep
lived only in a scratch directory and was lost entirely when its agent
finished; this is the permanent replacement.

Pipeline (matches the project's twin-lane convention exactly):
  1. Stream reverse/functions.csv for MATCHED, non-scaffold, non-blocked rows
     sized 8 to 64 bytes. Eight is the real floor: add_match's masked path
     enforces MIN_LIB_CONCRETE = 8 concrete (non-relocation) bytes.
  2. Read each body's retail bytes and index by exact content, collapsing
     duplicates (many rows share one body via identical-code folding).
  3. ONE Aho-Corasick pass over the whole retail .text section finds every
     occurrence of every indexed body.
  4. Keep occurrences at addresses functions.csv leaves UNCLAIMED, or that
     hold only a gen-dump scaffold row. De-duplicate self-overlaps (an
     occurrence at the body's own claimed address is dropped by the
     unclaimed-address filter automatically).
  5. Re-verify each surviving candidate with an INDEPENDENT byte read (a
     fresh build.read_target_bytes call at both addresses) before writing it
     out -- the indexing pass's own copy is never reused for verification.

Output: reverse/twin_candidates.csv (or --out), columns:
  twin_rva, size, source, object_symbol, slot_state
where slot_state is "unclaimed" or "scaffold" and object_symbol is the
mangled name of the already-matched body the twin duplicates.

Usage:
  python3 tools/twin_sweep.py
  python3 tools/twin_sweep.py --min-rva 0x00000000 --max-rva 0x00300000
  python3 tools/twin_sweep.py --out reverse/twin_candidates_lo.csv --min-rva 0 --max-rva 0x300000
"""
import argparse
import csv
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import build as B

ROOT = B.ROOT
FUNCTIONS_CSV = ROOT / "reverse" / "functions.csv"
DEFAULT_OUT = ROOT / "reverse" / "twin_candidates.csv"

MIN_SIZE = 8
MAX_SIZE = 64

BLOCKED_SOURCE_SUBSTRINGS = [
    "gen_small", "gen_asm", "reference/", "vendored", "d3dx9", "libc",
    "comsupp", "meshmatdesc.cpp", "mem_ops.cpp", "memory_pool.cpp",
    "v3_rnd.cpp", "fx_particle_system_bulk.cpp",
    "fx_particle_system_category_accessors.cpp",
]


def is_blocked_source(source):
    low = source.replace("\\", "/").lower()
    return any(sub.lower() in low for sub in BLOCKED_SOURCE_SUBSTRINGS)


def load_ledger_rows(path):
    rows = []
    with open(path, "r", encoding="utf-8", newline="") as f:
        for row in csv.DictReader(f):
            try:
                rva = int(row["target_rva"], 16)
                size = int(row["target_size"])
            except (ValueError, KeyError):
                continue
            row["_rva"] = rva
            row["_size"] = size
            rows.append(row)
    return rows


class ClaimIndex:
    """Answers "is this RVA unclaimed / scaffold-only / claimed?" for the
    whole functions.csv ledger, regardless of row status -- a claim is a
    claim whether or not it is byte-verified yet."""

    def __init__(self, rows):
        # Sorted list of (start, end, is_scaffold) for interval queries.
        intervals = []
        for row in rows:
            if row["_size"] <= 0:
                continue
            intervals.append((row["_rva"], row["_rva"] + row["_size"],
                               B.is_scaffold_row(row), row))
        intervals.sort(key=lambda t: t[0])
        self.intervals = intervals

    def query(self, start, end):
        """Return the list of overlapping (start, end, is_scaffold, row) tuples."""
        # Linear-ish binary search entry point; intervals are non-overlapping
        # in the matched ledger except for known ICF groups, so a small local
        # scan from the first candidate is sufficient and fast in practice.
        import bisect
        starts = [iv[0] for iv in self.intervals]
        i = bisect.bisect_right(starts, start)
        i = max(0, i - 4)
        hits = []
        while i < len(self.intervals) and self.intervals[i][0] < end:
            s, e, scaf, row = self.intervals[i]
            if s < end and start < e:
                hits.append(self.intervals[i])
            i += 1
        return hits

    def slot_state(self, start, end):
        """None if the span collides with a real (non-scaffold) claim, else
        'unclaimed' or 'scaffold'."""
        hits = self.query(start, end)
        if not hits:
            return "unclaimed"
        if all(h[2] for h in hits):
            return "scaffold"
        return None


def object_symbol_of(row):
    notes = row.get("notes", "")
    for part in notes.split(";"):
        if part.startswith("object-symbol="):
            return part[len("object-symbol="):]
    return row["name"]


def build_candidate_bodies(rows, min_size, max_size):
    """Index unique bodies among matched, non-scaffold, non-blocked,
    in-size-range rows. Returns {body_bytes: [(size, source, object_symbol)]}."""
    by_body = {}
    for row in rows:
        if row.get("status") != "matched":
            continue
        if B.is_scaffold_row(row):
            continue
        size = row["_size"]
        if size < min_size or size > max_size:
            continue
        source = row.get("source", "")
        if is_blocked_source(source):
            continue
        body = B.read_target_bytes(row["_rva"], size)
        if len(body) != size:
            continue
        by_body.setdefault(body, []).append((size, source, object_symbol_of(row), row["_rva"]))
    return by_body


def sweep_text(by_body):
    """One Aho-Corasick pass over the full retail .text section.

    Returns list of (occurrence_rva, body_bytes).
    """
    import ahocorasick

    data = B.EXE.read_bytes()
    sections = B.pe_sections(data)
    text = next(s for s in sections if s["name"] == ".text")
    lo_rva, size, raw = text["rva"], text["size"], text["raw_pointer"]
    chunk = data[raw:raw + size]

    # pyahocorasick's Automaton keys on str, not bytes. latin-1 is a 1:1
    # byte<->codepoint mapping so this is lossless and the search is still
    # exact-byte matching under the hood.
    text_str = chunk.decode("latin-1")

    automaton = ahocorasick.Automaton()
    for body in by_body:
        key = body.decode("latin-1")
        automaton.add_word(key, body)
    automaton.make_automaton()

    occurrences = []
    for end_index, body in automaton.iter(text_str):
        start_index = end_index - len(body) + 1
        occ_rva = lo_rva + start_index
        occurrences.append((occ_rva, body))
    return occurrences


def main():
    parser = argparse.ArgumentParser(
        description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--min-rva", default="0x0", help="lower bound (inclusive) on twin RVA, hex or decimal")
    parser.add_argument("--max-rva", default=None, help="upper bound (exclusive) on twin RVA, hex or decimal")
    parser.add_argument("--min-size", type=int, default=MIN_SIZE)
    parser.add_argument("--max-size", type=int, default=MAX_SIZE)
    parser.add_argument("--out", type=Path, default=DEFAULT_OUT)
    parser.add_argument("--no-reverify", action="store_true",
                         help="skip the independent second byte read before emitting "
                              "(debug only -- production runs must not pass this)")
    args = parser.parse_args()

    def parse_int(s):
        return int(s, 16) if s.lower().startswith("0x") else int(s)

    min_rva = parse_int(args.min_rva)
    max_rva = parse_int(args.max_rva) if args.max_rva is not None else 0xFFFFFFFF

    print(f"twin_sweep: loading ledger from {FUNCTIONS_CSV} ...", file=sys.stderr)
    rows = load_ledger_rows(FUNCTIONS_CSV)
    print(f"twin_sweep: {len(rows)} ledger rows", file=sys.stderr)

    claim_index = ClaimIndex(rows)

    by_body = build_candidate_bodies(rows, args.min_size, args.max_size)
    total_rows = sum(len(v) for v in by_body.values())
    print(f"twin_sweep: {total_rows} eligible rows collapse to {len(by_body)} unique bodies", file=sys.stderr)

    print("twin_sweep: scanning .text (one Aho-Corasick pass) ...", file=sys.stderr)
    occurrences = sweep_text(by_body)
    print(f"twin_sweep: {len(occurrences)} raw occurrences", file=sys.stderr)

    candidates = []
    seen_rva = set()
    for occ_rva, body in occurrences:
        size = len(body)
        end = occ_rva + size
        if not (min_rva <= occ_rva < max_rva):
            continue
        state = claim_index.slot_state(occ_rva, end)
        if state is None:
            continue  # collides with a real claim -- not a candidate
        # De-duplicate self-overlaps: keep only the first (largest, since
        # Aho-Corasick yields shorter matches after longer at the same
        # position only incidentally) candidate per exact (rva, size).
        key = (occ_rva, size)
        if key in seen_rva:
            continue
        seen_rva.add(key)
        # A body can be shared by several already-matched rows (identical-code
        # folding); attribute the twin to exactly ONE of them -- the first in
        # ledger order -- so a candidate is one row per occurrence, matching
        # the existing gen-alias convention of one <source> owning the name.
        orig_size, source, object_symbol, orig_rva = by_body[body][0]
        candidates.append((occ_rva, size, source, object_symbol, state, orig_rva))

    print(f"twin_sweep: {len(candidates)} candidates after unclaimed/scaffold filter", file=sys.stderr)

    if not args.no_reverify:
        print("twin_sweep: independent re-verification pass ...", file=sys.stderr)
        verified = []
        for occ_rva, size, source, object_symbol, state, orig_rva in candidates:
            # Independent second read of BOTH addresses -- do not reuse the
            # indexing pass's copy for either side.
            twin_bytes = B.read_target_bytes(occ_rva, size)
            orig_bytes = B.read_target_bytes(orig_rva, size)
            if twin_bytes != orig_bytes:
                continue
            verified.append((occ_rva, size, source, object_symbol, state, orig_rva))
        print(f"twin_sweep: {len(verified)} survive independent re-verification", file=sys.stderr)
        candidates = verified

    candidates.sort(key=lambda t: t[0])

    args.out.parent.mkdir(parents=True, exist_ok=True)
    with open(args.out, "wb") as f:
        f.write(b"twin_rva,size,source,object_symbol,slot_state\r\n")
        for occ_rva, size, source, object_symbol, state, orig_rva in candidates:
            line = f"0x{occ_rva:08X},{size},{source},{object_symbol},{state}\r\n"
            f.write(line.encode("utf-8"))

    print(f"twin_sweep: wrote {len(candidates)} candidates to {args.out}", file=sys.stderr)


if __name__ == "__main__":
    main()
