# Codegen recipes

Full history: docs/lessons-archive.md and git log.
This file is curated, not append-only: edit a recipe in place rather than
appending a new section; the commit message is the place for the war story.

## A naked body passing the byte gate proves nothing

Symptom: `Functions: OK N/N` on a file that is still `__declspec(naked)` /
`__asm { __emit ... }` — the dump reproduces its own bytes by construction.
Removing only the `naked` keyword around a pure `__emit` block also still
passes. Rule: a conversion means NO `__asm`/`__emit` anywhere in the file;
check what is on disk, not the ledger — `status=matched` can be leftover from
the original dump commit.

## A naked row's name is unverified by construction

The byte check is a tautology for a dump, so the attached name was never
tested. Read the body against the claimed signature BEFORE starting: `ret N`
vs the mangled argument list, `or eax,-1` vs a void return, eax loaded vs `_N`
return, this-relative offsets that make no sense for the claimed class.
Example: `??1TooltipUpgrade@@UAE@XZ` ends in `ret 4` — destructors take no
arguments, so the name is wrong whatever the bytes say.

## Row boundary rules

A MASM dump matches at any length (one 231-byte function claimed 1006 bytes
and swallowed three neighbours); a 5-byte row matches any E9 thunk; a 1-byte
row matches every bare `ret`. Before adding or trusting a row: deref the thunk
chain, measure the body by disassembly, and check the claimed address is an
instruction boundary — linear-decode from the containing function's start;
interior `int3` is decisive. Functions from different TUs do not interleave in
the image.

## vptr scheduling: screen before writing

MSVC sinks a constructor's vptr store exactly to the end of the leading run of
same-valued member stores, no further; retail's placement varies. Compare
retail's vptr position against that prediction: if they agree, convert; if
not, park — no source ordering reaches vptr placement.
Members initialised by a member constructor land after the vptr and before the
body; stores between the interim and most-derived vtable groups are base-
subobject member inits, not body statements.

## novtable is one knob with two effects

It removes the interim per-base vtable stores (module ctors writing each
interface vtable twice → once) AND removes that base's unwind entry (all EH
states shift down by one, body a few bytes short). Set it by what retail
shows, not habit. Destructor variant: retail restoring only the base vptr at
the end means the derived class is novtable; a derived vptr store at entry
means it is not.

## Read destructible subobjects off the unwind states

Retail's highest EH state + 1 = destructible subobjects, bases included. A
base gets an unwind entry only if it has a declared destructor — declaring
`~Base();` (undefined) adds the missing frame; a virtual destructor where
retail has none adds a state and shifts every index. A virtual destructor
stores a vptr only in a ROOT polymorphic class; in derived destructors it is
elided as redundant, so "no vptr store AND no base-destructor call" is the
test for non-polymorphic, and neither half alone means anything.

## throw() removes EH frames and temporary unwind states

`new T` carries an EH frame just to call `operator delete` if T's ctor throws;
declaring the reachable constructors `throw()` removes it (an undefined ctor
is assumed throwing). Wider: `throw()` on whatever executes between a
temporary's construction and destruction removes that temporary's unwind
state. Declaring `void __cdecl operator delete[](void *) throw();` (as real
<new> does) removes the state for `delete[]` in a destructor. Scope the
declaration to a TU shim; editing a real shared header is its own tick.
Counter-lesson: the constructor-inlined-into-new-expression shape is NOT
reachable from source (forceinline/throw()/nothrow all tried) — park those.

## SEH shape is a flag, not code

Base build is `/EHs-c-`. Right length but an extra `fs:[0]` prologue means the
per-file `// cl:` line re-enabled exceptions (`/GX-` restores). The
`mov [esp+N],esp` stash before a by-value class argument is the /EHs model;
/EHsc and /EHa add an SEH prologue retail may lack. Probe flags directly with
a throwaway TU and build.py's compile_source instead of round-tripping the
byte gate, and give the probe the same destructible locals as the target.

## x87 flags from byte tests are mostly false

`any byte in D8..DF` matches displacements and immediates: 603 of 753 flagged
functions had no x87 at all. Decode with capstone before believing an x87 (or
any opcode-shaped) label, and re-screen parked rows when a screen is fixed.

## Write the reference's loop; MSVC's rotation is the target

A counted `for`/`while` gets rotated (entry test peeled, value test on the
back edge) and small counted loops get unrolled — `for (i=0;i<4;i++)
size=(size<<8)|b[i]` unrolls two-at-a-time into paired dword/word loads that
no hand-unrolled spelling reproduces. Retail's bottom-tested scan with an
early exit past the loop is `do{}while` plus `goto`; reach for that only when
no plain loop form produces the flow.

## Byte loads widen within the array they belong to

