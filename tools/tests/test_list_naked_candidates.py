#!/usr/bin/env python3
"""Fast unit tests for fleet partitioning and dead-end memory."""

import tempfile
from pathlib import Path

import sys

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import list_naked_candidates as queue


def candidate(index):
    return {
        "symbol": f"?candidate{index}@@YAXXZ",
        "path": f"Code/candidate{index}.cpp",
        "line": index,
        "signature": f"void candidate{index}()",
    }


def main():
    candidates = [candidate(index) for index in range(100)]
    shards = [queue.apply_shard(candidates, (index, 6)) for index in range(6)]
    identities = [{item["symbol"] for item in shard} for shard in shards]
    assert sum(len(shard) for shard in shards) == len(candidates)
    assert set().union(*identities) == {item["symbol"] for item in candidates}
    for left in range(6):
        for right in range(left + 1, 6):
            assert identities[left].isdisjoint(identities[right])

    with tempfile.TemporaryDirectory() as temporary:
        log = Path(temporary) / "dead.tsv"
        log.write_text("?candidate7@@YAXXZ\tno-match\tverified dead end\n"
                       "?candidate8@@YAXXZ\tother\tnot terminal\n",
                       encoding="utf-8")
        assert queue.logged_no_match([log]) == {"?candidate7@@YAXXZ"}
    print("PASS naked queue: stable shards and no-match filtering")


if __name__ == "__main__":
    main()
