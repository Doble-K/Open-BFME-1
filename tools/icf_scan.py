#!/usr/bin/env python3
"""Elimination scan for find_gaps.py candidates -- the repo copy.

Three separate agents have rebuilt this from scratch because it only ever
lived in a scratch directory and one run lost a measured 28-candidate list
entirely. It lives here now.

For each gap from find_gaps.py's candidate list, this compiles the flanking
translation unit(s), enumerates every defined non-section COMDAT symbol they
produce, masks relocation sites by width, trims leading/trailing 0xCC from
both sides, and exact-compares against the gap's retail bytes. A candidate
symbol is then cross-checked against reverse/functions.csv by mangled NAME, by
`target=` reference, and by RVA (including gen-alias and dup_ rows) to see
whether it is already claimed somewhere else in the ledger.

    exactly one unclaimed byte-match -> CLOSED, landable with add_match
    more than one unclaimed byte-match -> TIE(n)
    matches exist but every one is already claimed -> ALL-CLAIMED
    no byte-match at all -> NO-MATCH

SECTION-TYPE FILTERING (mandatory): a .text gap cannot be occupied by a data
COMDAT. Masking a DATA COMDAT that is mostly relocations zeroes almost all of
it, so its handful of surviving bytes can coincidentally match nearly any gap
-- every spurious tie member found in the last run was a vtable (`??_7`,
.rdata) or a dynamic-initializer slot (`_$S4`/`_$S8`, .CRT$XCU). Every
candidate is filtered by its OBJECT SECTION before it is even byte-compared.

Usage:
  python3 tools/icf_scan.py --max-size 48 --min-real-bytes 1 --exclude-stub-neighbors --out reverse/icf_scan_results.csv
  python3 tools/icf_scan.py --gaps-csv some_gap_report.csv --out reverse/icf_scan_results.csv
  python3 tools/icf_scan.py --rva 0x00812340 --gap-end 0x00812360   # single gap, ad hoc
"""
import argparse
import csv
import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import build as B
import find_gaps as FG

ROOT = B.ROOT
FUNCTIONS_CSV = ROOT / "reverse" / "functions.csv"
DEFAULT_OUT = ROOT / "reverse" / "icf_scan_results.csv"

OBJECT_SYMBOL_RE = re.compile(r"(?:^|;)object-symbol=([^;]+)")
DUP_OF_RE = re.compile(r"(?:^|;)dup-of=([^;]+)")
TARGET_RE = re.compile(r"(?:^|;)target=FUN_([0-9a-fA-F]+)")


# --------------------------------------------------------------------------
# functions.csv cross-check index
# --------------------------------------------------------------------------

class LedgerIndex:
    """Everything the elimination scan needs to know is already claimed.

    Built once from reverse/functions.csv, covering every row regardless of
    status -- a claim is a claim whether or not it has been byte-verified yet,
    and a scaffold or gen-alias row still occupies the name it names.
    """

    def __init__(self, path):
        self.claimed_names = set()
        self.witness_rva = {}  # rva(int) -> [row name, ...] via target=FUN_hex
        self.rows_by_rva = {}
        with open(path, "r", encoding="utf-8", newline="") as f:
            for row in csv.DictReader(f):
                name = row.get("name", "")
                notes = row.get("notes", "")
                if name:
                    self.claimed_names.add(name)
                m = OBJECT_SYMBOL_RE.search(notes)
                if m:
                    self.claimed_names.add(m.group(1))
                m = DUP_OF_RE.search(notes)
                if m:
                    self.claimed_names.add(m.group(1))
                m = TARGET_RE.search(notes)
                if m:
                    rva = int(m.group(1), 16)
                    self.witness_rva.setdefault(rva, []).append(name)
                try:
                    rva = int(row["target_rva"], 16)
                except (ValueError, KeyError):
                    rva = None
                if rva is not None:
                    self.rows_by_rva.setdefault(rva, []).append(row)

    def is_claimed(self, symbol_name):
        return symbol_name in self.claimed_names

    def witness_for(self, gap_start):
        """functions.csv rows whose target= points exactly at this gap's start."""
        return self.witness_rva.get(gap_start, [])


