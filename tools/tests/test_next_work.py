#!/usr/bin/env python3
"""Focused tests for the validated, decentralized work queue."""

import csv
import json
import subprocess
import sys
import tempfile
from pathlib import Path

import pytest

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))


def run(args=(), cwd=ROOT, env=None):
    return subprocess.run(
        [sys.executable, str(cwd / "tools" / "next_work.py"), *args],
        cwd=cwd, env=env, capture_output=True, text=True, timeout=60, check=False)


def get_ranked_json(extra=()):
    proc = run(["--ranked", "--json", *extra])
    assert proc.returncode == 0, f"ranked JSON failed (rc {proc.returncode}):\n{proc.stderr}"
    return json.loads(proc.stdout)


def get_selection_json(extra=(), env=None):
    proc = run(["--json", *extra], env=env)
    assert proc.returncode == 0, f"selection JSON failed (rc {proc.returncode}):\n{proc.stderr}"
    return json.loads(proc.stdout)


# Six tests below take `ranked`/`data`, but the fixtures were never defined, so
# pytest errored them out at setup and they have not run. Each ranked run is a
# subprocess that re-reads the whole ledger, so it is built once per module.
@pytest.fixture(scope="module")
def ranked():
    return get_ranked_json()


@pytest.fixture(scope="module")
def data(ranked):
    return ranked


def test_plain_run(ranked):
    proc = run()
    assert proc.returncode == 0, f"plain run failed (rc {proc.returncode}):\n{proc.stderr}"
    available = any(ranked[key] for key in
                    ("drift_quick_wins", "structural", "ghidra_absent"))
    if available:
        assert proc.stdout.count("== selected work:") == 1, proc.stdout
        assert proc.stdout.count("       start:") + proc.stdout.count(
            "then byte-verify:") == 1, proc.stdout
        assert "== 1. drift quick wins" not in proc.stdout, proc.stdout
    else:
        assert "No validated queue candidates remain." in proc.stdout
    print("PASS plain run: one work unit, no ranked queue dump")


def test_ranked_view():
    proc = run(["--ranked", "--limit", "2"])
    assert proc.returncode == 0, proc.stderr
    for needle in ("== 0. ledger health ==", "== 1. drift quick wins",
                   "== 2. structural reconciliation",
                   "== 3. Ghidra-anchored absent functions",
                   "== 4. rest of the ladder =="):
        assert needle in proc.stdout, f"ranked output missing {needle!r}"
    print("PASS --ranked: full human/debug queue remains available")


def test_selection_draws_from_the_whole_queue(ranked):
    first = get_selection_json(["--tier", "structural"])
    second = get_selection_json(["--tier", "structural"])
    candidates = ranked["structural"]
    if not candidates:
        assert first["selection"] is None and second["selection"] is None
        return

    functions = {candidate["function"] for candidate in candidates}
    for result in (first, second):
        assert result["selection"]["function"] in functions, result
        assert result["selection_meta"]["pool"] == len(candidates), result
    print(f"PASS default picker: draws from all {len(candidates)} queue candidate(s)")


def test_selection_beats_uniform_under_both_cost_models(ranked):
    """The selector must not discard the ranking, and must not bet the whole
    queue on an unmeasured cost model.

    Attempt duration is not recorded anywhere, so bytes-per-hour cannot be
    computed. The two plausible cost models pull in opposite directions, so the
    weighting is only defensible if it beats a uniform draw under BOTH:
      cost constant       -> value is P(land) * size
      cost scales w/ size -> value is P(land)
    """
    import yield_model

    candidates = ranked["structural"]
    if len(candidates) < 50:
        pytest.skip("queue too small to measure a distribution")

    def mean(sample, value):
        return sum(value(c) for c in sample) / len(sample)

    import next_work
    drawn = [next_work.weighted_choice(candidates) for _ in range(4000)]
    per_attempt = lambda c: yield_model.land_rate(c["size"]) * c["size"]
    per_hour = lambda c: yield_model.land_rate(c["size"])

    for label, value in (("bytes/attempt", per_attempt), ("bytes/hour", per_hour)):
        pool, got = mean(candidates, value), mean(drawn, value)
        assert got > pool, (
            f"weighted draw is no better than uniform on {label}: "
            f"{got:.2f} against a {pool:.2f} pool")
        print(f"PASS weighted picker: {label} {pool:.2f} -> {got:.2f} "
              f"({got / pool:.2f}x uniform)")

    # Assert suppression of the 14%-land-rate band RELATIVE to this pool's own
    # uniform baseline, not against a constant. An absolute ceiling rots as the
    # queue shifts: it silently becomes either unreachable or a coin flip
    # depending on how many small candidates happen to be queued that week.
    tiny = sum(1 for c in drawn if c["size"] < 64) / len(drawn)
    baseline = sum(1 for c in candidates if c["size"] < 64) / len(candidates)
    if baseline:
        assert tiny < baseline / 2, (
            f"{tiny:.2%} of draws in the <64B band against a {baseline:.2%} "
            f"uniform baseline — the band is not being suppressed "
            f"(measured suppression is normally ~3.9x)")
    assert len({id(c) for c in drawn}) > 20, "selection concentrated on too few candidates"