Adjacent byte reads widen to the widest access that stays inside their own
array: `struct { u8 magic[2]; u8 size[4]; }` gets dword+word where a flat
`u8[6]` gets neither. Split buffers into the sub-arrays retail's accesses
imply.

## Register allocation is not source-controllable

Same instruction count, same length, but a different induction base, lea-base
vs direct displacements, esi/edi swapped, or a constant in a different
register: these are compiler tie-breaks with no source lever. Stop permuting
and record present-unmatched. (Distinguish from *placement* of stores, which
source does control.)

## Ordering levers that ARE source-controllable

- Initialiser list emits in declaration order; body assignments emit as
  written. Retail's store order tells you which to use — a flag at +0x54
  stored before the word at +0x50 means body statements, not init list.
- Independent locals initialise in declaration order.
- Switch arms lay out in source order; sort the jump table by target address
  to recover it.
- `x = y` (inline operator= forwarding to set) materialises the destination
  before the argument; `x.set(y)` pushes the argument first.
- A discarded return value becomes a tail jump: retail's real call where you
  emit `jmp` means the function returns something the reference discards.

## A this-adjustment hoists only if the source goes through the owning base

An override of a virtual declared in a *secondary* base is entered with that
subobject's `this`. Reading a member off it directly gives negative
displacements from the entry register:

    ours:   mov esi,ecx / mov eax,[esi-8] / mov ecx,[esi-0xc]
    target: mov eax,[ecx-8] / lea esi,[ecx-0x10] / mov ecx,[esi+4]

Retail materialises the *primary* base once (`lea esi,[ecx-0x10]`) and indexes
forward off it. That is not a scheduling tie-break: it happens because the
reference source calls a helper declared on the primary base, so the adjustment
is a real subexpression with two uses. Spelling the helper's body inline at the
call site removes it, and no permutation of the inlined form gets it back.
Write the wrapper as an inline member of the base that declares it
(`DieModule::isDieApplicable` calling `getDieModuleData()` and `getObject()`),
then call it unqualified. Same instruction count either way, so the size is no
clue -- look at whether displacements off the entry register are negative.

## `delete p` shape reads the type's completeness

Null check + `push 1` + call through vtable slot 0 = complete polymorphic
type (deleting destructor). Plain `operator delete` call = incomplete type.
Complete the class (with virtual dtor) or keep it forward-declared to match.

## A vtable slot belongs to the class that DECLARES the virtual

Reordering a derived header cannot move a base-declared slot. Reference base
classes often carry slots BFME lacks (SubsystemInterface adds six;
MemoryPoolObject's pure getObjectMemoryPool adds one) — one wrong base slot
count shifts every virtual in every derived class. Same-name virtual
overloads lay out in reverse declaration order.

## Temporaries schedule by how visible their type is

An extern, undefined constructor makes a temporary opaque and reorders the
unwind-slot store vs the receiver load; making construction visible (inline
delegation) restores retail's order. When retail inlines part of a string
class, do not derive from StringBase — use a standalone shim class with an
inline `m_text = 0` ctor, a destructor pinned to releaseBuffer, and real ops
via cast to `StringBase<T>*` (the campaignmanagerascii shim is the model).

## Shim headers do not invalidate the build cache

The deps cache keys on content of previously-seen paths; a brand-new shim
compiles nothing ("Compile: 0 of 1 TU(s)") and you diff stale bytes. Change
the source text (any character) to force the recompile, and always read the
build's own compile count before theorising.

## Header edits cost the host-wide full gate — batch them

Any staged header/shim change runs the full gate, serialised host-wide (one
commit queued 44 minutes). Per-file verifies (<8 TUs) take no lock: make every
header edit first, verify each dependent source with `./build.sh`, then pay
the gate once. Never run a per-file verify while a full gate is running.

## Union-merge duplicate row: delete the line by hand, not dedup_csv

The ledgers mix `\r\r\n`, `\r\n` and bare-LF terminators (~94k `\r\r\n` rows)
and `add_match` indexes them by physical line. `tools/dedup_csv.py` rewrites
both files normalised — a ~157,000-line diff that conflicts with every branch
in flight — so ignore the `Fix: dedup_csv` hint for a simple post-merge
duplicate: it is one line, delete it by hand. Union merge can also silently
drop pins during a rebase; check `git status` before pushing.

## Comment lines that start with a mangled name are parsed as claims

find_declared_unmatched.py reads any line starting `// ?` as the next
definition's declared symbol — a wrapped prose comment then fails the claims
gate on an unrelated function. Write names in prose form
(`ControlBar::findNonConstCommandSet`) or keep them off the line start.

## Convert families, not functions

Normalise bodies (zero rel32 operands and image-address immediates), hash
against converted rows AND against other naked rows: ICF-folded twins convert
by substituting the one class name that reaches the mangled symbol;
constructors differing only in vtable address are one reconstruction written
N times. Each landed conversion is a model for whatever still matches it.

## Count the blockers before starting, and stop at single digits

A big function's cost is its least-known callee: count unresolved call
targets against functions.csv/symbols.csv first (GameEngine::init: ~50
independent naming problems). Read the disassembly before building — a bare
`ret` against claimed arguments, or provably dead code retail kept, kills a
candidate in one read. When a body stalls within single digits of exact with
every instruction present, the residue is retail's TU structure (what the
inliner saw), not a spelling — record it and move on.

