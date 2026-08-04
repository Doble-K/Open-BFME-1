# Mechanical program: execution state (final, 2026-08-04)

The deterministic drain is COMPLETE. Six phases planned, six executed; the
generator, the conventions and the integrity findings are all landed on
`origin/master`. This file is the program's closing record — what was banked,
what was proved, and what a later session should not re-derive.

## Drain totals

Baseline `4b0f15bbe`: 91,800 matched rows, 2,466,592 unique .text bytes
(12.16% C++ / 18.90% total of a 13,049,856-byte .text).

| phase | avenue | marker | rows | bytes | commits |
|---|---|---|---|---|---|
| 1 | SEH funclets, FuncInfo-owned | `gen-funclet` | 1,280 | 13,368 | f3af87a3e, 0ccb3b4e4, 510717bd0 |
| 2 | ZH exact harvest, non-STL | `vendored=cnc-zh` | 85 | 6,082 | 80ccac73d, b499b0422, b6b3fa02f, 73fb873a5, 5207a3a22, 71091b750 |
| 3 | libpng 1.0.5 | `vendored=libpng-1.0.5` | 73 | 7,707 | fc259afc2 |
| 3 | IJG jpeg-6b | `vendored=jpeg-6b` | 15 | 789 | ad1e1abb4 |
| 4 | GameSpy SDK 2004 | `vendored=gamespy-2004` | 465 | 66,919 | 822528dfe |
| 5 | ZH STLport sites + families | `vendored=cnc-zh` | 401 | 20,140 | f5ae69ab0, 1a6060b38, a3fbde01a (− ed516d1e4) |
| | **total** | | **2,319** | **115,005** | |

Phase 6 then added 105 bytes (`??0FileSystem@@QAE@XZ` restored) and moved 1,617
bytes from ASM-only to C++ (`_send_heartbeat` replacing a wrong MASM claim).

Final: **13.07% C++ / 19.78% total** (+0.91pp C++, +0.88pp total). The
total-exact delta below is the drain's and is stable; the C++/ASM split keeps
moving as the fleet converts dumps, so read it from `progress.py`, not here.

The whole-drain `progress.py 4b0f15bbe` delta reconciles to the byte:

    115,110  drain-marked rows, unique bytes new since the baseline
    +    56  fleet rows added in the same window (956966def, 2 turret forwarders)
    −   501  fleet retraction (467867c89, the AIAttackMoveStateMachine dump)
    ─────────
       114,665 = progress.py "Total exact  delta +114,665 bytes"

The `getLastLadderPort` retraction subtracts nothing, because `_send_heartbeat`
re-covers the identical 1,617 bytes — which is also why the gamespy marker sums
68,536 bytes but contributes only 66,919 *new* ones.

Phases 2 and 5 landed 86 and 404 rows gross; the table is net of one row dropped
by fc259afc2 (since restored, see below) and the three rows ed516d1e4 retracted
(213B). Every per-phase self-report matches the per-commit ledger delta exactly.

## Method findings worth keeping

- **Funclets pay far less than FuncInfo ownership suggests.** The map owns
  ~20,700 funclets, but a row may only be claimed where the parent's TU actually
  emits the matching `.text$x` COMDAT. Most owners are MASM dumps or partial
  `*Thunk.cpp` that emit none, so 1,280 of a nominal 73KB pool landed.
- **Retail does not fold identical COMDATs.** It keeps 8-9 copies of each
  template instantiation's helpers. Two real names on one (rva,size) therefore
  means an over-claim, not an ICF alias — swept and retracted in ed516d1e4, and
  now written into AGENTS.md as standing guidance.
- **REL32 resolution, not masked bytes, gates STLport rows.** Follow the E9
  incremental-link thunk to the body, verify the body reproduces the compiled
  callee outside its reloc slots, then pin name→body in symbols.csv; build.py
  maps a pinned body back to all its thunks. 98 such pins unlocked 100 rows.
- **`vendored=<lib>-<ver>`** is the convention for third-party bodies: real
  upstream identities, never `gen-` prefixed, upstream provenance in a file
  header comment, sources at their official BFME path, pristine C TUs compiled
  against `reference/shims/gamespy/` rather than a real Platform SDK.

## Integrity queue: dispositions

| # | item | outcome |
|---|---|---|
| 1 | DIR32 gate dropped valid rows on `__ehhandler$*` | FIXED — 4a80433f2 |
| 2 | malformed 9-hex address in symbols.csv | FIXED — 19ce96f89, plus a gate rule |
| 3 | `?getLastLadderPort@CustomMatchPreferences@@QAEGXZ` claims 1,617B | WRONG CLAIM — retracted and replaced, 5769a2191 |
| 4 | ICF pair at 0x000E3F80 | FIXED — FileSystem was the wrong half; see below |
| 5 | 87 round-1 `uw_` rows with contested `parent=` notes | DOCUMENTED, deliberately not rewritten — see below |
| 6 | Microsoft SDK trees one `git add build/` from being committed | FIXED — b5c2b796a |
| 7 | stray `origin` ref | NOT REPRODUCIBLE, nothing to remove — see below |
| 8 | `next_work.py` timing at final scale | OK: 1.53s at 94,121 rows (target <10s) |
| + | a drain row silently dropped by an unrelated commit | FIXED — e8a071e1e |