def test_land_rate_curve_is_not_monotonic_in_size(ranked):
    """Guards the measured shape against being 'simplified' back into a
    bigger-is-better weight. P(land) peaks at 128-255B (41%) and falls to 9%
    above 512B; a monotonic curve would re-serve the bands that do not pay."""
    import yield_model

    assert yield_model.land_rate(32) < yield_model.land_rate(200)
    assert yield_model.land_rate(1024) < yield_model.land_rate(200)
    assert yield_model.land_rate(200) == max(
        yield_model.land_rate(n) for n in (32, 100, 200, 400, 1024, 4096))
    print("PASS land-rate curve: peaks at the measured 128-255B band")


def test_anchored_candidates_are_real_and_unclaimed(data):
    """The string-anchor tier must never serve a body the ledger already covers.

    Its input is a cached CSV (tools/anchor_unclaimed.py), so it goes stale as
    the fleet lands rows — the tier has to re-check every candidate against the
    live ledger rather than trusting the cache."""
    ranges, claimed_rvas = [], set()
    with (ROOT / "reverse" / "functions.csv").open(newline="") as fh:
        for row in csv.DictReader(fh):
            if row["target_rva"]:
                start = int(row["target_rva"], 16)
                claimed_rvas.add(start)
                if row["target_size"]:
                    ranges.append((start, start + int(row["target_size"])))
    for candidate in data["anchored"]:
        rva = int(candidate["target_rva"], 16)
        assert rva not in claimed_rvas, candidate
        assert not any(lo < rva < hi for lo, hi in ranges), candidate
        assert candidate["size"] > 0, candidate
        assert candidate["confidence"] in ("high", "medium"), candidate
        assert candidate["anchor"], candidate
        assert candidate["zh_source"], candidate
    print(f"PASS anchored queue: {len(data['anchored'])} candidates, none claimed")


def test_explicit_stable_sharding(ranked):
    full = ranked["structural"]
    shards = [get_ranked_json(["--tier", "structural", "--shard", f"{i}/3"])
              for i in range(3)]
    names = [{candidate["function"] for candidate in data["structural"]}
             for data in shards]
    assert not (names[0] & names[1] or names[0] & names[2] or names[1] & names[2])
    assert set().union(*names) == {candidate["function"] for candidate in full}
    for index, data in enumerate(shards):
        assert data["shard"] == {"index": index, "count": 3}, data["shard"]

    selection = get_selection_json(["--tier", "structural", "--shard", "1/3"])
    assert selection["selection_meta"]["shard"] == {"index": 1, "count": 3}
    if selection["selection"]:
        assert selection["selection"]["function"] in names[1]

    invalid = run(["--shard", "3/3"])
    assert invalid.returncode != 0 and "0 <= INDEX < COUNT" in invalid.stderr
    obsolete = run(["--any"])
    assert obsolete.returncode != 0 and "unrecognized arguments: --any" in obsolete.stderr
    print("PASS explicit sharding: stable, disjoint, complete partitions")


def test_ranked_json_shape(data):
    for key in ("ledger", "drift_quick_wins", "structural",
                "ghidra_meta", "ghidra_absent", "pointers"):
        assert key in data, f"ranked JSON missing key {key!r}"
    for stale in ("slot", "pool", "filtered"):
        assert stale not in data, f"ranked JSON retained sharding field {stale!r}"
    assert data["shard"] is None
    print(f"PASS ranked JSON: {len(data['structural'])} structural and "
          f"{len(data['ghidra_absent'])} Ghidra candidates")


def test_ghidra_candidates_validated(data):
    claimed_names, claimed_rvas = set(), set()
    with (ROOT / "reverse" / "functions.csv").open(newline="") as fh:
        for row in csv.DictReader(fh):
            claimed_names.add(row["name"])
            if row["target_rva"]:
                claimed_rvas.add(int(row["target_rva"], 16))
    for candidate in data["ghidra_absent"]:
        assert candidate["function"] not in claimed_names, candidate
        assert int(candidate["target_rva"], 16) not in claimed_rvas, candidate
        assert (ROOT / candidate["source"]).exists(), candidate
        assert candidate["target_size"] > 0 and candidate["anchors"], candidate
        assert candidate["confidence"] in ("high", "medium"), candidate
        assert candidate["command"].startswith("python3 tools/explain_mismatch.py ")
    print(f"PASS Ghidra queue: {len(data['ghidra_absent'])} validated candidates")