# --------------------------------------------------------------------------
# gap candidate list -- reuses find_gaps.py's own logic so the two tools never
# drift; this does NOT change find_gaps.py's own CLI/output.
# --------------------------------------------------------------------------

def generate_gaps(max_size, min_gap, min_real_bytes, exclude_stub_neighbors):
    exe_data = FG.EXE_PATH.read_bytes() if FG.EXE_PATH.exists() else None
    matched = FG.stream_matched_rows(FG.FUNCTIONS_CSV)
    matched.sort(key=lambda t: t[0])
    ghidra = FG.stream_ghidra_boundaries(FG.GHIDRA_CSV)
    reloc = FG.stream_reloc_names(FG.RELOC_CSV)
    ghidra_scanner = FG.OverlapScanner(ghidra)
    reloc_scanner = FG.OverlapScanner(reloc)

    out = []
    for i in range(len(matched) - 1):
        rva0, size0, name0, src0 = matched[i]
        rva1, size1, name1, src1 = matched[i + 1]
        gap_start = rva0 + size0
        gap_end = rva1
        gap_len = gap_end - gap_start
        if gap_len < min_gap or gap_len > max_size:
            continue

        ghidra_hits_raw = ghidra_scanner.query(gap_start, gap_end)
        reloc_hits = reloc_scanner.query(gap_start, gap_end)
        unwind_hits = [h for h in ghidra_hits_raw if h[2].startswith("Unwind@")]
        ghidra_hits = [h for h in ghidra_hits_raw if not h[2].startswith("Unwind@")]
        if unwind_hits and not ghidra_hits and not reloc_hits:
            continue
        starts = sorted(set([h[0] for h in ghidra_hits] + [h[0] for h in reloc_hits]))
        if len(starts) > 1:
            continue

        if exe_data is not None:
            chunk = exe_data[gap_start:gap_end]
            real_bytes = len(chunk) - chunk.count(0xCC)
            if real_bytes < min_real_bytes:
                continue

        if exclude_stub_neighbors and FG.is_stub_name(name0) and FG.is_stub_name(name1):
            continue

        out.append({"gap_start": gap_start, "gap_end": gap_end,
                    "before_name": name0, "before_source": src0,
                    "after_name": name1, "after_source": src1})
    return out


def load_gaps_csv(path):
    out = []
    with open(path, "r", encoding="utf-8", newline="") as f:
        for row in csv.DictReader(f):
            out.append({
                "gap_start": int(row["gap_start"], 16),
                "gap_end": int(row["gap_end"], 16),
                "before_name": row.get("before_name", ""),
                "before_source": row.get("before_source", ""),
                "after_name": row.get("after_name", ""),
                "after_source": row.get("after_source", ""),
            })
    return out


# --------------------------------------------------------------------------
# per-TU COMDAT enumeration
# --------------------------------------------------------------------------

_TU_CACHE = {}


def ensure_object(source_rel, stats):
    """Return (data, sections, symbols) for source_rel's object, compiling it
    if the on-disk obj is missing or stale. Cached per source for the run."""
    if source_rel in _TU_CACHE:
        return _TU_CACHE[source_rel]
    path = ROOT / source_rel
    if not path.exists():
        stats["source_missing"] += 1
        _TU_CACHE[source_rel] = None
        return None
    obj = B.obj_path(path)
    if not obj.exists() or not B.compile_is_current(path, obj):
        try:
            print(f"icf_scan: compiling {source_rel} ...", file=sys.stderr)
            B.compile_source(path, obj)
        except SystemExit as exc:
            print(f"icf_scan: compile failed for {source_rel}: {exc}", file=sys.stderr)
            stats["compile_failed"] += 1
            _TU_CACHE[source_rel] = None
            return None
    stat = obj.stat()
    layout = B._object_layout(str(obj), stat.st_mtime_ns, stat.st_size)
    _TU_CACHE[source_rel] = layout
    return layout