### 1. DIR32 `__ehhandler$` exemption (fixed)

`__ehhandler$<mangled>` is the same case as the `$L`/`$T`/`$SG` local labels the
gate already exempts, one step out: the compiler emits one per TU alongside the
COMDAT it guards, and since retail does not fold COMDATs, an instantiation
claimed at N retail addresses legitimately resolves its handler to N stubs.
Measured before the change: 122 inconsistent symbols, 120 whitelisted, **2 NEW —
both `__ehhandler$*`**, zero non-exempt. After: 0 new. Red-green held (removing
`?CRC32_Table@@3PAKA` from the whitelist still fails the gate with exit 1).

### 2. The nine-digit addresses (fixed)

Three symbols.csv rows carried a nine-hex-digit address:
`?_M_allocate@?$__node_alloc@$00$0A@@_STL@@CAPAXI@Z` (`0x00082E540`),
`?clear@?$_List_base@VQueuedDownload@@…` (`0x000627270`) and
`?set@ParseStringData@@QAEXPBDH@Z` (`0x000887D20`). Each was one **leading** zero
too many, so `int(address, 16)` parsed every one of them to the right value and
no consumer is width-sensitive — the ledger was never wrong, only mis-spelled.
`0x887D20` is confirmed correct independently: the first instruction of
`parseSystemCallback` at 0x487818 is `call 0x00887D20`, and three sibling calls
in the same function reach 0x887B60 / 0x887940 / 0x887C90, the same
string-setter cluster.

check_csv now rejects **more than** eight hex digits (a value that cannot be a
32-bit RVA in any spelling, hence always a typo). It deliberately does not
require exactly eight: 342 rows across both ledgers are legitimately short and
only inconsistently zero-padded. One empty record next to the ParseStringData
row was dropped at the same time.

### 3. `getLastLadderPort` (wrong claim, retracted and replaced)

The row claimed 1,617 bytes at 0x856900 from a MASM dump, which byte-verifies at
any length under any name — the gate could never object. Four disproofs:
EA's own ZH source has `CustomMatchPreferences::getLastLadderPort` as an
eight-line accessor (`UserPreferences.cpp:462` — a `find`, an `end()` compare,
then `atoi`); the identical function on the sibling class is 84B at 0x000ABF10
in the UserPreferences.cpp cluster where `getLastLadderAddr` also sits at
0x000AC1B0; 0x856900 lies inside qr2.c's contiguous run (0x008561F0 …
0x008570F0), ending 15 bytes before `_qr2_check_send_heartbeat` at 0x00856F60;
and the GameSpy landing had already pinned `_send_heartbeat` at exactly
0x00856900 in symbols.csv — it could not land a row there because the address
was already taken by this claim.

Retracted with a `deleted_rows.csv` tombstone, the dump deleted, and
`_send_heartbeat` landed from `qr2.c` in its place (34/34 functions in that TU
byte-verify). Net effect: a wrong identity removed and 1,617 bytes moved from
ASM-only to clean C++.

### 4. 0x000E3F80: FileSystem is the wrong half

`tools/audit_dtor_aliases.py` already frames this: "51 scalar-destructor
address(es) claimed by more than one class. At least 109 of those rows are
wrong: the body installs one vtable, and a vtable belongs to one class." For
this address it reports both names as *unexplained*, because no claimed
constructor installs the vtable in question. Resolving that gap decides it.

The body at 0x000E3F80 installs vtable VA 0x01084BA0 (`mov [esi], imm32` at
+0x1F). Only two sites in .text write that constant: this destructor, and an
unclaimed constructor at 0x000E3F5C immediately before it. The vtable's own
slots resolve to `?loadIniFilesFromLegend@SubsystemInterface@@UAE_NXZ` plus ILT
thunks — a SubsystemInterface-derived class, which both candidates are, so the
slots alone do not decide. **Placement does.** Every matched row in
[0xE3C50, 0xE4300) comes from `Common/RTS/PlayerTemplate.cpp` — the vector
helpers, `erase`, `clear`, `?init@PlayerTemplateStore@@UAEXXZ` at 0xE41A0,
`parsePlayerTemplateDefinition` at 0xE4210 — *except* the two disputed rows.
The ctor / dtor / deleting-dtor / init run contiguously at
0xE3F5C / 0xE3F80 / 0xE4170 / 0xE41A0, which is exactly how MSVC lays one
class's COMDATs out of one TU.

Verdict: `??1PlayerTemplateStore@@UAE@XZ` and `??_GPlayerTemplateStore@@UAEPAXI@Z`
are right; `??1FileSystem@@UAE@XZ` (82B @ 0x000E3F80) and
`??_GFileSystem@@UAEPAXI@Z` (30B @ 0x000E4170) were the wrong half. The second
row even carried `icf-owner=??_GPlayerTemplateStore@@UAEPAXI@Z`, so the alias was
registered deliberately.

