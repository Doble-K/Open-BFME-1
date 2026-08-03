#!/usr/bin/env python3
"""Answer "what should I work on right now" with one validated candidate.

The default picks uniformly at random from the selected tier's whole queue, so
many concurrent contributors rarely collide. ``--ranked`` is the human/debug
view of the complete queues. No network, no compiling — runs in seconds.

Sections, in priority order:
  0. Ledger health   tools/check_csv.py — a corrupt ledger aborts everything (exit 2)
  1. Drift quick wins  immediate-only / imm+reg literal fixes from drift_report.csv
  2. Structural reconciliation  closest source-shape mismatches
  3. Ghidra-anchored absent  source literals identify an unclaimed retail function
  4. Rest of the ladder (pointer commands only, nothing computed)

Usage:
  python3 tools/next_work.py [--tier structural]
  python3 tools/next_work.py --ranked [--limit 10] [--json]

Exit codes: 0 ok, 1 missing/bad inputs, 2 ledger corrupt.
"""
import argparse
import ast
import csv
import json
import secrets
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))

ROOT = Path(__file__).resolve().parents[1]
# drift_report.csv is the shared drift classification (general RE infra, not the
# retired ZH source-porting sweep) — it feeds the drift/structural/ghidra tiers.
DRIFT = ROOT / "reverse" / "zh_sweep" / "drift_report.csv"
FUNCTIONS = ROOT / "reverse" / "functions.csv"
GHIDRA_FUNCTIONS = ROOT / "reverse" / "ghidra_functions.csv"
STRING_XREFS = ROOT / "reverse" / "string_xrefs.tsv"
RE_ATTEMPTS = ROOT / "reverse" / "re_attempts.log"
_NO_MATCH = None
_SOURCE_INDEX = None
_SOURCE_TEXT = {}

POINTERS = [
    ("python3 tools/land_ambiguous.py",
     "land string-anchored exact-ambiguous drift copies"),
    ("python3 tools/list_naked_candidates.py Code",
     "choose one naked-asm function worth decompiling to C++"),
]

FIX_INSTRUCTIONS = """\
LEDGER CORRUPT — fix this before doing anything else:
  1. python3 tools/dedup_csv.py
  2. byte-verify any remaining conflicting claims: python3 tools/build.py <source>
     for each claimant — the row that fails verification is the wrong one; delete it
  3. re-run: python3 tools/check_csv.py"""


def check_ledger():
    proc = subprocess.run([sys.executable, str(ROOT / "tools" / "check_csv.py")],
                          cwd=ROOT, capture_output=True, text=True)
    if proc.returncode != 0:
        sys.stderr.write(proc.stdout + proc.stderr)
        print(FIX_INSTRUCTIONS, file=sys.stderr)
        raise SystemExit(2)
    return proc.stdout.strip()


def read_csv(path, regen):
    if not path.exists():
        raise SystemExit(f"{path.relative_to(ROOT)} is missing — regenerate it: {regen}")
    with path.open(newline="") as fh:
        reader = csv.DictReader(fh)
        rows, header_dups = [], 0
        for row in reader:
            if row[reader.fieldnames[0]] == reader.fieldnames[0]:
                header_dups += 1  # union-merge damage: a second header line mid-file
                continue
            rows.append(row)
    if header_dups:
        print(f"warning: {path.relative_to(ROOT)} contains {header_dups} repeated "
              f"header line(s) (bad merge) — ignored", file=sys.stderr)
    return reader.fieldnames, rows


def to_int(value, base, what):
    try:
        return int(value, base) if base != 10 else int(value)
    except ValueError:
        raise SystemExit(f"{what}: bad value {value!r} — regenerate the report")


