#!/usr/bin/env python3
"""Small, decentralized work selection shared by the queue tools."""

import json
import os
import secrets
from pathlib import Path


QUALITY_GROUP_LIMIT = 64
STATE_FILE = "openbfme-recent-work.json"


def _git_dir(root):
    dotgit = Path(root) / ".git"
    if dotgit.is_dir():
        return dotgit
    if not dotgit.is_file():
        return None
    try:
        line = dotgit.read_text(encoding="utf-8").strip()
    except OSError:
        return None
    if not line.startswith("gitdir: "):
        return None
    path = Path(line[8:])
    return path if path.is_absolute() else (Path(root) / path).resolve()


def _state_path(root):
    git_dir = _git_dir(root)
    return git_dir / STATE_FILE if git_dir is not None else None


def _read_state(path):
    if path is None:
        return {}
    try:
        data = json.loads(path.read_text(encoding="utf-8"))
    except (OSError, ValueError, TypeError):
        return {}
    return data if isinstance(data, dict) else {}


def _write_state(path, state):
    if path is None:
        return
    temp = path.with_name(f"{path.name}.{os.getpid()}.tmp")
    try:
        temp.write_text(json.dumps(state, sort_keys=True) + "\n", encoding="utf-8")
        temp.replace(path)
    except OSError:
        try:
            temp.unlink()
        except OSError:
            pass


def choose_ranked(items, conflict_key, candidate_key, namespace, root,
                  randbelow=secrets.randbelow, group_limit=QUALITY_GROUP_LIMIT):
    """Choose one item from a random top-ranked conflict group.

    ``items`` must already be ranked best-first. The first ``group_limit``
    distinct conflict groups define the quality-bounded pool; all candidates in
    those groups remain reachable. Group and per-group candidate cycles are kept
    automatically in a worktree-private file under ``.git``.
    """
    group_order = []
    groups = {}
    for item in items:
        group = str(conflict_key(item))
        if group not in groups:
            if len(group_order) >= group_limit:
                continue
            group_order.append(group)
            groups[group] = []
        identity = str(candidate_key(item))
        if any(old_identity == identity for old_identity, _ in groups[group]):
            continue
        groups[group].append((identity, item))
    if not group_order:
        return None, {"pool_groups": 0, "conflict_key": None,
                      "candidate_key": None}

    path = _state_path(root)
    state = _read_state(path)
    raw_namespace = state.get(namespace, {})
    # Migrate the group-only state written by the first randomized selector.
    if isinstance(raw_namespace, list):
        raw_namespace = {"groups": raw_namespace, "candidates": {}}
    if not isinstance(raw_namespace, dict):
        raw_namespace = {}

    eligible_groups = set(group_order)
    raw_groups = raw_namespace.get("groups", [])
    recent_groups = ([str(group) for group in raw_groups]
                     if isinstance(raw_groups, list) else [])
    recent_groups = [group for group in recent_groups if group in eligible_groups]
    # Keeping every other group in the recent window makes one group available:
    # no immediate repeat, and every quality-bounded group is reached each cycle.
    recent_groups = recent_groups[:max(0, len(group_order) - 1)]
    available_groups = [group for group in group_order if group not in recent_groups]
    group = available_groups[randbelow(len(available_groups))]

    raw_candidates = raw_namespace.get("candidates", {})
    if not isinstance(raw_candidates, dict):
        raw_candidates = {}
    candidate_history = {}
    for current_group in group_order:
        valid = {identity for identity, _ in groups[current_group]}
        old = raw_candidates.get(current_group, [])
        if isinstance(old, list):
            kept = [str(identity) for identity in old if str(identity) in valid]
            if kept:
                candidate_history[current_group] = kept

    recent_candidates = candidate_history.get(group, [])
    available_candidates = [entry for entry in groups[group]
                            if entry[0] not in recent_candidates]
    if not available_candidates:
        recent_candidates = []
        available_candidates = groups[group]
    # Ranking already carries the tool's quality judgment. Randomize ownership
    # groups for distribution, then take that group's best untried candidate.
    identity, item = available_candidates[0]

    recent_groups = [group] + [old for old in recent_groups if old != group]
    recent_groups = recent_groups[:max(0, len(group_order) - 1)]
    candidate_history[group] = ([identity]
                                + [old for old in recent_candidates if old != identity])
    state[namespace] = {"groups": recent_groups, "candidates": candidate_history}
    _write_state(path, state)
    return item, {"pool_groups": len(group_order), "conflict_key": group,
                  "candidate_key": identity}
