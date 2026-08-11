#!/usr/bin/env python3
"""Read reverse/re_attempts.log into a boundary-aware dead-end index.

Every work-selection tool must consult this, or it serves candidates the fleet
has already investigated. Two log shapes are in the file and both are load-bearing:

  symbol <TAB> no-match <TAB> evidence                      (3 fields, AGENTS.md)
  symbol <TAB> rva <TAB> size <TAB> status <TAB> evidence   (5 fields, in use since)

The previous reader only understood the first, because it tested field 1 for the
literal "no-match" — in a 5-field row field 1 is the RVA, so 441 rows were
invisible and list_naked_candidates.py consulted the log not at all.

Two rules keep this from over-suppressing, which would be worse than the leak:

* The log is append-only and chronological, so the LAST *verdict* for a boundary
  wins, and annotation rows are skipped rather than counted as verdicts.
  ?removeAllShadows@W3DProjectedShadowManager@@QAEXXZ ends in `converted` after
  earlier dead ends and must be released; ??0FastAllocatorGeneral@@QAE@XZ ends
  in `refuted` after three `solved` rows and must stay retired.
* A verdict describes the boundary its author examined. Where the row records an
  RVA the comparison is exact, so once an image-derived snap moves a candidate
  somewhere else the old verdict no longer covers it. Where the row records no
  RVA there is no boundary to have moved, and the verdict stands: the 3-field
  shape is a finding about the symbol.
"""
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
RE_ATTEMPTS = ROOT / "reverse" / "re_attempts.log"

# Rows fall into three kinds and only two of them are verdicts. `note`,
# `evidence`, `lever`, `method`, `open`, `correction` and friends are
# annotations hung on an earlier finding — treating them as verdicts would let
# a follow-up note silently release a symbol the fleet had closed, which is how
# ?validateAudio@ThingTemplate@@IAEXXZ (no-match, then six annotations) came
# back ten times. Anything unrecognised is treated as an annotation, so a new
# status word leaks a candidate rather than burying one.
DEAD_END_STATUSES = frozenset({
    "no-match", "blocked", "not-convertible", "refuted", "attempted",
    "negative", "abandoned", "no-boundary", "mis-anchored?", "identity-suspect",
})
RESOLVED_STATUSES = frozenset({
    "converted", "solved", "mapped", "landed",
})
VERDICT_STATUSES = DEAD_END_STATUSES | RESOLVED_STATUSES

_BY_BOUNDARY = None   # {symbol: {rva|None: latest status}}
_LATEST = None        # {symbol: latest status seen at any boundary}


def _parse(fields):
    """Return (symbol, status, rva) for one log row, or None if it is not a verdict."""
    if len(fields) >= 5:
        symbol, rva_text, status = fields[0], fields[1], fields[3]
        try:
            rva = int(rva_text, 16) if rva_text else None
        except ValueError:
            rva = None
        return symbol, status, rva
    if len(fields) >= 3:
        return fields[0], fields[1], None
    return None


def _load():
    global _BY_BOUNDARY, _LATEST
    if _BY_BOUNDARY is not None:
        return
    _BY_BOUNDARY, _LATEST = {}, {}
    if not RE_ATTEMPTS.exists():
        return
    with RE_ATTEMPTS.open(encoding="utf-8", errors="replace") as handle:
        for line in handle:
            parsed = _parse(line.rstrip("\r\n").split("\t"))
            if parsed is None:
                continue
            symbol, status, rva = parsed
            if not symbol or not status:
                continue
            if status not in VERDICT_STATUSES:
                continue          # an annotation never overrides a standing verdict
            _BY_BOUNDARY.setdefault(symbol, {})[rva] = status
            _LATEST[symbol] = status


def is_dead_end(symbol, rva=None, *, boundary_moved=False):
    """True when serving `symbol` at `rva` would rerun a finished investigation.

    `boundary_moved` is the caller's evidence that this candidate's address was
    re-derived since the log was written (a drift snap): a verdict recorded
    against a *different* boundary does not retire it. A verdict recorded
    against no boundary at all still does, because it is a finding about the
    symbol rather than about an address -- reading it the other way leaked 377
    already-investigated candidates back into the queue, every drift candidate
    being snap-corrected by construction.
    """
    _load()
    verdicts = _BY_BOUNDARY.get(symbol)
    if not verdicts:
        return False
    if rva is not None and rva in verdicts:
        return verdicts[rva] in DEAD_END_STATUSES
    if boundary_moved and None not in verdicts:
        return False
    return _LATEST.get(symbol) in DEAD_END_STATUSES


def stats():
    """Return (symbols carrying a live dead-end verdict, total symbols logged)."""
    _load()
    dead = sum(1 for status in _LATEST.values() if status in DEAD_END_STATUSES)
    return dead, len(_LATEST)


def _record(argv):
    """Append one verdict row with correct framing; the safe path for agents.

    Hand-appending has produced three shapes of damage this index has to
    tolerate: LF/CRLF mixes (editor tools normalise the whole file on touch),
    missing columns, and status words nothing recognises. This writes exactly
    one 5-field CRLF row and refuses statuses outside the vocabulary, loudly.

    Usage:
      python3 tools/re_log.py record <symbol> <rva> <size> <status> <evidence...>

    Put attempt duration and model in the evidence free-text (e.g. "t=25min
    model=haiku ...") — that is what lets the selection weights in
    tools/yield_model.py be refit from outcomes instead of guessed.
    """
    if len(argv) < 5:
        raise SystemExit(_record.__doc__)
    symbol, rva_text, size_text, status = argv[0], argv[1], argv[2], argv[3]
    evidence = " ".join(argv[4:])
    if status not in VERDICT_STATUSES:
        raise SystemExit(
            f"unknown status {status!r}. Dead ends: {sorted(DEAD_END_STATUSES)}; "
            f"resolutions: {sorted(RESOLVED_STATUSES)}. An unrecognised status "
            f"would be ignored by every queue, so it is refused here.")
    int(rva_text, 16), int(size_text)          # fail loudly on malformed fields
    row = f"{symbol}\t{rva_text}\t{size_text}\t{status}\t{evidence}\r\n"
    with RE_ATTEMPTS.open("ab") as handle:
        handle.write(row.encode("utf-8"))
    print(f"recorded: {symbol} @ {rva_text} -> {status}")


if __name__ == "__main__":
    import sys
    if len(sys.argv) > 1 and sys.argv[1] == "record":
        _record(sys.argv[2:])
    else:
        dead, total = stats()
        print(f"{dead} standing dead ends of {total} symbols with verdicts; "
              f"append with: re_log.py record <symbol> <rva> <size> <status> <evidence>")