def drift_quick_wins():
    _, rows = read_csv(DRIFT, "python3 tools/drift_classify.py")
    claimed = set()
    with FUNCTIONS.open(newline="") as fh:
        for row in csv.DictReader(fh):
            if row["target_rva"]:
                claimed.add(int(row["target_rva"], 16))  # check_csv validated these
    last = {}
    for row in rows:
        if row["class"] in ("immediate-only", "imm+reg"):
            last[row["function"]] = row
    out = []
    for name, row in last.items():
        rva = to_int(row["candidate_rva"], 16, f"drift_report.csv candidate_rva for {name}")
        if rva in claimed:
            continue
        rel = resolve_drift_source(row["source"], name)
        if rel is None:
            print(f"warning: drift_report.csv row for {name} names a missing source "
                  f"{row['source']} — stale report, skipped", file=sys.stderr)
            continue
        out.append({"function": name, "source": rel,
                    "class": row["class"], "aligned_pct": int(row["aligned_pct"]),
                    "candidate_rva": row["candidate_rva"], "hint": row["hint"],
                    "command": f"python3 tools/build.py {rel}"})
    out.sort(key=lambda c: (-c["aligned_pct"], c["function"]))
    return out


def source_index():
    global _SOURCE_INDEX
    if _SOURCE_INDEX is None:
        _SOURCE_INDEX = {}
        for base in (ROOT / "Code", ROOT / "src"):
            if not base.exists():
                continue
            for path in sorted(base.rglob("*.cpp")):
                _SOURCE_INDEX.setdefault(path.name.casefold(), []).append(path)
    return _SOURCE_INDEX


def resolve_drift_source(basename, function=None):
    """drift_report source column is a bare basename; landed files live under
    Code/ (official tree layout); a few remainders sit under src/. Resolve
    case-insensitively because drift reports normalize names to lowercase.
    When duplicate basenames exist, the decorated-symbol marker is decisive."""
    hits = source_index().get(Path(basename).name.casefold(), [])
    if function and len(hits) > 1:
        marked = []
        for path in hits:
            text = _SOURCE_TEXT.setdefault(path, path.read_text(errors="replace"))
            if function + " present-unmatched" in text or function in text:
                marked.append(path)
        if marked:
            hits = marked
    return hits[0].relative_to(ROOT).as_posix() if hits else None


_GHIDRA_STARTS = None


def _ghidra_starts():
    """(sorted-list, set) of ghidra function-start RVAs, cached. Empty on a fresh
    clone without the generated inventory, so correction silently no-ops."""
    global _GHIDRA_STARTS
    if _GHIDRA_STARTS is None:
        starts = set()
        if GHIDRA_FUNCTIONS.exists():
            with GHIDRA_FUNCTIONS.open(newline="") as fh:
                for row in csv.DictReader(fh):
                    try:
                        starts.add(int(row["rva"], 16))
                    except (ValueError, KeyError, TypeError):
                        pass
        _GHIDRA_STARTS = (sorted(starts), starts)
    return _GHIDRA_STARTS


def snap_rva(rva):
    """drift candidate_rva is an alignment vote, wrong ~99% of the time — it lands
    in int3 padding just before the real start, a few bytes into the SEH prologue,
    or (no leading 0xCC to skip) still inside the PRECEDING function's tail — e.g.
    `c4 10 c3 cc cc ...`, a couple of misdecoded bytes plus a real `ret` before the
    pad run, so the naive leading-0xCC scan never fires. Snap to the nearest ghidra
    function start, trying both directions and keeping whichever is closer.
    Returns (corrected_rva, note|None)."""
    ordered, starts = _ghidra_starts()
    if rva in starts:
        return rva, None
    if not ordered:
        # No Ghidra inventory (it is gitignored, so this is the fresh-clone case):
        # recover the boundary from the retail image instead of no-opping.
        return padding_snap(rva)
    try:
        import bisect
        import build
        data = build.read_target_bytes(rva, 16)
        off = 0
        while off < 15 and off < len(data) and data[off] == 0xCC:
            off += 1
        if off and (rva + off) in starts:
            return rva + off, f"drift-corrected +{off}B (skipped int3 pad)"
        candidates = []
        i = bisect.bisect_right(ordered, rva) - 1
        if 0 <= i < len(ordered) and 0 < rva - ordered[i] <= 48:
            d = rva - ordered[i]
            candidates.append((d, ordered[i], f"drift-corrected -{d}B (snapped to ghidra start)"))
        j = bisect.bisect_left(ordered, rva)
        if 0 <= j < len(ordered) and 0 < ordered[j] - rva <= 48:
            d = ordered[j] - rva
            candidates.append((d, ordered[j],
                                f"drift-corrected +{d}B (snapped to ghidra start, was in preceding fn's tail)"))
        if candidates:
            candidates.sort()
            return candidates[0][1], candidates[0][2]
    except Exception:
        pass
    return padding_snap(rva)


