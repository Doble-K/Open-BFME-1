#!/usr/bin/env python3
"""Answer "what should I work on right now" with one validated candidate.

The default draws one candidate at random from the selected tier, weighted by
measured land rate for its size, so concurrent contributors still rarely
collide but no draw is worth merely the pool average. ``--ranked`` is the human/debug
view of the complete queues. No network, no compiling — runs in seconds.

Sections, in priority order:
  0. Ledger health   tools/check_csv.py — a corrupt ledger aborts everything (exit 2)
  1. Reloc-named  an unclaimed function whose mangled name a byte-true call proved
  2. Drift quick wins  immediate-only / imm+reg literal fixes from drift_report.csv
  3. Structural reconciliation  closest source-shape mismatches
  4. Ghidra-anchored absent  source literals identify an unclaimed retail function
  5. Rest of the ladder (pointer commands only, nothing computed)

Usage:
  python3 tools/next_work.py [--tier structural]
  python3 tools/next_work.py --ranked [--limit 10] [--json]

Exit codes: 0 ok, 1 missing/bad inputs, 2 ledger corrupt.
"""
import argparse
import ast
import bisect
import csv
import hashlib
import json
import secrets
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))

import re_log
import yield_model

ROOT = Path(__file__).resolve().parents[1]
# drift_report.csv is the shared drift classification (general RE infra, not the
# retired ZH source-porting sweep) — it feeds the drift/structural/ghidra tiers.
DRIFT = ROOT / "reverse" / "zh_sweep" / "drift_report.csv"
FUNCTIONS = ROOT / "reverse" / "functions.csv"
GHIDRA_FUNCTIONS = ROOT / "reverse" / "ghidra_functions.csv"
STRING_XREFS = ROOT / "reverse" / "string_xrefs.tsv"
ANCHORED = ROOT / "reverse" / "anchored_candidates.csv"
RELOC_NAMES = ROOT / "reverse" / "reloc_names.csv"
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


def structural_candidates(claimed, claimed_names, claimed_ranges, big=False):
    """The manual-RE tier: drifted functions whose source exists but whose code
    shape differs (class structural / register-swap). Workflow: docs/structural.md."""
    _, rows = read_csv(DRIFT, "python3 tools/drift_classify.py")
    last = {}
    for row in rows:
        if row["class"] in ("structural", "register-swap"):
            last[row["function"]] = row
    # Matched ranges never overlap (identical ICF ranges aside), so "strictly
    # inside any claimed range" is one bisect instead of a scan of ~90k rows
    # per candidate — the scan went quadratic as generated claims tripled the
    # ledger and put next_work minutes over its ten-second budget.
    ranges = sorted(claimed_ranges)
    starts = [start for start, _ in ranges]

    def inside_any(point):
        i = bisect.bisect_left(starts, point) - 1
        return i >= 0 and point < ranges[i][1]

    out = []
    for name, row in last.items():
        rva = to_int(row["candidate_rva"], 16, f"drift_report.csv candidate_rva for {name}")
        # candidate_rva is an alignment vote and wrong ~99% of the time; snap it to
        # the real ghidra start so the printed command is usable, and skip if either
        # the raw or corrected rva is already matched (the name filter catches the rest).
        crva, snap_note = snap_rva(rva)
        # A snap result that says the vote is inside a function (or cannot
        # establish a boundary) is not actionable work. Previously these rows
        # were still queued, making agents prove the queue's own warning right.
        if snap_note and ("function-interior" in snap_note
                          or "no trustworthy boundary" in snap_note):
            continue
        # Alignment votes frequently land a few bytes into an already verified
        # function.  A start-address-only check lets those stale rows through and
        # sends contributors on an impossible reconstruction.  Reject both raw
        # and corrected RVAs when either lies strictly inside a claimed range.
        inside_claim = inside_any(rva) or inside_any(crva)
        if rva in claimed or crva in claimed or name in claimed_names or inside_claim:
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


def _candidate_rva(candidate):
    """The address this candidate would actually be worked at, as an int."""
    text = candidate.get("candidate_rva") or candidate.get("target_rva")
    try:
        return int(text, 16) if text else None
    except ValueError:
        return None


