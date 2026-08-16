# Phase 3: Measure whether a Zero Hour packet converts better than a nameless dump

## Objective
Convert ten pinned ZH work packets and compare the landing count against
`tools/yield_model.py`'s fitted, size-weighted baseline, so continued investment in lead
generation rests on evidence rather than on the assumption that a better starting point
must help.

## Why this is not optional
The queues now serve packets ahead of everything else, and a packet is selected on byte
alignment (`tools/zh_sweep.py:441`, `align >= NEAR_ALIGN`, with `NEAR_ALIGN = 0.85`).
`tools/yield_model.py:17-19` names alignment as a feature it measured and **rejected**,
quoted in full because the second clause matters as much as the first:

> WHAT DID NOT PREDICT, and must not be reintroduced as a weight without new evidence:
> drift `aligned_pct`. Landed candidates averaged 22.7% alignment against 24.9% for dead
> ends (Cohen's d = -0.18 — very slightly the WRONG way), and the per-band land rate has
> no trend at all: 15.1 / 36.4 / 16.3 / 35.1 / 16.8%.

The current routing is a bet against the repo's own fitted model. A packet is richer than a
bare alignment number — it carries EA's actual source and the real symbol name — but that
difference is precisely the untested claim. This phase supplies the evidence the model
demands.

## Establish the population, then pin the sample — before opening any packet
The workable population **must be recomputed, not copied from this file**. It moves: the
fleet claims addresses continuously, and a static table written yesterday already disagreed
with the live ledger by six packets. Write a scratch census under `build/` that, for every
`reverse/zh_sweep/packets/*.md`, parses the size and keeps the packet if its RVA is either
unclaimed or claimed only by a `gen-dump` row. Print the count per size band. Commit
nothing.

Then **pin ten addresses before reading any packet content**: in each size band, the two
with the lowest RVA. That rule is arbitrary on purpose — it is deterministic, reproducible
from the census alone, and independent of anything believed to predict success.

Do **not** rank within a band by alignment. Every packet already sits in a compressed
85–100% window, so that ordering is noise, and `yield_model.py` reports the per-band land
rate has no trend against alignment at all. Do not select via `next_work.py --tier packet`
either: it sorts by descending size (`:801`), applies `drop_logged` (`:1092`), and cannot
see packets sitting on dump rows (`:787`) — that is the bug Phase 4 fixes, and Phase 4 runs
after this. Packets on dump rows are reachable through `tools/list_naked_candidates.py Code`;
unclaimed ones through `next_work.py`. Which queue would serve a given packet is irrelevant
here: the ten are pinned by address and worked directly.

Both outcomes are read symmetrically. This is an arbitrary draw, not a best-case one, so a
failure is not "even the best could not land" and a success is not an upper bound.

## Pre-registered decision rule, with the arithmetic
Baselines per band come from `LAND_RATE_BY_SIZE`: <64 B 14.0%, 64–127 B 27.3%,
128–255 B 41.3%, 256–511 B 20.6%, ≥512 B 8.8%. Two draws per band gives an expected

    2 × (0.140 + 0.273 + 0.413 + 0.206 + 0.088) = 2.24 landings out of 10

The design is stratified across five different rates, so the null is **Poisson-binomial,
not Binomial(10, 0.224)**. The means coincide; the tails do not. Computed over the ten
per-draw rates:

    P(X >= 6) = 0.0085   (0.85%)
    P(X >= 5) = 0.0441   (4.4%)
    P(X <= 2) = 0.6047   (60.5%)

- **≥6 land** → 2.7× baseline, a 0.85% outcome under the null. The lever is real: fund lead
  generation (the `no-needle` 4,709 and `exact-multi` 3,783 buckets).
- **≤2 land** → at or below baseline. The lever is dead: stop routing packets first and
  revert the two queue changes.
- **3–5** → **inconclusive, and must be reported as inconclusive.** Do not argue it toward
  either action. State that ten samples cannot separate these hypotheses and give the
  sample size that could.

Two properties of this rule to state plainly rather than discover afterwards. First, 3
landings is *above* the 2.24 baseline, so any rule treating 3 as failure would be scoring
the thesis against a number it was never measured against. Second, P(X≤2) = 60.5%: the
revert branch fires on the majority of null outcomes **by construction**. That is correct
for a decision rule, but it is what will justify reverting two shipped changes, so the tally
must be reported with the probability beside it.

## Implementation
For each pinned packet: read it, port the named Zero Hour body into the correct `Code/`
source, close the remaining gap against the disassembly the packet quotes, and land the row
with `tools/add_match.py`. A packet that resists after roughly 30 minutes without byte
progress is a **dead end, recorded and counted as not-landed** — not retried until it works,
which would destroy the measurement. Record every verdict, landed or not, with
`python3 tools/re_log.py record`.

Clean C++ only. A `__declspec(naked)`/`__emit` body byte-matches by construction, scores
zero, and is rejected by `tools/conversion_gate.py` in both hooks.

## Verification
1. Every landed body is proven by `./build.sh <source>` printing
   `Functions: OK N/N matched`, and `python3 tools/check_csv.py` printing `check_csv: OK`.
2. `python3 tools/progress.py origin/master` shows a positive byte delta equal to the sum of
   the landed rows. A landed conversion that moves the figure by 0 bytes means an `__emit`
   body survived and the conversion did not happen. (Unlike Phase 2, no ICF fold is involved
   here, so the delta is meaningful.)
3. The deliverable is the tally: the ten pinned addresses, attempted and landed per band,
   the 2.24 expectation, the null probability of the observed count, and the pre-registered
   verdict. A phase that lands bodies but does not produce the tally has not met its
   objective.

## Landing it
**Commit and push each converted body as its own commit, as it is verified** — not as one
batch at the end. Ten conversions against a ledger the fleet rewrites continuously will
not rebase cleanly as a single lump, and a per-body commit is what makes a partial result
still count.

- Per body: stage the `Code/` source and `reverse/functions.csv` explicitly, commit, then
  `git pull --rebase origin master` / `git push` with the 12-attempt retry loop, checking
  exit codes directly.
- Never `git add .` or `git add -A`. Never `--no-verify`. **Never add a `Co-Authored-By`
  trailer.**
- Dead ends are recorded with `tools/re_log.py record` and pushed too — a measurement that
  only commits its successes is not a measurement.
- Finish with one commit carrying the tally (pinned addresses, landed per band, the 2.24
  expectation, the null probability, the verdict), so the decision is in the history rather
  than only in a chat log.
- Confirm at the end: `git fetch -q origin && git merge-base --is-ancestor <your-sha> origin/master`. Do NOT use
  `git rev-parse --short HEAD origin/master`: `--short` rejects two revisions and exits 128
  with "Needed a single revision", which reads as a failed push.

## Result: 5 of 10 landed — INCONCLUSIVE

Census recomputed at the start of the phase: 335 packets, 198 blocked by a real
ledger row, **137 workable** (51 / 59 / 15 / 8 / 4 across the five bands). The
ten were pinned from that census alone — two lowest RVAs per band — before any
packet content was read.

| band | pinned | landed | outcome |
|---|---|---|---|
| <64 B | `0x000CF211`, `0x000DF3C0` | **0 / 2** | one is not a function; one is 45 of 97 bytes |
| 64–127 B | `0x00085BA0`, `0x000A1FB0` | **2 / 2** | |
| 128–255 B | `0x000D19C0`, `0x001020D0` | **1 / 2** | the miss is a post-link patched body |
| 256–511 B | `0x001062C0`, `0x00151F70` | **2 / 2** | |
| ≥512 B | `0x004DF13A`, `0x004DF520` | **0 / 2** | both blocked on BFME-added statements |

**5 of 10** against a fitted expectation of **2.24**. Under the pre-registered
Poisson-binomial null, P(X≥5) = **0.0441** and P(X = 5) = 0.0356.

**Verdict: INCONCLUSIVE, as pre-registered for 3–5.** 2.2× baseline at p = 0.044
is suggestive and not significant at the ≥6 bar the phase set for "the lever is
real". Ten samples cannot separate the hypotheses: distinguishing a true rate of
0.224 from one of 0.50 at 80% power needs roughly **35 draws**, so a follow-up
should pin 35 by the same rule before the routing question is settled. Do not
revert the queue changes on this result, and do not fund lead generation on it
either.

1,032 bytes moved from byte-dumps to clean C++ (102 + 93 + 162 + 326 + 349); no
`__emit` or naked body in any of the five sources.

### What the misses were actually made of

Not one of the five failures was "the ZH body does not compile close enough" —
every one of them reached the retail bytes and stopped on something else:

- **Retail is patched.** `0x001020D0` `CopyProtect::notifyLauncher` compiles to
  exactly 242 bytes and agrees on 232. All ten that differ are branch opcodes
  the shipped image was patched at after link — `eb 00` at 0x102173 jumps to the
  next instruction, and 0x1021B2 replaces a 6-byte `je` with `jmp` plus four
  `nop` — every one forcing copy protection to pass. Unreachable from C++.
- **The packet address is not a function.** `0x000CF211` is 17 bytes inside the
  55-byte body at `0x000CF200`. `0x004DF13A` is mid-instruction; that body
  starts at `0x004DF130`. Both packets also carry the wrong size.
- **BFME added code Zero Hour has nothing for.** `0x004DF520` is missing exactly
  33 bytes of appended calls, `0x004DF130` clears a `GameWindow` field at
  `+0x1F4`, `0x000DF3C0` appends 52 bytes notifying two unpinned singletons.
  Each needs an identity nobody has yet.

The five landings were the mirror image: the ZH logic was already right and the
gap was **layout** — `State` one member shorter, `Player`/`Team`/the relation
maps shifted, `AsciiString::str()` at +0x08 — plus two MSVC shape lessons
recorded in `reverse/re_attempts.log`.

Three corrections to this file's own instructions, for whoever writes phase 4:

1. Verification step 2 cannot pass as written. `progress.py origin/master`
   reads `+0` **because** the phase requires pushing each body as it lands, so
   there is never an unpushed delta to measure. Prove the bytes against the
   session's base commit, or against the landed rows directly.
2. Packet sizes are not trustworthy. Three of the ten disagreed with the ledger:
   374 vs 349 (int3 padding counted), 804 vs 837, 50 vs 97. Take the size from
   the row, not the packet.
3. Packet boundaries are not trustworthy either — two of the ten were interior
   addresses. Disassemble from the covering dump row's start before believing
   the packet.