PAD_BYTES = (0xCC, 0x90)
SNAP_WINDOW = 64


def padding_snap(rva):
    """Ghidra-free fallback for the correction above.

    The Ghidra inventory is gitignored, so on a fresh clone `_ghidra_starts()` is
    empty and every drift vote keeps its raw rva — which the docstring above says
    is wrong ~99% of the time. MSVC pads between functions with int3, so the byte
    after a padding run is a real function start and the image alone is enough to
    recover one. Where no boundary is in range, say the candidate is interior
    rather than invent a start: that verdict is what saves the 30-60 minutes."""
    try:
        import build
        head = build.read_target_bytes(rva, SNAP_WINDOW)
        back = build.read_target_bytes(rva - SNAP_WINDOW, SNAP_WINDOW)
    except Exception:
        return rva, None
    if len(head) < 2 or len(back) < SNAP_WINDOW:
        return rva, None

    # The vote landed inside the pad run; the next real body starts after it.
    if head[0] in PAD_BYTES:
        off = 0
        while off < len(head) and head[off] in PAD_BYTES:
            off += 1
        if off < len(head):
            return rva + off, f"drift-corrected +{off}B (queued rva was int3 padding)"
        return rva, None

    # Otherwise the nearest preceding padding run ends on the real start. A lone
    # 0xCC/0x90 is often just an operand byte, so trust a single-byte run only
    # when it lands on MSVC's 16-byte function alignment.
    for distance in range(1, SNAP_WINDOW + 1):
        if back[SNAP_WINDOW - distance] not in PAD_BYTES:
            continue
        start = rva - distance + 1
        run = 0
        while (SNAP_WINDOW - distance - run) >= 0 and back[SNAP_WINDOW - distance - run] in PAD_BYTES:
            run += 1
        if run < 2 and start % 16:
            return rva, (f"lone 0x{back[SNAP_WINDOW - distance]:02X} {distance - 1}B back is an "
                         f"operand byte, not padding — no trustworthy boundary in {SNAP_WINDOW}B")
        if distance == 1:
            return rva, None  # already on a start
        return start, f"drift-corrected -{distance - 1}B (snapped to int3-delimited start)"

    return rva, f"no int3 boundary within {SNAP_WINDOW}B — candidate is function-interior"


