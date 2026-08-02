# Contributing

Several agents usually push to `origin/master`. Keep each change small, verified,
and easy to rebase. Read `docs/matching.md` for byte matching and
`docs/structural.md` for manual reverse engineering.

## Authority and work selection

An explicit user request or assigned task lane overrides the generic queue. If a
task names a file, symbol, tier, or audit, stay in that lane. Otherwise:

1. `git pull --rebase origin master`
2. `python3 tools/check_csv.py`; repair ledger errors before other work
3. `python3 tools/next_work.py`; it returns one randomized candidate

Use `python3 tools/next_work.py --tier ghidra` or `--tier structural` when
assigned. Use `python3 tools/list_naked_candidates.py Code` for inline assembly.
Each command returns one randomized candidate. Finish or revert it, then ask
again; do not keep speculative edits open.

## Bank one verified unit

1. Make the smallest source and ledger change for one function or file.
2. Run exact focused verification: `./build.sh <file-or-symbol>`. If a command
   returns a process or session ID, poll that ID until completion. Never launch a
   duplicate long build because the first call is still running.
3. Stage only the files for this unit with `git add <specific-paths>`. Never use
   `git add .` or `git add -A`; check that every new ledger source is tracked.
4. Commit normally. Never bypass hooks.
5. Run `git pull --rebase origin master`, `git push`, then
   `git pull --rebase origin master` again. On rejection, rebase, recheck the
   ledger, retry the push, and perform the final pull.

Header, vendored-reference, and shared-shim changes trigger the long full gate in
the commit hook; do not launch a duplicate. A manually resolved merge also needs
one full gate. Poll any returned process/session until completion. For ordinary
source-only work, use the focused build and hooks. Never filter a gate through a
pipeline that hides its exit status.

## Reverse-engineering policy

Clean C++ is preferred. Use MASM or a small inline-assembly body only when the
original compiler machinery, x87 shape, SEH, or another proven codegen blocker
prevents exact C++. A five-byte `E9 rel32` dump should be repointed to an exact
C++ body when available.

Ghidra boundaries, xrefs, callees, vtables, and the retail executable are
identity evidence; decompiled C is not byte-match proof. Resolve REL32 pins only
while call sites align. After several failed shapes or roughly 30 minutes without
byte progress, revert the experiment and take a fresh candidate. Never leave a
nonmatching reconstruction in the tree.

## Placement and integrity

- Game source belongs under the official `Code/` tree. MASM dumps belong in
  `Code/masm_dumps/`; scratch files belong untracked under `build/`.
- Shared headers affect every includer. Prefer translation-unit-scoped shims and
  verify the full affected surface when a shared edit is unavoidable.
- Progress means `matched` `reverse/functions.csv` claims backed by real source
  and successful byte verification. Markers, prose, and unverified source are not
  progress.
- `python3 tools/progress.py <start-ref>` reports unique retail `.text` coverage
  and the clean-C++/ASM split; it does not verify claims.
- Do not add fallback paths for convenience; they conceal mismatches.
- Query huge ledgers with repository tools or narrow `rg`/Python filters. Never
  load `reverse/functions.csv`, `reverse/ghidra_functions.csv`, or
  `reverse/exports.csv` wholesale into context.
- Preserve unrelated work in a dirty tree. If an attempt fails verification,
  revert only that attempt.