**The full gate then proved it independently.** Restoring the FileSystem
constructor row (above) gave `FileSystem.cpp` a second DIR32 reference to
`??_7FileSystem@@6B@`, and the consistency check resolved that one symbol to two
bases: 0x1084BA0 through the destructor row, and 0x109DF10 — FileSystem's real
vtable — through the rest of the TU. One symbol, one address; the destructor row
was the half pointing at PlayerTemplateStore's vtable.

That also explains fc259afc2. The phase-3 executor almost certainly hit this
same red gate, and removed the *new* constructor row rather than the *wrong* old
destructor row — which is exactly why the drop went unexplained.

Both rows are now retracted with tombstones, `FileSystem.cpp` carries a
`// ??1FileSystem@@ present-unmatched` marker in the pattern the file already
uses for its other unmatched members, and DIR32 is back to 0 new. No coverage was
lost: the PlayerTemplateStore rows already claim those bytes.

### 5. The round-1 `uw_` parent notes: do not mechanically rewrite

Recomputing FuncInfo ownership for the 87 pre-drain `uw_` rows (the map CSV
excludes them, because it drops funclets already inside a claimed range) gives:

    40  parent agrees with the FuncInfo owner
     8  FuncInfo names a different owner that a matched row starts at
    27  FuncInfo gives an owner RVA that no matched row starts at
    12  no FuncInfo reaches the funclet at all

Rewriting the 35 contested `parent=` notes was considered and rejected on three
grounds:

1. `tools/gen_small.py` already implements the opposite policy on purpose: "A
   landed row whose parent this map disagrees with is never overwritten here:
   the row already carries a name, so a second attribution has to be reported
   for a human to retract rather than quietly re-pointed."
2. The sweep's contest detector compares the pair `(source, parent)`. Editing
   `parent=` while `source` stays put manufactures a pair the map never emits,
   which converts a currently-*detected* contradiction into a silent one — the
   exact failure mode this queue exists to prevent.
3. The replacement names are lower-confidence than what they would replace.
   Three of the eight point at one 7,882-byte body named
   `?speedUp@FiringTracker@@AAEXXZ`, and one would replace the canonical
   `?gatherDebugStats@W3DDisplay@@IAEXXZ` with the truncated spelling
   `?gatherDebugStats@W3DDisplay@@` that a MASM dump row carries.

The honest reading is that these 35 rows are byte-true but identity-contested,
and the retraction path — not a notes edit — is what would resolve them.

### 7. The `origin` ref (not reproducible)

`refs/remotes/origin` is a directory, not a ref; `.git/packed-refs` has no entry
for it; `git show-ref` lists nothing at that exact path; no ref name is a prefix
of another (no directory/file conflict anywhere in the ref store);
`refs/remotes/origin/HEAD` is a well-formed symref to `refs/remotes/origin/master`;
`git rev-parse origin/master`, `git fetch` and `git pull --rebase` all succeed.
There is no stray ref file to remove. The plausible cause of a one-off error is a
transient ref-transaction race — several agents fetch and push against this one
clone — which is self-healing.

### The row fc259afc2 dropped (fixed)

`??0FileSystem@@QAE@XZ` (105B at 0x1B7D70, landed by phase 2 in 5207a3a22) was
deleted along with its TU `FileSystemCtor.cpp` by the **libpng** commit, with no
mention in the commit message and no `re_attempts.log` tombstone. The TU still
byte-verifies unmodified, so nothing about the claim was wrong. Restored in
e8a071e1e. This is why the phase-2 and phase-5 self-reports and the raw
per-commit deltas differ by exactly one 105-byte row.

## Pre-existing debt the close-out surfaced (not drain-introduced)

The repo's own audits are loud about work that predates this program; none of it
comes from drain rows (the drain added only `gen-funclet` and `vendored=*` rows):

- `audit_dtor_aliases`: 51 scalar-destructor addresses claimed by more than one
  class; **at least 109 of those rows are wrong** — a body installs one vtable
  and a vtable belongs to one class.
- `audit_ret_arity`: 35 rows whose calling convention disagrees with retail's
  `ret` arity.
- `audit_short_rows`: 6 rows with a conditional jump landing past the claimed end.
- `audit_internal_padding`: rows whose body ends well before the claimed size,
  with INT3 padding in between.

These are the highest-value identity cleanups left, and they are all on old MASM
dumps rather than on anything the drain produced.

## Where the durable state lives

- Generator v2 (all engines + 28 passing tests + blacklist): LOCAL branch
  `gen-small-full`, tip `6e08861f4`, committed **with hooks**, no upstream, never
  pushed. The working-tree copies at `tools/gen_small.py`,
  `tools/tests/test_gen_small.py`, `reverse/ghidra_artifacts_blacklist.txt` are
  byte-identical to that tip and stay untracked on master.
- Conventions: `AGENTS.md`. Remaining levers: `plans/road-to-20pp.md`.
- The phase files `plans/phase-1.md` … `phase-6.md` are deleted; the drain is done.