def structural_candidates(claimed, claimed_names, big=False):
    """The manual-RE tier: drifted functions whose source exists but whose code
    shape differs (class structural / register-swap). Workflow: docs/structural.md."""
    _, rows = read_csv(DRIFT, "python3 tools/drift_classify.py")
    last = {}
    for row in rows:
        if row["class"] in ("structural", "register-swap"):
            last[row["function"]] = row
    out = []
    for name, row in last.items():
        rva = to_int(row["candidate_rva"], 16, f"drift_report.csv candidate_rva for {name}")
        # candidate_rva is an alignment vote and wrong ~99% of the time; snap it to
        # the real ghidra start so the printed command is usable, and skip if either
        # the raw or corrected rva is already matched (the name filter catches the rest).
        crva, snap_note = snap_rva(rva)
        if rva in claimed or crva in claimed or name in claimed_names:
            continue
        source = resolve_drift_source(row["source"], name)
        if source is None:
            print(f"warning: drift_report.csv row for {name} names a missing source "
                  f"{row['source']} — stale report, skipped", file=sys.stderr)
            continue
        crva_hex = f"0x{crva:08X}"
        hint = row["hint"] + (f"; {snap_note}, verify the prologue" if snap_note else "")
        out.append({"function": name, "source": source, "class": row["class"],
                    "aligned_pct": int(row["aligned_pct"]), "size": int(row["size"]),
                    "candidate_rva": crva_hex, "hint": hint,
                    "command": (f"python3 tools/explain_mismatch.py '{name}' "
                                f"--rva {crva_hex} --size {row['size']} "
                                f"--source {source}")})
    if big:
        # byte-yield mode: biggest functions first (still gated by alignment)
        out.sort(key=lambda c: (-c["size"],
                                -c["aligned_pct"], c["function"]))
    else:
        # highest alignment first (closest to matching), small before big at equal alignment
        out.sort(key=lambda c: (-c["aligned_pct"],
                                c["size"], c["function"]))
    return out


def marked_function_literals(text, name):
    """Return real C/C++ string literals from the function following its
    `present-unmatched` marker. A small lexer keeps braces and quoted text in
    comments from leaking literals out of adjacent functions."""
    marker = name + " present-unmatched"
    pos = text.find(marker)
    if pos < 0:
        return []
    i = text.find("\n", pos)
    if i < 0:
        return []
    i += 1
    depth = 0
    started = False
    literals = []
    while i < len(text):
        if not started and text.startswith("present-unmatched", i):
            return []
        if text.startswith("//", i):
            end = text.find("\n", i + 2)
            i = len(text) if end < 0 else end + 1
            continue
        if text.startswith("/*", i):
            end = text.find("*/", i + 2)
            i = len(text) if end < 0 else end + 2
            continue
        ch = text[i]
        if ch in ("'", '"'):
            quote = ch
            raw = []
            i += 1
            while i < len(text):
                ch = text[i]
                if ch == "\\" and i + 1 < len(text):
                    raw.extend((ch, text[i + 1]))
                    i += 2
                    continue
                i += 1
                if ch == quote:
                    break
                raw.append(ch)
            if quote == '"':
                try:
                    value = ast.literal_eval('"' + "".join(raw) + '"')
                except (SyntaxError, ValueError):
                    value = "".join(raw)
                if isinstance(value, str) and len(value) >= 5:
                    literals.append(value)
            continue
        if ch == "{":
            depth += 1
            started = True
        elif ch == "}" and started:
            depth -= 1
            if depth == 0:
                return literals
        i += 1
    return []


def read_string_xrefs():
    out = {}
    with STRING_XREFS.open(encoding="utf-8", errors="replace") as fh:
        for line in fh:
            literal, tab, rvas = line.rstrip("\n").partition("\t")
            if not tab:
                continue
            values = out.setdefault(literal, set())
            for value in rvas.split(","):
                if value:
                    values.add(int(value, 16))
    return out


