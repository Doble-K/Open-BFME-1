#!/usr/bin/env python3
"""Adjacency-gap placement tool.

Streams reverse/functions.csv, collects MATCHED rows (rva, size, name, source),
sorts by RVA, and finds every non-empty gap between consecutive matched rows.
Cross-references each gap against ghidra_functions.csv and reverse/reloc_names.csv
to count how many distinct known-function boundaries fall inside it.
Reports gaps that appear to hold exactly ONE small function (< 32 bytes by default).
"""
import csv
import sys
import argparse
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
FUNCTIONS_CSV = ROOT / "reverse" / "functions.csv"
GHIDRA_CSV = ROOT / "reverse" / "ghidra_functions.csv"
RELOC_CSV = ROOT / "reverse" / "reloc_names.csv"
EXE_PATH = ROOT / "baselines" / "bfme1" / "workshop-vanilla-1.03" / "files" / "lotrbfme.exe"


def stream_matched_rows(path):
    rows = []
    with open(path, "r", encoding="utf-8", newline="") as f:
        reader = csv.DictReader(f)
        for row in reader:
            if row.get("status") != "matched":
                continue
            try:
                rva = int(row["target_rva"], 16)
                size = int(row["target_size"])
            except (ValueError, KeyError):
                continue
            if size <= 0:
                continue
            rows.append((rva, size, row["name"], row["source"]))
    return rows


def stream_ghidra_boundaries(path):
    """Return sorted list of (rva, size, name) from ghidra_functions.csv."""
    out = []
    with open(path, "r", encoding="utf-8", newline="") as f:
        reader = csv.DictReader(f)
        for row in reader:
            try:
                rva = int(row["rva"], 16)
                size = int(row["size"])
            except (ValueError, KeyError):
                continue
            out.append((rva, size, row["name"]))
    out.sort(key=lambda t: t[0])
    return out


def stream_reloc_names(path):
    """Return sorted list of (rva, size, name) from reverse/reloc_names.csv."""
    out = []
    with open(path, "r", encoding="utf-8", newline="") as f:
        reader = csv.DictReader(f)
        for row in reader:
            try:
                rva = int(row["target_rva"], 16)
                size = int(row["target_size"])
            except (ValueError, KeyError):
                continue
            out.append((rva, size, row["name"]))
    out.sort(key=lambda t: t[0])
    return out


class OverlapScanner:
    """Two-pointer scanner over a list sorted by rva, for use against a
    monotonically-increasing sequence of query gaps (also sorted by start).
    Avoids O(gaps * list) blowup from rescanning the whole list per gap.
    """

    def __init__(self, sorted_list):
        self.list = sorted_list
        self.n = len(sorted_list)
        self.lo = 0  # index of first element that might still overlap a future gap

    def query(self, gap_start, gap_end):
        # advance lo past entries that end before gap_start
        while self.lo < self.n and self.list[self.lo][0] + self.list[self.lo][1] <= gap_start:
            self.lo += 1
        out = []
        i = self.lo
        while i < self.n and self.list[i][0] < gap_end:
            rva, size, name = self.list[i]
            if rva + size > gap_start:
                out.append((rva, size, name))
            i += 1
        return out


