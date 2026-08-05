"""Rows claimed per directory against source files present, for orientation.

Answers "which parts of the tree are barely touched" -- a directory with many
sources and few rows is either untried or structurally blocked. Pair it with
tools/gap_owner.py, which answers the same question from the binary's side.

Run from the repo root: python3 tools/coverage_by_dir.py
"""
import csv, collections, os, posixpath

claimed = collections.Counter()          # by directory of the source file
for r in csv.DictReader(open('reverse/functions.csv', newline='')):
    src = r['source'].replace('\\', '/')
    claimed[posixpath.dirname(src)] += 1

files = collections.Counter()
for root, dirs, fs in os.walk('Code'):
    d = root.replace(os.sep, '/')
    for f in fs:
        if f.endswith(('.cpp', '.c')):
            files[d] += 1

rows = []
for d, n in files.items():
    rows.append((n, claimed.get(d, 0), d))
rows.sort(reverse=True)

print("directories with source files but NO claimed rows:")
empty = [(n, d) for n, c, d in rows if c == 0]
for n, d in empty[:25]:
    print(f"  {n:>4} files   {d}")
print(f"  ... {len(empty)} such directories, {sum(n for n, _ in empty)} files total")

print("\nlargest directories by file count (files / rows):")
for n, c, d in rows[:18]:
    print(f"  {n:>4} / {c:>6}   {d}")