def ghidra_absent_candidates(claimed, claimed_names):
    """Map ZH functions classified `absent` to BFME functions through rare
    string literals found inside the marked source body. Ghidra already gives
    each literal's referencing function RVA, exact boundary, and size."""
    if not GHIDRA_FUNCTIONS.exists() or not STRING_XREFS.exists():
        return [], ("Ghidra outputs unavailable — generate them per "
                    "tools/ghidra/README.md")

    _, rows = read_csv(DRIFT, "python3 tools/drift_classify.py")
    last = {row["function"]: row for row in rows if row["class"] == "absent"}
    functions = {}
    with GHIDRA_FUNCTIONS.open(newline="") as fh:
        for row in csv.DictReader(fh):
            functions[int(row["rva"], 16)] = row
    xrefs = read_string_xrefs()
    source_text = {}
    out = []
    for name, row in last.items():
        if name in claimed_names:
            continue
        hits = source_index().get(Path(row["source"]).name.casefold(), [])
        if not hits:
            continue
        source_rel = resolve_drift_source(row["source"], name)
        if source_rel is None:
            continue
        source_path = ROOT / source_rel
        text = source_text.setdefault(source_path, source_path.read_text(errors="replace"))
        literals = set(marked_function_literals(text, name))
        anchored = {}
        rarity = {}
        for literal in literals:
            refs = xrefs.get(literal, set())
            # Common UI words and format fragments create misleading cross-file
            # matches. Multiple rare literals remain useful and rank together.
            if not refs or len(refs) > 8:
                continue
            for rva in refs:
                if rva not in functions or rva in claimed:
                    continue
                anchored.setdefault(rva, set()).add(literal)
                rarity[rva] = rarity.get(rva, 0.0) + 1.0 / len(refs)
        viable = []
        source_size = int(row["size"])
        for rva, anchors in anchored.items():
            # One unique/two-way literal or two independent literals is enough
            # to justify a Ghidra inspection; weaker guesses stay hidden.
            if len(anchors) < 2 and rarity[rva] < 0.5:
                continue
            target_size = int(functions[rva]["size"])
            viable.append((rva, anchors, rarity[rva], target_size))
        if not viable:
            continue
        viable.sort(key=lambda c: (-len(c[1]), -c[2],
                                   abs(c[3] - source_size), c[3], c[0]))
        rva, anchors, anchor_score, target_size = viable[0]
        confidence = "high" if len(anchors) >= 2 and anchor_score >= 1.0 else "medium"
        source = source_path.relative_to(ROOT).as_posix()
        out.append({
            "function": name, "source": source, "source_size": source_size,
            "target_rva": f"0x{rva:08X}", "target_size": target_size,
            "ghidra_name": functions[rva]["name"], "confidence": confidence,
            "anchors": sorted(anchors), "anchor_score": round(anchor_score, 3),
            "alternates": len(viable) - 1,
            "command": (f"python3 tools/explain_mismatch.py '{name}' --rva 0x{rva:08X} "
                        f"--size {target_size} --source {source}"),
        })
    out.sort(key=lambda c: (c["confidence"] != "high",
                            -len(c["anchors"]), -c["anchor_score"], c["target_size"],
                            abs(c["target_size"] - c["source_size"]), c["function"]))
    return out, (f"{len(functions)} Ghidra functions + {len(xrefs)} string literals loaded")


def logged_no_match():
    """Symbols already reduced to a `no-match` verdict in reverse/re_attempts.log.

    Those boundaries were investigated and rejected — stale drift votes, interior
    fragments, absent bodies — so re-serving them spends another agent's 30-60
    minutes rediscovering a known dead end. The log is TSV (symbol, status, prose)
    and append-only, so reading it is cheap."""
    global _NO_MATCH
    if _NO_MATCH is None:
        symbols = set()
        if RE_ATTEMPTS.exists():
            with RE_ATTEMPTS.open(encoding="utf-8", errors="replace") as fh:
                for line in fh:
                    fields = line.rstrip("\r\n").split("\t")
                    if len(fields) >= 2 and fields[1] == "no-match":
                        symbols.add(fields[0])
        _NO_MATCH = symbols
    return _NO_MATCH


def drop_logged(candidates):
    """Filter one queue, returning (kept, dropped_count). Never silent: main()
    reports the count so a shrunken queue is visibly explained, not mistaken
    for an exhausted tier.

    A logged verdict describes the boundary that agent actually examined, and
    most existing rows reject a *stale* one. So a row only retires a candidate
    while the boundary still matches: once the image-derived snap moves the
    candidate somewhere else, the old verdict no longer covers it and it comes
    back. Without that, this filter would permanently bury exactly the
    candidates the snap just repaired."""
    logged = logged_no_match()
    kept, dropped = [], 0
    for candidate in candidates:
        if (candidate["function"] in logged
                and "drift-corrected" not in candidate.get("hint", "")):
            dropped += 1
            continue
        kept.append(candidate)
    return kept, dropped


