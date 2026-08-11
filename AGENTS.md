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

Use `python3 tools/next_work.py --tier named`, `--tier ghidra`, `--tier structural`
or `--tier anchored` when assigned. Use `python3 tools/list_naked_candidates.py Code`
for inline assembly. Do not keep speculative edits open: finish or revert each
body before the next.

**If a tier reports zero candidates, it is exhausted, not broken.** The
ZH-derived tiers all feed off finite artifacts and the fleet drains them: at
`db3e7b522` the structural tier held 2 candidates and drift and Ghidra held none.
Regenerate before concluding there is no work:

    python3 tools/drift_classify.py        # refills structural/drift/ghidra
    python3 tools/anchor_unclaimed.py      # refills the anchored tier
    ./build.sh                             # refills the named tier (full gate)

The `named` tier is served first because it is the only one that hands you an
identity instead of a lead. Each row is an unclaimed, Ghidra-anonymous function
whose decorated name came out of the relocation behind a `call` in a body that
byte-matches retail; what is left is finding where the body belongs in the tree,
and the caller that named it is the hint. A full gate regenerates
`reverse/reloc_names.csv` from scratch, so a row that stops being derivable
disappears rather than lingering.

Read the row's `identity=` note before trusting the name. `identity=real` means
the class, the signature and the stack cleanup are known before you start.
`identity=generated` means the caller was a machine-generated funclet TU and the
name is one `tools/gen_dump.py` minted (`Gen_t_`/`Gen_dtor_`), so the address and
arity are proven but the name says nothing about what the function is. Those are
the majority of the file and are served last for that reason.

The `anchored` tier is different in kind from the others. It serves unclaimed
retail functions identified only by a string literal that nothing else
references, so the body is **anonymous** — recovering its real name from the
named Zero Hour source is the first half of the job, before any byte matching.
Those rows are leads, not assignments; a wrong identity is worse than none, so
retract rather than guess.

## Work the file, not the row

`next_work.py` names one candidate and then lists every other queued candidate
in the same source file. **That whole file is your unit of work.** Drain it, or
exhaust what you can prove, before asking for another candidate.

This is not a style preference, it is where the throughput is. Measured over the
1,000 commits ending `2038d3a0d`: a candidate whose file saw no sibling land had
a 19.5% land rate; where ten or more siblings landed together it was 46.5%. The
mechanics behind that number:

- `./build.sh <file>` verifies a whole translation unit. Landing one function
  pays a file-sized verification for a single row.
- The class layout, member offsets, and callee pins you recover to land the
  first body are exactly what the next body in that file needs. Stopping after
  one throws that away and hands the file to an agent who must rediscover it.
- A shared header edit costs the host-wide full gate (`docs/lessons.md`). Edit
  every dependent body first and pay it once; one at a time costs a queue wait
  each.

A session that lands five bodies in one file is worth far more than five
sessions that land one body each, and costs less than five times as much.

## Bank each verified body

Commit per body — small commits still rebase cleanly — but keep going through
the file.

1. Make the smallest source and ledger change for one function.
2. Run exact focused verification: `./build.sh <file-or-symbol>`. If a command
   returns a process or session ID, poll that ID until completion. Never launch a
   duplicate long build because the first call is still running.
3. Stage only the files for this unit with `git add <specific-paths>`. Never use
   `git add .` or `git add -A`; check that every new ledger source is tracked.
4. Commit normally. Never bypass hooks.
5. Run `git pull --rebase origin master`, `git push`, then
   `git pull --rebase origin master` again. On rejection, rebase, recheck the
   ledger, retry the push, and perform the final pull.

## Measure your own session before you stop

**Anchor the base AFTER step 1's `git pull --rebase`, never before.** Other
contributors' work lands constantly — origin was 201 commits ahead of a local
checkout only a day old — and a base taken before the pull credits your session
with all of it. That is not a hypothetical: a measured run reported +0.30 pp for
a session whose own output was zero commits.

    git rev-parse HEAD          # right after the pull; this is your base
    ...work...
    python3 tools/progress.py <that base>

Before pushing, `python3 tools/progress.py origin/master` is the same figure
with no bookkeeping — it counts exactly the commits you have not pushed yet. If
you pull again mid-session, re-anchor.