def is_stub_name(name: str) -> bool:
    """Heuristic: gen_asm/dtor-stub/enumerator/dup/alias rows aren't real named
    functions and gaps between two of them are almost always 0xCC alignment
    padding rather than a missing function."""
    if name.startswith("_$E"):
        return True
    if name.startswith("?d_0") or name.startswith("?a_0"):
        return True
    if name.startswith("uw_0") or name.startswith("uw_gen"):
        return True
    if "dup_" in name or "Gen_dtor" in name:
        return True
    return False


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--max-size", type=int, default=32,
                     help="report gaps at/under this length as candidates for a single function")
    ap.add_argument("--min-gap", type=int, default=1,
                     help="ignore gaps smaller than this many bytes (default 1 = any non-empty gap)")
    ap.add_argument("--out", type=str, default=None, help="write full gap report CSV here")
    ap.add_argument("--min-real-bytes", type=int, default=1,
                     help="require at least this many non-0xCC bytes in the gap (filters pure padding)")
    ap.add_argument("--exclude-stub-neighbors", action="store_true",
                     help="drop gaps flanked by gen_asm/dup_/alias/_$E stub rows on BOTH sides "
                          "(those gaps are almost always alignment padding, not real functions)")
    args = ap.parse_args()

    exe_data = None
    if EXE_PATH.exists():
        print(f"Loading retail exe from {EXE_PATH} ...", file=sys.stderr)
        exe_data = EXE_PATH.read_bytes()
    else:
        print(f"WARNING: retail exe not found at {EXE_PATH}; skipping padding-byte filter", file=sys.stderr)

    print(f"Loading matched rows from {FUNCTIONS_CSV} ...", file=sys.stderr)
    matched = stream_matched_rows(FUNCTIONS_CSV)
    matched.sort(key=lambda t: t[0])
    print(f"  {len(matched)} matched rows", file=sys.stderr)

    print(f"Loading ghidra boundaries from {GHIDRA_CSV} ...", file=sys.stderr)
    ghidra = stream_ghidra_boundaries(GHIDRA_CSV)
    print(f"  {len(ghidra)} ghidra function rows", file=sys.stderr)

    print(f"Loading reloc_names from {RELOC_CSV} ...", file=sys.stderr)
    reloc = stream_reloc_names(RELOC_CSV)
    print(f"  {len(reloc)} reloc_names rows", file=sys.stderr)

    # Also index matched rows by rva to know which addresses are already claimed,
    # so we can exclude them from ghidra/reloc overlap counts within the gap
    # (a matched row's own successor gap starts right after it, but overlapping
    # boundary entries in ghidra/reloc that duplicate an already-matched row
    # elsewhere should not be double counted; in practice gaps by definition
    # exclude matched ranges already).

    all_gaps = []
    unambiguous = []

    ghidra_scanner = OverlapScanner(ghidra)
    reloc_scanner = OverlapScanner(reloc)

    for i in range(len(matched) - 1):
        rva0, size0, name0, src0 = matched[i]
        rva1, size1, name1, src1 = matched[i + 1]
        gap_start = rva0 + size0
        gap_end = rva1
        gap_len = gap_end - gap_start
        if gap_len < args.min_gap:
            continue
        # alignment of gap start
        align = 16 if gap_start % 16 == 0 else (8 if gap_start % 8 == 0 else (4 if gap_start % 4 == 0 else 1))

        ghidra_hits_raw = ghidra_scanner.query(gap_start, gap_end)
        reloc_hits = reloc_scanner.query(gap_start, gap_end)

        # "Unwind@..." rows in ghidra_functions.csv are SEH unwind-info data
        # blocks, not code -- a gap that is entirely unwind data is not a
        # landable function, so drop it outright rather than counting it as
        # "1 known boundary" (which would misreport it as an unambiguous
        # function candidate).
        unwind_hits = [h for h in ghidra_hits_raw if h[2].startswith("Unwind@")]
        ghidra_hits = [h for h in ghidra_hits_raw if not h[2].startswith("Unwind@")]
        if unwind_hits and not ghidra_hits and not reloc_hits:
            continue

        # merge boundary knowledge: union of distinct start addresses seen
        # across both sources gives a lower bound on function count in the gap
        starts = sorted(set([h[0] for h in ghidra_hits] + [h[0] for h in reloc_hits]))

        real_bytes = None
        if exe_data is not None:
            chunk = exe_data[gap_start:gap_end]
            real_bytes = len(chunk) - chunk.count(0xCC)
            if real_bytes < args.min_real_bytes:
                continue

        if args.exclude_stub_neighbors and is_stub_name(name0) and is_stub_name(name1):
            continue

        rec = {
            "gap_start": gap_start,
            "gap_end": gap_end,
            "gap_len": gap_len,
            "align": align,
            "before_name": name0,
            "before_source": src0,
            "after_name": name1,
            "after_source": src1,
            "ghidra_hits": ghidra_hits,
            "reloc_hits": reloc_hits,
            "n_boundaries": len(starts),
            "real_bytes": real_bytes,
        }
        all_gaps.append(rec)

        if gap_len <= args.max_size and len(starts) <= 1:
            unambiguous.append(rec)

    print(f"\nTotal non-empty gaps: {len(all_gaps)}", file=sys.stderr)
    print(f"Gaps <= {args.max_size} bytes holding <=1 known boundary (unambiguous single-function candidates): {len(unambiguous)}", file=sys.stderr)

    if args.out:
        with open(args.out, "w", encoding="utf-8", newline="") as f:
            w = csv.writer(f)
            w.writerow(["gap_start", "gap_end", "gap_len", "real_bytes", "align", "before_name", "before_source",
                        "after_name", "after_source", "n_boundaries", "boundary_names"])
            for r in all_gaps:
                bnames = ";".join(sorted(set([h[2] for h in r["ghidra_hits"]] + [h[2] for h in r["reloc_hits"]])))
                w.writerow([hex(r["gap_start"]), hex(r["gap_end"]), r["gap_len"], r["real_bytes"], r["align"],
                            r["before_name"], r["before_source"], r["after_name"], r["after_source"],
                            r["n_boundaries"], bnames])
        print(f"Wrote full gap report to {args.out}", file=sys.stderr)

    print("\n=== Unambiguous single-function gaps ===")
    for r in unambiguous:
        bnames = sorted(set([h[2] for h in r["ghidra_hits"]] + [h[2] for h in r["reloc_hits"]]))
        print(f"gap {hex(r['gap_start'])}-{hex(r['gap_end'])} len={r['gap_len']} align={r['align']} "
              f"between [{r['before_name']} <- {r['before_source']}] and [{r['after_name']} <- {r['after_source']}] "
              f"boundary={bnames}")


if __name__ == "__main__":
    main()