def selected_queue(tier, drifts, structural, ghidra_absent):
    queues = {
        "harvest": ("drift quick win", drifts),
        "structural": ("structural reconciliation", structural),
        "ghidra": ("Ghidra-anchored absent function", ghidra_absent),
    }
    if tier:
        return queues[tier]
    for name in ("harvest", "structural", "ghidra"):
        label, candidates = queues[name]
        if candidates:
            return label, candidates
    return "validated queue", []


def print_candidate(label, candidate, meta):
    print(f"== selected work: {label} ==")
    print(f"  chosen uniformly at random from {meta['pool']} candidate(s)")
    if label == "drift quick win":
        print(f"  {candidate['aligned_pct']:>3}% {candidate['class']:<14} "
              f"{candidate['function']}")
        print(f"       {candidate['source']} @ {candidate['candidate_rva']}  "
              f"hint: {candidate['hint']}")
        print(f"       fix the literal in source, then byte-verify: {candidate['command']}")
    elif label == "structural reconciliation":
        print(f"  {candidate['aligned_pct']:>3}% {candidate['size']:>5}B "
              f"{candidate['function']}")
        print(f"       {candidate['source']} @ {candidate['candidate_rva']}  "
              f"hint: {candidate['hint']}")
        print(f"       start: {candidate['command']}")
    else:
        anchors = ", ".join(repr(value) for value in candidate["anchors"][:3])
        print(f"  {candidate['confidence']:<6} {candidate['target_size']:>5}B "
              f"{candidate['function']}")
        print(f"       {candidate['source']} -> {candidate['target_rva']} "
              f"{candidate['ghidra_name']} ({len(candidate['anchors'])} anchor(s): "
              f"{anchors}; {candidate['alternates']} alternate(s))")
        print(f"       start: {candidate['command']}")