def drop_logged(candidates):
    """Filter one queue, returning (kept, dropped_count). Never silent: main()
    reports the count so a shrunken queue is visibly explained, not mistaken
    for an exhausted tier.

    A logged verdict is terminal for automatic selection — workers must not
    rediscover a recorded dead end; --include-logged reopens it for humans.
    It describes the boundary that agent actually examined, so a row only
    retires a candidate while the boundary still matches: where the log
    records the RVA (5-field shape) that comparison is exact; where it does
    not, `drift-corrected` in the hint is evidence our boundary moved.
    See tools/re_log.py."""
    kept, dropped = [], 0
    for candidate in candidates:
        if re_log.is_dead_end(
                candidate["function"], _candidate_rva(candidate),
                boundary_moved="drift-corrected" in candidate.get("hint", "")):
            dropped += 1
            continue
        kept.append(candidate)
    return kept, dropped


def parse_shard(value):
    """Parse INDEX/COUNT using zero-based indexes."""
    try:
        index_text, count_text = value.split("/", 1)
        index, count = int(index_text), int(count_text)
    except (AttributeError, TypeError, ValueError):
        raise argparse.ArgumentTypeError("shard must be INDEX/COUNT, for example 0/3")
    if count <= 0 or index < 0 or index >= count:
        raise argparse.ArgumentTypeError(
            "shard requires COUNT > 0 and 0 <= INDEX < COUNT")
    return index, count


def shard_key(candidate):
    """Return a stable key independent of queue order and processes."""
    for field in ("target_rva", "candidate_rva"):
        value = candidate.get(field)
        if value:
            return int(value, 16)
    digest = hashlib.sha256(candidate["function"].encode("utf-8")).digest()
    return int.from_bytes(digest[:8], "big")


def apply_shard(candidates, shard):
    if shard is None:
        return candidates
    index, count = shard
    return [candidate for candidate in candidates
            if shard_key(candidate) % count == index]


def candidate_weight(candidate):
    """Selection weight for one candidate: see tools/yield_model.weight.

    The queues already rank themselves and the selector used to throw that
    ranking away, so every draw was worth the pool average."""
    return yield_model.weight(
        candidate.get("size") or candidate.get("target_size") or 1)


def weighted_choice(candidates):
    """Draw one candidate with probability proportional to candidate_weight.

    Still random, so concurrent contributors still rarely collide — collision
    avoidance never required a flat distribution.
    """
    weights = [candidate_weight(c) for c in candidates]
    cutoff = secrets.randbelow(sum(weights))
    for candidate, weight in zip(candidates, weights):
        cutoff -= weight
        if cutoff < 0:
            return candidate
    raise AssertionError("weighted_choice fell through its cumulative walk")


def anchored_candidates(claimed, claimed_names, claimed_ranges):
    """Unclaimed retail functions identified by a literal only they reference.

    The Ghidra tier anchors strings starting from a drift row, so it only ever
    reaches functions that already have a Zero Hour counterpart -- a finite
    input, now drained. tools/anchor_unclaimed.py runs the same evidence from
    the image side and caches the result here, because scanning 5,512 reference
    files does not fit this tool's ten-second budget.

    These carry an identity LEAD, not a name: the anchor says which ZH source
    the body came from, and recovering the symbol is the first part of the job.
    """
    if not ANCHORED.exists():
        return [], (f"{ANCHORED.relative_to(ROOT)} not generated — "
                    f"run python3 tools/anchor_unclaimed.py")
    _, rows = read_csv(ANCHORED, "python3 tools/anchor_unclaimed.py")
    ranges = sorted(claimed_ranges)
    starts = [start for start, _ in ranges]

    def inside_any(point):
        index = bisect.bisect_left(starts, point) - 1
        return index >= 0 and point < ranges[index][1]

    out, stale = [], 0
    for row in rows:
        rva = to_int(row["target_rva"], 16,
                     f"anchored_candidates.csv target_rva for {row['ghidra_name']}")
        if rva in claimed or inside_any(rva):
            stale += 1          # landed since the cache was generated
            continue
        source = resolve_drift_source(row["zh_source"])
        out.append({
            "function": row["ghidra_name"],
            "source": source or f"(no Code/ file yet; ZH: {row['zh_source']})",
            "zh_source": row["zh_source"],
            "target_rva": row["target_rva"],
            "size": int(row["target_size"]),
            "confidence": row["confidence"],
            "alternates": int(row["alternates"]),
            "anchor": row["anchor"],
            "command": (f"python3 tools/decode_calls.py --rva {row['target_rva']} "
                        f"--size {row['target_size']}"),
        })
    out.sort(key=lambda c: (c["confidence"] != "high", -c["size"]))
    note = f"{len(out)} anchored candidate(s)"
    if stale:
        note += f"; {stale} already landed (regenerate with anchor_unclaimed.py)"
    return out, note


