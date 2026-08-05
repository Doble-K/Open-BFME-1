# Road to +20pp C++ coverage: research synthesis, drained 2026-08-04

Written when coverage was 11.58% C++ / 18.34% total. The deterministic avenues
below have now been drained; what is left is recorded as levers, not plans.

## Verdict (unchanged by the drain)

+20pp is not reachable by determinism alone. Measured deterministic headroom was
~0.45-0.6MB and the drain converted 115,005 bytes of it. The only lever with
megabyte potential is class-layout recovery against the ZH engine (below).
Everything else is fleet velocity.

## Drained: what each avenue actually paid

Baseline `4b0f15bbe` — 91,800 matched rows, 2,466,592 unique .text bytes
(12.16% C++ / 18.90% total). Five phases, all byte-verified and pushed:

| avenue | marker | rows | bytes | vs estimate |
|---|---|---|---|---|
| SEH funclets via FuncInfo ownership | `gen-funclet` | 1,280 | 13,368 | est. 73,301 — see below |
| ZH exact harvest, non-STL | `vendored=cnc-zh` | 85 | 6,082 | est. 5,549 |
| libpng 1.0.5 | `vendored=libpng-1.0.5` | 73 | 7,707 | est. 110-220KB with jpeg |
| IJG jpeg-6b | `vendored=jpeg-6b` | 15 | 789 | (same estimate) |
| GameSpy SDK 2004 | `vendored=gamespy-2004` | 465 | 66,919 | est. 100-300KB |
| ZH STLport sites + families | `vendored=cnc-zh` | 401 | 20,140 | est. 100-200KB |
| **total** | | **2,319** | **115,005** | |

Result: 13.06% C++ / 19.78% total (+0.90pp C++, +0.88pp total).

Where estimates missed, the reason is now known:
- **Funclets** paid 13,368B, not 73,301B. The estimate counted every
  FuncInfo-owned funclet; the sweep may only claim one whose parent TU actually
  emits the matching `.text$x` COMDAT, and most owners are MASM dumps or partial
  `*Thunk.cpp` that emit none.
- **libpng/jpeg** paid 8,496B against a 110-220KB estimate: see the VC6 lever.
- **GameSpy** landed at the low end of its range and is the single largest
  deterministic prize the program has banked.

## Premise correction: the toolchain was never "trimmed VS2003"

The original framing said PlatformSDK and atlmfc were "stock VS2003 install
components someone trimmed". Half wrong, and it matters for anyone repeating the
restore:
- `PlatformSDK/` is the **Windows XP SP2 Platform SDK (Aug 2004)**. No VS2003
  media carries a PlatformSDK at all — it cannot be restored from the VS2003
  discs, and its absence was never someone trimming the toolchain.
- `atlmfc/` **is** a genuine VS2003 component (Disc 1) that had been removed.

2026-08-04, maintainer decision: both trees (plus the DX8.1 SDK headers at
build/toolchains/dx81/) are COMMITTED so every clone carries the complete
byte-exact build environment; the earlier .gitignore refusal is reverted.

## The three levers left, in descending value

1. **Class-layout recovery.** BFME is the ZH engine with edited class layouts —
   inserted/removed members and renumbered vtable slots, with small uniform
   per-base-register deltas. 256 sites are confirmed uniform-shift (seed
   equations in the fleet layout artifact; 262 more are already
   identical-displacement, 114 multi-delta). Solve a class's BFME layout once
   and every function touching it becomes reachable, including the small-edit
   functions a whole-sequence matcher rejects. This is the only megabyte-scale
   lever; the whole-image ceiling of the plain exact/fuzzy route is ~156KB.
2. **The EH-frame flag crack.** 167 STLport rows are parked purely because their
   callees do not compile byte-identical here: retail's copies carry no EH frame
   where ours do. Worth ~10.7KB directly, and it would retire the naked `__emit`
   byte dumps the repo already resorted to for exactly those bodies
   (`Code/Libraries/Source/WWVegas/WWLib/*Thunk.cpp`).
3. **A VC6-era `cl.exe`.** libpng and jpeg paid only 8,496B of their estimate
   because retail's copies were built by an older compiler than the VS2003 one
   the gate uses; roughly 73KB of png/jpeg cluster stays out of reach until a
   period-correct compiler is available. Same likely story for any other
   statically-linked C library.

## Closed, do not repeat

- **stlport.diff** (EA's cnc_gzh patch): applies cleanly, but sets
  `_STLP_NO_OWN_NAMESPACE`, putting STLport in `std` while all 574 harvested
  retail symbols are mangled `@_STL@@`. Baseline vendored STLport 538 sites /
  28,735B; patched: does not compile. Do not adopt a second variant.
- **The /MD question**: settled. Retail links the DLL CRT
  (`/MD` + `/D_STLP_USE_STATIC_LIB`); that flag model is now the default.
- **GameSpy provenance**: EA stripped it from the GPL release; the landed copy
  is pristine upstream C from the public Area 51 source release.

## Still open, unpursued

- ~600 hidden EH functions (stubs no known interval references) whose prologues
  would seed boundary recovery in the 1.9MB gap-code residual.
- Naming upgrades: eh_ stubs with matched owners could repoint to
  `__ehhandler$<real>` — identity quality, not bytes.
- zlib crc32/zutil misses and the untested Lua parser/lexer TUs: one flag
  iteration each.