def test_structural_candidates_do_not_start_inside_claimed_ranges(data):
    ranges = []
    with (ROOT / "reverse" / "functions.csv").open(newline="") as fh:
        for row in csv.DictReader(fh):
            if row["target_rva"] and row["target_size"]:
                start = int(row["target_rva"], 16)
                ranges.append((start, start + int(row["target_size"]), row["name"]))
    for candidate in data["structural"]:
        rva = int(candidate["candidate_rva"], 16)
        overlaps = [name for start, end, name in ranges if start < rva < end]
        assert not overlaps, (candidate, overlaps[:3])
    print(f"PASS structural queue: {len(data['structural'])} candidates outside claimed ranges")


def test_logged_dead_ends_suppressed(ranked):
    """A standing dead-end verdict is a finished investigation, so the queues
    must not serve that boundary again; --include-logged restores it."""
    import re_log

    queues = ("drift_quick_wins", "structural", "ghidra_absent")
    for key in queues:
        # A verdict retires a candidate only while its boundary is unchanged;
        # a snap-corrected boundary is new evidence and comes back.
        stale = [c["function"] for c in ranked[key]
                 if re_log.is_dead_end(
                     c["function"],
                     int((c.get("candidate_rva") or c.get("target_rva") or "0"), 16),
                     boundary_moved="drift-corrected" in c.get("hint", ""))]
        assert not stale, f"{key} served {len(stale)} finished candidate(s): {stale[:3]}"

    full = get_ranked_json(["--include-logged"])
    hidden = sum(len(full[key]) - len(ranked[key]) for key in queues)
    assert hidden == ranked["suppressed_logged"], (hidden, ranked["suppressed_logged"])
    assert hidden >= 0
    print(f"PASS re_attempts filter: {hidden} finished candidate(s) suppressed, "
          f"--include-logged restores them")


def test_dead_end_index_reads_both_log_shapes():
    """re_attempts.log carries a 3-field and a 5-field shape; the old reader
    tested field 1 for "no-match", which in a 5-field row is the RVA, so 441
    rows were invisible. Annotations must not overturn a standing verdict."""
    import re_log

    dead, total = re_log.stats()
    assert total > 0 and dead > 0, (dead, total)
    # ends `converted` after earlier dead ends -> released for work
    assert not re_log.is_dead_end("?removeAllShadows@W3DProjectedShadowManager@@QAEXXZ")
    # ends `refuted` after three `solved` rows -> stays retired
    assert re_log.is_dead_end("??0FastAllocatorGeneral@@QAE@XZ")
    # no-match then six annotation rows -> the annotations must not release it
    assert re_log.is_dead_end("?validateAudio@ThingTemplate@@IAEXXZ")
    assert not re_log.is_dead_end("?NeverLoggedAnywhere@@QAEXXZ")
    print(f"PASS dead-end index: {dead} standing dead ends of {total} symbols with verdicts")


def test_corrupt_ledger():
    (ROOT / "build").mkdir(exist_ok=True)
    with tempfile.TemporaryDirectory(dir=ROOT / "build") as temp:
        temp = Path(temp)
        (temp / "tools").mkdir()
        (temp / "reverse" / "zh_sweep").mkdir(parents=True)
        (temp / "src" / "zh").mkdir(parents=True)
        for name in ("next_work.py", "check_csv.py", "re_log.py", "yield_model.py"):
            (temp / "tools" / name).write_bytes((ROOT / "tools" / name).read_bytes())
        (temp / "src" / "zh" / "stub.cpp").write_text("// stub\n")
        row = "?Foo@@QAEXXZ,,0x00400000,16,src/zh/stub.cpp,matched,\r\n"
        (temp / "reverse" / "functions.csv").write_bytes(
            b"name,export_rva,target_rva,target_size,source,status,notes\r\n"
            + (row + row).encode())
        (temp / "reverse" / "symbols.csv").write_text("name,address,notes\n")
        (temp / "reverse" / "zh_sweep" / "drift_report.csv").write_text(
            "function,source,size,candidate_rva,aligned_pct,class,first_diff,hint,votes\n")
        proc = run(cwd=temp)
        output = proc.stdout + proc.stderr
        assert proc.returncode == 2, output
        assert "dedup_csv" in output and "LEDGER CORRUPT" in output, output
        assert "selected work" not in output, output
    print("PASS corrupt ledger: exit 2 before selection")


def main():
    ranked = get_ranked_json()
    test_plain_run(ranked)
    test_ranked_view()
    test_selection_draws_from_the_whole_queue(ranked)
    test_selection_beats_uniform_under_both_cost_models(ranked)
    test_land_rate_curve_is_not_monotonic_in_size(ranked)
    test_anchored_candidates_are_real_and_unclaimed(ranked)
    test_explicit_stable_sharding(ranked)
    test_ranked_json_shape(ranked)
    test_ghidra_candidates_validated(ranked)
    test_structural_candidates_do_not_start_inside_claimed_ranges(ranked)
    test_logged_dead_ends_suppressed(ranked)
    test_dead_end_index_reads_both_log_shapes()
    test_corrupt_ledger()
    print("ALL TESTS PASSED")


if __name__ == "__main__":
    main()