def reloc_named_candidates(claimed, claimed_ranges):
    """Unclaimed functions whose mangled name a byte-true call site proved.

    For an `identity=real` row this is the strongest identity the queue carries.
    Every other tier hands over a lead -- a shape that lines up, a literal only
    one function references -- and recovering the name is the first half of the
    job. Here the decorated name IS the evidence: it came out of the relocation
    of a call whose compiled bytes are retail's own, so the class, the signature
    and the stack cleanup are all known before the work starts. What remains is
    placing the body in the tree, and the caller that named it says where to
    look.

    `identity=generated` rows are the same evidence about a name this project
    minted itself for a machine-generated funclet, and they outnumber the
    recovered ones about two to one. They are served last rather than dropped:
    the address and arity are still proven, but nothing about the name tells a
    worker what the function is, so they must not bury the real ones.
    """
    _, rows = read_csv(RELOC_NAMES, "./build.sh")
    ranges = sorted(claimed_ranges)
    starts = [start for start, _ in ranges]

    def inside_any(point):
        index = bisect.bisect_left(starts, point) - 1
        return index >= 0 and point < ranges[index][1]

    out, stale = [], 0
    for row in rows:
        rva = to_int(row["target_rva"], 16,
                     f"reloc_names.csv target_rva for {row['name']}")
        if rva in claimed or inside_any(rva):
            stale += 1          # landed since the last full gate regenerated it
            continue
        out.append({
            "function": row["name"],
            "source": row["source"],
            "target_rva": row["target_rva"],
            "size": int(row["target_size"]),
            "notes": row["notes"],
            "generated": row["notes"].endswith("identity=generated"),
            "command": (f"python3 tools/decode_calls.py --rva {row['target_rva']} "
                        f"--size {row['target_size']}"),
        })
    out.sort(key=lambda candidate: (candidate["generated"], -candidate["size"]))
    recovered = sum(1 for candidate in out if not candidate["generated"])
    note = (f"{len(out)} reloc-named candidate(s): {recovered} recovered "
            f"identity, {len(out) - recovered} generated placeholder")
    if stale:
        note += f"; {stale} already landed (regenerated by the next full gate)"
    return out, note


def selected_queue(tier, drifts, structural, ghidra_absent, anchored, named):
    queues = {
        "named": ("reloc-named unclaimed function", named),
        "harvest": ("drift quick win", drifts),
        "structural": ("structural reconciliation", structural),
        "ghidra": ("Ghidra-anchored absent function", ghidra_absent),
        "anchored": ("string-anchored unclaimed function", anchored),
    }
    if tier:
        return queues[tier]
    for name in ("named", "harvest", "structural", "ghidra", "anchored"):
        label, candidates = queues[name]
        if candidates:
            return label, candidates
    return "validated queue", []


def cluster_of(candidate, candidates):
    """Every queued candidate sharing this candidate's source file.

    The file is the real unit of work here, not the function. `./build.sh <file>`
    verifies a whole translation unit at once, a shared-header edit pays the
    host-wide gate once for the file rather than once per function, and the
    class layout an agent recovers to land one body is exactly what the next
    body in that file needs.

    It shows up in the outcomes: over the 1,000 commits ending 2038d3a0d, a
    drift candidate whose file saw no other row land had a 19.5% land rate;
    where ten or more siblings landed together it was 46.5%. Serving one
    function per session throws that away and hands the file to another agent.
    """
    same = [c for c in candidates if c["source"] == candidate["source"]]
    same.sort(key=lambda c: -yield_model.land_rate(
        c.get("size") or c.get("target_size") or 1))
    return same


def print_cluster(candidate, candidates):
    siblings = cluster_of(candidate, candidates)
    if len(siblings) < 2:
        return
    total = sum(c.get("size") or c.get("target_size") or 0 for c in siblings)
    print(f"\n  == the rest of {candidate['source']} ({len(siblings)} queued, "
          f"{total:,}B) ==")
    print("  Take the file, not just the row above. Recover the layout once and "
          "the siblings")
    print("  follow; verify them together with a single "
          f"`./build.sh {candidate['source']}`.")
    for sibling in siblings[:12]:
        size = sibling.get("size") or sibling.get("target_size") or 0
        marker = "->" if sibling is candidate else "  "
        print(f"   {marker} {size:>5}B  "
              f"{int(100 * yield_model.land_rate(size)):>2}% land  "
              f"{sibling['function'][:88]}")
    if len(siblings) > 12:
        print(f"      ... and {len(siblings) - 12} more in this file")
    print("  Bank each body as its own commit, but do not stop at one: the gate "
          "and the")
    print("  layout work are already paid for. If a shared header is involved, "
          "edit every")
    print("  dependent body first and pay the full gate once (docs/lessons.md).")


