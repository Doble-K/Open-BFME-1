#!/usr/bin/env python3
"""Focused tests for the validated, decentralized work queue."""

import csv
import json
import os
import subprocess
import sys
import tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]


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


def test_random_selection_is_uniform_over_queue(ranked):
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
    print(f"PASS default picker: uniform over all {len(candidates)} queue candidate(s)")


def test_no_sharding_interface():
    env = os.environ.copy()
    env.update({"AGENT_SLOT": "0", "AGENT_POOL": "0"})
    result = get_selection_json(["--tier", "structural"], env=env)
    assert "slot" not in result and "pool" not in result and "filtered" not in result
    obsolete = run(["--any"])
    assert obsolete.returncode != 0 and "unrecognized arguments: --any" in obsolete.stderr
    print("PASS no sharding: worker environment ignored and --any removed")


def test_ranked_json_shape(data):
    for key in ("ledger", "drift_quick_wins", "structural",
                "ghidra_meta", "ghidra_absent", "pointers"):
        assert key in data, f"ranked JSON missing key {key!r}"
    for stale in ("slot", "pool", "filtered"):
        assert stale not in data, f"ranked JSON retained sharding field {stale!r}"
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


def test_corrupt_ledger():
    (ROOT / "build").mkdir(exist_ok=True)
    with tempfile.TemporaryDirectory(dir=ROOT / "build") as temp:
        temp = Path(temp)
        (temp / "tools").mkdir()
        (temp / "reverse" / "zh_sweep").mkdir(parents=True)
        (temp / "src" / "zh").mkdir(parents=True)
        for name in ("next_work.py", "check_csv.py"):
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
    test_random_selection_is_uniform_over_queue(ranked)
    test_no_sharding_interface()
    test_ranked_json_shape(ranked)
    test_ghidra_candidates_validated(ranked)
    test_structural_candidates_do_not_start_inside_claimed_ranges(ranked)
    test_corrupt_ledger()
    print("ALL TESTS PASSED")


if __name__ == "__main__":
    main()