def comdat_symbols(layout):
    """[(name, section_name, body_bytes, relocs)] for every defined, non-section
    COMDAT symbol in an object -- section symbols (aux-carrying, no real name)
    and undefined externs (section <= 0) are not candidates."""
    data, sections, symbols = layout
    out = []
    for sym in symbols:
        if sym["section"] <= 0 or sym["section"] > len(sections):
            continue
        if not sym["name"] or sym["aux"]:
            continue
        section = sections[sym["section"] - 1]
        start = section["raw_pointer"] + sym["value"]
        end = section["raw_pointer"] + section["raw_size"]
        if start > end or start < 0:
            continue
        body = data[start:end]
        relocs = []
        for r in range(section["reloc_count"]):
            ro = section["reloc_pointer"] + r * 10
            rva = B.u32(data, ro)
            sym_idx = B.u32(data, ro + 4)
            rtype = B.u16(data, ro + 8)
            if sym["value"] <= rva < sym["value"] + len(body):
                relocs.append((rva - sym["value"], rtype, symbols[sym_idx]["name"]))
        out.append((sym["name"], section["name"], body, relocs))
    return out


def trim_cc(data):
    """(start, end) bounding the non-0xCC core of `data`."""
    n = len(data)
    start = 0
    while start < n and data[start] == 0xCC:
        start += 1
    end = n
    while end > start and data[end - 1] == 0xCC:
        end -= 1
    return start, end


def masked_equal(a, a_relocs, b_is_target, holes):
    """Compare `a` (candidate, with its relocation offsets pre-zeroed by width)
    against `b_is_target` (retail gap bytes) with the same offsets zeroed."""
    if len(a) != len(b_is_target):
        return False
    left, right = bytearray(a), bytearray(b_is_target)
    for offset, width in holes:
        left[offset:offset + width] = b"\0" * width
        right[offset:offset + width] = b"\0" * width
    return left == right


def try_match(candidate_body, relocs, target_core):
    """True if candidate_body (trimmed to its own non-0xCC core) reloc-masked
    equals target_core (already trimmed retail bytes)."""
    c_start, c_end = trim_cc(candidate_body)
    core = candidate_body[c_start:c_end]
    if len(core) != len(target_core):
        return False
    holes = []
    for offset, rtype, _sym in relocs:
        rel_off = offset - c_start
        if 0 <= rel_off < len(core):
            width = min(B.RELOC_WIDTH.get(rtype, 4), len(core) - rel_off)
            holes.append((rel_off, width))
    return masked_equal(core, relocs, target_core, holes)


# --------------------------------------------------------------------------
# per-gap classification
# --------------------------------------------------------------------------

