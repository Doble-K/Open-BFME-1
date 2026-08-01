#!/usr/bin/env python3
"""Unit and CLI tests for randomized queue selection."""

import json
import subprocess
import sys
import tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))

import list_naked_candidates
import list_thunk_dumps
import work_selection


def test_distinct_quality_groups_and_recent_history():
    (ROOT / "build").mkdir(exist_ok=True)
    with tempfile.TemporaryDirectory(dir=ROOT / "build") as temp:
        root = Path(temp)
        (root / ".git").mkdir()
        items = [
            {"id": "a-best", "group": "a"},
            {"id": "a-worse", "group": "a"},
            {"id": "b", "group": "b"},
            {"id": "c", "group": "c"},
            {"id": "outside-quality-pool", "group": "d"},
        ]
        choose_last = lambda count: count - 1
        selected = []
        metadata = []
        for _ in range(6):
            item, meta = work_selection.choose_ranked(
                items, lambda item: item["group"], lambda item: item["id"],
                "test", root, randbelow=choose_last, group_limit=3)
            selected.append(item["id"])
            metadata.append(meta)

        assert selected == ["c", "b", "a-best", "c", "b", "a-worse"]
        assert "outside-quality-pool" not in selected
        assert metadata[0] == {"pool_groups": 3, "conflict_key": "c",
                               "candidate_key": "c"}
        state_path = root / ".git" / work_selection.STATE_FILE
        state = json.loads(state_path.read_text())
        assert state["test"]["groups"] == ["a", "b"]
        assert state["test"]["candidates"]["a"] == ["a-worse", "a-best"]
    print("PASS selector: quality-bounded group rotation reaches same-group siblings")


def test_tool_conflict_keys():
    (ROOT / "build").mkdir(exist_ok=True)
    with tempfile.TemporaryDirectory(dir=ROOT / "build") as temp:
        root = Path(temp)
        (root / ".git").mkdir()
        thunks = [
            {"class": "Wide", "name": "?a", "source": "a.asm", "rva": 1, "dest": 2},
            {"class": "Wide", "name": "?b", "source": "b.asm", "rva": 3, "dest": 4},
            {"class": "Other", "name": "?c", "source": "c.asm", "rva": 5, "dest": 6},
        ]
        picked_thunks = [list_thunk_dumps.select_thunk(thunks, root)[0]
                         for _ in range(4)]
        assert all(left["class"] != right["class"]
                   for left, right in zip(picked_thunks, picked_thunks[1:])), (
                       "consecutive thunks must use distinct classes")
        assert {item["name"] for item in picked_thunks if item["class"] == "Wide"} == {
            "?a", "?b"}, "both siblings in one thunk class must be reachable"

        naked = [
            {"path": "same.cpp", "score": 10, "size": 1, "line": 1},
            {"path": "same.cpp", "score": 9, "size": 1, "line": 2},
            {"path": "other.cpp", "score": 8, "size": 1, "line": 1},
        ]
        picked_naked = [list_naked_candidates.select_candidate(naked, root)[0]
                        for _ in range(4)]
        assert all(left["path"] != right["path"]
                   for left, right in zip(picked_naked, picked_naked[1:])), (
                       "consecutive naked candidates must use distinct sources")
        assert {item["line"] for item in picked_naked if item["path"] == "same.cpp"} == {
            1, 2}, "both siblings in one source file must be reachable"
    print("PASS tool grouping: immediate group collisions avoided; siblings reachable")


def test_cli_defaults():
    naked = subprocess.run(
        [sys.executable, "tools/list_naked_candidates.py", "Code"], cwd=ROOT,
        capture_output=True, text=True, timeout=60, check=False)
    assert naked.returncode == 0, naked.stderr
    if "No validated" not in naked.stdout:
        assert naked.stdout.count("== selected naked-asm conversion ==") == 1
        assert naked.stdout.count("        verify:") == 1, naked.stdout

    ranked = subprocess.run(
        [sys.executable, "tools/list_naked_candidates.py", "Code", "--ranked", "--limit", "2"],
        cwd=ROOT, capture_output=True, text=True, timeout=60, check=False)
    assert ranked.returncode == 0, ranked.stderr
    assert "== selected naked-asm conversion ==" not in ranked.stdout

    thunks = subprocess.run(
        [sys.executable, "tools/list_thunk_dumps.py"], cwd=ROOT,
        capture_output=True, text=True, timeout=60, check=False)
    assert thunks.returncode == 0, thunks.stderr
    assert (thunks.stdout.count("== selected convertible thunk ==") == 1
            or "No validated" in thunks.stdout)

    for tool in ("next_work.py", "list_thunk_dumps.py", "list_naked_candidates.py"):
        help_run = subprocess.run(
            [sys.executable, f"tools/{tool}", "--help"], cwd=ROOT,
            capture_output=True, text=True, timeout=60, check=False)
        for obsolete in ("--pick", "--window", "--seed"):
            assert obsolete not in help_run.stdout, f"{tool} exposes {obsolete}"
        assert "--ranked" in help_run.stdout, f"{tool} lacks the debug escape"
    print("PASS CLI: one default unit, explicit ranked escape, no picker knobs")


def main():
    test_distinct_quality_groups_and_recent_history()
    test_tool_conflict_keys()
    test_cli_defaults()
    print("ALL TESTS PASSED")


if __name__ == "__main__":
    main()