## Layout facts you can read straight off the bytes

Element size from the `sar`/`shl` pair or a reciprocal-multiply magic
constant; POD-ness from memmove vs an element-wise loop; funclet count = EH-
protected temporaries; an untouched gap between stored offsets is still a
member (declare it, do not initialise it). A raw address literal is honest
where a name would be invented: `(void (*)(MultiIniFieldParse &))0x0043ABC0`
emits the same push as an unattested name without asserting one.

## W3DRopeDraw::buildSegments: two real drifts, then the shim's STL stops it

Worked as the first test of the `callers_of.py --files` queue: the 587-byte dump at
0x0075A990 asserts in `W3DRopeDraw.cpp` and its sole caller
`W3DRopeDraw::doDrawModule` lives there too, so the name had to be one of that
file's eight unmatched functions. `buildSegments` compiled to 602 bytes against the
587 wanted, which is close enough to work. Two drifts came out of it:

- **`NEW Line3DClass(...)` should be `::new Line3DClass(...)`.** Retail calls the
  global `??2@YAPAXI@Z` at both allocation sites. Our `NEW` routes through the W3D
  memory pool, which is what leaves `?allocateFromW3DMemPool@@YAPAXPAXH@Z` and
  `?getClassMemoryPool@Line3DClass@@CAPAXXZ` unresolved. Fixing it took the body
  from 602 bytes to exactly 587.
- **The leading `m_segments.clear()` is an `erase(begin(), end())`.** With `clear()`
  the helper call takes four pushed arguments; retail pushes five. Switching to
  `erase` matched the argument count and the `push edi`, and moved the first
  difference from +0x1A to +0x21.

It still does not land, and the reason is worth writing down because it is not this
function's fault. What is left is a single CSE decision:

    target: mov eax,[esi+0x14]                 push edx / push ecx / push eax / push eax
    ours:   mov edx,[esi+0x14] / mov eax,...   push edi / push ecx / push edx / push eax

Same five values in the same order. Retail reads `_M_finish` once and pushes the
register twice; we read it twice into two registers. That is `vector::erase` doing
`copy(last, _M_finish, first)` where `last` and `_M_finish` are the same read - and
whether they get folded is decided inside the STL header, not here. Hoisting `end()`
into a local changes nothing and `resize(0)` is worse (567 bytes).

So the finding is that **the shim's `vector` differs from BFME's**: our `clear()`
lowers to a four-argument helper where theirs takes five. The three-byte offset from
that one extra `mov` never re-syncs, so 172 of 184 instructions read as different
even though the total size is exactly right. Do not chase the tail of this diff -
size agreement plus a cascade from instruction one means look at the container.

Reverted rather than committed: both edits are almost certainly correct, but the
body does not byte-verify, and changing unverified C++ on inference alone puts a
wrong guess where the next agent will read it as fact.

## A shared shim header is not the place for a member declaration

`ArchiveFileSystem.cpp` did not compile for twelve hours, and the cause is worth
generalising because the change that broke it looked completely innocuous: two
copy constructors were converted to real C++, and their declarations were added
to `reference/shims/archivefilesystem_nosubsystem/Common/ArchiveFileSystem.h`.

Declaring a copy constructor suppresses the **implicit default constructor**, and
`ArchivedDirectoryInfoMap` default-constructs its values. So a TU that merely
*included* the header stopped compiling:

    ArchiveFileSystem.cpp(204) : error C2512: 'ArchivedDirectoryInfo' :
        no appropriate default constructor available

There is a second effect that is easy to miss and does not go away by adding a
default constructor back. With the copy constructor visible in the shared header,
MSVC stops inlining `pair`'s copy constructor in the including TU: retail's
`_Construct` copies the two members individually (`AsciiString` copy ctor, then
`ArchivedDirectoryInfo` copy ctor at `+4`), while ours emits one out-of-line
`pair` copy constructor call. Restoring the default constructor got the TU
compiling and still left that row failing.

**Both effects disappear if the declaration lives in the TU that needs it.**
Guard-suppress the shim and spell the class locally:

    #define __ARCHIVEFILESYSTEM_H_
    #include "Common/AsciiString.h"
    ...
    class ArchivedDirectoryInfo
    {
    public:
        ArchivedDirectoryInfo(const ArchivedDirectoryInfo &);
        ...
    };

