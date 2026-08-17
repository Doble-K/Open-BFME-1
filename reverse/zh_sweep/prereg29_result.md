# Do Zero Hour work packets convert better than a nameless dump?

Pre-registered before any packet was opened (design in build/sweepscan/prereg29.json,
scratch); rerun of an earlier 10-packet test that returned 5/10 INCONCLUSIVE at only
62% power, and which ran against packet metadata since found to be wrong.

## Design

29 addresses pinned by a rule independent of anything believed to predict success:
the lowest RVAs per size band, drawn only from packets nobody had attempted.
Allocation 10/10/6/2/1 across the bands, deliberately unequal because the scarce
bands hold 24/27/6/2/1 workable packets and equal allocation capped n at 15.

Baselines are tools/yield_model.py's fitted LAND_RATE_BY_SIZE: 0.140 / 0.273 /
0.413 / 0.206 / 0.088. The null is Poisson-binomial, not Binomial, because the
draw is stratified across five different rates.

    null mean 7.11        power vs a true 0.50 = 0.87
    REJECT   >= 12        (p = 0.0295)
    DEAD     <=  7        (at or below baseline)
    INCONCLUSIVE 8-11, and to be reported as inconclusive

## Result: 12 of 29 landed. p = 0.0295. REJECT — the lever is real.

    slice 1 (<64 B)      7 / 10
    slice 2 (64-127 B)   4 / 10
    slice 3 (larger)     1 /  9

Robust to the one contested classification: if 0x00647950 leaves the denominator
(its residual byte is a REL32 whose callee the ledger claims at the wrong address),
12 of 28 gives p = 0.0246. Still REJECT.

A "landed" body is byte-exact through ./build.sh at the pinned address, in clean
C++; a naked/__emit body byte-matches by construction and was counted not-landed.

## What the misses were, and why this is not a contradiction

The packets that pointed at the right place converted well above baseline. The
ones that did not, did not — and 51 of the 144 packets carry a banner saying their
address is not a function start.

- Start addresses: in the bad cases the END is correct and only the START is
  derived, from a length the sweep never verified. Packets whose extent came from
  reverse/ghidra_functions.csv had a correct address 3 for 3; those whose extent
  came from the Zero Hour candidate's own length were wrong 6 for 6. Fix: keep the
  end, snap the start to the enclosing ghidra start, recompute size.
  NOT universal — slice 1 re-derived all ten of its boundaries from the PE and
  found delta +0 on every one. Reconcile before treating the rule as general.

  DO NOT implement this as "snap past the leading int3 run". Commit 1c78906e5
  records that mechanism from a two-packet sample where the candidate overshoot
  happened to equal the padding. It does not generalise: of three early-anchored
  packets in another slice the deltas are 2, 1, 13 against int3 runs of 36, 4, 13,
  so snapping to the start of the run would have placed 0x001DC59E thirty-six
  bytes early instead of two — worse than the bug. The slide is (candidate length
  - real length), not the pad.

  The slice that proposed the int3 mechanism then measured it against retail and
  refuted itself: the true runs before its own two addresses are 18 and 21 bytes
  against deltas of 4 and 2, so its starts sit INSIDE those runs. It had seen only
  the 4 and 2 leading 0xCC bytes its packets' quoted ranges happen to begin with,
  and generalised from truncated evidence. Its practice was right — it looked both
  real starts up in the ghidra inventory — and only its write-up was wrong.
  Retracted in fb3c6a70f, which supersedes the record in af52c2d6f.

  DO NOT implement it as a size formula either. Half the bad cases go the other
  way, starting INSIDE the body, where packet_size = real_size MINUS delta
  (0x00747493 245 vs 248, 0x0070F97D 293 vs 306, one of them landing
  mid-instruction inside an 0f 84 displacement). A size rule derived from the
  early cases would silently no-op on those.

  The end-invariance is the only thing true in both directions: keep the end,
  snap the start to the enclosing start in reverse/ghidra_functions.csv,
  recompute size = end - start. No case analysis needed.
- Identity: eight independent packets named the wrong function, one of them a
  function already landed at another address. Identity fails hardest where the
  sweep reports a TIE between candidates.
- Callee pins: a pin marked "(already in the ledger)" is matched by NAME and not
  followed, so it can name a different copy of the symbol than the one retail
  calls. docs/lessons.md already documents this trap at another address.

So the lever is real and the metadata is still broken. Fixing the derivation should
raise the rate further; that is now a funded change rather than a guess.

## Run artifacts, excluded from the tally by rule

Three agents shared one working tree and one index, which is a dispatching error,
not a property of the packets: sibling reverts, contention, and a mid-flight
tools/build.py edit could each have produced a false not-landed. The fix for a
future fan-out is a per-agent `git worktree add --detach`, which one agent verified
by landing seven bodies through one while the shared index was contended.

Ledger blame is fragile: tools/dedup_csv.py rewrites the whole file, and `git log -S`
on an RVA returns the original dump commit because the address string has been there
since the gen_asm dump. Attribute with `git show <sha> -- reverse/functions.csv` and
read the -gen_asm/+real-name pair. Reading it wrong is what made an earlier draft of
this file say INCONCLUSIVE.