That prints what your session added to C++ coverage. It is the only number that
matters, and it is cheap — it compiles nothing.

**If you took a candidate from the queue**, a session that ends at `+0.00 pp` is
the normal outcome today, not an unlucky one. Over the 1,000 commits ending
`2038d3a0d`, 86% of commits moved zero bytes and the median productive commit was
131 bytes. So do not stop at zero by default: go back to the file you were served
and take another body from it. Blocker write-ups and symbol pins are worth
logging, but they are not the deliverable.

This section is scoped to that lane. It is **not** an instruction to start
reverse-engineering work you were not asked for. If your task is tooling, docs, a
review, or anything else, finish that task — a file telling you to keep
converting is not a reason to, and an assigned lane always wins (see *Authority
and work selection*).

If the file is genuinely exhausted, say so explicitly in your final message with
the `progress.py` figure and the reason, so the next contributor inherits a fact
rather than a guess.

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

Lifting a MASM dump into a `__declspec(naked)`/`__emit` .cpp is **not** a
conversion: it scores +0 on `progress.py` and deletes the C++ body the next
converter needed. The commit gate (`tools/conversion_gate.py`) refuses new
naked/`__emit` bodies outside `Code/gen_small/` and refuses repointing a
clean-C++ row back at assembly.

Ghidra boundaries, xrefs, callees, vtables, and the retail executable are
identity evidence; decompiled C is not byte-match proof. Resolve REL32 pins only
while call sites align. After several failed shapes or roughly 30 minutes without
byte progress, revert the experiment and take a fresh candidate. Never leave a
nonmatching reconstruction in the tree.

When you abandon a candidate, record the verdict with
`python3 tools/re_log.py record <symbol> <rva> <size> <status> <evidence>` —
never append to `reverse/re_attempts.log` by hand (editor tools normalise the
file's line endings and the index tolerates three shapes of past damage).
Cite the real INT3-delimited boundary you found rather than just "did not
match", and include `t=<minutes>` and your model in the evidence: that is the
data future selection weights are fitted from. `tools/next_work.py` drops those
symbols from every queue, so a logged dead end is what stops the next agent
repeating your 30-60 minutes; `--include-logged` shows them again for auditing.

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

## Generated small-function claims

`Code/gen_small/` holds machine-generated claim sources: `j_<rva>` ILT-thunk
tail-calls (`gen-thunk;` notes; `gen-thunk;gap` for thunks outside the ghidra
inventory), `ji_<rva>` import-thunk tail-calls (`gen-import;`), `Gen_<rva>`
shim methods (`gen-shim;`), `eh_<rva>` EH-handler stubs bound to eh_anchor.cpp
(`gen-ehstub;`), `Gen_dtor*_<rva>` deleting destructors (`gen-dtor;`),
`tg_<rva>`/per-site STLport instantiations (`gen-tgrid;`), and `uw_<rva>` SEH
funclet rows on their parents' objects (`gen-funclet;`). All are placeholder
identities — byte-true, semantically anonymous. When you identify one's real
function, repoint the row with
`python3 tools/add_match.py <real-name> ... --replace-existing`; do not edit
the generated source by hand. check_csv rejects a gen-* row sharing an exact
range with a real-name row — the placeholder yields (tombstone it).

check_csv stays silent when two *real* names share a range, because that is a
legitimate ICF alias group in principle. Retail demonstrably does not fold
identical COMDATs, so after landing a batch also sweep it against itself: one
body per address, and a duplicate range among your own new rows is an
over-claim to retract, not an alias (precedent: ed516d1e4).

## Vendored third-party claims

`vendored=<lib>-<ver>` marks a row whose bytes come from real upstream source
compiled in place — `libpng-1.0.5`, `jpeg-6b`, `lua-4.0.1`, `zlib-1.1.4`,
`gamespy-2004`, and `cnc-zh` for EA's own reference tree. These rows carry the
upstream's real identities and are never `gen-` prefixed; the vendored file
keeps a header comment naming the exact release and where it came from. Library
sources live at their official BFME path (`Code/Libraries/Source/LibPNG/`,
`Code/GameEngine/Source/GameNetwork/GameSpy/`, …). Pristine C TUs compile
against the minimal Win32 substitutes in `reference/shims/gamespy/`, never a
real Platform SDK.