The conversions are then kept exactly as they were and the including TU is
untouched. All three verify 18/18.

The general rule: a shim header is compiled into every TU that includes it, so any
change to a class in one is a change to all of them. Prefer TU-local modelling for
anything that only one translation unit actually needs - which is the same advice
that already applies to member offsets and enum widths.

### Two failure modes that hide everything else

A red gate is not always a DIR32 problem, and both of these silence it completely:

- **A TU that will not compile** stops the gate at the compile phase, so DIR32
  never runs. Twelve hours of commits landed behind that wall. When the compile is
  fixed, the DIR32 failures that appear are usually *not* new - check which objects
  emit the symbol (`grep -rl '_$E2' build/match/*.obj`) before assuming you caused
  it.
- **A Windows extended-length path.** `Path.resolve()` returns a `\?\` prefix for
  deep paths on Python 3.14 and `ROOT` never has one, so `relative_to` threw in
  `verify_string_refs` - *after* 157,929 functions had already verified. Fixed by
  `tools/build.py`'s `resolved()` helper.

And the payoff for having the gate back: it immediately caught
`RegistryGetUnicodeString.cpp` calling `RegOpenKeyExA` where retail calls
`RegOpenKeyExW`, seen as one symbol resolving to both the A slot (0x01359148) and
the W slot (0x0135914C). The body byte-matches either way because relocation sites
are masked, so no other check in the gate could ever have seen it. **When a symbol
reports two bases four bytes apart in the IAT, suspect A-versus-W before you
suspect a duplicate import.**

## The EH-temporary transposition: one phenomenon, many near-miss bodies

Several bodies in the pairing queue come back at **exactly the right size** with only
four to six differing instructions, and every one of them is the same two
instructions swapped:

    target: 89 64 24 08   mov [esp+8], esp      ours: 8b cc         mov ecx, esp
            8b cc         mov ecx, esp                89 64 24 08   mov [esp+8], esp

Confirmed instances so far, all `--source`-paired against real C++ that is
otherwise byte-identical:

    435B  0x004D7740  PopupJoinGameSystem     (2 sites, 4 diffs)
    446B  0x004C8910  GameInfoWindowInit      (2 sites, 4 diffs)
    737B  0x004DEB70  PopupReplaySystem       (3 sites, 6 diffs)

The construct is always a `UnicodeString` passed **by value** -
`GadgetStaticTextSetText(GameWindow *, UnicodeString)` - so MSVC copy-constructs the
argument on the stack, sets `ecx` to its address, and records that address in a
frame slot so the unwind funclet can destroy it if the call throws. Retail records
first and loads `ecx` second; we do it the other way round. Both orderings are
correct, the byte count is identical, and the rest of the body matches exactly.

Levers already tried, none of which move it:

- `UnicodeString.TheEmptyString` versus `UnicodeString::TheEmptyString`. Note that
  MSVC 7.1 accepts the dot form on a type name and generates identical code, so
  that spelling in the tree is not a drift even though it looks like one.
- The callee signature: ZH declares the parameter by value and so do we, so this is
  not a by-value-versus-const-reference mismatch.

Do not spend a session picking at one of these bodies. They are worth attacking as
a family, and the way in is a TU whose flags differ, not a source rewrite - a
matched body containing the *same* construct would prove which flag flips the
order. Until then, treat "right size, four diffs, `89 64 24` against `8b cc`" as a
known-unfixed classification and move to the next candidate.


## The baseline exe is not entirely compiler output

`CopyProtect::notifyLauncher` at `0x001020D0` will not match, and the reason is not
in our source. The target's branch shape is impossible for a compiler to emit:

    0x0010211F   eb ..      jmp    (where the port emits 75 .. jne)
    0x00102173   eb 00      jmp    to the very next instruction
    0x001021B2   eb 04      jmp    followed by 90 90 90 90

A `jmp` whose displacement is zero, and four `nop` bytes padding the middle of a
body, are what a **hand patch** looks like: someone disarmed the copy-protection
checks in place, keeping every instruction boundary so the file length did not
move. `baselines/bfme1/workshop-vanilla-1.03` is a redistributable, not a pressed
retail image, and this is where that shows.

The damage is narrow. The other three `CopyProtection.cpp` bodies --
`isLauncherRunning`, `checkForMessage` and `shutdown` -- byte-match from clean C++,
so only the checks that actually gate the launcher were touched. But the rule
generalises: when a diff is *only* conditional branches turning unconditional, or
shows `nop` runs inside a body, suspect the binary before rewriting the source. No
amount of C++ reproduces a patch.