def print_candidate(label, candidate, meta, candidates=()):
    print(f"== selected work: {label} ==")
    print(f"  drawn from {meta['pool']} candidate(s), weighted by measured land rate")
    if label == "reloc-named unclaimed function":
        print(f"  {candidate['size']:>5}B  {candidate['function']}")
        print(f"       {candidate['target_rva']} — name recovered from a byte-true "
              f"call site ({candidate['notes']})")
        print(f"       named by a call in {candidate['source']}; the body is "
              f"unclaimed and anonymous in Ghidra")
        print(f"       start: {candidate['command']}")
        # No file cluster here: the whole point of this tier is that the body
        # has no source file yet, so there is no translation unit to drain and
        # nothing for `./build.sh <file>` to verify. The caller is a locality
        # hint, not the work.
        siblings = [c for c in candidates if c["source"] == candidate["source"]]
        if len(siblings) > 1:
            print(f"       {len(siblings) - 1} other unclaimed function(s) were "
                  f"named by calls in that same file")
        return
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
    elif label == "string-anchored unclaimed function":
        print(f"  {candidate['confidence']:<6} {candidate['size']:>5}B "
              f"{candidate['function']}  (anonymous — recovering the name is step 1)")
        print(f"       {candidate['target_rva']} anchored by {candidate['anchor']!r}")
        print(f"       that literal appears in ZH {candidate['zh_source']}"
              + (f" (+{candidate['alternates']} other file(s))"
                 if candidate['alternates'] else ""))
        print(f"       local source: {candidate['source']}")
        print(f"       start: {candidate['command']}")
    else:
        anchors = ", ".join(repr(value) for value in candidate["anchors"][:3])
        print(f"  {candidate['confidence']:<6} {candidate['target_size']:>5}B "
              f"{candidate['function']}")
        print(f"       {candidate['source']} -> {candidate['target_rva']} "
              f"{candidate['ghidra_name']} ({len(candidate['anchors'])} anchor(s): "
              f"{anchors}; {candidate['alternates']} alternate(s))")
        print(f"       start: {candidate['command']}")
    print_cluster(candidate, candidates)