def print_ranked(args, ledger, drifts, structural, ghidra_meta, ghidra_absent,
                 suppressed=0):
    print("== 0. ledger health ==")
    print(f"  {ledger}")
    if suppressed:
        print(f"  re_attempts: {suppressed} candidate(s) hidden as already "
              f"no-match (--include-logged to show)")

    if args.tier not in ("structural", "ghidra"):
        print(f"\n== 1. drift quick wins: literal-only diffs ({len(drifts)}) ==")
        for candidate in drifts[:args.limit]:
            print(f"  {candidate['aligned_pct']:>3}% {candidate['class']:<14} "
                  f"{candidate['function']}")
            print(f"       {candidate['source']} @ {candidate['candidate_rva']}  "
                  f"hint: {candidate['hint']}")
            print("       fix the literal in source, then byte-verify: "
                  f"{candidate['command']}")

    if args.tier not in ("harvest", "ghidra"):
        shown = structural[:args.limit]
        print(f"\n== 2. structural reconciliation — manual RE ({len(structural)}; "
              f"workflow: docs/structural.md) ==")
        for candidate in shown:
            print(f"  {candidate['aligned_pct']:>3}% {candidate['size']:>5}B "
                  f"{candidate['function']}")
            print(f"       {candidate['source']} @ {candidate['candidate_rva']}  "
                  f"hint: {candidate['hint']}")
            print(f"       start: {candidate['command']}")

    if args.tier in (None, "ghidra"):
        shown = ghidra_absent[:args.limit]
        print(f"\n== 3. Ghidra-anchored absent functions ({len(ghidra_absent)}; "
              f"workflow: docs/structural.md) ==")
        print(f"  {ghidra_meta}")
        for candidate in shown:
            anchors = ", ".join(repr(value) for value in candidate["anchors"][:3])
            print(f"  {candidate['confidence']:<6} {candidate['target_size']:>5}B "
                  f"{candidate['function']}")
            print(f"       {candidate['source']} -> {candidate['target_rva']} "
                  f"{candidate['ghidra_name']} ({len(candidate['anchors'])} anchor(s): "
                  f"{anchors}; {candidate['alternates']} alternate(s))")
            print(f"       start: {candidate['command']}")

    if args.tier in ("structural", "ghidra"):
        return
    print("\n== 4. rest of the ladder ==")
    for command, why in POINTERS:
        print(f"  {command:<55} # {why}")


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--limit", type=int, default=10,
                    help="max items per section with --ranked (default 10)")
    ap.add_argument("--json", action="store_true",
                    help="machine-readable selected item (or full queues with --ranked)")
    ap.add_argument("--ranked", action="store_true",
                    help="show complete ranked queues for humans/debugging")
    ap.add_argument("--tier", choices=("harvest", "structural", "ghidra"),
                    help="choose from only this task lane")
    ap.add_argument("--big", action="store_true",
                    help="sort structural candidates by size (byte yield) instead of alignment")
    ap.add_argument("--include-logged", action="store_true",
                    help="keep candidates already recorded no-match in "
                         "reverse/re_attempts.log (they are dropped by default)")
    args = ap.parse_args()

    ledger = check_ledger()  # exit 2 happens in there; nothing below matters if red
    drifts = drift_quick_wins() if args.tier not in ("structural", "ghidra") else []
    claimed, claimed_names = set(), set()
    with FUNCTIONS.open(newline="") as fh:
        for row in csv.DictReader(fh):
            if row["target_rva"]:
                claimed.add(int(row["target_rva"], 16))
                claimed_names.add(row["name"])
    structural = (structural_candidates(claimed, claimed_names, big=args.big)
                  if args.tier not in ("harvest", "ghidra") else [])
    if args.tier not in ("harvest", "structural"):
        ghidra_absent, ghidra_meta = ghidra_absent_candidates(
            claimed, claimed_names)
    else:
        ghidra_absent, ghidra_meta = [], "Ghidra tier not requested"

    # A `no-match` row is a finished investigation, not a pending task; serving
    # one again is pure rework. ~20% of the structural queue is in that state.
    suppressed = 0
    if not args.include_logged:
        drifts, dropped_drift = drop_logged(drifts)
        structural, dropped_structural = drop_logged(structural)
        ghidra_absent, dropped_ghidra = drop_logged(ghidra_absent)
        suppressed = dropped_drift + dropped_structural + dropped_ghidra

    if args.ranked and args.json:
        print(json.dumps({
            "ledger": ledger,
            "drift_quick_wins": drifts,
            "structural": structural,
            "ghidra_meta": ghidra_meta, "ghidra_absent": ghidra_absent,
            "suppressed_logged": suppressed,
            "pointers": [cmd for cmd, _ in POINTERS],
        }, indent=2))
        return

    if args.ranked:
        print_ranked(args, ledger, drifts, structural, ghidra_meta,
                     ghidra_absent, suppressed)
        return

    label, candidates = selected_queue(args.tier, drifts, structural, ghidra_absent)
    candidate = candidates[secrets.randbelow(len(candidates))] if candidates else None
    meta = {"pool": len(candidates), "suppressed_logged": suppressed}
    if args.json:
        print(json.dumps({"ledger": ledger, "tier": label,
                          "selection": candidate, "selection_meta": meta}, indent=2))
        return
    print("== ledger health ==")
    print(f"  {ledger}")
    if suppressed:
        print(f"  re_attempts: {suppressed} candidate(s) hidden as already "
              f"no-match (--include-logged to show)")
    if candidate is None:
        print(f"\nNo {label} candidates remain.")
        return
    print()
    print_candidate(label, candidate, meta)


if __name__ == "__main__":
    main()