def scan_gap(gap, ledger, image, sections, stats):
    gap_start, gap_end = gap["gap_start"], gap["gap_end"]
    offset = B.rva_to_file_offset(sections, gap_start)
    raw_gap = image[offset:offset + (gap_end - gap_start)]
    t_start, t_end = trim_cc(raw_gap)
    target_core = raw_gap[t_start:t_end]
    match_rva = gap_start + t_start
    match_size = len(target_core)

    tus = []
    for source in {gap["before_source"], gap["after_source"]}:
        if source and (source.endswith(".cpp") or source.endswith(".c") or source.endswith(".cc")):
            tus.append(source)

    matches = []       # (symbol, source, section, claimed_bool)
    for source in tus:
        layout = ensure_object(source, stats)
        if layout is None:
            continue
        for name, section_name, body, relocs in comdat_symbols(layout):
            if not section_name.startswith(".text"):
                continue  # mandatory: a .text gap cannot be a data COMDAT
            if try_match(body, relocs, target_core):
                matches.append((name, source, section_name, ledger.is_claimed(name)))

    witnesses = ledger.witness_for(gap_start)
    unclaimed = [m for m in matches if not m[3]]

    if not matches:
        verdict = "NO-MATCH"
    elif not unclaimed:
        verdict = "ALL-CLAIMED"
    elif len(unclaimed) == 1:
        verdict = "CLOSED"
    else:
        verdict = f"TIE({len(unclaimed)})"

    return {
        "gap_start": gap_start, "gap_end": gap_end,
        "match_rva": match_rva, "match_size": match_size,
        "before_name": gap["before_name"], "before_source": gap["before_source"],
        "after_name": gap["after_name"], "after_source": gap["after_source"],
        "verdict": verdict,
        "matches": matches,
        "unclaimed": unclaimed,
        "witnesses": witnesses,
    }


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--max-size", type=int, default=48)
    ap.add_argument("--min-gap", type=int, default=1)
    ap.add_argument("--min-real-bytes", type=int, default=1)
    ap.add_argument("--exclude-stub-neighbors", action="store_true")
    ap.add_argument("--gaps-csv", type=str, default=None,
                    help="read candidates from a find_gaps.py --out CSV instead "
                         "of generating them")
    ap.add_argument("--limit", type=int, default=None,
                    help="scan only the first N candidates (for a quick pass)")
    ap.add_argument("--rva", type=str, default=None, help="scan one gap ad hoc: start RVA")
    ap.add_argument("--gap-end", type=str, default=None, help="ad hoc gap end RVA (with --rva)")
    ap.add_argument("--out", type=str, default=str(DEFAULT_OUT),
                    help="write full classification to this CSV (default: %(default)s)")
    args = ap.parse_args()

    ledger = LedgerIndex(FUNCTIONS_CSV)
    image = B.EXE.read_bytes()
    sections = B.pe_sections(image)

    if args.rva:
        if not args.gap_end:
            print("icf_scan: --rva requires --gap-end", file=sys.stderr)
            raise SystemExit(2)
        gaps = [{"gap_start": int(args.rva, 16), "gap_end": int(args.gap_end, 16),
                "before_name": "", "before_source": "", "after_name": "", "after_source": ""}]
    elif args.gaps_csv:
        gaps = load_gaps_csv(args.gaps_csv)
    else:
        print("icf_scan: generating gap candidates via find_gaps.py logic ...", file=sys.stderr)
        gaps = generate_gaps(args.max_size, args.min_gap, args.min_real_bytes,
                             args.exclude_stub_neighbors)
    print(f"icf_scan: {len(gaps)} candidate gaps", file=sys.stderr)
    if args.limit:
        gaps = gaps[: args.limit]

    stats = {}
    results = []
    for i, gap in enumerate(gaps):
        if not gap["before_source"] and not gap["after_source"] and not args.rva:
            continue
        result = scan_gap(gap, ledger, image, sections, stats)
        results.append(result)
        print(f"[{i + 1}/{len(gaps)}] 0x{result['gap_start']:08X}-0x{result['gap_end']:08X} "
              f"{result['verdict']}", file=sys.stderr)

    dist = {}
    for r in results:
        key = r["verdict"].split("(")[0]
        dist[key] = dist.get(key, 0) + 1
    print("\n=== classification distribution ===", file=sys.stderr)
    for key in ("CLOSED", "TIE", "ALL-CLAIMED", "NO-MATCH"):
        print(f"  {key}: {dist.get(key, 0)}", file=sys.stderr)
    print(f"  total inspected: {len(results)}", file=sys.stderr)
    if stats:
        print(f"  stats: {dict(stats)}", file=sys.stderr)

    out_path = Path(args.out)
    out_path.parent.mkdir(parents=True, exist_ok=True)
    with out_path.open("w", encoding="utf-8", newline="") as f:
        w = csv.writer(f)
        w.writerow(["gap_start", "gap_end", "match_rva", "match_size", "before_name", "before_source",
                    "after_name", "after_source", "verdict",
                    "winning_symbol", "winning_source", "winning_section",
                    "all_matches", "witnesses"])
        for r in results:
            winner = r["unclaimed"][0] if len(r["unclaimed"]) == 1 else None
            all_m = ";".join(f"{n}@{s}" for n, s, _sec, claimed in r["matches"])
            w.writerow([hex(r["gap_start"]), hex(r["gap_end"]), hex(r["match_rva"]), r["match_size"],
                       r["before_name"], r["before_source"], r["after_name"], r["after_source"],
                       r["verdict"],
                       winner[0] if winner else "", winner[1] if winner else "",
                       winner[2] if winner else "",
                       all_m, ";".join(r["witnesses"])])
    print(f"icf_scan: wrote {len(results)} rows to {out_path}", file=sys.stderr)

    print("\n=== CLOSED (landable) ===")
    for r in results:
        if r["verdict"] == "CLOSED":
            name, source, section = r["unclaimed"][0][:3]
            print(f"0x{r['match_rva']:08X} size={r['match_size']} (gap 0x{r['gap_start']:08X}-0x{r['gap_end']:08X}) "
                  f"{name}  <-  {source}  [{section}]")


if __name__ == "__main__":
    main()