def print_ranked(args, ledger, drifts, structural, ghidra_meta, ghidra_absent,
                 suppressed=0, named=(), named_note=""):
    print("== 0. ledger health ==")
    print(f"  {ledger}")
    if suppressed:
        print(f"  re_attempts: {suppressed} candidate(s) hidden as already "
              f"investigated (--include-logged to show)")

    if args.tier in (None, "named"):
        print(f"\n== 1. reloc-named unclaimed functions ({len(named)}) ==")
        print(f"  {named_note}")
        for candidate in named[:args.limit]:
            print(f"  {candidate['size']:>5}B  {candidate['function']}")
            print(f"       {candidate['target_rva']} named by a call in "
                  f"{candidate['source']} ({candidate['notes']})")
            print(f"       start: {candidate['command']}")

    if args.tier not in ("named", "structural", "ghidra"):
        print(f"\n== 2. drift quick wins: literal-only diffs ({len(drifts)}) ==")
        for candidate in drifts[:args.limit]:
            print(f"  {candidate['aligned_pct']:>3}% {candidate['class']:<14} "
                  f"{candidate['function']}")
            print(f"       {candidate['source']} @ {candidate['candidate_rva']}  "
                  f"hint: {candidate['hint']}")
            print("       fix the literal in source, then byte-verify: "
                  f"{candidate['command']}")

    if args.tier not in ("named", "harvest", "ghidra"):
        shown = structural[:args.limit]
        print(f"\n== 3. structural reconciliation — manual RE ({len(structural)}; "
              f"workflow: docs/structural.md) ==")
        for candidate in shown:
            print(f"  {candidate['aligned_pct']:>3}% {candidate['size']:>5}B "
                  f"{candidate['function']}")
            print(f"       {candidate['source']} @ {candidate['candidate_rva']}  "
                  f"hint: {candidate['hint']}")
            print(f"       start: {candidate['command']}")

    if args.tier in (None, "ghidra"):
        shown = ghidra_absent[:args.limit]
        print(f"\n== 4. Ghidra-anchored absent functions ({len(ghidra_absent)}; "
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

    if args.tier in ("named", "structural", "ghidra"):
        return
    print("\n== 5. rest of the ladder ==")
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
    ap.add_argument("--tier",
                    choices=("named", "harvest", "structural", "ghidra", "anchored"),
                    help="choose from only this task lane")
    ap.add_argument("--shard", type=parse_shard, metavar="INDEX/COUNT",
                    help="stable zero-based partition for concurrent workers")
    ap.add_argument("--big", action="store_true",
                    help="sort structural candidates by size (byte yield) instead of alignment")
    ap.add_argument("--include-logged", action="store_true",
                    help="keep candidates already recorded no-match in "
                         "reverse/re_attempts.log (they are dropped by default)")
    args = ap.parse_args()

    ledger = check_ledger()  # exit 2 happens in there; nothing below matters if red
    drifts = (drift_quick_wins()
              if args.tier not in ("named", "structural", "ghidra") else [])
    claimed, claimed_names, claimed_ranges = set(), set(), []
    with FUNCTIONS.open(newline="") as fh:
        for row in csv.DictReader(fh):
            if row["target_rva"]:
                start = int(row["target_rva"], 16)
                claimed.add(start)
                claimed_names.add(row["name"])
                if row.get("target_size"):
                    claimed_ranges.append((start, start + int(row["target_size"])))
    structural = (structural_candidates(claimed, claimed_names, claimed_ranges,
                                        big=args.big)
                  if args.tier not in ("named", "harvest", "ghidra", "anchored")
                  else [])
    if args.tier in (None, "named"):
        named, named_note = reloc_named_candidates(claimed, claimed_ranges)
    else:
        named, named_note = [], "reloc-named tier not requested"
    if args.tier in (None, "anchored"):
        anchored, anchored_note = anchored_candidates(
            claimed, claimed_names, claimed_ranges)
    else:
        anchored, anchored_note = [], "anchored tier not requested"
    if args.tier not in ("named", "harvest", "structural", "anchored"):
        ghidra_absent, ghidra_meta = ghidra_absent_candidates(
            claimed, claimed_names)
    else:
        ghidra_absent, ghidra_meta = [], "Ghidra tier not requested"

    # A `no-match` row is a finished investigation, not a pending task; serving
    # one again is pure rework. ~20% of the structural queue is in that state.
    suppressed = 0
    if not args.include_logged:
        named, dropped_named = drop_logged(named)
        drifts, dropped_drift = drop_logged(drifts)
        structural, dropped_structural = drop_logged(structural)
        ghidra_absent, dropped_ghidra = drop_logged(ghidra_absent)
        anchored, dropped_anchored = drop_logged(anchored)
        suppressed = (dropped_named + dropped_drift + dropped_structural
                      + dropped_ghidra + dropped_anchored)

    named = apply_shard(named, args.shard)
    drifts = apply_shard(drifts, args.shard)
    structural = apply_shard(structural, args.shard)
    ghidra_absent = apply_shard(ghidra_absent, args.shard)
    anchored = apply_shard(anchored, args.shard)
    shard_meta = (None if args.shard is None else
                  {"index": args.shard[0], "count": args.shard[1]})

    if args.ranked and args.json:
        print(json.dumps({
            "ledger": ledger,
            "named_meta": named_note, "reloc_named": named,
            "drift_quick_wins": drifts,
            "structural": structural,
            "ghidra_meta": ghidra_meta, "ghidra_absent": ghidra_absent,
            "anchored_meta": anchored_note, "anchored": anchored,
            "suppressed_logged": suppressed,
            "shard": shard_meta,
            "pointers": [cmd for cmd, _ in POINTERS],
        }, indent=2))
        return

    if args.ranked:
        print_ranked(args, ledger, drifts, structural, ghidra_meta,
                     ghidra_absent, suppressed, named, named_note)
        return

    label, candidates = selected_queue(args.tier, drifts, structural, ghidra_absent,
                                       anchored, named)
    candidate = weighted_choice(candidates) if candidates else None
    meta = {"pool": len(candidates), "suppressed_logged": suppressed,
            "shard": shard_meta}
    if args.json:
        meta = dict(meta, cluster=[
            c["function"] for c in cluster_of(candidate, candidates)]) \
            if candidate else meta
        print(json.dumps({"ledger": ledger, "tier": label,
                          "selection": candidate, "selection_meta": meta}, indent=2))
        return
    print("== ledger health ==")
    print(f"  {ledger}")
    if suppressed:
        print(f"  re_attempts: {suppressed} candidate(s) hidden as already "
              f"investigated (--include-logged to show)")
    if candidate is None:
        print(f"\nNo {label} candidates remain.")
        return
    print()
    print_candidate(label, candidate, meta, candidates)


if __name__ == "__main__":
    main()
