* When hand-declaring a class just to carry a naked body's decorated name, the access specifier is part of the name: MSVC encodes public as Q, protected as I and private as A in the third character (`??0X@@QAE@XZ` vs `??0X@@IAE@XZ`). Declaring DisconnectManager's constructor under `protected:` produced ??0DisconnectManager@@IAE@XZ and the build failed with "symbol not found in object" rather than a byte mismatch, which is the tell. Match the reference header's section, not just the signature.

* A byte-exact function needs every call site to resolve, so a big function's
  cost is set by its least-known callee, not by its size. GameEngine::init is
  7123 bytes with 165 distinct call targets: 92 are named, 73 are not. Of those
  73, sixteen are the 154-byte initSubsystem bodies that cannot be claimed until
  their T is proven, and only seven reference a string that could anchor a name
  -- the other fifty have no evidence attached to them at all. So init is not
  blocked on effort or on codegen, it is blocked on roughly fifty independent
  naming problems, and counting them is cheaper than discovering them one
  mismatch at a time. Run the same count before committing to any large
  function: for each call, deref the thunk chain and check functions.csv plus
  symbols.csv. Applied to the 96 INI block parsers the same count sorts them
  into four with no blockers, eleven with exactly one, and the rest with two or
  more, which is a work queue rather than a list.

* A MASM dump byte-matches at any length you give it, because it is the retail
  bytes. That makes an over-long dump row invisible to the verifier in a way an
  over-long C++ row is not: ?parse@DataChunkInput@@QAE_NPAX@Z claimed 1006 bytes
  where the function is 231, ran past its ret 0x10 and the int3 padding after it,
  and silently swallowed three later functions -- one of which, LocalFile's
  constructor, then could not be claimed because its address was already inside
  somebody else's range. tools/audit_short_rows.py looks for the opposite
  mistake. Check a dump row's size against a real disassembly before trusting
  it, especially when a claim inside its range mysteriously will not land.


## A mangled name can encode an argument list the body does not have

`?queueSend@Transport@@QAE_NIGPBEH@Z` mangles four parameters
(`UnsignedInt, UnsignedShort, const UnsignedByte *, Int`), so a `__thiscall`
body would end in `ret 0x10`. BFME's body at 0x00683830 ends in `ret 0xc`, and
the caller (`NAT::sendAProbe`, 0x00671020) builds a local
`{ UnsignedInt ip; UnsignedShort port; }` on the stack and passes its address --
the callee reads `[ecx]` and `[ecx+4]` off it. BFME merged the reference's first
two scalars into one struct-by-pointer, so the name in the ledger cannot be the
name retail's linker emitted, and the struct's type name is not recoverable
from a POD with no RTTI.

The row is harmless as long as it only claims the 5-byte thunk, which is what it
does, but it will silently mislead anyone who trusts the name to write the body.
Check `ret imm16` against the mangled parameter list before writing a body from
a thunk-claimed name: the stack-pop is free evidence and it disagrees loudly.

## Compilers pick an induction base by a tie-break you cannot see from the source

`Transport::Transport` clears two 128-element arrays in one loop, and every
candidate base address gives the same instruction count and the same total
length. Retail anchors on `&m_inBuffer[i].length`; writing the out buffer first
anchors on `&m_outBuffer[i].length`, writing the in buffer first anchors on
`&m_inBuffer[i].data`. All three are 182 bytes of the same instructions. When a
body reaches the right length with the right instructions and differs only in
which base register displacement scheme was chosen, source-order permutations
are unlikely to be the lever; stop permuting and mark it present-unmatched.

* tools/find_declared_unmatched.py reads the `//` comment line immediately above
  a definition as that definition's declared symbol, so an explanatory comment
  whose line *begins* with a mangled name is taken as the symbol and the
  pre-commit hook rejects the file. This cost three cycles in one session --
  `// ??_7RAMFile@@6B@ is at 0x01143C58, which...`,
  `// ?newTerrain@TerrainTypeCollection@@, on the same receiver...`, and
  `// ?findNonConstCommandSet@ControlBar@@ -- so it is the CommandSet parser`.
  Write the name in prose form (`ControlBar::findNonConstCommandSet`) or push it
  off the start of the line. The failure looks like "staged sources define
  functions the ledger does not declare" for a function that is plainly in the
  ledger, which is the tell.


## A claimed address that is not an instruction boundary cannot be a function

MASM byte dumps byte-verify against whatever bytes they were cut from, so a dump
cut out of the middle of the wrong function passes the gate forever. Eight rows
in the ledger were exactly that, 4,502 bytes of coverage that was never real.
Every one of them claimed an address that lands *inside* an instruction of the
function containing it -- one of them three bytes into a `cmp`, another one byte
into an SEH prologue's `mov eax, fs:[0]`.

The test is decisive and needs no judgement: linear-disassemble from the
containing function's start; if the decode walks straight over the claimed
address without landing on it, the row is wrong. `tools/audit_claim_boundaries.py`
does this and stays silent on everything ambiguous -- a desynced decode, a claim
in a gap, a claim that is itself a known function start. That is why it finds
eight rows where two earlier attempts at ledger auditing found thousands of
things that were fine and got thrown away.

Two of the eight were also blocking real work: the bogus range covers the
function the dump was cut from, so no honest claim on that function can be
added while it exists. `?setGameOptions@GameSpyInfo@@UAEXXZ` sat 198 bytes
inside `NAT::notifyUsersOfConnectionFailed`, in a different translation unit
entirely -- which is its own tell, since functions from different TUs do not
interleave in the image.

* A row whose size makes it unfalsifiable can carry a wrong name past every check
  the gate has, and there are three shapes of it. A MASM dump is the retail
  bytes, so it matches at any length -- ?parse@DataChunkInput@@ claimed 1006
  bytes against a 231-byte function and swallowed three later ones. A five-byte
  thunk row matches any ILT entry, because every one is E9 xx xx xx xx --
  ?showBuildTooltipLayout@ControlBar@@ claimed the thunk whose body is
  ?friend_lookupScience@ScienceStore@@, and ?undoNamedMapReveal@ScriptEngine@@
  claimed the one whose body is ?removeNamedMapReveal@ScriptEngine@@. A one-byte
  row is a bare ret and matches every empty function in the image.
  For all three the test is the same and it is cheap: deref the thunk chain or
  measure the body by disassembly, then ask what the ledger already says that
  address is. Do it before adding the row, not after a mismatch elsewhere sends
  you looking.
  Note the comment trap interacts with this: writing the evidence into the source
  as `// ?showBuildTooltipLayout@ControlBar@@ claimed ...` makes
  find_declared_unmatched.py read that line as the next definition's symbol. The
  lesson above about prose form applies to the comment documenting this one --
  which is how it was hit for the fourth time in a day.

## Adding a shim header does not invalidate the build cache

The deps cache records the headers a TU resolved *last* time. A brand-new shim
header is a path it has never seen, so adding one and rebuilding reports
"Compile: 0 of 1 TU(s) (deps-cache: 1 current)" and silently compiles the old
output. This cost two rounds of "the shim isn't working" before the pattern was
obvious: the compiled bytes had not changed at all, which is the tell -- a shim
that is genuinely being ignored usually still shifts *something*.

Touching the file is not enough either; the cache keys on content. Change the
source, even by a character in a comment, and it recompiles.

## MSVC shaping rules that only turn up as byte diffs

Four of these cost an iteration each before the pattern was obvious. All were
found while matching functions that were otherwise structurally identical.

**A loop is not interchangeable with its unrolled form.** In
`Win32BIGFile::getFileInfo` the compressed-size decode only matched when written
as `for (i = 0; i < 4; i++) size = (size << 8) | header.size[i];`. MSVC unrolls
that two iterations at a time, and that is what pairs the byte loads into the
dword and word accesses retail emits. Every hand-unrolled spelling of the same
value -- including the one grouped exactly the way the target accumulates --
schedules the third byte's load early and loses the pairing.

**Splitting a byte buffer into named sub-arrays changes how loads widen.** The
same function needed `struct { unsigned char magic[2]; unsigned char size[4]; }`
rather than a flat `unsigned char[6]`. MSVC widens a pair of adjacent byte reads
to the widest access that stays inside *the array they belong to*, so `size[0]`
gets a dword and `size[2]`, with two bytes of the array left, gets a word. A flat
buffer gets neither.

**Naming a member through a reference is not cosmetic.** In
`Win32BIGFile::setNameAndPath`, writing `AsciiString &name = m_name;` once
instead of `m_name.set(...)` twice makes MSVC hoist the address into a
callee-saved register ahead of an inlined strlen. That costs the register that
forces `this` onto the stack, which is what grows the frame by the four bytes
retail's `chkstk` asks for. Same code, four bytes of frame apart.

**Initialiser list versus constructor body decides ordering against member
array construction.** `ChunkLoadClass`'s constructor only matched with its first
three members in the initialiser list: members initialise in declaration order,
which is what puts their stores ahead of `HeaderStack`'s 256 element
constructors. Written in the body they land after.

## CORRECTED: WW3DFormat is still dense; only one helper takes D3DFORMAT

This entry previously claimed BFME replaced `WW3DFormat` with Direct3D's own
enumeration, and that this was why the texture pipeline would not scan. The first
half is wrong and the second does not follow.

What is true: the 180-byte function at 0x0090C400 switches on 20 through 30, 40,
41, 50 through 52 and 'DXT1' through 'DXT5', which are `D3DFMT_` values exactly,
and it matches with those values declared locally in `ww3dformat_bits.cpp`.

What was assumed: that its parameter is a `WW3DFormat`. The mangled name
`?Get_Bits_Per_Pixel@@YIIW4WW3DFormat@@@Z` is **not** in `reverse/symbols.csv` --
it was invented when the row was added, so the `W4WW3DFormat@@` in it is a guess,
not evidence. The function takes a D3DFORMAT; the name is what needs revisiting.

The counter-evidence is direct: `WW3D_FORMAT_COUNT` sizes
`DX8Caps::SupportTextureFormat[]` and bounds seven loops in `dx8caps.cpp`, and
`Compute_Caps` (0x0091C230, 2220 bytes) matches today with the dense 26-entry
enum. Sparse D3D values would make that array absurd. So do **not** renumber
`ww3dformat.h`.

The texture pipeline's real blocker is still open. `locate.py` places nothing
from `texture.cpp` (0/53), `textureloader.cpp` (0/67), `surfaceclass.cpp`
(0/27), `ddsfile.cpp` (0/17), `bitmaphandler.cpp` (0/12) or `texproject.cpp`
(0/26). Whatever it is, it is shared across all six and it is not the enum.
Suspect a class layout -- `TextureBaseClass` is the common root -- and find it
the way `HRawAnimClass`'s was found: reconstruct one small function and let the
first wrong byte name the field.

## Header changes cost a full gate, and the gate lock is host-wide

`build.py` takes an exclusive lock for any build over 8 TUs, and the pre-commit
hook runs a full gate for any staged header or shim change. With sibling clones
running their own gates, a header commit sat queued for 44 minutes without
compiling a single TU -- the holder had burned 10 seconds of CPU in that time,
because it was serialised too.

Per-file verifies stay under 8 TUs and take no lock. So the way to land header
work is to make every header edit first, check the blast radius by hand with
`./build.sh` on each dependent source, and then pay the gate once. Landing them
one at a time costs a queue wait each.

Corollary: the union merge on `reverse/symbols.csv` can silently drop pins
during a rebase. Check `git status` before pushing -- two pins the converted
`Set_Animation` bodies needed went missing that way and only turned up because
the working tree still had them.

## Win32BIGFileSystem::openArchiveFile, decoded but not yet landed

0x009CC710, 900 bytes. Everything below is read off the instruction stream and
verified as far as it goes -- a written version matched the whole prologue on
the first attempt, through the file open, the lowercased name, the archive
allocation and the null-file return. It is recorded here so the next attempt
starts from the structure rather than the disassembly.

What BFME does differently from Zero Hour:

- one sixteen byte header read, not three four-byte reads;
- the whole directory table read in a single call into `operator new[]` storage
  and then walked in memory, rather than each entry read a byte at a time;
- `"BIG4"` accepted alongside `"BIGF"`, both loaded through pointer variables at
  0x012D9030 and 0x012D9034 rather than pushed as literals;
- the archive is told its own name through vtable slot 9 before anything else;
- a bad magic is **not** fatal: the parse is skipped but the archive is still
  attached to the file and returned, so the caller gets an empty archive. Only a
  null file pointer returns NULL.

Header, sixteen bytes: magic at +0x00, archive size at +0x04, entry count at
+0x08 big endian, and at +0x0c, big endian, where the entry data starts. That
last one is the allocation size; the read length is it minus sixteen. Entries
are packed back to back: offset and length, both big endian, then a
NUL-terminated name, and the next entry begins at name + strlen(name) + 1.

Callee pins are already in `reverse/symbols.csv`: ArchivedFileInfo's constructor
and destructor at 0x009CC650 and 0x009CC600, `addFile` at 0x009D1110 and
`attachFile` at 0x009CE560.

Two deltas remain, and they are the same delta twice over. The frame comes out
at 0x38 where retail has 0x3c, because retail spills the entry counter to memory
(`dec dword ptr [esp+0x1c]` closes the loop) and the written version keeps it in
a register. Every register choice downstream follows from that, including the
four big-endian decodes, which come out three to six bytes short apiece because
they have a spare register retail does not. Total 61 to 81 bytes short depending
on how the decode is spelled -- and spelling the decode differently does not
help, because the difference is not in the decode. Find the frame slot first.

## To name a global, find its setter and then the setter's callers

`FileSystem::openFile` reads three globals that nothing named. Reading the
global itself is useless -- all three live in `.data`'s zero-fill tail, so their
file bytes are the next section's, and even with correct bytes they are written
at runtime.

What works is going up the write side, one hop at a time:

1. Scan `.text` for the 4-byte little-endian address. `tools/xref_global.py`
   does the claimed half; the unclaimed sites are the interesting ones, because
   a global's *writers* are usually small unclaimed helpers.
2. Disassemble each site. A write that stands alone between `int3` padding is a
   whole setter function -- `0x00061BE2` is literally
   `mov byte [0x0134CB4C], 1; ret`.
3. Scan for `E8` calls to that setter. Setters have few callers.
4. Read the caller's arguments. That is where the name lives.

For `byte_134CA48` the chain ended at `GameEngine::init+291`, which formats
`"Lang\%s"` and passes the result -- so the global is the localisation
subdirectory, and `sprintf("%s\\%s", byte_134CA48, filename)` is the
language-specific lookup path. No other evidence in the image says that.

The same sweep also settled `byte_134CB4C` against the reading that was already
written down. It had been guessed to suppress the archive lookup; the
disassembly shows two archive blocks, one gated on `!flag` before the local
block and one gated on `flag` after it. It selects search *order*, not
presence -- a distinction a byte dump cannot express and a guess got backwards.

Note what the chain does NOT give you: a retail identifier. Knowing a global is
the language path is not knowing what EA called it, so these stay
`byte_134CA48`-style address names. The evidence names the *role*; only a symbol
source names the symbol. Record the role in the header and leave the name alone.

## BFME's pivot fade, and what still blocks the two blend evaluators

`HTreeClass::Anim_Update` (0x00953AD0, 987 bytes) is matched, and getting there
turned up a whole subsystem Zero Hour does not have. The fade lives in four
places:

- `PivotClass::PivotFade` at +0xac, written by `Base_Update`, `Anim_Update`,
  `Blend_Update` and `Slave_Update` alike;
- `HAnimClass` virtual slot 13, a per-pivot fade getter taking the same
  `(pividx, frame)` the visibility getter does;
- `NodeMotionStruct`'s ninth channel at +0x20 -- Zero Hour's struct is eight
  pointers and BFME's stride is 0x24 -- which is where a raw animation's fade
  curve lives;
- and `Blend_Update` lerps the two animations' fades by the same percentage it
  lerps the pose: `fade0 + (fade1 - fade0) * percentage`.

The other BFME change in the same family: `Get_Orientation` returns bool rather
than void. It reports whether the animation has any rotation for that pivot.
`Anim_Update` skips the matrix build and post-multiply when it is false;
`Blend_Update` skips the blend when *neither* animation has one and substitutes
identity for whichever does not.

### What still blocks Blend_Update and Combo_Update

With the fade, the orientation guard and the identity substitution written in,
`Blend_Update` compiles to 1473 of retail's 1746 bytes. The remaining 273 are
one thing: retail **inlines `Matrix3D::Multiply`** there, where our build emits
a call. Retail calls it in `Anim_Update` and inlines it in `Blend_Update`, which
is just MSVC's cost model differing between the two functions -- but our
`matrix3d.h` declares `Multiply` non-inline, so we always call it.

That guess was wrong, and the right answer is simpler. Making `Multiply`
`WWINLINE` breaks five other functions in htree.cpp, because MSVC then inlines
it everywhere. `Matrix3D::mul` is **already** `WWINLINE` and does the same job:
`pivot->Transform.mul(a, b)` inlines where `Matrix3D::Multiply(a, b, &dest)`
calls, and that one substitution takes Blend_Update from 1473 to **1744 of
retail's 1746 bytes**. Two different spellings of the same multiply, chosen per
call site -- that is how retail gets the split.

`Matrix3D::Multiply` did turn out to be worth converting on its own account: its
403 bytes match the reference's ALLOW_TEMPORARIES arm exactly, first try,
despite matrix3d.cpp's own note claiming its codegen had drifted.

The last two bytes were the fade, not the multiply: retail reads **motion1's
fade before motion0's** and keeps both results on the x87 stack, where reading
them in the written order makes MSVC spill one and add it back from memory --
`fadd st,st(1)` against `fadd DWORD PTR [esp+0x18]`, two bytes. Declaring the
second animation's fade first closes it, and Blend_Update now compiles to
**exactly 1746 bytes**.

What survives is one operand ordering. Retail's inlined `submul` runs its three
products X, Z, Y -- (0x38 x [esi+0x44]), (0x58 x [esi+0x4c]), (0x48 x
[esi+0x48]) -- and ours runs them Z, Y, X. Things that do **not** move it:
splitting `postMul(Build_Matrix3D(q,mtx))` into two statements, moving `mtx`
inside the rotation block, or using the temp-taking spelling
(`Matrix3D pre = t; t.mul(pre,mtx)`, which costs 124 bytes instead). `submul` is
a shared WWINLINE that `Anim_Update` already matches through, so the ordering is
a scheduling artifact of the larger function rather than a spelling of the
source. That is the whole remaining distance.
## An inlined member call materialises its receiver at the inline site

`File::open` came out six bytes long and would not shrink. The extra bytes were
a `push esi`/`pop esi` pair and a loop-align nop, and the cause was one
instruction in the wrong place: retail computes `lea ecx,[edi+4]` immediately
before the `set` call, and we computed it before the null-check branch.

That one hoist cascades. Holding `&m_nameStr` in ecx across the branch means the
inlined strlen loop cannot use `cl`, so it uses `dl`; that pushes `filename` out
of `edx` into a callee-saved register; that is a third `push`/`pop`; and the
extra instructions push the loop off a 16-byte boundary so the compiler inserts
an align nop. Six bytes, none of them at the site of the actual difference.

The trigger is that `m_nameStr = filename` goes through `AsciiString::operator=`.
When an inlined member call is expanded, its receiver is a *parameter* of the
inlined body, so it is materialised where the body is spliced in -- the dominator
of everything inside, including the `s ? strlen(s) : 0` diamond. Writing the same
expression as a direct call on the member instead:

    ((StringBase<char> *)&m_nameStr)->set( filename, filename ? (int)strlen( filename ) : 0 );

lets the receiver sink to the call it belongs to, and retail's shape falls out
on its own -- one callee-saved register, `push len; push filename; lea ecx,[edi+4]`.

This is the same expression either way; only the spelling differs. So when a
function is a handful of bytes long and the diff is register choice rather than
control flow, suspect an inlined operator or accessor whose receiver got hoisted,
and try spelling the call out. Hoisting an address above a branch is cheap to
cause and expensive to spot, because the byte that differs is nowhere near the
line that caused it.

## Combo_Update's fade is accumulated, and it calls Multiply where Blend_Update inlines it

Two things fall out of retail's `HTreeClass::Combo_Update` (0x00954D90, 1753
bytes) that do not carry over from its sibling.

**The multiply spelling does not generalise.** Retail calls `Matrix3D::Multiply`
here -- `call 0x008D80C0` at 0x00954E99 -- where `Blend_Update` inlines the same
operation through `Matrix3D::mul`. So the two spellings really are chosen per
call site in the original source, and substituting one for the other everywhere
is wrong in both directions.

**The fade is summed, not lerped.** Inside the same loop that ors the
visibilities together:

```
009553C5  call dword ptr [eax + 0x34]      ; the slot-13 fade getter
009553C8  fadd dword ptr [edi + 0xac]      ; += PivotFade
009553CE  fstp dword ptr [edi + 0xac]
009553D7  fld  dword ptr [esp + 0x48]      ; a running count
009553DC  fadd dword ptr [0x01075334]      ; += 1.0f
009553E5  fstp dword ptr [esp + 0x48]
```

and the count is reloaded once the loop ends, so the accumulated fade is
averaged over the animations that contributed. That is a third fade rule, after
`Anim_Update`'s straight read and `Blend_Update`'s lerp.

The C++ body also compiles 96 bytes **longer** than retail's, which points at
the pivot-weight-map handling in the reference having no counterpart in BFME --
retail's HAnimComboClass calls in this function are `Get_Motion`, `Get_Frame`
and three others, with nothing that looks like `Get_Pivot_Weight_Map`.

## Never pass `--no-verify` to `tools/add_match.py`

It writes `matched` into the ledger without building, so it manufactures a claim
that is simply false. Doing this to `HTreeClass::Combo_Update` repointed the row
from its MASM dump to `htree.cpp` and staged a lie for commit; only the
pre-commit full gate would have caught it, tens of minutes later. If a row needs
to move while the answer is still unknown, leave it on the dump.

## A folded body is not evidence about the class it is named after

MSVC folds identical COMDATs, so one address can serve many symbols, and a row
naming that address is only as good as whoever assigned it. Two rows claimed
`NodeMotionStruct`:

- `??0NodeMotionStruct@@QAE@XZ` at 0x005CD350 -- a constructor zeroing *eight*
  dwords
- `??_ENodeMotionStruct@@QAEPAXI@Z` at 0x005D5B60 -- a vector deleting destructor
  whose element destructor is `mov [ecx],0x1073744; ret`, a vtable store

`NodeMotionStruct` has no vtable, so the second was impossible on its face, and
neither address had a single xref. Both were generic bodies that happened to
compile the same.

The way to identify a constructor is to find the site that *passes* it: an array
`new` hands the constructor to `` `eh vector constructor iterator' `` as an
immediate, alongside the element size. `xrefs_imm(IMAGE_BASE+candidate)` found
exactly one site for 0x009594A0, and it was HRawAnimClass's node-motion
allocation -- `lea ecx,[esi+esi*8]` (nine dwords), `push 0x24`, result stored to
`[ebp+0x4c]`, which is the field `HTreeClass::Anim_Update` reads back.

## BFME's NodeMotionStruct has nine channels, and the ninth is a fade

Zero Hour's is X, Y, Z, XR, YR, ZR, Q, Vis -- eight pointers, 0x20 bytes. BFME
inserts a `MotionChannelClass * Fade` **ahead of Vis**, so Vis moves to +0x20 and
the array stride becomes 0x24. Three independent confirmations:

- `nodeMotion += 1` compiles to `add esi,0x24` (0x0095468B)
- the allocation pushes 0x24 as its element size (0x0095AE37)
- `~NodeMotionStruct` destroys +0x1c through `MotionChannelClass::~MotionChannelClass`
  (0x00978140) and +0x20 through a different one (0x00978160, BitChannelClass)

The destructor is worth a second look: it deletes X..Q, then **Vis, then the
fade**, even though the fade is declared first. Declaration order sets the
layout; the destructor body is hand-written and simply appends the new delete to
Zero Hour's existing run. Both orders have to be reproduced, and they differ.

## HAnimComboDataClass has no PrevFrame

Retail exposes exactly two float accessors on it, `fld [ecx+4]` and `fld [ecx+8]`,
and both `Get_` and `Peek_Pivot_Weight_Map` read `[edx+0xc]`. Three dwords ahead
of the pivot map leaves no room for a third float. `Combo_Update` multiplies the
+8 one by the pivot map entry and gates on it being non-zero, so it is the
weight, and the class is HAnim, Frame, Weight, PivotMap, Shared.

Our ledger had the +8 accessors named `Get_`/`Set_Prev_Frame`. Renaming them to
their Weight spellings keeps them matched -- the bytes never changed -- and drops
`Set_Frame` back to a plain store instead of Zero Hour's `PrevFrame = Frame;
Frame = frame;`, which let four more accessors land at once.

## BFME's HAnimClass is 0x10 bytes -- there is no embedded-sound bone

`HTreeClass::Anim_Update(HRawAnimClass*)` came out 2046 of 2047 bytes with a
single byte wrong: `mov esi,[esi+0x4c]` against our `+0x50`. That byte is
`Get_Node_Motion_Array`, and every member ahead of it is fixed, so the base class
was one dword too large.

`HAnimClass : public RefCountClass, public HashableClass` is two vptrs, `NumRefs`
and `NextHash` -- 0x10 exactly -- with no room for Zero Hour's
`EmbeddedSoundBoneIndex`. Its three accessors were declared *after* `Class_ID`,
so they sat at slots 23-25 and removing them costs no slot anything reaches.
Corroboration: both `Animatable3DObjClass::Set_Animation` bodies that were
reconstructed from retail contain no embedded-sound code at all, while the
unmatched Zero Hour copies in `animobj.cpp` do.

## CORRECTED: MotionChannelClass has no CompressedData at all

This entry previously concluded that `CompressedData` survives in BFME but sits
past `LastFrame`, because deleting it also deletes `Do_Data_Compression` -- its
only caller -- and that function is the only thing in the tree that emits
`WWMath::Float_To_Int_Floor`, which owned a matched row.

That reasoning preserved a row at the cost of the layout, and the layout was
wrong. `HRawAnimClass::read_channel` allocates the class at 0x00959AF6 with
**push 0x20**: eight dwords, which is PivotIdx, Type, VectorLen, ValueOffset,
ValueScale, Data, FirstFrame and LastFrame with nothing left over. The
constructor at 0x00977760 confirms it -- it zeroes +0 through +0x14 and sets
+0x18 and +0x1c to -1, then stops.

So `CompressedData` and `Do_Data_Compression` are both gone, and the
`Float_To_Int_Floor` row was dropped: nothing in the tree emits it any more.
Retail does contain it, at 0x007239D0 with no callers at all, so some other BFME
translation unit emits it as dead code; whoever finds that one can restore the
row there.

The general lesson stands but with the priority the other way round: removing
code can delete a matched symbol, and you should notice when it does -- but a
row is not worth a layout. Fix the layout, then go find where the orphaned
symbol really lives.

## Texture pipeline: what is actually known, and the three sibling vtables

`locate.py` places nothing from any of the six texture sources -- 0 of 152
functions across `texture.cpp`, `textureloader.cpp`, `surfaceclass.cpp`,
`ddsfile.cpp`, `bitmaphandler.cpp` and `texproject.cpp`. The nine "ambiguous"
hits it does report are all 30-byte `??_G` scalar deleting destructors resolving
to the same six addresses -- folded bodies, worth nothing (see the folded-body
entry above).

`bitmaphandler.cpp` is the useful datapoint: its twelve functions are static and
take no object, so no class layout can be blamed, and they still do not place.
That points at rewritten bodies rather than one shared structural fault.

Three sibling vtables in the family, all reached from constructors around
0x0090E3D0:

```
VA 0x0113A668   stored at 0x0090E4A1
VA 0x0113A6B0   stored at 0x0090E5A1
VA 0x0113A6F8   stored at 0x0090E8AD and 0x0090E9AB
```

All three are 12 slots and share slots 0, 4, 5, 6, 7, 8, 10 and 11; only 1, 3
and 9 are overridden (plus slot 2 in the third). Slot 0 is
`mov eax,[ecx+0x18]; ret`, a plain getter -- **not** a destructor, so whatever
owns this vtable has no polymorphic base, which rules out the `TextureBaseClass`
chain (it derives from `RefCountClass`) and does not fit
`TextureLoadTaskClass` either, whose subclasses override far more than three
slots. Identify the owner before writing anything against these.

Note on addresses: values encoded in instruction operands are **VAs**, and
`IMAGE_BASE` is 0x400000, while the ledger is in RVAs. `read()`/`u32()` in the
probe helper take RVAs, so a vtable printed as `0x0113A668` must be read at
`0x00D3A668`. Getting this wrong returns empty bytes, not an error.
## Destructors are the blind spot of the byte gate

A destructor consists almost entirely of the two operands `build.py` masks:

  * `??1<C>` installs the vptr — `mov [ecx], offset <C>'s vtable` — a DIR32,
    filled in from the target;
  * `??_G<C>` calls the scalar destructor — a REL32, filled in from the target.

Strip those and a destructor is a prologue, a store, and an epilogue. So the
gate tests the *shape* and never the class, and a destructor row can carry any
name at all and stay green forever. This is the same unfalsifiable-size problem
as a 5-byte ILT thunk and a 1-byte bare `ret`, except it is not tied to a size,
so `audit_short_rows.py` and `audit_thunk_rows.py` both walk straight past it.

It is not hypothetical and it is not rare. When this was written the ledger had
205 different class names on 0x005BF290 alone, and 51 scalar-destructor
addresses claimed by more than one class.

What makes it tractable is that the masking has a floor. Identical bodies really
are folded by the linker, and folding really does put several correct names on
one address — so "several names, one address" is not by itself a defect. But
folding cannot join two bodies that install *different* vtable pointers, because
those bodies differ before masking, and a vtable belongs to exactly one class.
So n distinct class names on one body that installs a vtable means at least n-1
are wrong, and that conclusion needs no view on which one is right. By that test
alone, 111 rows are wrong.

Deciding which name survives needs the vptr read back out of the image and
matched against a claimed constructor that installs the same pointer.
`??0RAMFile@@` installs 0x01143C58, so the body at 0x009D19A0 installing
0x01143C58 is `~RAMFile` and the `??1SaveLoadSubSystemClass@@` row on it is
wrong. Note what that attribution rests on: a false `??0` would propagate
through it unchallenged, so confirm the owner against a vtable pinned by a
byte-matched *caller* before editing anything.

`tools/audit_dtor_aliases.py` runs both halves. The general lesson is worth
separating from destructors: whenever a construct's identity lives entirely in
relocated operands, the byte gate cannot see it, and the check has to come from
somewhere the relocation still exists — a vtable, a caller, or a string.

## MSVC lays out same-name virtual overloads in reverse declaration order

`Win32LocalFileSystem::openFile` is a 22-byte forwarder: BFME widened `openFile`
to four parameters and left the two-parameter form calling the wide one. Written
the obvious way —

    virtual File *openFile( const char *, Int );                // meant to be slot 2
    virtual File *openFile( const char *, Int, Int, Int );      // meant to be slot 3

— it compiled to 21 of 22 bytes, with `call [eax+0x08]` where retail has
`call [eax+0x0c]`. Overload resolution was right; the slot was not. Swapping the
two declarations, widest first, fixed it.

MSVC assigns vtable slots to a run of overloads sharing a name in *reverse* of
the order they are declared. So when the target calls one overload through the
vtable, the declaration order in the shim is load-bearing, and the natural
narrow-to-wide reads as the wrong slot.

The symptom is worth recognising because it is easy to misread: a one-byte diff
in a `call [reg+disp]` displacement looks like a wrong slot *number* — a
miscounted vtable — when the count is right and only the ordering is wrong.
Check for an overload set before recounting slots. Anywhere a shim declares two
virtuals with the same name, the order is a decision, not a formatting choice.

## A folded ??_G body can make two pools look like one symbol

Adding `??0HAnimComboClass@@QAE@H@Z` (0x00974820) tripped the gate's DIR32
consistency check:

```
?Allocator@?$AutoPoolClass@VHAnimComboDataClass@@$0BAA@@@0V?$ObjectPoolClass@...@A
    bases ['0x134b128', '0x134bc4c']
```

Retail is perfectly consistent: 0x134b128 is referenced only from the
dx8renderer range (0x009463C1, 0x009463DA, 0x009465F5, 0x00947668, 0x00949CA1,
0x00949CB0) and 0x134bc4c only from the HAnimCombo range (0x009745B1,
0x009745CA, 0x00974881, 0x0097492E, 0x00974E07). They are two different pools'
statics.

Our build conflates them. `PolyRenderTaskClass : AutoPoolClass<PolyRenderTaskClass,256>`
is declared correctly, so this is not a source typo -- it is that
`??_GPolyRenderTaskClass` and the HAnimComboDataClass `??_G` compile to identical
bodies, fold, and the surviving copy carries only one of the two relocations. The
claim at 0x00947668 therefore rests on a folded body, exactly like the
NodeMotionStruct rows did.

The row was dropped rather than whitelisted. Whitelisting would bury a real
ambiguity, and the remaining 31 rows from that batch are unaffected. Resolving it
properly means deciding which of the two `??_G` claims owns 0x00947668 -- do that
before re-adding the constructor.

Watch for this whenever a new row lands near a pooled class: the DIR32 check is
the only thing that sees it, and the per-file verify a delta commit runs does
not.

## The texture pipeline's real blocker: BFME split the texture classes handle/impl

Earlier entries blamed the format enum for `locate.py` placing nothing from the
texture sources. That was retracted above; this is the actual reason.

BFME's texture objects hold a **pointer at +0 to a separate implementation
object**, where Zero Hour's classes hold their state inline. Seven of thirteen
sampled bodies in the 0x0090D000-0x0090E900 cluster open by dereferencing and
null-testing `[ecx]`, then calling virtuals on what it points at:

```
0090DC60  ?Peek_D3D_Base_Texture@TextureBaseClass@@QBEPAUIDirect3DBaseTexture8@@XZ
0090DC61  mov esi, [ecx]        ; the impl, not a vptr
0090DC63  test esi, esi ; je -> return 0
0090DC6B  mov eax, [esi]        ; the impl's vtable
0090DC6F  call [eax + 0x28]     ; ...and its virtuals
0090DC7A  call [eax + 0x2c]
0090DC7D  mov eax, [esi + 0x14]
0090DC80  mov eax, [eax + 8]
```

The impl is **0x48 bytes** and is allocated at 0x0090D211 (`push 0x48`, then
zeroing +4, +8 through +0x20, +0x34 and +0x38). `+0x38` holds the D3D texture --
`Poke_Texture` writes it and 0x0090E810 writes it through the handle.

This is why no amount of faithful porting makes those bodies match: every Zero
Hour texture method reaches its members directly, and every BFME one reaches
them one indirection away. It is a redesign, not an offset fix, and it explains
all six sources at once (0 of 152 placed).

Do not try to salvage this with small corrections. The way in is the same one
that produced 62 animation functions today: establish the two class shapes from
allocation sites, destructors and vtables first, then let locate.py place the
family. The three sibling vtables noted above (VA 0x0113A668/0x0113A6B0/
0x0113A6F8, 12 slots, slot 0 a plain getter rather than a destructor) are
consistent with being the *impl* side of this split, which is why slot 0 did not
look like a destructor.

Beware the small matched rows here when reconstructing: `?As_TextureClass@TextureBaseClass`
and `?Get_Asset_Type@ZTextureClass` are both 3 bytes at the same address
(0x006CF680), and `?Poke_Texture@TextureBaseClass` is 10 bytes at 0x001BD780
that writes `[ecx+0x38]` -- an impl offset. Folded and near-folded rows like
these will not constrain the layout, and may mislead.
## Naming a temporary can decide which stack slot it gets

`ArchiveFileSystem::openFile` is Zero Hour's three lines unchanged:

    archiveFilename = getArchiveFilenameForFile(AsciiString(filename));

and written that way it came out the right length with the right calls, but the
two `releaseBuffer` calls at the end came out in the opposite order. Nothing was
wrong with the lifetimes — both temporaries die at the end of the full
expression either way, and in reverse construction order. What differed was
which stack slot each got: the argument temporary and the returned temporary had
swapped places, and that rippled into the register choices for the rest of the
function.

Giving the argument a name and a block fixed it:

    {
        AsciiString key(filename);
        archiveFilename = getArchiveFilenameForFile(key);
    }

Same lifetimes, same destruction order, same generated calls — different slot
assignment. So when a function is the right length, calls the right things in
the right order, and still differs in `[esp+N]` displacements and register
picks, look at the temporaries before doubting the structure. An unnamed
temporary inside a call expression and a named one in a block are not the same
input to the register allocator, even though they are the same C++.

Worth pairing with the note on inlined member calls materialising their
receiver: both are cases where the spelling, not the semantics, is what the
compiler is responding to.

## A compiler-generated name cannot be checked by anything but its relocations

A full gate failed on a DIR32 conflict:
`?Allocator@?$AutoPoolClass@VHAnimComboDataClass@@$0BAA@@@` resolved to two
different bases, both from `hanim.cpp`. `??0HAnimComboClass@@` gave 0x0134BC4C,
which is that class's pool. A row named `_$E8` at 0x00C71350 gave 0x0134B128 —
the `PolyRenderTaskClass` pool, which `dx8renderer.cpp` owns. So the funclet at
0x00C71350 belongs to a different translation unit, and `hanim.cpp` still
verifies 66/66 without it.

`_$E8` is an exception funclet: a compiler-generated symbol. That makes it the
worst case of the unfalsifiable-row problem, for two reasons at once.

The *body* is unfalsifiable in the usual way — its only distinguishing operand
is a DIR32, which `build.py` fills in from the target, so it byte-matches
wherever you put it. And the *name* is unfalsifiable too: `_$E8` says nothing
about a class, a signature, or a translation unit, so none of the naming oracles
apply. There is no vtable slot to read, no string literal to anchor to, no
sibling class whose method set constrains it. Every technique that resolved a
wrong `??1` or `??_G` row is unavailable here.

What caught it is the one check that looks at the masked operand instead of the
bytes: DIR32 consistency, which noticed that two rows in the same TU disagreed
about where one symbol lives. That only works when the funclet happens to touch
a global some *other* row in the same TU also touches. Thirty-one `_$E` rows
remain in the ledger; none is currently contradicted, but that is the absence of
a coincidence rather than evidence they are right.

So treat a compiler-generated row as carrying no claim at all. If one is
blocking something, prefer deleting it to relocating it — there is nothing in it
to be right about.

## `locate.py --emit` will re-add a row you deliberately dropped

`??0HAnimComboClass@@QAE@H@Z` (0x00974820) is dropped because it trips the DIR32
consistency check -- see the folded-`??_G` entry above. It locates cleanly, so
every `tools/locate.py Code/Libraries/Source/WWVegas/WW3D2/hanim.cpp --emit`
puts it straight back, and the next full gate rejects the commit again. It has
cost two gate runs so far.

There is no suppression list. After an `--emit` sweep, diff the staged ledger
(`git diff --cached -- reverse/functions.csv`) and check nothing deliberately
excluded has returned, rather than trusting `check_csv` -- a re-added row is
perfectly well-formed, so `check_csv` is silent about it.

## If every shell command starts failing, check the session temp directory

Symptom: commands that produce output exit 1 and return nothing, while `true`
and `echo hello > /dev/null` succeed. It looks like the shell died; it has not.
The harness writes each command's output to a file under its session directory
in `/tmp`, and if that directory goes missing -- `/tmp` here is a 16G tmpfs that
sits around 80% full with four clones building -- every command that writes
anything fails while silent ones still work.

`mkdir -p` on the session directory restores it. Until then, `cmd > /tmp/x 2>&1`
followed by reading `/tmp/x` with the Read tool is a working escape hatch, and is
how to run diagnostics (`df`, `ls`) while the capture is broken.

Do not read this as a disk-full problem without checking: the root filesystem had
237G free throughout.

## The near-miss tie-breaks are not a compiler-flag mismatch

A recurring failure looks like this: the body compiles to retail's exact length
with retail's exact instructions, and differs only in which registers hold what,
or in the order of two adjacent stores, or in where one block was placed. It has
now blocked Transport::queueSend, the Transport and NetPacket and Connection
constructors, getNATPortAllocationScheme, FrameDataManager::addNetCommandMsg,
DisconnectManager::processDisconnectVote, and two NAT notify functions.

Nine instances invites the theory that retail's netcode was built with different
optimisation settings than our `-O2 -GR- -EHsc-`. It was not. Tested per-source
against the NetPacket constructor, whose only defect is that retail stores the
vptr before two field zeroes and we hoist an inlined init's stack temp above
them: `-O1`, `-Ox`, `-G6`, `-G7`, `-Os` and `-Oy-` all still fail, and none of
them turns any part of it green.

So these are per-function source problems, not a global setting, and the lever
is the shape of the source -- statement order, whether a value is a named local,
argument evaluation order. When a body is the right length with the right
instructions, stop reaching for flags.

Note also what a global flag change would have to survive: about 14,000 rows
already byte-match under -O2, so any setting that fixes a near-miss must keep
all of those. Per-source `// cl:` flags are the only safe place to experiment.
## Do not run a per-file verify while a full gate is running

A full gate reported two NEW DIR32 inconsistencies:

```
__except_list:    bases ['0x0', '0xd', '0x83000000']
__real@4f800000:  bases ['0x1075358', '0x3b04c083', '0x8f4c8dc0']
```

Both look alarming and neither is real. `0x83000000`, `0x3b04c083` and
`0x8f4c8dc0` are instruction bytes, not addresses, and `__except_list` is a
compiler-internal symbol whose address is 0 by definition.

The cause is concurrency, not the ledger. `verify_dir32_consistency` reads the
`.obj` files, and an `add_match` (or any `build.py --files`) running alongside
rewrites them; the gate then reads a half-written object and the
`final - addend` arithmetic produces garbage. Re-running the check alone
afterwards gives a single base for both symbols and NEW: 0.

Two things follow. Per-file verifies take no lock, which is what makes them
usable while a full gate is queued -- but once the gate is actually *running*,
they corrupt its reading. And a DIR32 failure whose "addresses" do not look like
addresses should be re-checked in isolation before anything is whitelisted or
any row is blamed; the check is a real bug detector (it caught the
AutoPoolClass<HAnimComboDataClass> fold earlier today) and whitelisting noise
would blunt it.

Attribution warning from the same episode: the two outlying sites both landed in
ArchiveFileSystem rows added by peer commits that morning, which made a
tidy-looking story about a TU-scoped STLport shim changing the SEH epilogue.
Both rows verify as exact matches and were never at fault. A plausible culprit
turned up by `git log -S` is not evidence.

## An initialiser list and a body assignment are ordered differently

`MemoryWriteFile`'s constructor zeroes four members and also has an `AsciiString`
member that needs constructing. Retail does it in this order:

    mov [esi+0x14], edx     ; m_data
    mov [esi+0x18], edx     ; m_size
    mov [esi+0x1c], edx     ; m_pos
    mov [esi+0x20], edx     ; m_capacity
    mov [esp+0x14], edx     ; EH state
    mov [esi+0x24], edx     ; m_pendingName's construction

Writing the four as body assignments cannot produce that, and no amount of
reordering the body will. Every member is constructed before the body runs, so
body assignments necessarily land *after* `m_pendingName` is built. Four stores
in the wrong place, and nothing in the body to move.

They have to be initialisers. Members are initialised in declaration order, and
`m_data`..`m_capacity` are declared before `m_pendingName`, so as initialisers
they come first and the shape falls out.

The general form: if a constructor's stores are interleaved with a member's
construction rather than sitting wholly after it, the ones before it are
initialisers. That is a real structural fact about the retail source, readable
straight off the instruction order, and it is one of the few things in a
constructor that the byte comparison can actually tell you.

## Two things that decide what `delete p` compiles to

`Win32BIGFileSystem::closeArchiveFile` came out four bytes short and the wrong
shape in one place. Retail deletes the mapped value like this:

    mov ecx,[esi+0x14]   ; it->second
    test ecx,ecx
    jz  skip
    mov edx,[ecx]
    push 1
    call [edx]           ; deleting destructor, slot 0, delete flag set

and we emitted `mov edx,[edi+0x14]; push edx; call <operator delete>`. Same
source line. The difference is that `ArchiveFile` was only forward-declared, and
`delete` on an incomplete type has nothing to dispatch to, so it degenerates to a
plain `operator delete`. Completing the class *with a virtual destructor* is what
produces the null-check-and-dispatch pair.

So when a `delete` comes out too short, the question is not how the statement is
written — it is whether the compiler can see the type and whether that type's
destructor is virtual. Both are visible in the target: the null check and the
`push 1` before an indirect call are the signature of `delete` on a polymorphic
type, and their absence is the signature of an incomplete one.

The same function also needed exceptions turned OFF. Retail has no SEH frame at
all despite holding an `AsciiString` temporary with a destructor, so the TU was
built without them. `build.py`'s base is already `-EHsc-`; the per-file `// cl:`
line was switching them back on. `/GX-` restores it. Worth checking whenever a
function is the right length but carries an `fs:[0]` prologue the target lacks --
that prologue is not a code difference, it is a flag difference.

## A prose comment starting with `// ?` is read as a symbol annotation

`find_declared_unmatched.py` treats any line whose stripped form starts with
`// ?` as the mangled name of the next definition it sees, and it does not
clear that state until it finds one. A file-header paragraph that happens to
wrap so a line begins with a mangled name -- `// ??0?$StringBase@G@@AAE@...` --
therefore attaches itself to the first function defined dozens of lines later,
which then fails the pre-commit claims gate as an undeclared definition even
though its ledger row is right there.

The symptom is confusing because the reported function is not the one the
comment is about. Reflow the paragraph so no line starts with `// ?`.

This is the same parser state that makes `// <mangled> present-unmatched` work,
and the same reason that marker has to sit immediately above its definition.
## An opaque temporary and a transparent one schedule differently

`Win32BIGFileSystem::init` sat at 109 of 111 bytes for a long stretch. One
instruction pair, twice, in the wrong order:

    retail   push ecx; mov [esp+0xc],esp; mov ecx,esp; push offset "*.big"
    ours     push ecx; mov ecx,esp; mov [esp+0xc],esp; push offset "*.big"

`mov [esp+N],esp` is MSVC recording the temporary's address for the unwind
table. None of the usual levers moved it — explicit temporaries, a declared
rather than inline destructor, access changes, a defaulted argument, and ten
different codegen and exception flags. Nor argument order, which was already
right.

What fixed it was how the temporary's **type** was declared. The shim had

    AsciiString( const char *s );          // declared, never defined

and changing it to a visible delegation

    AsciiString( const char *s ) { ((StringBase<char> *)this)->StringBase<char>::StringBase( s ); }

reordered the pair to retail's. With an undefined extern constructor the
temporary is opaque: the compiler knows only that something happens to it, and
registers it for unwinding after computing the receiver. With the construction
visible it can order the two the other way.

Both spellings are the same program and produce the same call. The lesson is
where to look: when a diff is pure scheduling around a temporary, the lever may
not be at the call site at all but in how completely the temporary's type is
declared. Nothing in the byte diff points there, which is why it is worth
writing down — the same shim is used elsewhere in the tree as a plain extern and
will produce the same two-byte difference in any function that builds one of
these by value.

## `x = y` and `x.set(y)` schedule the destination differently

Two AsciiString setters sat one instruction apart from retail for several
rounds: retail emits `lea ecx,[esi+0x1c]` then `push eax`, and a source
written as `m_x.set(expr)` emits the push first. Nothing about registers or
flags -- the same two instructions, swapped.

The cause is the shape of the call, not the scheduler. Retail's source is
`m_x = expr`, and `operator=` is an inline that forwards to `set`. Inlining
materialises the assignment target before the argument, which is exactly the
order retail shows. Writing `.set()` by hand skips that step and lets the
argument go first.

So when a member-call near-miss differs only in whether the `this` adjustment
precedes the argument push, check whether retail was really calling an inline
wrapper. Reaching for a pointer local (`T *dst = &m_x; dst->set(...)`) can
force the same order, but it is a worse source and it moves the `lea` too
early as soon as the argument is itself a call.

## A nothrow `operator delete[]` declaration removes a spurious EH state

`~NetFileCommandMsg` initialised its EH state variable to 1 and stepped it
down to 0 before destroying its string member, where retail sets 0 once and
never moves. The extra state is the unwind entry MSVC adds for a function
body that can throw while a destructible member is alive -- and the only call
in the body was `delete[] m_data`.

Declaring `void __cdecl operator delete[](void *) throw();` in the TU is what
the real <new> does, and with it the body needs no state of its own. Without
any declaration the compiler assumes the array deallocation can throw.

## A temporary passed by value to an out-of-line function schedules differently

Four of NetPacket's readers sit exactly one instruction pair away from retail
and no closer. Retail writes the temporary's unwind pointer and then loads its
address into ecx:

    push ecx                  ; allocate the temporary
    lea  edx, [esp+0x14]      ; the argument to its constructor
    mov  [esp+0x18], esp      ; record the temporary for unwinding
    mov  ecx, esp             ; this
    push edx

and every source shape tried here emits `mov ecx, esp` before the record. The
difference survives writing the argument as an explicit constructor call, as an
implicit conversion, and via a pointer local.

What separates the readers that DO match is not the temporary -- it is the
call. readFileMessage and readFileAnnounceMessage build the same temporary and
match exactly, because their setter is inline, so there is no by-value argument
crossing a call boundary. The four that miss all hand the string to an
out-of-line setter by value.

So this is not a register-allocation or flag mismatch: it is specific to
materialising a temporary into an outgoing by-value class argument. Worth
revisiting with a matched caller elsewhere in the tree that does the same thing.

## The vptr store sinks unless a member constructor holds it in place

NetPacket's two constructors both start with the vptr store, then zero
`m_dest.ip` and `m_dest.port`, then do their own work. Writing those two zeroes
as ordinary statements makes MSVC sink the vptr store below them and hoist the
inlined `init()`'s stack temporary above everything -- a three-instruction
reordering that no statement order fixes.

Giving the address struct a default constructor puts the vptr first in both,
because member construction is ordered after the vptr and before the body. But
it also makes the struct non-POD, and `m_dest = dest` inside `init()` then
compiles to member-wise assignment (a word store plus the dword pair) where
retail copies the eight bytes as two dwords.

`: m_dest()` is not the answer either -- MSVC 7.1 restructures the whole copy.

So the zeroing reads like member construction and the assignment reads like POD
assignment, and no single declaration produces both. Worth revisiting if a
matched constructor elsewhere in the tree zeroes a POD member and still emits
its vptr first.

## Retail's search loops are bottom-tested; a while/for gets rotated

`Transport::queueSend` scans for a free slot. Retail emits a plain top-tested
body with the bound check at the bottom:

    lea eax, [ebp+0x404]
  L: cmp dword ptr [eax], 0
     je  found
     inc edi
     add eax, 0x40e
     cmp edi, 0x80
     jl  L
     ...return FALSE
  found:

Writing that as `while (...)`, as `for (i = 0; i < N; ++i)` with a `break`, or
as `for (;;)` with an internal `return` all miss -- MSVC rotates the loop,
peeling the first test into a separate `test ecx,ecx` above the loop and making
the value test the back edge. The `for` form additionally unrolls four ways.
Neither `/Os`, `/Ot`, a `volatile` read, a second induction variable nor an
explicit `goto` out of the body prevents it.

`do { ... } while (i < N);` with a `goto` for the early exit produces retail's
shape exactly, because there is nothing left to rotate. Reach for it whenever a
scan loop comes out with a peeled first test.

## Local declaration order picks the register initialisation order

The obfuscation pass next door was one swapped pair away: retail loads the key
constant before the walking pointer, and the source declared the pointer first.
Swapping the two declarations fixed it. Where two locals are initialised from
constants or parameters with no dependency between them, MSVC emits them in
declaration order.

## MSVC lays switch arms out in source order — read the order off the table

`NetPacket::addCommand` is a 29-way switch. Getting the arms to match is not
about the cases themselves, which are one instruction each; it is about their
order in the file. MSVC emits the arm bodies in the order the cases appear in
the source, so writing them in numeric order produces a function of exactly the
right length whose arms are all in the wrong places.

The order is recoverable: sort the jump-table entries by the address they point
at, and the sequence of case values is the source order. For addCommand that is
game command, the three ack stages, the frame command, the per-slot frame
ratios, then the rest -- very nearly the order
ConstructNetCommandMsgFromRawData tests in.

The same table names every handler, so a dispatcher like this can be matched
before any of the functions it dispatches to are owned: pin each arm's target
from the table.

Note the arms encode a thunk one hop further out than `build_call_thunks`
discovers, so pin both the handler body and the address the arm literally
encodes.
## A vtable slot belongs to the class that DECLARES the virtual

`Win32LocalFileSystem::openFile` reached `createDirectory` through `[eax+0x28]`
where retail uses `[eax+0x1c]`, and reordering the derived class's header did
nothing. It could not: `createDirectory` is declared on `LocalFileSystem`, so
its slot number is fixed by the base's layout and the derived class only
supplies the body. Shimming a derived header to fix a slot only works for
virtuals that derived class introduces.

Two things had to change in the base before the offset moved:

  * the declaration order, so the family's own order applies rather than Zero
    Hour's; and
  * the base list itself. The reference `LocalFileSystem` derives from
    `SubsystemInterface`, which contributes six slots and pushes
    `createDirectory` to 11. Standalone it lands at 7, which is retail's. That
    is the same finding already recorded for `ArchiveFileSystem`, so it is worth
    assuming for the rest of the family rather than rediscovering per class.

The same mechanism, one level down, explains a whole-class shift: the reference
`File` derives from `MemoryPoolObject`, which declares a virtual destructor AND
a pure `getObjectMemoryPool`. Two slots, so `File::open` lands at 2 where retail
calls it at `[eax+4]`, and `close`, `read`, `write` and `seek` are each one slot
out behind it. BFME's pooled objects carry only the destructor. A single wrong
base slot count moves every virtual in every derived class.

## Measure the function you think you are measuring

A flag sweep over `Win32LocalFileSystem.cpp` reported that `/G7` took the target
function from 271 differing bytes to 9 -- a spectacular-looking result, and
wrong. The TU had two failing functions, and the tool being swept took the first
`target:`/`compiled:` pair it found in the build output. The 9 belonged to
`doesFileExist`, a 25-byte function that had been matching until `/G7` broke it.
Measured against the function actually under test, `/G7` scores 495, worse than
the 271 it started from.

Retail is not `/G7` in any case, and one byte says so: it emits `inc eax` where
`/G7` emits `add eax,1`, because on Pentium 4 `inc` has a partial-flags stall.
That check costs nothing and would have caught the bad reading immediately.

The tool now requires `--symbol` when more than one function fails rather than
choosing one. Anything that silently picks a subject turns every later
measurement into a measurement of an unknown function, and the numbers still
look perfectly reasonable while it happens.

## A discarded return value turns the last call into a tail jump

`FrameDataManager::addNetCommandMsg` sat one instruction short for a long time:
retail saves esi, calls, restores and returns, where the same body written with
a `void` return compiles to a bare `jmp`. Nothing about the arithmetic differed.

The function returns the `NetCommandRef *` that `FrameData::addCommand` hands
back. With the value returned MSVC cannot tail-jump; with it discarded it can,
and does. The reference declares this one `void`, so the return type is a BFME
change and reading it off the call shape is the only way to see it.

Worth checking whenever a one-call function comes out as a tail jump and retail
has a real call: the missing piece may be a return value the reference throws
away.

## Use the reference's loop form; MSVC's rotation is the thing to reproduce

`readGameMessage` came out wrong when its two loops were hand-written as
guarded `do/while` shapes to mimic the emitted code, and right when they were
written as the reference's plain `for` loops. MSVC rotates a counted `for` whose
index the body never reads into a countdown -- `dec ebx; jne` -- and guards it
with the entry test, which is exactly what retail shows.

That is not in tension with the `queueSend` lesson: there the loop exits early
to a label past the loop, and no `for` or `while` produces that. The rule is to
write the loop the way the source plausibly had it and only reach for a
hand-rotated shape when the control flow genuinely is not a counted loop.

## A short claim can match the TAIL of a real function

`?stringLength@@YAHPBD@Z` is claimed at 0x000A30D4, 13 bytes, from
string_base.cpp, and it verifies exactly. `locate.py` nevertheless keeps placing
`?length@?$char_traits@D@_STL@@SAIPBD@Z` at 0x000A30D0, 17 bytes, and the two
overlap, which makes the full gate refuse to patch.

The bytes settle where the function starts:

```
000A30C8  cc cc cc cc cc cc cc cc      <- padding
000A30D0  8b 44 24 04    mov eax, [esp + 4]
000A30D4  8d 50 01       lea edx, [eax + 1]     <- the 13-byte claim starts HERE
000A30D7  8a 08          mov cl, [eax]
...
000A30E0  c3             ret
000A30E1  cc cc ...                              <- padding
```

Padding either side puts one function at 0x000A30D0 spanning 17 bytes. The
13-byte claim begins four bytes inside it, after the argument load -- and
`?stringLength@@YAHPBD@Z` demangles to `int __cdecl stringLength(char const *)`,
which cannot have a complete body that never touches the stack. It is `static` in
string_base.cpp, so MSVC is free to pass the pointer in a register, and that
13-byte register-convention body happens to equal the tail of the real function.

So an exact byte match at a given RVA is not by itself proof the claim is right:
the range has to start where the function starts. Two rows verifying and
overlapping means one of them is anchored inside the other.

Not changed here -- string_base.cpp owns 165 other rows so nothing is at risk
either way, and it is not mine to retire on inference alone. Whoever owns that
file should decide; the evidence is above. Until then `locate --emit` over any
file using char_traits<char> will keep re-adding the 0x000A30D0 row, and it has
to be dropped again each time.
## A shim on the include path loses to a sibling of the file that includes it

`reference/shims/bfme_mempool/Common/GameMemory.h` corrects one thing:
`MemoryPoolObject` contributes ONE vtable slot in BFME, not the two the
reference gives it (a virtual destructor AND a pure `getObjectMemoryPool`). That
second slot pushes every virtual in every pooled class down by one, so
`File::close` sits at slot 3 and every call through it is wrong — retail reaches
it at `[eax+8]`.

Putting that shim first on the include path fixed `Win32LocalFileSystem.cpp` and
did nothing at all for `ArchiveFile.cpp`. The difference is which file asks for
the header. `Win32LocalFileSystem.cpp` includes `"Common/GameMemory.h"` itself
from a directory with no such sibling, so the `-I` order decides and the shim
wins. `ArchiveFile.cpp` includes `"PreRTS.h"`, which lives in
`reference/shims/sweep/` and asks for `"Common/GameMemory.h"` — and MSVC
resolves a quoted include against the **including file's own directory first**,
which is `reference/shims/sweep/`, where `Common/GameMemory.h` exists. No `-I`
ordering can beat that, because `-I` is never consulted.

The fix is to get there first and let the guard do the work: include
`"Common/GameMemory.h"` in the .cpp BEFORE `"PreRTS.h"`, so `_GAME_MEMORY_H_` is
already defined when sweep's copy is reached. Pulling it in via a wrapper header
does not work — `PreRTS.h` sets up `__PLACEMENT_VEC_NEW_INLINE`, the CRT and
several engine headers before it includes `GameMemory.h`, and that header needs
them.

Two things follow. A shim that appears to be ignored is worth checking for a
sibling before assuming the `-I` order is wrong. And this one is worth trying
wherever a call lands exactly one slot late on a pooled class — it is a
tree-wide fact, not something about these two files.
## Recognise MSVC's inlined CRT intrinsics before hand-writing the loop

A 62-byte strdup resisted a dozen source shapes -- do/while, postfix increment
in the condition, an explicit counter, the length written as distance-to-NUL
plus one -- and every one of them came out a couple of instructions off. The
body is not open-coded at all: it is MSVC's intrinsic `strlen` and `strcpy`
expanded inline, and writing `malloc(strlen(str) + 1)` then `strcpy` matched on
the first try.

The tell for inline `strlen` is the shape:

    mov eax, str
    lea edx, [eax + 1]
  L: mov cl, byte ptr [eax]
     inc eax
     test cl, cl
     jne L
    sub eax, edx

The `lea` of `str + 1` before the loop and the `sub` against it afterwards are
not something a hand-written loop produces -- the compiler folds that to a
single subtraction. Inline `strcpy` is similarly recognisable: it walks the
source pointer and indexes the destination through a precomputed delta rather
than advancing two pointers.

When a byte loop is a couple of instructions off and no source shape moves it,
check whether the original called a CRT function and let the compiler expand it.

## The texture impl class is a BFME invention, not a modified Zero Hour one

The handle/impl entry above establishes that BFME's texture objects hold a
pointer at +0 to a separate 0x48-byte implementation object. This is the part
that decides how to approach the subsystem: that object has no Zero Hour
counterpart at all.

The evidence is a string. The cluster around the impl allocation references

```
0090D112  'dyntex_%08x'
0090E210  "Texture '"
0090EBC8  '.tga'   0090EBF0  '.dds'   0090EC42  '.jpg'
```

and `dyntex_%08x` appears nowhere in `reference/CnC_Generals_Zero_Hour` or in
`Code/`. It is a format for naming a dynamically created texture, and Zero Hour
has no such naming anywhere in WW3D2.

So the texture layer is not a port with drift. There is a class in retail that
was never in the Westwood source, the ported classes hand their state to it, and
every ported body reaches its members one indirection further than ours does.
`locate.py` placing 0 of 152 across all six texture sources is the expected
result, not a puzzle.

What that means for anyone picking this up: do not keep adjusting the Zero Hour
bodies. Reconstruct the impl class first -- its size is 0x48, its constructor
zeroes +4 through +0x20 and +0x34/+0x38 at 0x0090D211, it carries a vtable, the
D3D texture sits at +0x38, and three sibling vtables at VA 0x0113A668, 0x0113A6B0
and 0x0113A6F8 share slots 0, 4, 5, 6, 7, 8, 10, 11 with slot 0 a plain getter
rather than a destructor. The handle classes only make sense once it does.
2026-08-03: tools/land_ambiguous.py currently requires reverse/ghidra_functions.csv, which is absent in this checkout; regenerate that inventory before using the ambiguous-copy pass.
* BFME W3DModelDraw keeps ONE weapon-recoil vector where ZH has WEAPONSLOT_COUNT (3): each WeaponRecoilInfoVec is 12B and retail puts m_renderObject at this+0x28 vs our +0x40 - exactly two vectors. But the bytes come straight back: an already-matched row in the same TU reads a field at +0x58 that retail agrees with UNSHIFTED, so reference/shims/w3dmodeldraw pairs the [1] array with a 0x18 pad right after m_renderObject and all 130 rows survive. Same insert/remove shape as GlobalData - when a class-size hypothesis breaks exactly one matched row, look for the compensating pad before abandoning it. Probe trick for exact member offsets: a scratch TU with '#define private public' and an extern "C" unsigned[] of offsetof(...) values, then read the array out of the .obj (symbol gets a leading underscore: __bfme_probe); note a MINIMAL probe can disagree with the real TU (bases differed by 0x10 here) so build the probe with the TU's own cl line and headers.
* BFME WeaponTemplate is 0x53C bytes, not the 0x1D4 the ZH header adds up to (WeaponStore::newWeaponTemplate @0x1E7F50 passes 0x53C to operator new). A class whose only proven fact is its SIZE takes a tail pad, not a mid-class one: parked after the last member it changes sizeof alone and every existing member offset survives (45/45 rows in Weapon.cpp held). Also: BFME's Debug is polymorphic where ZH's has no virtuals at all - DebugIOCon::Execute @0x891200, DebugIONet::Execute @0x890810 and ExecCommand @0x88ABA0 all call operator<<(const char*) through slot 0x38, so ~1300B waits on triangulating that vtable; inventing 14 dummy virtuals is not viable because the vptr at offset 0 would shift every Debug member.
* BFME Display has THREE more virtuals ahead of getWidth than ZH: ControlBarResizer::sizeWindowsAlt @0x4AB1A0 calls getWidth via slot 0x2C and getHeight via 0x30 where we emit 0x20/0x24, and the pair stays one slot apart in both. reference/shims/display now carries the stubs - and note it must be based on reference/shims/sweep/GameClient/Display.h, NOT the raw reference header: the latter still has the DebugDisplayCallback default argument that vendored RTM cl rejects with C2383 (lesson above), so a fresh copy fails to compile. Display.cpp's setDisplayMode is NOT unlocked by this - it diverges structurally (220B) with extra TheTacticalView vtable calls.
* BFME puts ControlBar's six toggle-button images at this+0x2A0..0x2B4 (setUpDownImages @0x49D160), a uniform -0x40 from the ZH header's +0x2E0. Fixing it needs no pad at all: MOVING the six declarations up so they start where m_animateDownWin2Pos did displaces exactly 0x18 bytes downward into the space the block vacated, so everything from m_transitionHandler onward keeps its offset and all 43 rows in ControlBar.cpp survive. Prefer a move over a pad when the drift is a relocation rather than a size change - and note reference/shims/controlbar is a PARTIAL reconstruction of the class (interior replaced by blobs, ends at +0xFC) that ControlBar.cpp does not use; the new controlbarlayout shim is the full ZH header with one block moved.
* add_match writes the source path VERBATIM into the ledger, and on Windows a wrong-case path still opens fine - so passing NAT.cpp when git tracks nat.cpp lands a row that check_csv rejects at commit time with "source not in git". Confirm the spelling with `git ls-files` before add_match, not with ls.
* GameWindowManager.cpp CANNOT take reference/shims/gamewindow even though that shim already pins the field its dtor needs (GameWindow::m_next @0x1F8, where the unshimmed header gives 0x1E8): opting the TU in breaks 7 of its 112 matched rows outright. So either the shim's GameWindow reconstruction and those 7 rows disagree about the class, or some of the 7 are false matches - resolve that before touching this TU. Separately, CaveSystem::registerNewCave @0x378970 proves only sizeof(TunnelTracker)=0x20 vs our 0x24; the TU merely allocates it, so ANY 4-byte removal would verify and picking one (dropping the Snapshot base? a member?) would be a guess, not a finding.
* A `rep movsd` count IS a struct size pin: GameSpyBuddyMessageQueue::getRequest @0x63C770 moves 0xAE dwords where we emit 0x82, and getResponse @0x63C840 moves 0x219 vs 0xB6 - so BFME's BuddyRequest is 0x2B8 (ours 0x208) and BuddyResponse 0x864 (ours 0x2D8). Tail pads in reference/shims/buddythread fixed FOUR bodies at once (get/add x request/response, 704B) because add* copy the same structs. Scan for lone `mov ecx,<imm>` diffs before assuming a class-layout problem - a size-only pin with a tail pad is the cheapest fix there is.
* The GameWindowManager/gamewindow-shim conflict is RESOLVED, and the shim was the wrong half: BFME moves GameWindow's sibling-list pointers 0x10 later (m_next at +0x1F8, ours +0x1E8) but everything EARLIER is already correct - seven matched accessors in GameWindowManager.cpp pin m_instData.m_tooltipDelay at +0x1C4 and the win*Color array at +0x48. reference/shims/gamewindow spreads the same 0x10 as a BFME-only pointer at +0x04 plus three later fields, which shifts both pins and breaks all seven; its +0x04 field can only coexist with them if something before +0x48 is 4 bytes SMALLER in BFME, which nothing proves yet. New reference/shims/gamewindowlist puts the whole 0x10 immediately before the pointers and landed the dtor + linkWindow with all 112 rows intact. winDestroy still needs more: retail writes a field at [edi+8] where we emit [edi+4], and makes a VIRTUAL call where we emit a direct one.
* BFME's Render2DSentenceClass is 0xC bytes bigger than ZH's: W3DDisplayString embeds TWO of them, and its dtor @0x6F4C50 takes m_textRendererHotKey's address at [esi+0xE0] (ours 0xD4) and m_hotkey's at [esi+0x1B0] (ours 0x198) - +0xC then +0x18 cumulative, exactly one renderer's growth each. A third pin, +0x1C more before m_size (computeExtents @0x6F5420 writes it at +0x1F0), completes reference/shims/w3ddisplaystring. CONFLICT to resolve: computeExtents ALSO needs reference/shims/displaystring's claim that DisplayString has only one base virtual (its two vtable calls are one slot early), but adding that shim regresses the dtor from 0 to 19 diffs - the two cannot both be right, and the dtor is the one backed by field pins, so it is what landed.
* Two size-only pins in PeerDefs, and they NEST: GameSpyStagingRoom is 0xA8 bigger in BFME (removeStagingRoom @0x632A50 takes one by value and pops 0x468 where we emit ret 0x3C0) and GameSpyInfo is 0x700 vs our 0x624 (createNewGameSpyInfoInterface @0x637760 passes it to operator new) - but GameSpyInfo EMBEDS a staging room, so its own pad is 0x700-0x624-0xA8 = 0x34, not 0xDC. Adding both naively overshot to 0x7A8; when two tail pads land in classes that contain one another, subtract the inner growth from the outer pin.
* A by-value parameter read tells you WHICH field moved, not just that the class grew: work back through the prologue (push/sub esp AND the pushed registers) to get the parameter base, then subtract. Getting the base wrong by 0xC made me pad in front of m_requiresPassword when the pinned field was actually m_id. Then setExeCRC/setIniCRC - matched rows in the same TU keeping ZH offsets 0x398/0x39C right AFTER m_id - proved BFME RELOCATES m_id to +0x41C rather than shifting the block: the fix is a hole where it was plus a re-declaration in the appended region, not a pad. Also: adding a NEW header to a shim dir does not invalidate build.py's deps sidecar (it recorded the old resolution), so delete the .obj and .deps.json or the next build silently reuses the stale object.
* The GameWindow +0x04 field IS real - winDestroy @0x47CE30 reads and writes m_status at [win+8] where the ZH header gives +4 - but it is paid back before m_instData, since the seven matched win*Color accessors still index from +0x48 and setTooltipDelay still writes +0x1C4. So reference/shims/gamewindowlist declares the anchor and relocates ONE 4-byte member (m_userData, chosen only because nothing pins it) to the class tail. That reconciles the conflict logged earlier against reference/shims/gamewindow: its +0x04 field was right, its later placement of the remaining 0xC was not. Gotcha while doing it: relocating a member to 'the tail' means AFTER m_next/m_prev too - dropping it just past the sibling-list pad silently pushed those pointers 4 bytes and broke the two rows already landed.
* reference/shims/display's three stubs are NOT a clean prefix insertion into Display's vtable. They land sizeWindowsAlt (getWidth 0x20->0x2C, getHeight 0x24->0x30) but adding the same shim to ControlBar.cpp regresses setSquishedControlBarConfig from 2 diffs to 19: that body calls getHeight at the SAME +0xC shift yet its other Display calls do not move at all. So BFME both adds and removes slots inside Display, exactly like GameWindow and DisplayString - do not widen the display shim to another TU without first pinning the methods that stay put. Remaining ControlBar work also needs the m_specialPowerShortcut* block relocated (buttons 0xF8->0xCC with 10 elements not 11, currentlyUsed 0x17C->0xF4, parent 0x184->0xFC; the same offsets reference/shims/controlbar already documents) - a multi-member reshuffle inside a header whose 44 rows are matched, not a pad.
* BuildListInfo::duplicate @0x1944D0 gives two solid pins - sizeof is 0x8C (we emit push 0x90) and m_nextBuildList is read at +0x2C (ours 0x30) - and the offsets it DOES agree on (0x10/0x14 in m_location, 0x1C/0x20 in m_rallyPointOffset) prove everything up to 0x24 is unchanged. So exactly one 4-byte member between +0x24 and +0x30 is absent in BFME, but WHICH is unknowable from this body: dropping m_angle, m_isInitiallyBuilt or m_numRebuilds all satisfy both pins, so it stays unlanded rather than guessed 1-in-3. Worse, the ledger's three 10-byte BuildListInfo setters (setNumRebuilds@0x2C, setNextBuildList@0x30, setHealth@0x38) CONTRADICT duplicate - they encode our unshifted layout and are exactly the generic 'mov eax,[esp+4]; mov [ecx+N],eax; ret 4' shape that ICF-folds across classes, so treat them as suspect the way friend_setNext@UpgradeTemplate already is.
* BFME's AsciiString::isEmpty() tests the header's 16-bit LENGTH, not the first character: ModuleFactory::findModuleInterfaceMask @0x129100 emits `cmp word ptr [eax+4], 0` where the ZH body reads peek()[0] as a byte. Fixing it in reference/shims/asciistring8 landed newModule outright and is a second independent confirmation of the WWLib StringBase header (int ref_count @0, ushort len @4). findModuleInterfaceMask still needs one more thing and it is NOT a ModuleTemplate pad: it returns m_whichInterfaces from [tmpl+0xC] where ours gives +8, but padding ModuleTemplate breaks four matched ctor bodies that write the field at +8 - so either the object it dereferences is not a ModuleTemplate, or those ctors are wrong.
* BFME TerrainLogic has ONE more virtual ahead of getLayerHeight than ZH: Pathfinder::adjustCoordToCell @0x3D6040 calls it through slot 0x1C where the header gives 0x18. One stub in reference/shims/terrainlogic lands it with all 30 AIPathfind.cpp rows intact. Scanning tip that found it: grep the retail bytes of every candidate for the isEmpty signature `66 83 78 04 00` (cmp word [eax+4],0) - it groups the AsciiString-shaped bodies - but check the COMDAT length first, since a 60-byte retail body whose source compiles to a single `ret` (ThingTemplate::validateAudio) reports a fake 1-diff.
* BFME Radar carries 0x108 more bytes ahead of m_radarWindow than ZH (screenPixelToWorld @0x107C50 reads it at this+0x1438, ours +0x1330). One pad in reference/shims/radar landed that body AND findDrawPositions @0x106FC0 (302B) which dropped straight to zero diffs - after any single-field pad, re-scan the whole TU before moving on, since one offset often gates several bodies.
* Object is RELOCATED, not grown, and padding it is provably wrong. Three retail pins say fields move a long way - m_disabledMask 0x130->0x1A4 (doSpecialPowerUsingWaypoints @0x1C3850), m_triggerInfo 0x240->0x2D8 and m_numTriggerAreasActive 0x298->0x346 (isInside @0x1BEA90) - but six ALREADY-MATCHED accessors in Object.cpp pin fields that sit BETWEEN them and do not move at all: getBodyModule reads +0x194 and hasAnyWeapon +0x20C, both unshifted. So m_disabledMask cannot simply shift past +0x194; BFME reorders Object rather than inserting runs, the same shape as GameSpyStagingRoom::m_id. Padding in front of each pinned field breaks exactly those six rows - do not retry that. Probe note: Object.cpp compiles against reference/shims/sweep/GameLogic/Object.h, NOT the reference header, and one member there (m_hasDiedAlready) is behind an #ifdef, so an offsetof probe must be built from the sweep copy and must drop names the compiler rejects.
* A by-value parameter's teardown tells you whether the class has a REAL destructor: GameInfo::setSlot @0x61F630 ends with one call on the parameter's base, while our build inlined the member teardown and called UnicodeString::releaseBuffer at +0x28 instead. Declaring ~GameSlot() in reference/shims/gameinfo (no definition needed - build.py only compiles, and the ledger pin resolves the call) collapsed that to a single ??1GameSlot call and finished the body. Its other pin was the plain size one: GameSlot is 0x44 bytes, from `ret 0x48` vs our 0x44. Watch for this shape whenever the only leftover diff is an lea of a stack address near the epilogue.
* The W3DDisplayString shim conflict is RESOLVED and reference/shims/displaystring was right after all: DisplayString really does drop one base virtual (computeExtents' two vtable calls sit one slot early), it just also needs its DESTRUCTOR out-of-line. With the shim's inline `virtual ~DisplayString() { }` the compiler inlines the base teardown (lea ecx,[esi+4]; mov [esi],0) where retail CALLS the dtor thunk @0xD823 - the same GameSlot shape. w3ddisplaystring now carries a local copy declaring it, which lands computeExtents AND keeps the dtor at zero diffs. Note the mangling flips with access level: declaring it public gives ??1DisplayString@@UAE@XZ where the protected reference form is @@MAE@XZ, so both spellings need pinning to the same thunk.
* FontCharsClass in BFME is BOTH shorter at the front and roomier in the middle: Grow_Unicode_Array @0x93D320 reads UnicodeCharArray at +0x44C and FirstUnicodeChar at +0x45C where ours gave +0x45C/+0x460, which pins 0x10 removed before ASCIICharArray and only 0xC re-inserted after the pointer - a net -4. Moving four GDI handles past UnicodeCharArray gets the pointer right but leaves the uint16 pair 4 late; the fix is three moved there plus a fourth (GDIFont) parked at the class tail. Note render2dsentence.h lives in Code/, not reference/, so this is a direct header edit and a full-gate commit - no shim dir involved.
* Object IS reconstructable - the earlier 'padding breaks six accessors' finding was right about the method, not the class. Harvesting BOTH directions settles it: rows that already byte-match pin +0x124, +0x12C, +0x18C, +0x190, +0x194, +0x1A0, +0x1A8, +0x1F0 and +0x23C UNCHANGED, so BFME agrees with the ZH header nearly everywhere, and only three fields relocate - m_disabledMask +0x130->+0x1A4 (trading places with m_partitionData, both 4 bytes), m_triggerInfo +0x240->+0x2D8 and m_numTriggerAreasActive +0x298->+0x346, the latter two into a block BFME appends past the 0x29C end. reference/shims/bfmeobjectlayout encodes exactly that and keeps all 106 pre-existing rows green. GENERAL METHOD: for a class where naive padding fails, harvest the CONFIRMED offsets (from matched rows) before the moved ones - the confirmed set is what tells you it is a reorder, and it bounds where the moved fields may go.
* InGameUI pins harvested the same way as Object, but this one does NOT pay off yet: findSWInfo @0x449E70 indexes m_superweapons from +0x5CC where our header puts the array at +0x17F0, while matched rows in the TU pin +0xC8, +0xDC, +0x568, +0x570 and +0x7A1 unchanged. The destination is boxed in by confirmed offsets on both sides (+0x570 below, +0x7A1 above), so relocating the array there would displace fields that are proven stationary - it needs more pins before it can be encoded, and only one 75-byte body depends on it. Also note the Object shim does NOT generalise: of every candidate outside Object.cpp only getReadyFrame@SpecialPowerModule touches a known Object relocation, and it still has 6 other diffs, so opting other TUs in buys nothing.
* BFME ScriptEngine is 0x6868 bytes bigger ahead of m_freezeByScript, and TWO independent pins agree: m_freezeByScript ours +0x10DBC -> retail +0x17624 (the existing reference/shims/scriptengine stand-in) and m_objectsShouldReceiveDifficultyBonus ours +0x10DCC -> +0x17634 (doEnableOrDisableObjectDifficultyBonuses @0x2F0840). The old shim is a minimal stand-in CLASS, usable only by TUs that touch nothing else; reference/shims/scriptenginelayout is the real header with one pad and works for full TUs - all 56 rows in ScriptActions.cpp stay green. Note the old shim's comment says the delta is 27240 bytes, which is 0x6A68 and wrong by 0x200; the measured value is 0x6868.
* BFME declares EstablishConnectionsMenu's five public methods virtual where ZH has them as plain calls: NAT::setConnectionState @0x670DC0 reaches setPlayerStatus through slot 0x14 on TheEstablishConnectionsMenu's vtable. With the destructor already at slot 0, marking initMenu/endMenu/abortGame/setPlayerName/setPlayerStatus virtual IN THEIR EXISTING ORDER puts setPlayerStatus at index 5 with no stubs invented - when a whole small class turns out to be polymorphic in BFME, try promoting its declared methods before padding the vtable with placeholders.
* ModuleFactory::findModuleInterfaceMask @0x129100 is one byte from matching: retail reads the interface mask at ModuleTemplate+0xC where our 12-byte template puts it at +8. Do NOT widen ModuleTemplate - the already-matched newModule @0x127E00 calls (*m_createProc)() straight off the same node+0x14 base, pinning m_createProc at template+0, and the matched pair<NameKeyType,ModuleTemplate> copy ctors move exactly three dwords, pinning sizeof at 12. Widening the template fixes this one row and breaks four. Either retail reads a member we cannot see from a 12-byte layout or one of those four rows is an ICF mis-attribution; left unresolved.
* BFME does not stack MemoryPoolObject and Snapshot the way ZH does: retail TunnelTracker has ONE vptr (dtor @0xF8A40 touches only [this+0]), is still handed straight to Xfer::xferSnapshot, and still answers deleteInstance - so the two ZH bases are one merged base there. Its vtable @0x1085FD8 is dtor / loadPostProcess @0xF8F60 / a pool-name accessor @0xF8A30 / xfer @0xF8E20, four slots against the shared base table @0x1073744 of dtor plus three _purecall. Every member drops one dword versus ZH (xfer @0xF8E20 walks +4,+8,+0xC,+0x10,+0x14,+0x18,+0x1C in declaration order), making sizeof 0x20 - the operator new argument in CaveSystem::registerNewCave. A TU shim cannot express this by editing GameMemory.h: PreRTS.h pulls the reference copy first via MSVC's includer-relative quote search and the guard then blocks the shim, so derive the class from Snapshot alone and declare deleteInstance on it.
* LANAPI needs a whole-class reconstruction before its 34 markers can land, and RequestLobbyLeave @0x6850F0 measures all three axes at once: sizeof(LANMessage) is 0x1DC not 0x1D8, fillInLANMessage sits at vtable +0xC4 not +0xAC (six extra virtuals ahead of it), and m_transport is at +0x4C not +0x44. The already-matched rows pin the front of the class - LookupGameByListOffset reads m_games at +0xC and ResetGameStartTimer writes the start-timer pair at +0x1C/+0x20 - so the eight extra bytes appear between m_gameStartSeconds and m_transport. Only 8 of the 34 markers have ledger rows, so there is not enough matched code in the TU to place them; do LANAPI as a deliberate class job, not as a near-miss chase.
* BFME's View carries two more virtuals ahead of setHeight (slot +0x40, not +0x38) on top of the three Display already has ahead of getWidth, and ControlBar::setSquishedControlBarConfig @0x49D0B0 needs both at once - reuse the Display half of reference/shims/display but pair it with a REAL View.h, not that shim's synthetic slot skeleton, which has no usable API for a second TU. Separately: retail reaches ControlBarSchemeManager::setControlBarSchemeByPlayerTemplate through the incremental-link thunk at 0x378EE, which jumps to 0x4ADE40 - an RVA nothing in the ledger claims - while functions.csv puts that same mangled name at 0x3865B0 from a string-anchor guess. The thunk is pinned in symbols.csv; the 0x3865B0 body claim is probably a misattribution and wants re-checking.
* ControlBar's special-power shortcut block is far smaller in BFME: animateSpecialPowerShortcut @0x49D3F0 puts m_specialPowerShortcutButtons at +0xCC and m_currentlyUsedSpecialPowersButtons at +0xF4, a 0x28-byte gap where the ZH header's three MAX_SPECIAL_POWER_SHORTCUTS arrays need 132 - ten dwords, not thirty-three - and the whole block also starts 0x2C lower than ours, so something ahead of it shrank too. m_specialPowerShortcutParent keeps its one-member gap after the counter (+0xFC vs our +0x184), and the animate-window-manager virtual it calls is one slot further along (+0x10 vs +0xC). Two independent shrinks over a class with 45 matched rows: treat ControlBar's tail as a deliberate reconstruction, not a near-miss fix.
* A lone JA-where-we-emit-JG is a type fact, not a layout fact: DisconnectManager::sendKeepAlive @0x66B2D0 matched byte for byte once the local holding timeGetTime() became UnsignedInt instead of ZH's time_t, because the usual arithmetic conversions then make (curTime - m_lastKeepAliveSendTime) > 500 an unsigned test. Check the signedness of the locals before reaching for a shim whenever the only difference is the condition code of one branch.
* The BFME slot 6-8 stub trio that sweep's GameWindowManager.h documents is not confined to the window family: DisplayStringManager has it too, which is the whole reason CreditsLine::~CreditsLine @0x40C230 calls freeDisplayString through vtable +0x28 instead of +0x1C. When a SubsystemInterface-derived class's vtable pin is exactly three slots late, try declaring the three stubs right after its destructor before assuming anything about the derived class itself - and keep doing it per class, since sweep's SubsystemInterface.h records that the base does NOT carry them.
* When only the operator new size is wrong, read the retail constructor rather than padding the tail blind: GameSpyPeerMessageQueue asks for 0x78 bytes where ours is 0x6C, and its ctor @0x64D650 shows exactly what the extra 12 are - MutexClass's ctor runs a THIRD time on this+0x6C (the same one used for the mutexes at +4 and +0xC) and then a dword at this+0x74 is zeroed. The five matched rows in PeerThread.cpp confirm +0x14, +0x24, +0x3C, +0x64 and +0x68, so the two new members can only sit at the tail. Also: BFME's WW3D::End_Render @0x8FD880 returns via mov al,1 on both paths, i.e. a one-byte true, not the four-byte WW3D_ERROR_OK our signature returns - the WW3D error enum may be a bool in BFME, which would rename the symbol, so it is left alone.
* AIUpdateInterface's turret block is 0x18 further along in BFME: m_turretAI is at +0x1E8, not +0x1D0. The matched rows bracket it - ignoreObstacleID pins m_ignoreObstacleID at +0x154 and the hand-rolled struct in setLocomotorUpgrade pins m_curLocomotorSet at +0x1D0 - which splits the 0x18 into 0x14 unaccounted bytes ahead of the locomotor block (most likely LocomotorSet being 0x2C rather than 0x18) and 4 more between m_locomotorGoalData and m_turretAI. Holding both as holes inside AIUpdateInterface rather than resizing LocomotorSet keeps that type unchanged for its other users in the TU, and lands getWhichTurretForCurWeapon and isWeaponSlotOnTurretAndAimingAtTarget together.
* StreakLineClass::Set_Widths @0x91A380 wants PointWidths - the DynamicVectorClass whose vptr/Vector/VectorMax/ActiveCount it walks - at +0xF4, while our layout puts it at +0xC0. That cannot simply be shifted: the matched Set_Merge_Abort_Factor row writes a float to [ecx+0xF4], and a one-instruction setter of that shape is exactly the ICF-folded evidence lessons.md already warns about. One of the two is wrong and the setter is the likelier suspect, so this is left alone until StreakLineClass gets a proper reconstruction.
* BFME's KindOf enum has two more entries than ZH's, and they sit between KINDOF_VEHICLE and KINDOF_AIRCRAFT: TunnelTracker::updateNemesis @0xF90D0 passes 7, 8 and 9 for STRUCTURE, INFANTRY and VEHICLE - the same numbers this header gives them - and then 12 for AIRCRAFT. Anything from KINDOF_AIRCRAFT onward is therefore two higher than the ZH header says, which is worth checking before blaming a layout whenever a lone isKindOf argument is off by a small constant.
* The merged pooled-snapshot base generalises: TurretAI, declared in ZH as MemoryPoolObject + Snapshot + NotifyWeaponFiredInterface, carries one vptr fewer in BFME exactly like TunnelTracker, which is why getWhichTurretForWeaponSlot @0x26EBB0 reads m_angle at +0x18 and m_pitch at +0x1C instead of +0x1C and +0x20. Same shim recipe both times: derive from Snapshot alone, keep the other non-pooled bases, and declare deleteInstance on the class. Expect any ZH class inheriting both MemoryPoolObject and Snapshot to be four bytes smaller in BFME with all its members shifted down a dword.
* Two separate layout jobs are now blocked by the same shape of bad evidence, one-instruction setters that ICF folds. ParticleSystem::getPosition @0x5BDDB0 puts m_localTransform at +0xC0 against our +0x274, and attachToDrawable's hand-rolled offset already pins m_attachedToDrawableID at +0xB4 - together they say BFME's ParticleSystemInfo base is about 0x1C0 bytes smaller. But the matched setControlParticle row insists m_controlParticle stays at +0x330, which a shrink of that size cannot leave alone; that row is mov [ecx+0x330],eax / ret 4, the same folding-prone shape as StreakLineClass's Set_Merge_Abort_Factor. Before starting either class, re-derive those two setter claims from a caller rather than trusting the ledger row.
* WinInstanceData::setText @0x499D60 comes down to six bytes once both display shims are applied together - displaystringmanager fixes newDisplayString at vtable +0x24 and displaystring fixes DisplayString::setText at +4 - and what is left is pure scheduling: retail emits mov [esp+8],esp before mov ecx,esp when constructing the by-value UnicodeString temporary, we emit them the other way round. Same instructions, same registers, same semantics. Nothing in the source expression appears to steer that order, so the pair is worth revisiting only if the compiler flags change; the two shims themselves are proven to compose.
* BFME's RenderObjClass has one more virtual than ZH's and it is the LAST slot, not an interior one: AABoxRenderObjClass @0x957880 and OBBoxRenderObjClass @0x957C20 reach BoxRenderObjClass's own first virtual, update_cached_box, through +0x20C where our header lands it at +0x208. Adding the slot in front of Set_Position instead broke 66 matched rows across WW3D2 and the draw modules, because everything from there down shifted - the extra slot only fits after every RenderObjClass virtual that existing rows already pin. Note the constructors call Set_Position directly and only update_cached_box through the vtable, so the pin is on the derived class's first own slot, not on Set_Position.
* One C++ function can sit in the ledger twice under two spellings of the same parameter type, and the wrong copy can be the one a symbols.csv pin points at. Matrix3D::Set(const Matrix3&, const Vector3&) is an 82-byte body at 0x8D6710, but the Matrix3x3 spelling that our TUs actually emit was pinned to 0x964150 - a 274-byte RVA shared with setEaseTimes@ParabolicEase, i.e. an ICF group that cannot be an 82-byte function. OBBoxRenderObjClass's constructor @0x957C20 calls 0x8D6710, and repointing the pin there kept the entire full gate green, so nothing else depended on the old target.
* BFME's WW3D entry points return bool, not ZH's four-byte WW3DErrorType, and two functions now say so independently: End_Render @0x8FD880 returns via mov al,1 on both paths, and Set_Render_Device @0x8FD120 ends test al,al / setne al / ret where we emit the neg/sbb/and/add sequence that turns the callee's bool into 0-or-5. Both are one-byte returns. Fixing it is not a shim job - it changes the mangled names, so every affected ledger row would have to be renamed, and add_match only replaces a row under its existing name while hand-editing functions.csv is what the tooling exists to prevent. Worth doing as a deliberate pass over the whole WW3D surface, with tooling for the rename, rather than one function at a time.
* The retail ParticleSystem layout is now pinned end to end, and it proves the setControlParticle ledger row wrong. Four neighbours of getPosition read it out: setLocalTransform @0x5BDE40 copies a full 48-byte Matrix3D into +0xC0..+0xEC, setPosition @0x5BDE00 writes only that matrix's translation column at +0xCC/+0xDC/+0xEC, and both then clear a byte at +0x1A4 - m_isLocalIdentity, the first of ZH's eight trailing Bools - while the stop/start pair @0x5BDD90 and @0x5BDDA0 write +0x1A7, which is m_isStopped, the fourth of them. That puts m_template at +0x19C, m_controlParticle at +0x1A0 and sizeof around 0x1AC, so the matched setControlParticle row claiming +0x330 cannot be this class at all - it is the ICF fold that lessons.md already suspected. Everything from m_localTransform down keeps ZH's order and spacing; only the ParticleSystemInfo base ahead of it is smaller, ending near +0xA0 given attachToDrawable's confirmed m_attachedToDrawableID at +0xB4.
* And the real body is findable: scanning .text for the exact setter MSVC would emit at the predicted offset - 8b 44 24 04 / 89 81 a0 01 00 00 / c2 04 00 - gives exactly one hit, 0x5BE2E0, unclaimed by any ledger row and sitting a few hundred bytes from getPosition @0x5BDDB0 in the same ParticleSystem cluster. That is where setControlParticle really lives. It cannot be repointed yet, because our header still puts m_controlParticle at +0x330 and the row would not verify until the ParticleSystemInfo base is reconstructed - but the address is settled, and the same trick (predict the offset from neighbours, then grep .text for the setter's exact encoding) is the way to re-derive any of the other ICF-suspect setter rows.
* LightEnvironmentClass looked like a clean one-dword insert and is not. Pre_Render_Update @0x94BB40 reads every member exactly four bytes later than ours - LightCount at +4, the loop base at +0x14, the fill-light floats at +0x164/+0x168/+0x16C - but adding a leading dword breaks six matched rows, among them getPointOrad @0x903370, whose imul 0x54 / fld [eax+ecx+0x48] pins InputLights at +0x10 exactly where we already have it. Both cannot hold with a single insert: something ahead of LightCount grows by 4, something between LightCount and InputLights shrinks by 4, and the tail grows again. Get_Light_Count @0x10BDB0 is no help either - three bytes of mov eax,[ecx] / ret is the most foldable shape in the binary. Needs the whole class done at once.
* GameSpyInfo is blocked by a bad ICF group, not by a layout puzzle, and the exact addresses are now known. An offsetof probe on the shimmed class gives our layout precisely (m_localName +0x64, m_localProfileID +0x68, m_cachedLocalPlayerStats +0x78, sizeof 0x700), and the 609-byte constructor @0x636D90 - far too big to fold - says BFME shifts everything from m_localName on by 8: it zeroes the four AsciiStrings at +0x6C/+0x74/+0x78/+0x7C with our exact 8/4/4 spacing and then runs a constructor on +0x80. Three matched rows contradict that, and all three are misattributions: getCachedLocalPlayerStats is claimed at 0x6372D0, whose body copies an AsciiString via StringBase's copy ctor at +0x78, while the real one - same shape at +0x80, calling the big EH-carrying map-copying constructor at 0x6577D0 - sits unclaimed at 0x637480; setLocalProfileID's real body at +0x70 is unclaimed at 0x637110, and setMaxMessagesPerUpdate's at +0x250 is unclaimed at 0x6307A0. Both are in the same cluster as the constructor. The root cause is the five-name ICF group at 0x887B60, 121 bytes of StringBase<char> copy constructor that also carries ??0PSPlayerStats@@QAE@ABV0@@Z - a class with 24 std::maps whose copy constructor cannot possibly be 121 bytes, and which really lives at 0x6577D0. Fixing GameSpyInfo means correcting that group first, which touches other TUs and needs its own pass.
* PersistentStorageThread.cpp is missing /D_STLP_USE_STATIC_LIB, and that one flag is worth more than any layout guess: without it the TU calls __new_alloc::allocate through __imp_ (a DIR32 indirect call) where retail calls it directly, which desynchronises every instruction after the first map. Adding it takes PSPlayerStats' copy constructor @0x6577D0 from 1374 byte differences down to 379 with the first 1249 bytes exact, and all 14 matched rows in the TU survive. Check that flag on any TU whose diff looks like a total desync right after the first container.
* With the flag on, PSPlayerStats reads out further. BFME has three more PerGeneralMaps than ZH - the copy ctor builds them at +0x124, +0x130 and +0x13C where our layout has already moved on - and the string block that follows is ordered differently: one dword at +0x148, a string at +0x14C, a lone dword at +0x158, then strings at +0x15C and +0x168, i.e. gamesAsRandom sits after options and there is a fourth std::string ZH does not have. The region between that block and the last string is two dwords shorter than ours, since the constructor copies plain dwords at +0x1B0 and +0x1B4 and then builds the final string at +0x1B8. Modelling all of that gets to 109 differences; what is left is register allocation around the string constructions, which means at least one more member is still in the wrong place. Note the class's copy constructor cannot be landed until its ledger row moves off the bogus 0x887B60 ICF group.
* PSPlayerStats is fully reconstructed and its ledger rows are off the bogus 0x887B60 ICF group. Three things had to be true at once: the TU needs /D_STLP_USE_STATIC_LIB (without it STLport's allocator is called through __imp_ and the instruction stream desyncs after the first map); BFME has three more PerGeneralMaps, drops QMwinsInARow and maxQMwinsInARow, orders the tail exactly the way the copy constructor assigns it, and carries a fourth std::string; and the copy constructor assigns that string between desyncsInARow and maxDesyncsInARow with lastLadderHost moved after lastLadderPort. All 1896 bytes then match. The two rows repointed are ??0PSPlayerStats@@QAE@ABV0@@Z (0x887B60 -> 0x6577D0) and the pair<const int, PSPlayerStats> constructor (0x0A9D80 -> 0x658880, found by grepping .text for that ctor's exact 30-byte shape and checking which hit calls the real copy ctor). Both old addresses were 121-byte StringBase<char> code that cannot copy a 0x1DC-byte class.
* The 0x887B60 ICF group had pulled a whole cluster of GameSpy rows onto wrong addresses, and once PSPlayerStats was reconstructed the rest fell out by one technique: take our compiled COMDAT, mask the reloc slots, find the longest reloc-free run, grep .text for it and keep the hits where every unmasked byte agrees, then disambiguate the survivors by which thunk their calls land on. That moved six rows into the GameSpyInfo cluster - getCachedLocalPlayerStats 0x6372D0 to 0x637480, setLocalProfileID 0x2ED490 to 0x637110, setMaxMessagesPerUpdate 0x0FB8A0 to 0x6307A0, the 0x34-node tree's dtor to 0x634060 and its _M_erase to 0x632FC0, and pair's scalar deleting dtor 0x4EA380 to 0x631E50 - and three symbols.csv pins onto the thunks retail actually encodes. Note the pins must name the THUNK, not the body: the copy ctor is reached through 0x1C783, _M_erase through 0x3EA2C and the pair dtor through 0x41C5E.
* add_match verifies the whole TU on every call, so a cluster of rows that are all wrong together cannot be repointed one at a time - each attempt fails on its siblings and reverts. Repoint all but one with --no-verify and let the last one run the verification; it byte-checks every row in the file, so nothing survives unverified.
* BFME keeps AsciiString::set and AsciiString::releaseBuffer OUT of line where the ZH header defines both inline, and that alone was the whole difference in GameSpyInfo::addToSavedIgnoreList @0x635670: retail calls 0x887C90 and 0x887940 at the points our build expands the ref-count dance inline. Deleting the two inline bodies from a TU-local AsciiString.h - the header is reachable through the include path because sweep does not shadow Common/AsciiString.h - took the function from 226 bytes with a divergence at +0x18 to an exact 149. Worth trying on any function that is a byte-for-byte prefix match until the first string assignment or destruction.
* Not every ledger row starts where its function does. joinBestGroupRoom's row claims 0x634EF2/433, but scanning back to the int3 padding shows the real function is 0x634EC0/483 - the claim begins eleven instructions in. That function also takes an argument (it compares it with 2 and picks a flag at +0x60 or +0x64 accordingly, which incidentally names the first dword of the 8-byte hole ahead of m_localName), so the row's NAME is wrong too: BFME's is not the void overload. Fixing it needs the row renamed, and add_match can only replace a row under its existing name.
* Two GameSpy shim facts were in the right size but the wrong place, and the constructor could not tell the difference. The 8 extra bytes in GameSpyInfo sit between m_currentGroupRoomID and m_gotGroupRoomList, not after it: addGroupRoom @0x636650 sets m_gotGroupRoomList at +0x68 where ours had +0x60, and joinBestGroupRoom @0x634EC0 reads the two new dwords at +0x60 and +0x64 - choosing between them on its argument - before clearing m_currentGroupRoomID at +0x5C. Likewise GameSpyGroupRoom's extra dword follows m_name rather than closing the class: addGroupRoom reaches the field after m_name with add eax,8 at four separate sites where we emitted add eax,4. Both placements leave every offset the constructor pins unchanged, which is exactly why it accepted the wrong ones - when a hole's position is only fixed by one function, look for a second.
* Rows that need renaming or removal are SKIPPED, never hand-edited. add_match can only replace a row under its existing name, and functions.csv is not to be edited by hand, so a function whose ledger row carries the wrong symbol name - or whose row would have to disappear - is left alone and written up instead. joinBestGroupRoom is the current example: its row claims 0x634EF2/433 while the real function is 0x634EC0/483 and takes an argument, so the void-overload name on that row cannot be right. It stays as it is until the tooling can express a rename.
* A candidate that matches as a long prefix and then makes one call too many is a source-content difference, not a layout one. ScriptActions::doBorderSwitch @0x2EFC50 matched 98 of its 102 bytes and then ran an extra ThePartitionManager->refreshShroudForLocalPlayer(); BFME returns straight after the observer re-reveal. Deleting that one statement matched all 102. The scan that finds these is cheap: for every candidate whose COMDAT is LONGER than retail, measure the common prefix - the high-percentage ones are either an inlined-versus-out-of-line call or a statement BFME does not have.
* UnicodeString::compareNoCase is out of line in BFME too - LANGameSlot::isUser @0x68E8F0 calls it at 0x9EFE0 where the ZH header's inline body expands the comparison into the caller - and taking it out of line drops that function from 166 bytes to 149 against retail's 132. It still does not match: our frame is 4 bytes larger and we write one more EH state slot than retail, so one extra temporary is being tracked. Reverted rather than left in, since it lands nothing on its own, but the out-of-line finding holds and the shim is two lines to recreate.
* sweep's Module.h already carries a BFME_MODULE_NO_MPO switch that drops MemoryPoolObject from Module's bases, and it is the same merged-base fact TunnelTracker and TurretAI showed: defining it on a module TU shifts every member down a dword. SwayClientUpdate's constructor @0x6044E0 went from writing +0x10/+0x14/+0x18 to the retail +0xC/+0x10/+0x14 the moment the define was added. Only eight TUs use it so far, so any module whose candidate is off by exactly 4 is worth trying it on. The remaining difference there was BFME zeroing two more dwords at +0x24 and +0x28 - two extra Reals after m_unused, held as holes.
* BuildListInfo was logged as a 1-in-3 ambiguity with three suspect setter rows, and the merged base settles it: BuildListInfo derives from MemoryPoolObject and Snapshot in ZH, so the same one-vptr merge that TunnelTracker, TurretAI and Module show applies, and duplicate @0x1944D0 matched all 194 bytes at once. The two setters it broke were indeed misattributed - setHealth and setWhiner really live at 0x191490 and 0x1914A0, right beside duplicate, while the ledger had them at 0x265BC0 and on a Snow ICF fold at 0x45A9A0. setHealth folds with setFrameToEvaluate, so it goes in as an --icf-owner alias. When a class is off by exactly 4 everywhere, check its ZH bases before doubting the near-miss.
* ControlBarSchemeManager's destructor @0x4AE850 shows the STLport flag is only half the story in some TUs. Without /D_STLP_USE_STATIC_LIB our build emits call dword ptr [__imp_] where retail emits a direct call - six bytes against five, which is the entire one-byte size difference - so the flag is proven here by the bytes. But adding it takes us to 156 against retail's 166 and exposes the rest: retail deallocates with a size, push 0xc / push eax / call 0x82E5F0 / add esp,8, while we call the unsized operator delete with add esp,4, and retail tracks one more EH state. That is a second STLport configuration axis - node allocator versus plain new/delete - not something the static-lib flag controls. Reverted, since half a fix lands nothing.
* Two of the four remaining -4 candidates are multi-cause and stay open. generateIndexBuffer @0x79EEA0 needs three things at once: a member at +0x128 rather than +0x12C, a literal 0 where we pass that member, and a vtable slot at +0x6C rather than +0x60 - and the object it calls through is a global in retail where ours is a member. parseImagePart @0x581480 has one local too many: retail's prologue is push ecx where ours is sub esp,8.
* AggregateDefClass::Initialize @0x980A50 is one byte from matching and the cause is a flag representation, not a layout. Retail reads the sub-object LOD flag as mov eax,[edi+0x10] / shr eax,0x14 / and eax,1 - a one-bit field at bit 20 of RenderObjClass::Bits - where our accessor returns Bits & SUBOBJS_MATCH_LOD and MSVC folds that into a byte load at +0x12. Rewriting the accessor as (Bits & SUBOBJS_MATCH_LOD) != 0 does NOT reproduce it: the compiler keeps the byte load and just appends and eax,1, which took the function from 1 differing byte to 86. Reverted. Getting the shr/and pair means declaring the flag as a real bitfield in Bits, which changes RenderObjClass for every TU and needs its own pass.
* AggregateDefClass::Initialize @0x980A60 needed three separate BFME facts and none of them was a layout offset. SUBOBJS_MATCH_LOD is bit 20 in BFME, not bit 16 - retail reads it with mov eax,[edi+0x10] / shr eax,0x14 / and eax,1, and bit 20 is exactly the slot IS_ADDITIVE vacated when it moved to 0x400000 - and the accessor returns a normalised 0/1 rather than the masked value. Initialize also calls the FREE Create_Render_Obj at 0x8FF290 instead of the virtual member. And Build_Subobject_List sits at vtable +0x40, two slots earlier than ours, because Load_Assets and Create_Render_Object are not virtual in BFME. Which two to demote is not a free choice: the ledger pins Free_Subobject_List, Add_Subobject, Find_Subobject and Is_Object_In_List as virtual through their MAE mangling, so demoting Is_Object_In_List makes its row's symbol vanish from the object - the build says symbol not found, which is a clean way to tell that a method must stay virtual.
* DX8Wrapper::Set_Default_Global_Render_States @0x9081D0 differed by one push: retail sends a single argument to 0x905990 where we sent two to the render-state helper, because BFME calls the dedicated Set_DX8_ZBias(0) rather than Set_DX8_Render_State(D3DRS_ZBIAS, 0). Switching the call was not enough - Set_DX8_ZBias is WWINLINE in dx8wrapper.h, so it expanded and took the function to 499 bytes. Retail keeps it out of line, and moving the body into dx8wrapper.cpp matched all 211. That move is safe precisely because every other call site in the tree is commented out, which is worth checking before demoting any WWINLINE.
* The Debug vtable was written off as needing fourteen invented virtuals; it needs none. BFME simply makes Debug polymorphic, and marking every non-static member function virtual IN DECLARATION ORDER - 35 of them, no destructor added, no placeholders - lands operator<<(const char*) at slot 14 exactly, which is the +0x38 that DebugIOCon::Execute @0x891200 calls through. All 239 bytes then match. The shim is reachable after all: _pch.h pulls debug/debug.h and sweep has no debug directory, so a shim carrying both debug.h and debug_debug.h wins on the include path and its sibling include resolves inside the shim. Same shape as EstablishConnectionsMenu - when a whole small class turns out to be polymorphic, promote what is already declared before inventing slots.
* Identification in a fresh clone is gated on one missing file. reverse/ghidra_functions.csv is gitignored and derived, and without it locate.py, anchor_by_string.py, audit_claim_boundaries.py and next_work.py's tier 3 all refuse to run - which is why only 619 of 10029 present-unmatched markers (6.2%) can even be byte-compared here. Regenerating it needs Ghidra plus a JDK 21; this machine has neither (Java 8 only), so the whole identification front is blocked on a one-time setup, not on analysis.
* int3 padding is a usable stand-in for Ghidra's function boundaries: scanning .text for runs of three or more 0xCC yields 82120 function starts against the README's estimate of ~78000, 9395 of which the ledger already claims. That is enough to reimplement locate.py's known-starts check without Ghidra, and enough to run the boundary audit - but only for the mid-INSTRUCTION verdict. The weaker mid-function-but-aligned verdict fires on 1263 rows and is mostly noise, because the linker does not always pad between functions; that class genuinely needs Ghidra's real boundaries.
* Two ledger rows claim an address inside an instruction, which no source can ever produce: assignDefaultGadgetLook is claimed at 0x4800FC while its function starts at 0x480090 (the claim lands inside mov [0x12F1BC0],eax), and parseFont at 0x485B60 while its function starts at 0x485B50 (inside the SEH prologue's mov fs:[0],esp). Both are MASM-dump rows, so they verify only because the dump reproduces bytes at the wrong place. Six other mid-instruction hits are artifacts - linear disassembly walking into the inline jump tables of the Get_DX8_*_Name switches - and must be filtered by checking whether the straddling instruction is code-like.
* next_work.py's structural-reconciliation queue proposes an RVA from shape similarity, and that RVA can be wrong - it is a hypothesis, not a claim. CommandButton::isReady was offered at 0x49AD65 with a 91%% shape ratio, but 0x49AD65 is 0x35 bytes inside the function that starts at 0x49AD30 (146 bytes, where the queue said 93). A masked scan of our compiled body finds no placement anywhere in .text, so that function genuinely differs: BFME's version null-checks the object first, then branches on a field at +0x10 being 0x16 and answers from a frame counter at Object+0x36C, and only otherwise runs the special-power and upgrade tests we have. Check a queued RVA against the int3 boundaries before trusting it.
* HeightMapRenderObjClass's destructor @0x6D33B0 is two facts deep. BFME does not delete m_extraBlendTilePositions there; it stores 0 to TheHeightMap and chains to the base destructor, which takes our 142 bytes down to 123 against retail's 116. The rest is a chain: our freeMapResources is a three-line wrapper that MSVC inlines into the destructor, while retail calls a real 122-byte function at 0x6D2690 (unclaimed) that releases the index and vertex buffers at +0x30D4/+0x30D8 directly. Our freeIndexVertexBuffers is 204 bytes and does not match it either, so BFME redistributed the work between the two - the destructor cannot land until freeMapResources is reconstructed.
* Smudge is not pool-allocated in BFME. SmudgeManager's destructor @0x5D4390 frees one with a plain single-argument operator delete where W3DMPO_GLUE routes through getClassMemoryPool and freeFromW3DMemPool; dropping the glue from a TU-local Smudge.h matched the whole function. Note SmudgeSet keeps its glue - its delete goes through the virtual destructor at vtable slot 0 and already matched - so the two structs in the same header differ. Also: the ledger row understated the size by 9 bytes (239 against the padding-delimited 248), and those last nine bytes match too, so verification had been comparing a truncated body. Worth checking the padding boundary whenever a row verifies but the COMDAT is longer than the claim.
* W3DProjectedShadowManager::init @0x7AF630 needed a layout shift and a shorter body. Every member from m_shadowCamera on sits 12 bytes later in BFME - the camera at +0x20 against our +0x14, the texture manager at +0x24C against our +0x240, the same +0xC for both - and the retail body returns straight after storing the camera, with no SpecialRenderInfoClass allocated and no light_environment assignment. Both together match all 156 bytes.
* Do not purge another TU's .obj while a full gate is running in the background: build.py opens the object it expects to find and dies with FileNotFoundError, so the commit fails for a reason that has nothing to do with the change being committed. Cost me one gate cycle.
* MeshMatDescClass::Init_Alternate @0x929410 is not a layout or statement problem and should not be chased as one. Ours is 1125 bytes against retail's 1047 with 423 differing bytes, but the first 0x161 are exact and the instruction streams stay in lockstep: the differences are SIB operand order - we emit mov eax,[ecx+ebx] where retail has [ebx+ecx], same effective address, different encoding - plus one extra reload of edi from [esp+0x24] at three points, i.e. one more value live across the loops. Both are compiler-choice symptoms of a slightly different source shape in the pass/stage loops, most likely how the default_materials pointer is hoisted. Nothing here is decidable from the bytes alone; it needs the loop rewritten by hand and re-measured, so it is a sit-down job rather than a near-miss fix.
* The freeMapResources that HeightMapRenderObjClass's destructor calls is at 0x6D2690, 122 bytes, unclaimed, and it is nothing like ours. Retail's body: if the pointer at +0x30D8 is non-null it takes a DX8 lock (call 0x903090, which waits on a handle with a 20-second timeout), deletes that pointer as an ARRAY of 196-byte objects with a destructor - the classic ??_M vector destructor iterator with count read from [p-4], element size 0xC4 and the element dtor pushed as 0x42B9A4, followed by operator delete[] on p-4 - releases the lock (call 0x905B10, which leaves a critical section), and nulls +0x30D8; then it zeroes +0x30E0, +0x30E4 and +0x30DC and deletes the array at +0x30D4. Our freeMapResources is a three-line wrapper (19 bytes) and our freeIndexVertexBuffers is 204 bytes releasing m_indexBuffer and the vertex-buffer tiles - neither matches. Writing this needs the members at +0x30D4..+0x30E4 named and the two lock functions identified, so it is blocked on evidence, not effort.
* SmudgeSet is not pool-allocated in BFME either: addSmudgeSet @0x5D4240 takes one from a plain single-argument operator new where W3DMPO_GLUE routes through getClassMemoryPool and allocateFromW3DMemPool. Note the destructor could not tell - SmudgeSet's delete goes through the scalar deleting destructor at vtable slot 0, which looks the same either way, so the allocation site is what discriminates. When a class looks pool-free on one side, check both new and delete before concluding.
* The AsciiString out-of-line lever applies to TUs that already use the asciistring8 shim, but the shim dirs must not be stacked: dropping asciistringsetoutofline in front of asciistring8 makes the plain 16-byte header win and silently discards the 8-byte AsciiStringData. Build a variant of the shim the TU already uses instead - asciistring8outofline is asciistring8's header with the set and releaseBuffer bodies removed - and swap it in place of the original. That took ImageCollection::addImage @0x5D3410 from 157 bytes with an inlined ref-count teardown to an exact 133, where retail calls releaseBuffer at 0x887940.
* W3DMouse needed three separate things and an offsetof probe to place them. The TU needs the 8-byte AsciiStringData - retail tests a cursor name with cmp word ptr [eax+4],0 where the plain header made us read a byte - and the Mouse hierarchy carries 0x368 more bytes than ours, arriving in three steps that two functions pin between them: 0x34C before Mouse::m_currentRedrawMode (+0x10E0 against our +0xD94), 0xC more before Mouse::m_currentCursor (+0x4DA8 against +0x4A50), and 0x10 more before Win32Mouse::m_currentWin32Cursor (+0x5E20 against +0x5AB8). The first and largest of the three is not a hole at all: BFME has ten more mouse cursors, so m_cursorInfo[NUM_MOUSE_CURSORS] is ten CursorInfo longer. The DIR32 consistency gate is what found it - the byte comparison masks reloc slots, so a wrong array length hides inside the loop's end-of-array pointer, and initPolygonAssets resolved the file-static cursorImages to two different bases until the enum grew. Retail's own imul eax,eax,0x54 in setCursorDirection fixes CursorInfo at 84 bytes, so ten entries are 0x348 of the 0x34C and only four bytes stay unexplained. The probe is what makes this placeable: offsetof on a copy of the TU with the access keywords redefined turns raw retail offsets into member names. Put those defines ABOVE the source's own prologue - after it they are too late, because the prologue has already pulled the headers.
* Another row with an understated size: initPolygonAssets was claimed at 174 bytes where the padding-delimited function is 184, and all 184 match. That is the second one today, so it is worth checking the int3 boundary routinely whenever our COMDAT is longer than the claim.
* BFME's InGameUI has nine more virtuals than ours ahead of isScrolling. W3DMouse::setCursorDirection @0x700820 calls isScrolling at vtable +0xA4 and getScrollAmount at +0xB4 where this header puts them at +0x80 and +0x90, and the two keep their four-slot spacing, so the count is exact even though the identities are not. Two notes for next time: the slot arithmetic has to come from the source line, not from counting virtual declarations in the header - the regex count put isSelecting at +0x80 and the first attempt at nine stubs landed between the two real calls, fixing one and leaving the other - and stubs belong immediately ahead of the first pinned slot so nothing below them moves.
* ModuleFactory::ModuleTemplate is 16 bytes in BFME and the tree contradicts itself about it. Two independent unique bodies say the fourth field sits at +0x8 and pushes m_whichInterfaces to +0xC: addModuleInternal @0x129AC0 writes [eax] [eax+4] [eax+8] and [eax+0xC] and rets 0x18 rather than 0x14 (a sixth argument), and findModuleInterfaceMask @0x129100 reads the mask at &it->second + 0xC where we read +8. module_factory.cpp already models exactly that and calls the field m_data - and it is a matched TU, so the repo asserts the 16-byte layout already. Three rows claimed to Thing/ModuleFactory.cpp assert the opposite: ??0ModuleTemplate@ModuleFactory@@QAE@XZ @0x5C5D0 zeroes three dwords and the two pair copy constructors @0x69580 and @0x695F0 copy three dwords of second. They are misattributed, not evidence. The 13-byte constructor is generic enough that 17 different classes in our own tree compile to those exact bytes, and retail holds 16 three-dword pair copies against 37 four-dword ones, so the real pair<NameKeyType,ModuleTemplate> constructors are among the four-dword bodies (tails at 0x69676D and 0x6970DD are the nearest). Adding m_data takes findModuleInterfaceMask to a byte-exact 84 and breaks those three, so the fix is blocked on re-attributing rows, which needs a rename the tooling does not offer - add_match's --icf-owner only registers a NEW row on an already-claimed RVA.
* The notes column has an object-symbol=<mangled> escape hatch that build.py's ledger_object_symbol reads, so a row whose name column is truncated or wrong does not have to be renamed to be repointed at a real COMDAT. ?loadD3DCursorTextures@W3DMouse@@ carries no signature in the ledger and is landable through it - the blocker there is the body, not the name: retail runs 559 bytes against our 332 because BFME loads cursor textures through a different API with an AsciiString temporary and a full EH frame.
* Ranking the whole backlog beats picking one candidate at a time. Every present-unmatched marker whose TU already compiles can be measured against its MASM-dump row in one pass - 503 of them are measurable, and the distribution is steep: one at a single differing byte, one at two, and roughly a dozen under ten. Prefilter the object files by searching the raw bytes for the retail pattern before parsing symbols, otherwise re-parsing each .obj per symbol makes the sweep unusable.
* Three pins harvested from the near-miss sweep, each a single delta and each blocked on a class being SMALLER in BFME rather than larger, which no shim can express by padding. ParticleSystem's transform matrix sits at this+0xC0 against our +0x274: getPosition @0x5BDDB0 reads its translation as three floats 0x10 apart at +0xCC, +0xDC and +0xEC, which is a row-major 4x4, so ParticleSystemInfo is 0x1B4 bytes shorter - and it is not the Generals-versus-Zero-Hour split, because the Generals header is the larger of the two. InGameUI::m_superweapons is at this+0x5CC against our +0x17F0, 0x1224 shorter, from findSWInfo @0x449E70. LANAPI has a member at +0x4C where we put it at +0x44, its LANMessage local is 0x1DC bytes rather than 0x1D8, and the virtual it calls is at +0xC4 against our +0xAC, all three from RequestLobbyLeave @0x6850F0.
* Growing a class is cheap and shrinking one is not. Every shim so far adds bytes or virtuals, which is why the Mouse, InGameUI-vtable and Debug cases landed; when retail puts a member EARLIER than we do the only honest fix is to find what we have that BFME does not, and that is class reconstruction, not a hole. Worth sorting the near-miss backlog by sign before picking work.
* LANAPI needed three separate growths and RequestLobbyLeave @0x6850F0 pins all of them at once: six more virtuals ahead of fillInLANMessage (called through +0xC4 against our +0xAC), eight more bytes ahead of m_transport (+0x4C against +0x44) and a LANMessage four bytes longer (0x1DC of frame against 0x1D8). The stubs go in LANAPIInterface, which owns the vtable, not in LANAPI which only overrides. Note the shape of the evidence: a 75-byte function carrying three independent structural facts is worth far more than its size suggests, so do not skip small functions that touch several subsystems.
* When a shim edit lands bytes in the wrong class, the symptom is that every member shifts by the same amount from offset zero. Anchoring on the string 'struct LANMessage' matched the forward declaration eighty lines above the definition, and brace-matching from there appended the padding to the end of a base class instead - which broke four previously matched rows at +8, +0xC, +0x1C and +0x20 while leaving the intended member alone. Anchor on the definition ('struct X' followed by a brace), and read a uniform low-offset shift as landing site error rather than as evidence about the class you were aiming at.
* LANAPI needed three separate growths and RequestLobbyLeave @0x6850F0 pins all of them at once: six more virtuals ahead of fillInLANMessage (called through +0xC4 against our +0xAC), eight more bytes ahead of m_transport (+0x4C against +0x44) and a LANMessage four bytes longer (0x1DC of frame against 0x1D8). The stubs go in LANAPIInterface, which owns the vtable, not in LANAPI which only overrides. A 75-byte function carrying three independent structural facts is worth far more than its size suggests.
* When a shim edit lands bytes in the wrong class the symptom is that every member shifts by the same amount from offset zero. Anchoring on the string 'struct LANMessage' matched the forward declaration eighty lines above the definition, and brace-matching from there appended the padding to the end of a base class - which broke four previously matched rows at +8, +0xC, +0x1C and +0x20 while leaving the intended member alone. Anchor on the definition, and read a uniform low-offset shift as landing-site error rather than as evidence about the class you were aiming at.
* Do not trust a local diff script that masks reloc slots to tell you a function is done: it hides exactly the calls that are not yet pinned. RequestLobbyLeave read as zero diffs while its call to LANAPI::sendMessage was unresolved, and only add_match's own verification caught it. The fix is a symbols.csv row for the call THUNK, not the body - 0x2B599 jmp 0x684CF0 here - and the file is CRLF despite check_csv describing it as LF-native, so append with the terminator the file actually uses.
* WinInstanceData::setText @0x499D60 gets to six differing bytes purely by attaching two shims that already exist, which is worth knowing as a pattern: before reconstructing anything, check whether some other TU already models the class. displaystringmanager's three stub virtuals in slots 6-8 move newDisplayString from +0x18 to +0x24, and displaystring's removal of the pool-glue virtual moves DisplayString::setText from +8 to +4 - both retail values, both hit exactly.
* What is left of setText is a pure instruction swap, and it resisted everything: retail emits mov [esp+8],esp then mov ecx,esp where we emit them the other way round, same six bytes reordered. Not a toolchain wall - our own compiler emits retail's order in 121 TUs, including the identical push ecx / lea edx / store / mov ecx,esp shape in W3DDisplay::gatherDebugStats. Insensitive to /O1, /Ot and /Oy-, and unchanged by removing the DEBUG_ASSERTCRASH between the two statements. Whatever perturbs the scheduler here is upstream of the flags, so the attempt was reverted rather than left as a near-match.

## RenderObjClass has no spare tail virtual, and two matched rows prove it

An attempt to give `RenderObjClass` one more virtual at the very end -- to move
`BoxRenderObjClass::update_cached_box` from slot +0x208 to the +0x20C that both
box constructors (`AABoxRenderObjClass` @0x957880, `OBBoxRenderObjClass`
@0x957C20) reach through -- is refuted by two rows that already match without it.
Adding a virtual to the base shifts every *derived* class's own slots by four,
and both of these are exact today:

- `Animatable3DObjClass::Simple_Evaluate_Bone` @0x982C20 forwards through
  `call [edx+0x214]`; with the extra slot it compiles to `[edx+0x218]`.
- `HLodClass::Get_Obj_Space_Bounding_Box` @0x97BC20 breaks the same way.

So the +4 the box constructors want cannot come from the end of
`RenderObjClass`. It is somewhere between `BoxRenderObjClass`'s own start and
`update_cached_box`, or the constructors' shape is wrong -- not settled here.
The two constructors stay as their naked thunk TUs, which do not depend on the
vtable at all, so no bytes are lost by leaving this alone. 495 bytes of matched
code outrank the 314 the conversion would have bought.

CRT functions reached under /MD are imported, so retail calls them indirectly through the IAT (ff 15); declare them __declspec(dllimport) or the compiler emits a direct rel32 that is one byte shorter and shifts every rel32 after it (hit on ceil in SupplyWarehouseDockUpdate::setCashValue).

The build's default -EHsc- only clears the /EHc half, so /EHs stays on and any destructor-bearing temporary gets an SEH prologue plus unwind state variable; a retail body with no unwind frame needs /EHs-c- on the source's cl line.

A boolean returned as `if (cond) return TRUE; return FALSE;` and as `return cond;` are not interchangeable: MSVC 7.1 computes the first in al (sbb al,al / inc al) and the second in eax (sbb eax,eax / inc eax). Read the ZH phrasing rather than assuming the compact form - it cost several attempts across the UserPreferences boolean getters. Check the String-ref verify line as well as Functions when batch-converting: a wrong literal still byte-matches because the DIR32 address is copied from the target.

## Two byte-equal candidates: count the thunk's callers, then name the cluster

`SimpleObjectIterator::firstWithNumeric` had two addresses on offer -- the
ledger's 0x001DE040 and 0x001CE6D0, which a masked-body sweep also reports as an
exact match for the same 51 bytes. Byte comparison cannot separate them and
never will: both really are those bytes.

Two cheap checks settle it, and neither needs a disassembly of the body.

**Who reaches it.** Both addresses are reached only through an ILT thunk, so the
question is who calls the thunk. 0x001DE040's thunk (0x000398C9) has exactly one
rel32 caller, at 0x001DE032 -- code sitting immediately above the body itself.
0x001CE6D0's thunk (0x00043126) has *zero* rel32 callers anywhere in `.text`: a
dead incremental-link entry, which is no evidence at all.

**Which translation unit owns the neighbourhood.** Functions from different TUs
do not interleave in the image, so the nearest claimed rows name the cluster.
0x001DE040 is surrounded by `sortFarToNear` (0x001DDF40), `next` (0x001DDFB0),
`~SimpleObjectIterator` (0x001DDFD0) and `??_GSimpleObjectIterator`
(0x001DE080) -- all SimpleObjectIterator.cpp. 0x001CE6D0 sits between
`Object::reactToTransformChange` (0x001CDC30) and `Object::setDisabled`
(0x001CE790), which is the Object.cpp/ObjectFields.cpp cluster and a different
TU entirely.

So the ledger row is right and the sweep's candidate is an unrelated 51-byte
body that happens to compile the same. Nothing was changed; the point is the
method. A sweep that reports several exact placements has not found several
candidates of equal standing -- caller count and cluster membership usually
leave exactly one, and both are two minutes of work against `functions.csv` and
the rel32 sites. Do that before spending a cycle on the bytes.

## The binary names the file that owns a gap, and the biggest gaps are not ours

`gaps.py`-style output is a list of addresses, which cannot be picked up as
work. It can be, though: retail kept the assert and DEBUG_LOG `__FILE__`
strings, and they are absolute paths out of the original build tree --
`F:\bfme\Code\gameengine\Source\GameLogic\Object\Update\AIUpdate.cpp`. A gap
whose code pushes one of those addresses is that translation unit's code, named
by the image rather than inferred. `tools/gap_owner.py` does the scan and rolls
the result up per source file.

Two things it establishes immediately.

**The largest holes in `.text` are vendored Microsoft middleware.** Everything
between roughly 0x9A0000 and 0xB00000 is statically linked library code:
0xAC8183 is 216KB of DirectX error-string tables (`E_ABORT`, the `CO_E_*` and
`DIERR_*` families), and 0xA40673 is 93KB of the D3DX shader assembler
(`POSITION`, `BLENDWEIGHT`, `TESSFACTOR`, "internal error: unknown node").
Those two alone are 310KB, they head every ranking of unclaimed bytes, and no
amount of work on them belongs in this project. The headline coverage number is
measured against a denominator that includes them.

**The largest holes that are ours, with their addresses**, are
`AIUpdate.cpp` (33,685 real bytes at 0x273DCE), `HordeContain.cpp` (26,101
across four gaps from 0x2369B5), `AIGroup.cpp` (24,566 at 0x1527B2 and
0x156C2E), `AptOnlineQuickMatch.cpp` (10,811 at 0x558F9E), `ScriptEngine.cpp`
(10,601 at 0x344291), `SpecialAbilityUpdate.cpp` (10,165 at 0x2A6588) and
`LuaScriptEngine.cpp` (9,695 at 0x2E3F04). Three of those -- HordeContain,
AptOnlineQuickMatch and LuaScriptEngine -- have no Zero Hour counterpart at
all, so they are reconstruction from the disassembly rather than porting.

The coverage is sparse by nature: a release build keeps only the asserts that
survived, and 118 gaps over 8KB hold 2.56MB of real bytes of which only 171KB
sits in a gap that names anything. Anonymity is not evidence that a region is
uninteresting -- it is usually just a file whose asserts were compiled out.

The OptionPreferences boolean getters backed by a GlobalData default compare their value with an inlined 4-byte repe cmpsb against "yes" plus sete, not a stricmp call - a plain memcmp with #pragma intrinsic still emits a real call under these flags, so that sub-shape is still unsolved and those rows remain naked.

SEH-framed bodies are convertible - findVeterancyUpgrade landed - but two have now died on MSVC bookkeeping order rather than logic: amIHost stores the EH frame pointer before setting up ecx for a by-value AsciiString temporary and parseAddModule pushes call arguments before storing a member flag, and neither order is reachable by rephrasing the source. Everything up to that point matched byte for byte in both.

For a by-value class argument built from a temporary at the call site, declare the copy constructor even though it is never called: without it MSVC materialises the temporary in a separate slot and re-pushes, with it the object is constructed straight into the reserved argument slot as retail does. That leaves only the EH-record store and the ctor this-pointer setup swapped (mov [esp+N],esp before mov ecx,esp in retail); no source phrasing and no /Ox /Og /O1 /Ob2 /Oy- /Gy /GF variation moved it, and it currently blocks ControlBarResizer::init and GameSpyStagingRoom::amIHost at one instruction pair.
## A dump row can be wrong at both ends, and the .asm file says so itself

`??0AIAttackMoveStateMachine@@QAE@PAVObject@@VAsciiString@@@Z` claimed 0x002C1061
for 501 bytes and byte-verified forever, because a MASM dump is the retail bytes.
It was wrong three ways over, each independently sufficient:

- **The start is inside another function.** The body containing 0x002C1061
  begins at 0x002C0FE0 — 16-byte aligned, preceded by `int3` padding — so the
  claim starts 129 bytes in. `audit_claim_boundaries.py` stays silent on this:
  it tests for a start inside an *instruction*, and 0x002C1061 is a clean
  instruction boundary. Being decodable is not being a function.
- **The range spans a boundary, and the dump admits it.** `0CCh` repeated
  twenty-seven times sits in the middle of the `db` lines. A function body does
  not contain a run of int3. Past that padding the claim covers two real
  functions, 0x002C11A0 and the thunk at 0x002C11D0.
- **The stack pop contradicts the name.** The body ends `c3`, `ret 0`. A
  `QAE@PAVObject@@VAsciiString@@` constructor is `__thiscall` with two
  parameters and must end `ret 8`.

Two things worth carrying forward. Reading the `db` lines of a dump for an int3
run costs nothing and catches the over-long ones directly — no disassembler
required. And with `reverse/ghidra_functions.csv` present you can ask the wider
question the boundary audit does not: which matched rows start strictly inside
a recovered function body? 319 rows do, overwhelmingly `Code/*.asm`. That is a
lead list, not a verdict — Ghidra also merges adjacent functions, so a row
ending exactly where its enclosing function ends is usually fine. Confirm with
padding and alignment before withdrawing anything.

### The address it was blocking is a trap of its own

`locate.py` places `??_GAIUpdateInterface@@MAEPAXI@Z` at the freed 0x002C11A0
and it will keep doing so. Do not land it. The body is the canonical scalar
deleting destructor — `push esi; mov esi,ecx; call <dtor>; test [esp+8],1; …;
ret 4` — whose only identifying operand is the destructor it calls, and
`build.py` fills that REL32 in from the target, so any class's `??_G` matches.
Following the call resolves through two thunks (0x0001E29F, 0x002C11D0,
0x0004AAF7) to a destructor body at 0x00172430, which sits among AIStates.cpp
and AIMoveToState code — a different translation unit from AIUpdate.cpp. So the
`??_G` belongs to one of the AI state classes, not to AIUpdateInterface. Chase
the destructor, never the deleting destructor.

## Interior int3 is the cheapest decisive test there is, and 18 rows fail it

The AIAttackMoveStateMachine withdrawal above turned on one observation that
generalises further than the row it killed: MSVC pads *between* functions with
0xCC and never inside one, so a run of int3 strictly inside a claimed range
proves the claim spans a function boundary. No disassembler, no Ghidra
inventory, no second opinion -- the retail bytes say it outright.

`tools/audit_internal_padding.py` runs it over the whole ledger. **Eighteen
matched rows fail**, twelve of them with runs of 64 int3 or more:

```
0x1699C2 1654B  body ends at +0x468, then 294 int3  AIPlayer::recruitSpecificAITeam
0x76E90A  568B  body ends at +0x15A, then 172 int3  Team::tryToRecruit
0x6000B0  807B  body ends at +0x274, then 172 int3  DefaultModuleTemplate<1>::writeINI
0x784783  984B  body ends at +0x0D2, then 171 int3  W3DRadar::drawViewBox
0x2AF8F9  523B  body ends at +0x126, then 129 int3  StructureToppleUpdate::doDamageLine
0x5A565D 1119B  body ends at +0x274, then 127 int3  LANAPI::handleRequestJoin
0x2BAFB8 1701B  body ends at +0x13E, then 122 int3  Locomotor::locoUpdate_moveTowardsPosition
0x6008AF 1257B  body ends at +0x2B9, then 120 int3  ParticleSystem::generateParticleInfo
0x37F2AD  711B  body ends at +0x19E, then 117 int3  Object::onVeterancyLevelChanged
0x4F1C4A  805B  body ends at +0x15E, then 104 int3  DownloadManagerMunkee::downloadFile
0x614F8E  496B  body ends at +0x10E, then  84 int3  ScriptActions::doTeamUseCommandButtonOnNearestKindof
0x0D93AC  487B  body ends at +0x11B, then  73 int3  Player::setRankLevel
```

Every one is a transcription of retail bytes -- a `.asm` dump, or the same
thing spelled as a `__declspec(naked)` body with an `__asm` block, which is why
three of the eighteen have `.cpp` sources. Both kinds byte-verify at any length,
so the gate has never had an opinion about them.

Worked example of what the overhang costs. `OptionPreferences::getLANIPAddress`
claims 0x092436 for 488 bytes. The body ends `add esp,0x10; ret 4` at
0x0924B1, 62 int3 follow, and 0x0924F0 -- 16-byte aligned -- opens `push -1;
push <handler>`, an SEH prologue. So the real function is 124 bytes and the row
has swallowed a whole SEH-bearing function that nobody can now claim, because
its address already belongs to getLANIPAddress.

Two cautions before acting on the list. Interior padding proves the *end* is
wrong; it says nothing about the start, which has to be checked separately (a
real start is 16-byte aligned or sits directly after a padding run). And these
rows belong to other people's work -- the tool reports, it does not edit.

- The if-form/expression-form split covers `!= 0` too: `if (x != 0) return true; return false;` gives `test eax,eax / setne al`, while `return x != 0;` gives the 32-bit `neg / sbb / neg`.
- `strcmp` is an intrinsic under `/Oi` so it inlines as `mov ecx,N / xor edx,edx / repe cmpsb`; `_stricmp` has no intrinsic and goes through the IAT. A retail `repe cmpsb` against a literal therefore means the case-sensitive one.
- A float local that MSVC keeps in st(0) is invisible except in the width of its constant loads: `fcom dword` / `fld dword` mean `float`, `fcom qword` / `fld qword` mean `double`. Assigning `atof`'s double to a float local emits no narrowing store at all, so the constants are the only evidence of the type.

## locate.py derived the evidence from the placement, and deleting destructors exploited it

`locate.py` validates a candidate placement by reading each REL32 out of the
retail bytes and recording what it points at — "callee addresses read from the
binary". For most bodies that is sound: the unmasked bytes carry the real
evidence and the callee is a bonus. For a deleting destructor there are no
other bytes. `??_G` is

    push esi / mov esi,ecx / call <the class destructor> /
    test [esp+8],1 / je / push esi / call operator delete / add esp,4 /
    mov eax,esi / pop esi / ret 4

and once the two calls are masked, what remains is identical for every class in
the program. So its identity *is* the destructor it calls — and that address
was just derived from the placement being tested. The placement proves itself.

This is not theoretical. Running `locate.py` over sixteen sources offered
**0x002C11A0 to six different translation units**, as `??_GActionManager`,
`??_GAIUpdateInterface`, `??_GAssaultTransportAIUpdate`,
`??_GChinookAIStateMachine`, `??_GDeliverPayloadAIUpdate` and
`??_GDozerPrimaryStateMachine`, each with its own invented `symbols.csv` pin
putting that class's `??1` at 0x0001E29F. Any one `--emit` would have landed a
false row *and* a false pin, and the pin is the worse half — it would go on to
"resolve" call sites in unrelated functions.

The tool now refuses these and reports them as SELF-CONFIRMING. The check that
works is narrow: for `??_G`/`??_E`, require that the **class destructor** callee
already has a known address. Requiring merely *some* known callee does not
work, because the body also calls `operator delete`, whose address is always
known and says nothing about which class this is — that first attempt let all
six through unchanged.

To claim one of these properly, pin the class destructor first from something
outside the body: a vtable slot, or a caller that is already byte-matched.

### And 0x002C11A0 really is identifiable — by the destructor, not by the bytes

Chasing the destructor instead of the deleting destructor settles it. The `??_G`
at 0x002C11A0 calls thunk 0x0001E29F, which reaches 0x00172430 via 0x002C11D0
and 0x0004AAF7. That body installs vtable VA 0x1095B08, and slots 4, 5 and 6 of
that table are the already-matched `onEnter`, `onExit` and `update` of
`AIInternalMoveToState` — so 0x00172430 is that class's destructor, named by
evidence entirely outside the bytes being compared.

Which makes 0x002C11A0 the *second* `??_G` of AIInternalMoveToState. The first
is at 0x0014F350, sitting in slot 0 of the same vtable, and the two differ by
exactly one operand: 0x0014F350 calls the thunk at 0x0004AAF7 directly, while
0x002C11A0 goes the long way through 0x0001E29F. Two translation units emitted
the same deleting destructor, the linker could not fold them because their call
chains differ, and both survived. Neither belongs to ActionManager,
AIUpdateInterface, AssaultTransportAIUpdate, ChinookAIStateMachine,
DeliverPayloadAIUpdate or W3DProjectedShadow, all of which the tool was happy
to put there.

Worth remembering as a positive result too: two byte-different copies of one
compiler-generated body are normal when they take different thunk hops, so
finding a second `??_G` for a class you have already placed is not evidence
that one of them is wrong.
- MSVC does not fold `a == K || a < K` into a single `jle`; it emits `cmp/je/jl` to the same target, exactly as written. A retail `cmp` followed by two conditional jumps to one label is therefore evidence of two source conditions, not one relational operator — and getting the split right can also settle register allocation that looked arbitrary.
- A divide-by-constant magic pins a structure size exactly: brute-forcing which divisor reproduces `imul <magic>` + add-back + `sar n` over a range of inputs gave a unique answer (292 for PlayerTemplate). A plain pointer subtraction then regenerates the whole sequence.
- MSVC returns a 4-byte struct in `eax`, so a one-pointer iterator will not reproduce a callee that takes a hidden return pointer. Declaring a copy constructor (never defined) makes the type non-trivial and forces the memory-return form — the same declaration trick that fixes by-value class arguments.


## docs/ini_schema.md is a complete layout oracle for 96 classes, and nothing uses it

Half the entries above are hand-triangulated class layouts — an offset read off
one instruction, a size read off an `operator new`, a pad placed and then walked
back when it broke a matched row. Meanwhile `docs/ini_schema.md` has been
sitting in the tree with the **exact retail offset of every INI-parsed field of
96 classes**, decoded from the binary's own `FieldParse` tables. Nothing in
`lessons.md`, `AGENTS.md` or `docs/structural.md` mentions it. It is not
inference: the table is plain data, `{ token, proc, userData, Int offset }`, and
`tools/dump_ini_schema.py` walks it.

Among the 96 are `Weapon`, `Object`, `Locomotor`, `Armor`, `Upgrade`,
`Science`, `PlayerTemplate`, `Terrain`, `FXList`, `ObjectCreationList` and
`CommandButton` — several of which have entries above describing exactly the
guesswork this file would have replaced.

**Correction to the WeaponTemplate entry.** It says "a class whose only proven
fact is its SIZE takes a tail pad, not a mid-class one", having pinned 0x53C
from `WeaponStore::newWeaponTemplate`. The size was not the only proven fact:
the `Weapon` table carries **112 fields with offsets**, up to 0x535. A tail pad
happens to keep every existing row green, but it is not the layout, and any
field it puts in the wrong place will surface later as a one-instruction diff
nobody can explain.

**Worked example, CommandButton.** `CommandButton::isReady` (0x0049AD30, 146
bytes — not the 93 the queue reports, which is our own body's length) reads
`[this+0x34]` and hands it to the same callee our source reaches with
`[this+0x24]`. The table says why, exactly:

```
Options   0x018    Object 0x01C   Upgrade 0x020      <- ours agree
NeededUpgrade 0x024                                  <- BFME-only, 4 bytes
BuildUpgrades 0x028  AsciiStringVector               <- BFME-only, 12 bytes
SpecialPower  0x034                                  <- ours has it at 0x024
```

so the divergence is two added fields totalling exactly 0x10. Further down the
same table shows `TextLabel` at 0x044 and `DescriptLabel` at 0x050 are
*AsciiStringVectors* where ours are plain AsciiStrings, adding 8 bytes each. The
class is reconstructable field by field rather than by triangulation.

Two limits worth stating. The table only names fields the INI parser writes, so
runtime-only members between them are still unconstrained — the offsets bracket
those gaps rather than filling them. And it gives retail's layout, not our
header: knowing `SpecialPower` belongs at 0x034 does not by itself say which of
our members to grow, so the existing matched rows still decide between an
insert, a pad and a relocation.
- A hand-rolled value type is not a substitute for the reference one. Replacing WWMath's `Vector3` with an equivalent-looking class (initialiser-list constructor, compiler-generated copy and assignment) made MSVC round-trip every temporary through memory with integer moves; copying the real header's form — user-defined copy constructor and `operator=`, constructor bodies that assign — kept each component in the FPU and the body collapsed onto retail.
- MSVC does not evaluate float operands in source order, and is not consistent between components of the same expression: `Max + Min` loaded `Min.X` first but `Max.Y` and `Max.Z` first. A reversed-looking operand pair in one component proves nothing on its own — flip the whole expression and re-compare.
- When a body is mostly a container's inline machinery, identify the exact container first — `SimpleDynVecClass` and `DynamicVectorClass` have different member order and different growth rules, so guessing costs a full reconstruction. Two divide-by-four sequences in one function were `Shrink` (`ActiveCount < VectorMax/4`, folding to `VectorMax/4 > 0` right after `Delete_All` zeroes the count) and `Grow` (`Length() + Length()/4`) — same idiom, unrelated meanings.

## Ledger and git traps that cost pushes rather than cycles

Three of these are specific to how the ledgers are stored and one is generic
git, and between them they cost several failed pushes in a single session.

**`symbols.csv` is CRLF, but not uniformly.** At least one row ends with a bare
LF. Appending after such a row leaves `\n\r\n`, and the union merge driver then
sees your line and the peer copy of the same pin as different lines, so the next
rebase produces an exact duplicate and `check_csv` blocks the push. Append by
taking `upstream/master`'s copy of the file and adding your line with `\r\n`,
rather than appending to whatever the working tree happens to hold.

**Do not reach for `tools/dedup_csv.py` when that happens.** It rewrites both
ledgers with normalised terminators — a 157,000-line diff that conflicts with
every other agent and destroys the `\r\r\n` rows `add_match` indexes by raw
line. Delete the duplicated line by hand; it is one line.

**`git reset --soft upstream/master` while upstream is ahead of your rebase base
stages a revert of the peer commits in between.** The index keeps your tree,
which relative to the newer base looks like undoing their work. Check
`git status --short` for files you never touched before committing.

**`docs/lessons.md` conflicts on almost every push** because everyone appends to
it. Both sides are appends, so keeping both hunks is always the resolution — but
a conflicted rebase still needs the merge checked, since `functions.csv` uses
union merge and has no concept of a deletion.

## Where the mechanical methods stand, so nobody re-runs them

Ranked by what they still return, as of 2026-08-04.

**Structural findings** remain the best return by far: one fact about a class
unlocks many functions at once, and `docs/ini_schema.md` now makes that fact
cheap for 96 INI-parsed classes (see the oracle entry above).

**Pinning through ILT thunks** still works and is the only way to get an address
that exists nowhere else. Pin the *thunk*, not the body — call sites encode the
thunk.

**The masked-body sweep (`tools/landsmall.py`) is exhausted.** It produced ~90
functions historically and produced nothing at all across four fresh attempts:
`Common/StateMachine.cpp`, all 51 files of `GameLogic/Object/SpecialPower`, and
the three largest gap-owning files (`AIUpdate.cpp`, `AIGroup.cpp`,
`W3DTreeBuffer.cpp`). Previously swept and empty: zlib, Lua, EAC, WWMath,
WWLib, WW3D2, WWDebug/WWSaveLoad, the Upgrade/Contain/Die/Body/Create modules,
GUI/Thing/ScriptEngine, most of GameClient and GameNetwork. Re-run it only when
a class layout changes and reopens what that class blocked.

**Thunk-located bodies (`tools/thunkchase.py`, `tools/claimlocated.py`)** are
nearly finished: down from 276 wrapper sites to ~29 distinct bodies, of which a
full run landed one.

So the remaining queue is genuinely structural. `tools/next_work.py --ranked`
tops out around 87% agreement and its `ghidra` tier is empty — "No
Ghidra-anchored absent function candidates remain."

## Open leads with addresses, so they are not rediscovered

**`AIInternalMoveToState`'s destructor is identified but unclaimed** at
0x00172430, 98 bytes. The proof is deliberately not its own bytes: it installs
vtable VA 0x1095B08 (RVA 0xC95B08), and slots 4, 5 and 6 of that table are the
already-matched `onEnter`, `onExit` and `update` of that class. Exactly two
sites in the image store the pointer — this destructor, and a store at
0x0014F2BF inside the 149-byte function at 0x0014F280, which is the constructor
and is also unclaimed, with the class's own `??_G` at 0x0014F350 behind it. The
destructor carries an SEH frame, a global null-check and a virtual call through
`[edx+0x4c]`, so it is a reconstruction rather than a transcription.

**`CommandButton` layout is proven and landing is blocked by five funclet rows.**
The INI field table gives the front exactly: `Options` 0x018, `Object` 0x01C and
`Upgrade` 0x020 agree with ours, then BFME inserts `NeededUpgrade` (0x024, 4B)
and `BuildUpgrades` (0x028, AsciiStringVector, 12B), which is why retail reads
`m_specialPower` at +0x34 where ours sits at +0x24. `CommandButton::isReady`
@0x0049AD30 is what exposed it — and note its real length is **146 bytes**, not
the 93 the work queue reports, which is our own body's length; it also needs a
BFME-only branch (`cmp [this+0x10],0x16`) that the Zero Hour source lacks.
Adding the two members to `reference/shims/controlbarlayout` compiles but
renumbers the compiler-generated labels in ControlBar.cpp, breaking five
`object-symbol=$L…` funclet rows (`uw_00c27f10`, `uw_00c27fe0`, `uw_00c27fee`,
`uw_00c27ffc`, `uw_00c28250`). `tools/relabel.py` reports **all five ambiguous**
and refuses them: the `std::vector` member adds code, so the labels do not shift
uniformly and its positional check fails. Landing this needs the layout and the
funclet re-keying in one commit, deriving each funclet's label from its position
inside its parent. Further down the same table `TextLabel` (0x044) and
`DescriptLabel` (0x050) are AsciiStringVectors where ours are plain
AsciiStrings, so the tail needs more than these two inserts.

**Still open, unchanged:** `MeshMatDescClass::Init_Alternate` @0x929410 (1047B,
80% agreement, remainder is SIB order and spill-register choice rather than
layout); `TurretAI::setTurretTargetObject` @0x18D120 (280B, 218 diffs, base
layout already correct so what is left is its own logic);
`?loadD3DCursorTextures@W3DMouse@@` (ledger name is truncated with no signature,
and the body diverges — retail 559B against our 332).

**`StateMachine` has no addresses at all.** `StateMachine.cpp` shows 10 matched
rows but every one is an STL helper; all 27 real methods are
`present-unmatched`, none is in the export table or in `reverse/vtables.tsv`,
and the masked sweep places none of them.
`reference/shims/turretai/Common/StateMachine.h` already encodes two extra BFME
virtuals ahead of `setState` (pinned by `recenterTurret` @0x18C8D0) but keeps
both Zero Hour bases — and the merged `MemoryPoolObject`+`Snapshot` finding
recorded above has never been tested on this class.

**Dropped as stale:** the `bfmeFactoryAnchor*` question in ModuleFactory.cpp. No
row in `functions.csv` and no pin in `symbols.csv` mentions those symbols any
more.

## The unclaimed gaps that are actually ours

From `tools/gap_owner.py`, which names the owning translation unit from the
`F:\bfme\Code\...` assert strings retail kept. Several of these files have no
translation unit in `Code/` at all — they are BFME-only and would be
reconstruction from the disassembly rather than porting.

| Real bytes | Address | Owner |
|---|---|---|
| 33,685 | 0x273DCE | `AIUpdate.cpp` |
| 26,101 | 0x2369B5, 0x2408CE, 0x23B6D5, 0x244AD5 | `HordeContain.cpp` — **no TU** |
| 24,566 | 0x1527B2, 0x156C2E | `AIGroup.cpp` |
| 10,811 | 0x558F9E | `AptOnlineQuickMatch.cpp` — **no TU**, Flash/Apt UI |
| 10,601 | 0x344291 | `ScriptEngine.cpp` |
| 10,165 | 0x2A6588 | `SpecialAbilityUpdate.cpp` — **no TU** |
| 9,695 | 0x2E3F04 | `LuaScriptEngine.cpp` — **no TU** |
| 9,588 | 0x73670E | `W3DTreeBuffer.cpp` |
| 8,932 | 0x76569E | `W3DScriptedModelDraw.cpp` — no TU |
| 8,912 | 0x71A140 | `W3DShrubBuffer.cpp` — no TU |
| 8,138 | 0x6ACB6D | `MilesAudioManager.cpp` — no TU |

## Triaging the eighteen over-long rows

Interior padding proves the end is wrong and says nothing about the start, so
each row still needs its start checked. Doing that — is it a Ghidra function
start, is it 16-byte aligned, is it preceded by padding — leaves only **three**
that are plain over-long rows safe to shrink:

| Row | claims | real body | start evidence |
|---|---|---|---|
| `DefaultModuleTemplate<1>::writeINI` @0x6000B0 | 807 | 628 | Ghidra start, aligned, padded |
| `RTS3DScene::Visibility_Check` @0x9446F0 | 1075 | 456 | 16-byte aligned |
| `StructureToppleUpdate::update` @0x8F7E80 | 1211 | 52 | 16-byte aligned |

The other fifteen have starts nothing corroborates, which puts them in the same
class as the withdrawn AIAttackMoveStateMachine row — but that is a triage
signal and not a verdict, since Ghidra misses a third of real-source starts and
MSVC does not align every function. Two are worth looking at first because the
arithmetic is extreme: `OptionPreferences::getLANIPAddress` claims 488 bytes for
a 124-byte body and `getOnlineIPAddress` claims 397 for 124, and both are
`__declspec(naked)` `.cpp` sources rather than dumps, so withdrawing them means
deleting source too.

Note that shrinking a dump row is not a one-line ledger edit: the `.asm` must
have its `db` lines truncated to the same length, or the source and the row
disagree about what is being verified.
- Padding filler must account for the vtable pointer explicitly, and whether one exists depends on the *shim* class, not the real one. A filler of `[0xD8]` in a class that declares a virtual puts the next member at 0xDC; the same filler in a class that declares none puts it at 0xD8. Both mistakes shift every offset in the dump by four and read like a different layout rather than an off-by-one-slot — check the shim's own virtuals before re-deriving the layout.
- `mov reg,0` where `xor reg,reg` would do is not a different constant: `xor` clobbers flags, so MSVC picks the longer encoding when a comparison has already set flags that a later branch still needs.

## The oracle is now a diff: tools/ini_layout_diff.py

The entry above says an INI-parsed class is reconstructable field by field
rather than by triangulation. `tools/ini_layout_diff.py` does it in one command:
it reads our `FieldParse` table out of the compiled object, lines it up by token
against retail's decoded table in `docs/ini_schema.md`, and prints the per-field
offset delta plus the list of fields retail parses that our table does not —
which is the list of members to add.

It reproduces, in seconds, the CommandButton analysis that took an hour of
disassembly: four fields agreeing, `SpecialPower` at our 0x24 against retail
0x34, the cascade to +24 and +32 as `TextLabel` and `DescriptLabel` widen into
vectors, and `NeededUpgrade` 0x024 / `BuildUpgrades` 0x028 at the head of the
additions list. That agreement with an independent measurement is the reason to
trust it.

Two things it immediately says about classes nobody had numbers for. Our
`WeaponTemplate` table has 76 fields against retail's 112, and its front is
0x24 *too high* — `AttackRange` sits at our 0x38 where retail has 0x14 — so the
tail pad recorded earlier is not merely incomplete, the class is smaller at the
front and larger later. `LocomotorTemplate` agrees on exactly one field out of
fifty, despite Locomotor.cpp verifying 44/44, which is a reminder that a green
translation unit says nothing about a template class whose accessors are not
among the matched rows.

Read the deltas as evidence about retail, not as instructions. The table only
constrains fields the parser writes, runtime-only members between them are
free, and the matched rows still decide between an insert, a pad and a
relocation.
- The decorated name distinguishes `class` from `struct`: `PBURGBColor@@` is a pointer-to-const *struct*, `PBVAsciiString@@` a pointer-to-const *class*. Declaring the wrong one produces a differently-mangled symbol and `build.py` fails with "symbol not found in object" rather than a byte mismatch — read the `U`/`V` before writing the shim.
- MSVC does not algebraically simplify integer division, so `LOGICFRAMES_PER_SECOND * t / DRAWABLE_FRAMES_PER_FLASH` stays a multiply followed by a divide instead of collapsing. Two constants in the source remain two operations in the bytes, which is what makes them individually recoverable.

## $L-keyed funclet rows freeze 503 translation units against layout work

A row whose note says `object-symbol=$L<n>` finds its compiled body by a
compiler-generated label. The number depends on how much code precedes it in the
translation unit, so *any* change that adds or removes code renumbers it and
`build.py` stops with `symbol not found in object: $L48498` — a message that
reads like a broken checkout and is really a layout change doing its job.

Measured on the current ledger: **1,367 such rows across 503 translation
units.** (An older note put it at 87; that number is stale.) The worst
concentrations are `module_pool_glue_bulk.cpp` with 146,
`subsystem_interface.cpp` with 63 and `UserPreferences.cpp` with 36.

`tools/relabel.py` repairs the easy case and refuses the rest, correctly: it
re-identifies a funclet by its bytes, funclets share a prologue and their one
distinguishing operand is a masked rel32, so it falls back to a positional check
— same label count, uniform shift, nth stays nth — and reports AMBIGUOUS when
that does not hold. It does not hold whenever the edit changes how many labels
the TU emits, which is exactly what adding a member with a constructor does.

Two independent attempts hit this in one session, and neither was an unusual
edit:

- adding `NeededUpgrade` and a `std::vector<AsciiString> BuildUpgrades` to
  `CommandButton` broke five funclet rows in ControlBar.cpp
  (`uw_00c27f10`, `uw_00c27fe0`, `uw_00c27fee`, `uw_00c27ffc`, `uw_00c28250`),
  all five AMBIGUOUS;
- opting Upgrade.cpp into the existing AudioEventRTS shim broke `$L48498`.

So the practical position is that the header layout of 503 TUs is frozen, and
every structural finding that lands in a header has to fight this first. Fixing
it is worth more than any single class: a funclet's real identity is its parent
plus its position among that parent's funclets, which the object's unwind data
states directly, and re-keying the rows that way would survive renumbering. Until
then, expect to land a layout change and its funclet re-keying as one commit.

## Frame size counts local slots, so it constrains the signature

`sub esp,N` is a direct count of the local slots MSVC allocated, and each is 4 bytes
(or the object's size). When a body otherwise matches and only the frame constant and
the esp displacements differ, do not look at the statements -- enumerate what would
occupy the slots. On ProcessAnimateWindowSlideFromLeft::updateAnimateWindow retail's
`sub esp,0x10` is exactly three locals: the saved `this`, one float temp, and the
8-byte Coord2D. Declaring the setter as `setVel(Coord2D)` reproduced every instruction
but added a fourth slot for the by-value copy; declaring it `setVel(const Coord2D &)`
removed that slot but cost a different one and spilled the FPU stack. The frame size
told me the accepted answer has three slots before any byte of the body was in doubt,
which is a much sharper constraint than reading the statements back.

## An inline accessor is not always the same code as the member read

ScriptActions::doUnitReceiveUpgrade came down to two bytes: retail loads the vtable
for the second virtual call with `mov eax,[esi]` where mine used `mov edx,[esi]`. The
first virtual call in the same block picks edx in both builds, because eax is busy
holding the argument there -- so the question was only why eax stayed unavailable in
mine. Neither the callee's return type nor the if-form moved it. What moved it was
reading the argument through `templ->getUpgradeMask()` instead of `templ->m_upgradeMask`.
Both are one `mov eax,[edi+0x20]`, but the inlined call and the direct member read reach
the allocator as different expressions and it frees eax afterwards in one and not the
other. So when a residue is nothing but a scratch-register choice, try swapping raw
member reads for the accessors the original almost certainly used -- it is a real
codegen lever, not just style.

## The $L freeze is breakable: re-key funclets by position, not by bytes

The entry above measures the problem -- 1,367 rows keyed to `object-symbol=$L<n>`
across 503 translation units, renumbered by any edit that changes how much code
precedes them, with `relabel.py` refusing most of them because funclets share a
prologue and their one distinguishing operand is masked. It is the standing
obstacle in front of every header and shim change.

Position survives renumbering even when bytes cannot tell the labels apart. The
compiler emits them in a fixed order, so the nth `$L` symbol of a given size
before the edit is the nth of that size after it. `tools/rekey_funclets.py`
records the label set first, and maps across afterwards.

Worked example. Opting Scripts.cpp into a shim broke four rows -- `uw_00c19370`,
`uw_00c19378`, `uw_00c194a8`, `uw_00c196c0` -- which `relabel.py` reported
AMBIGUOUS with seven and eight byte-identical candidates each. Positionally they
map to `$L64250`, `$L64251`, `$L65497` and `$L69079`: **all four shifted by
exactly -43**, and Scripts.cpp then verified 33/33.

That uniform shift is the corroboration to insist on. If every row moves by the
same delta the mapping is almost certainly right; a ragged one means code landed
between the funclets and the result needs checking by hand. Either way
`./build.sh <source>` decides, because a wrong label either fails to resolve or
fails the byte comparison -- there is no silent way to be wrong here, which is
what makes the positional guess safe to make.

The workflow is: snapshot, edit, re-key, verify.

    python3 tools/rekey_funclets.py --snapshot <source.cpp> /tmp/before.json
    # make the header or shim change
    python3 tools/rekey_funclets.py <source.cpp> /tmp/before.json
    ./build.sh <source.cpp>

## Two BFME facts that unlock ScriptEngine's callers

Both were needed for `ScriptAction::WriteActionDataChunk` (0x003513F0) and its
False twin, and a translation-unit-scoped shim keeps them off everyone else.

**ScriptEngine carries three more virtuals right after its destructor.**
WriteActionDataChunk reaches `getActionTemplate` through vtable +0x28 where the
Zero Hour header lands it at +0x1C. That is the same trio already recorded for
GameWindowManager and DisplayStringManager: a `SubsystemInterface` derivative
whose pin is exactly three slots late.

**Template has no base and no vtable.** `script_conditions.cpp` had already
derived the layout -- `lea edi,[esi+0x10720]` points straight at `m_uiName`, and
sizeof is 0x7C -- but the finding sat in one file's local stand-in class rather
than anywhere the real header could use it. It is why retail reads
`m_internalNameKey` at +0x0C where the pooled Zero Hour class, carrying
MemoryPoolObject's vptr in front, puts it at +0x10. Worth checking the other
locally-declared stand-ins in converted thunk files for layouts nobody promoted.

### And where the next three are NOT

`ScriptActions::doUnitGarrisonSpecificBuilding` (0x00302570) shows there are
three *more* BFME virtuals somewhere between `getActionTemplate` and
`getUnitNamed`: with only the trio after the destructor it reaches getUnitNamed
at +0x5C where retail has +0x68. Parking them immediately before getUnitNamed
gets that slot right and is still wrong -- it breaks
`doEnableOrDisableObjectDifficultyBonuses` and
`setObjectsShouldReceiveDifficultyBonus`, which pin slots in that range where
they are. Those two bound the search: the three go above whatever slots they
reach, not directly in front of getUnitNamed. Reverted rather than landed, so
ScriptActions.cpp stays 66/66.
## `jmp` over the alignment padding means a while loop, not a do-while

MSVC pads a loop head for alignment, and when the loop is pre-tested it has to jump
over that padding to enter the body: `je EXIT` / `jmp HEAD` / a multi-byte nop such as
`8d a4 24 00 00 00 00` / `HEAD:`. A do-while falls straight into the body and never
emits that `jmp`. On ScriptConditions::evaluateNamedOwnedByPlayer I wrote the mask walk
as a do-while, copying ScriptActions::doGiveMoney, and got the loop body byte-for-byte
with three things wrong outside it: the callee-saved `push esi` sat after the second
early return instead of before it, and consequently the two `return false` blocks
swapped which one was inlined and which one jumped. All three followed from the loop
form -- a pre-tested loop merges its entry test with the function's trailing
`return false`, which changes what the register save dominates. Changing do-while to
while fixed all of it in one edit. Read the entry jump before choosing the loop form,
and do not carry the form over from a sibling function just because the body matches.

### ScriptActions.cpp cannot take the same shim, and the reason is worth knowing

The trio works for Scripts.cpp and breaks ScriptActions.cpp: opting that file
into `reference/shims/scriptenginevtable` fails
`doEnableOrDisableObjectDifficultyBonuses` and
`setObjectsShouldReceiveDifficultyBonus`, whose setter writes
`[ecx+0x16F20]` where retail has `[ecx+0x17634]`.

The first guess -- that the shim, being a copy of the plain reference header,
had lost `reference/shims/scriptenginelayout`'s 0x6868 pad -- is wrong. Rebasing
it on the layout shim so the two differ *only* by the three stubs leaves the
member exactly 0x714 low all the same. So three added virtuals move a member of
that class by 1,812 bytes, which a normal derived class cannot do: whatever
`scriptenginelayout` declares, its ScriptEngine is a stand-in whose size and its
vtable are not independent. Anyone widening that shim has to understand that
first; ScriptActions.cpp was left on the layout shim alone, 66/66.

## The merged pooled-snapshot base fits State's members but not StateMachine's vtable

`TurretAIIdleState::onEnter` (0x0018CB40) reads the machine pointer at
`[esi+0x1C]` where `State : public MemoryPoolObject, public Snapshot` puts it at
+0x20, so State really does get BFME's merged base -- deriving it from Snapshot
alone moves that read onto retail's offset, which is the prediction the TurretAI
entry above makes for "any ZH class inheriting both".

The vtable does not follow, and the numbers are worth writing down because they
bound the answer. `TurretAI::recenterTurret` pins `StateMachine::setState` at
vtable +0x20. With both Zero Hour bases that needs two invented slots in front
of it, which is what `reference/shims/turretai` carries. Give StateMachine the
merged base and remove those two, and setState lands at **+0x24** -- one slot
too late. Each invented stub is worth 4, so the merged-base layout needs one
*fewer* virtual before setState than the Zero Hour declaration list provides,
not one more.

Counting the reference headers does not explain it: Snapshot has exactly three
pure virtuals and a non-virtual destructor, `MEMORY_POOL_GLUE_WITHOUT_GCMP`
contributes one virtual destructor, `GCMP_CREATE`'s getClassMemoryPool is
static, and StateMachine declares four virtuals before setState. That is slot 8
= +0x20 on paper against +0x24 measured. So one of those four is not virtual in
BFME, or the merged base contributes two slots rather than three -- and
recenterTurret alone cannot say which.

Reverted rather than landed: with the merged base and no stubs TurretAI.cpp goes
19/20, and the one casualty is recenterTurret itself. Anyone picking this up has
State confirmed, StateMachine's member offsets to check separately, and one slot
to account for.
## A declared copy constructor is what lets MSVC throw in place

`throw T(args)` should construct the exception object once. With `T` holding only
plain members and no declared copy constructor, MSVC 7.1 instead built the temporary,
then copied it memberwise into a second slot and threw that -- eight extra bytes of
frame and a run of movs the retail body does not have. The tell that it was a copy and
not just different addressing is that the loads came through the constructor's returned
`this` in eax rather than the stack slot the compiler had just written. Declaring a copy
constructor (no definition needed) removed the copy entirely and the function matched:
once the copy has to be a call, MSVC constructs directly into the exception temporary
instead. Same lever as forcing a hidden-pointer return -- a user-declared copy
constructor changes what the compiler is allowed to do inline -- but here it removes
work rather than adding it. /EHsc versus /EHs-c- made no difference at all.

## A naked byte dump proves its bytes, never its name

The byte gate compares a symbol's compiled bytes against the retail bytes at its recorded
address. For a `__declspec(naked)` body those bytes were copied from that address, so the
comparison is a tautology -- it passes for any name someone attached to the dump. Every
naked row therefore carries an unverified identity by construction, no matter which pass
produced it (the bad ones I have found span four different provenance tags, so this is not
one careless batch). Converting to real C++ is the first thing that actually tests a name,
because the mangled name has to compile from a declaration whose class, return type,
constness and arity all produce exactly those bytes.

So read the body against the claimed signature BEFORE starting. The cheapest tells:
a claimed `_N` return against a body ending `or eax,-1`; a claimed `X` (void) return
against a body that loads eax; `ret N` disagreeing with the decorated argument list; and
`this`-relative offsets that make no sense for the claimed class -- a GameLODManager method
has no reason to run _M_find over a map at this+4 while loading TheGameLODManager
separately from a global.

## The `mov [esp+N], esp` before a by-value AsciiString is still unsolved

Two unrelated functions emit the same idiom and neither reproduces it. In
OptionPreferences::getIdealStaticGameDetail (0x00090900) retail reserves the argument
slot with `push ecx`, then `mov [esp+0xC],esp`, then `mov ecx,esp` and only then
computes the source. In the AITunnelNetworkGuardState constructor (0x001717B0) it is
`push ecx` / `mov [esp+8],esp` / `mov ecx,esp` before building the name string. In both
cases the slot being written is an earlier `push ecx` reservation that nothing reads
again, so the compiler is stashing the address of a by-value class argument there.

What it is NOT: exception state (compiling /EHsc adds a full SEH prologue retail does
not have, and /EHs-c- reproduces everything else exactly); the argument expression
(member access, an explicit pointer cast and an explicit temporary all emit identical
bytes); or the ordering of the surrounding statements, which was already fixed and made
the rest of getIdealStaticGameDetail match to the byte.

This is worth solving once rather than per function: every preferences getter and every
named-state constructor passes an AsciiString by value, so the same six bytes block a
whole family. The next thing to vary is the shape of AsciiString itself -- how its
destructor and copy constructor are declared -- rather than anything at the call site.

## Probe the compiler directly instead of guessing through the byte gate

I spent six builds trying to make MSVC emit one `mov [esp+N],esp` by rewriting the
source around it -- five declarations of the class, three forms of the call site --
and every one of them compiled to identical bytes. The full build-and-compare loop is a
slow way to ask a narrow question.

Writing throwaway variants under Code/ and calling tools/build.py's own compile_source
on each answers the same question in one shot, and lets you check for two things at once
(does the idiom appear, does an SEH prologue appear) instead of eyeballing a diff. That
immediately localised it: the idiom is not a source-shape artifact at all, it is the
exception model. /EHs-c- never emits it, /EHs emits it cleanly, /EHsc and /EHa emit it
with an SEH prologue attached.

Two cautions the first pass got wrong. Search the object for BOTH the thing you want and
the thing that would disqualify it -- my first probe only looked for the idiom and
reported /EHs and /EHa as equal winners, when /EHa also drags in SEH. And remember the
probe is not the function: a probe with no destructible local said /EHs was clean, while
the real function has one and got an SEH prologue anyway. Give the probe the same locals
as the target, or drive the object with explicit init/destroy calls so it has none.
## A repointed pin leaves the wrong row behind, and both survive the gate

The Matrix3D entry above records that `?Set@Matrix3D@@QAEXABVMatrix3x3@@ABVVector3@@@Z`
was pinned to 0x00964150 -- a 274-byte ICF group shared with
`?setEaseTimes@ParabolicEase@@QAEXMM@Z` -- and that the pin was repointed to the
real 82-byte body at 0x008D6710. Two things it did not do survive today.

`reverse/symbols.csv` still carries **both** lines: line 2576 pins the symbol at
0x00964150 with no note, line 60243 pins it at 0x008D6710 with the repointing
rationale. The gate is happy either way, because a symbol legitimately has
several addresses -- the thunk and the body -- so nothing distinguishes a stale
pin from a real second one.

And `reverse/functions.csv` still claims the Matrix3x3 spelling **as a row** at
0x00964150, 274 bytes, from a `__declspec(naked)` `__emit` source, sharing that
address and size with `setEaseTimes`. The entry above already argues that
address cannot be an 82-byte function.

That is the shape to watch for whenever a pin is repointed: the note lands on
the new line, the old line stays, and a transcribed row keeps the wrong name
alive because it matches whatever bytes it was cut from. 498 symbols in
symbols.csv are pinned to more than one distinct address; most are the honest
thunk-and-body pair, and telling those apart from stale repoints needs the
5-byte `E9` test, not a count.

Next step for whoever picks it up: drop the 0x00964150 pin and the Matrix3x3
row, then re-check `??0OBBoxRenderObjClass@@QAE@ABVOBBoxClass@@@Z` (0x00957C20,
167 bytes), whose C++ is already in boxrobj.cpp and which the sweep reports at
exactly retail's size.

## Size the argument list before reading a single instruction

The decorated name says how many bytes a callee-cleaned function must pop, and the
body says how many it does pop. When they disagree the name is wrong and no amount of
getting the body right will make it build -- the mangled name is what the compiler
emits, so a five-argument name can never produce `ret 0x18`. This is the cheapest
possible check and it needs no disassembly beyond the last instruction.

The catch is sizing the list honestly. A first attempt that guessed at class and enum
return types reported 175 hits, nearly all noise from mis-consuming names. The fix is
to refuse rather than guess: a class passed by value has no size in the name, template
names embed their own `@@` so scanning for the terminator lands mid-name, and varargs
are caller-cleaned. Return None for all of those and treat None as no opinion. With
backreference digits resolved and a class-by-value return charged its hidden pointer,
the same screen reports 73 findings out of 964 naked rows, and the ones I have checked
by hand all hold up.

## A name on a byte-identical neighbour proves nothing -- follow the caller's thunk

`?getSlot@GameInfo@@QAEPAVGameSlot@@H@Z` sat on 0x0061E8E0 as `matched` and had done
for a long time. It was on the wrong body. The 25 bytes at 0x0061E8E0 are identical
to the 25 at 0x0061E900 that `getConstSlot` claims, so compiling our getSlot and
finding it agrees with one of them says only that we produced a plausible accessor,
not that we produced *this* accessor. Two byte-equal bodies mean the verifier cannot
tell them apart, and a `matched` row is then a coincidence dressed as evidence.

The discriminator is a caller. `checkForDuplicateColors` (0x00386520) calls getSlot
through the ILT thunk at 0x0001EC18, and that thunk jumps to 0x0061E8B0 -- a third,
32-byte body 0x30 earlier that nobody had claimed. Call sites encode the thunk, the
thunk names one body, and that is the only statement in the image about which of the
lookalikes carries the name. Whenever a short accessor has a byte-twin nearby, treat
its row as unproven until some caller points at it.

Two practical notes. First, the thunk target has to be decoded, not read off the
ledger note: functions.csv recorded `target=FUN_00a1e8b0` for 0x0001EC18, while the
`e9` displacement actually resolves to 0x0061E8B0. Second, repointing is cheap to
test -- the full gate went from 94119/94119 to 94119/94119 with the row moved, which
proves no matched caller had been leaning on the old address. Had the count dropped,
the old address would have been the right one.

## Confirm a source shape on a probe TU before touching the ledger

Rewriting a function to chase a hypothesis breaks its existing row the moment you
save, so the tree goes red while you are still guessing. Instead put the hypothesis
in a throwaway TU with just enough class around it to fix the offsets, compile it
with `build.compile_source`, and read the bytes back with `build.read_object_symbol_bytes`:

    import sys, pathlib; sys.path.insert(0, 'tools'); import build as B
    src = pathlib.Path('Code/probe.cpp').resolve()
    obj = pathlib.Path('build/obj_probe/probe.obj').resolve()
    B.compile_source(src, obj)                       # both args must be Path
    print(B.read_object_symbol_bytes(obj, '<mangled>', <size>)[0].hex(' '))

Compare against the retail bytes, and only edit the real source once they agree. This
is how the getSlot shape above was settled: the `&&`-for-`||` difference and the
never-firing array null check both had to be present, and the probe said so in one
compile without putting a single row at risk. `locate.py` is the wrong tool here --
it wants a unique placement in .text, and a short accessor with byte-twins is exactly
the case it refuses.

## BFME's INI parsers throw a variadic INIException where Zero Hour crashes

Zero Hour's parse helpers end with `DEBUG_CRASH((fmt, tok)); throw INI_INVALID_DATA;`,
which under NDEBUG leaves a bare throw of a constant. BFME replaced both with one
`throw INIException(code, fmt, ...)` -- a `__cdecl` variadic constructor, pinned at
0x00850600 as `??0INIException@@QAA@HPBDZZ`. In the image it shows up as pushes of the
argument, the format string, a small integer code, and a stack buffer, then the throw
helper with the same throw-info pointer the bare throw would have used. `ini.cpp` and
`GameLOD.cpp` already had the idiom; `parseDynamicGameLODLevel` (0x0007C390) needed it
with code 3 and the format string still readable at 0x01076BCC.

The same function also carries a content difference worth generalising: BFME's
`DynamicGameLODNames` has five entries, not four, with `"VeryLow"` inserted ahead of
`"Low"`, so every level constant after it shifts by one. When a parse loop's `cmp` is
one higher than the table you have, check the table before you check the codegen --
the pointers are sitting in .rdata and dumping them settles it immediately.

## A getter that returns a class zero-initialises what the scalar ones do not

Three preferences getters share one skeleton -- build a key, look it up in the map at
this+4, compare the node against the map header. Two of them return a scalar and
construct the key straight into its slot. The third returns AsciiString by value and
nulls the key slot first, `mov dword ptr [esp+0xc],0` immediately before the
constructor call, which was the entire eight-byte difference on an otherwise exact
body. In the shim that is `CustomAsciiStringShim key = { 0 };` rather than a plain
declaration. Worth remembering when porting a skeleton between siblings: the by-value
return changes more than the epilogue.

## BFME's INI object puts the scalars first and the buffers last

Zero Hour's `INI` starts with `File *m_file`, then drops an 8 KB `m_readBuffer`
immediately after it, so `m_loadType` lands at `+0x2010` and every other scalar sits
past the buffer too. BFME reordered the object: `parsePrerequisites` (0x001485B0)
reads the load type at `[ini+8]`, which is where it falls if `m_file`, `m_filename`
and `m_loadType` are the first three words and both character buffers move to the
end. `reference/shims/ini_bfme/Common/INI.h` is that reordering and nothing else.

The evidence is narrow but clean: with the shim in force parsePrerequisites compiles
to exactly retail's 63 bytes and the `cmp dword ptr [edi+8], 2` matches, where the
Zero Hour order gave 66 bytes and `[edi+0x2010]`. ThingTemplate.cpp's other 110
matched rows are untouched by the change, which is the useful half of the result --
nothing in that file was leaning on the old order, so the reorder is free to adopt
wherever it helps.

What it does not do is land the function. parsePrerequisites also reads
`m_prereqInfo` at `+0x2c4` where our ThingTemplate puts it at `+0x15c`, and 0x168
bytes of BFME additions inside a class that large is its own project.
`tools/ini_layout_diff.py` is the right instrument for it but refuses this block:
the source has 115 tokens against 110 live entries in the object because a
conditional entry compiles out, so position-based alignment is not safe. Teaching
the tool to skip conditional entries is the unblocking step, not more hand-reading.

Two smaller negatives from the same sweep, so nobody repeats them: parsePreferredAgainst
(0x0010FE90) compiles to 50 bytes against retail's 204 and parseArbitraryFXIntoMap
(0x00145C80) to 310 against 206, both with unresolved template callees. Neither is an
INI-layout problem and the shim does not move them.

## The field table names BFME's inserts, so stop guessing at pad sizes

With `ini_layout_diff.py` reading tokens out of the object, CommandButton falls out
in one run: every parsed field from `SpecialPower` onward is +16 against retail, and
retail's table has two entries ours does not at exactly the offsets that gap covers
-- `NeededUpgrade` at 0x24 and `BuildUpgrades` at 0x28. Four bytes for a pointer plus
twelve for a container is the 16, and `m_specialPower` moves from 0x24 to 0x34 where
`isReady` (0x0049AD30) reads it. No instruction-reading, no trial pad.

The general shape: when a run of parsed fields is off by a constant, look for retail
tokens missing from our table whose offsets fall inside the gap. They are the
insertion, they come with names, and the sizes are usually forced once you know
whether each is a scalar or a container.

Two operational notes. Adding a `std::vector` member introduces destructor unwind
funclets, so `rekey_funclets.py` reports a RAGGED shift (105 labels before, 107
after, three distinct deltas) rather than a uniform one. Ragged is a warning, not a
verdict -- here all 51 matched rows in ControlBar.cpp still verified, so the
positional mapping had been right. Build before believing the warning either way.
And `next_work.py`'s size for an unclaimed candidate is a hint: it offered isReady at
93 bytes, but the body branches to 0x49ADBB, and the int3 run does not start until
146 bytes in. Check the branch targets against the claimed extent before working to it.

## AsciiString's const char* constructor is out of line in retail

`reference/shims/asciistring_outofline` existed to push `operator=` out of line;
the `const char*` constructor needed the same treatment and did not have it. Retail
calls it at 0x00888BC0, already pinned as `??0AsciiString@@QAE@PBD@Z`, while the
inline body in the shim expands every construction from a literal into an
`ensureUniqueBufferOfSize` sequence. Removing the body -- leaving only the
declaration -- turns that into the single call retail makes.

The cost is nil where it has been tried: AIStates.cpp and Anim2DTemplate_ctor.cpp
both stay at 140/140 combined with the constructor out of line, so no matched row in
either was depending on the inline expansion. Any state or template constructor that
builds an AsciiString from a literal is a candidate for the same wiring.

## State's merged base does not generalise from TurretAI to AIStates

The entry above on `TurretAIIdleState::onEnter` concluded that State gets BFME's
merged pooled-snapshot base, and predicted the same for any Zero Hour class
inheriting both. AIStates.cpp says otherwise. Give `State` the merged base there --
`class State : public Snapshot` instead of `public MemoryPoolObject, public Snapshot`
-- and six matched rows break immediately: `setAdjustsDestination`,
`AIAttackPursueTargetState::onExit`, `AIPickUpCrateState::update`,
`AIAttackMoveToState::onExit`, `AIMoveAndDeleteState::update` and
`AIEnterState::update`. Those rows match today with both bases, which is direct
evidence against the merged layout for the State that AIStates.cpp compiles against.

So the prediction is narrower than it was written: TurretAI's own State-derived
classes want the merged base, and the AI states do not. Do not apply it file-wide on
the strength of the TurretAI measurement alone.

The concrete casualty of this is `??0AITunnelNetworkGuardState@@QAE@PAVStateMachine@@@Z`
(0x001717B0, 53 bytes). With the AsciiString constructor out of line it is two
differences from exact: an instruction-scheduling swap at the top, and one extra
`mov dword ptr [esi+4], 0` -- the second vptr that the two-base State installs and
retail's single-vptr State does not. Landing it needs a State whose layout is merged
without disturbing those six rows, which is a narrower shim than the one tried here.

## The by-value AsciiString stash is not reachable by any /EH setting

Eighteen flag combinations compiled against the exact shape of
OptionPreferences::getIdealStaticGameDetail, each object checked for three things at
once: the `mov [esp+N],esp` stash, an SEH prologue, and the frame size. The result is
clean and negative.

    /EHs-c-                     no stash,  no SEH,  4-byte frame   <- retail's frame
    /EHs, /EHsc, /EHc, and
      every /EHs + /GS- /Gy /GF
      /Gf /Ob0 /Ob1 /Ot /G6
      /G7 /GR /Gd variant       stash,     no SEH,  8-byte frame
    /EHa                        stash,     SEH,     8-byte frame
    /EHs /Oy-, /EHs /Os         no stash

Retail has the stash, no SEH, and a 4-byte frame. Nothing produces that combination:
turning exceptions on always buys the stash together with a 4-byte EH state slot, and
turning them off loses both. So this is not a flag we are missing on our side, and
further flag probing is wasted effort -- either the retail translation unit was built
by a compiler that differs from the vendored one in this detail, or the stash comes
from a source construct none of the shapes tried so far models. Five class
declarations and three call-site forms are already ruled out (see re_attempts).

## Keep names-on-the-wrong-body out of the queue that hands out work

Three candidates in a row from `list_naked_candidates.py` turned out to be
unconvertible for the same reason, and the reason was already known. The decorated
name says how many bytes a callee-cleaned function must pop; the transcribed bytes
say how many it does pop. When they disagree the name is on the wrong body and no
amount of writing the C++ correctly will ever produce those bytes.

  * `?getGroup@Object@@QAEPAVAIGroup@@XZ` at 0x008F9550 -- name takes nothing,
    body does `ret 8` and returns 0/1/2.
  * `?xfer@GarrisonContain@@MAEXPAVXfer@@@Z` at 0x00853EC0 -- name takes a pointer,
    body does `ret 0`, zeroes `[esi+4..0x10]` and returns `eax = esi`: a constructor.
  * `?removeObjectBuilt@ScoreKeeper@@QAEXPBVObject@@@Z` at 0x0056E160 -- name takes a
    pointer, body does `ret 0` and frees `[this]` with element size 0x44.

`audit_ret_arity.py` has flagged all three the whole time; the picker just was not
asking it. It does now, and the exclusion is reported rather than silent (8 rows at
--max-bytes 130). The general point is worth generalising beyond this tool: a check
that exists but is not wired into the thing that hands out work will keep costing
people the same afternoon.

Fixing the rows themselves is a separate job and harder than the getSlot repoint
was, because none of the three has a direct caller to name the body from -- 0x0056E160
is reached only through a vtable, so there is no call site whose thunk settles it.

## A rebased store group is a shape signal that survives guessing

`??0StealthUpgradeModuleData@@QAE@XZ` (0x00129C10, 90 bytes) is the friendliest kind
of body there is: no calls, no branches, no vtable, 0x68 bytes of members zeroed
except `+0x5c` which starts at -1. Writing the obvious struct with the obvious
constructor gets 86 of the 90 bytes and every store correct.

The four bytes are addressing. Retail does `mov edx, eax` and stores the first six
words through `[edx+0..0x14]`, then `lea edx, [eax+0x18]` and stores the next six the
same way, and only then switches to flat `[eax+0x30..]`. That is what an inlined
sub-object constructor looks like -- `ecx` is holding the zero constant, so the
inlined `this` has to live somewhere else. Ours addresses all twenty-two words
straight off `eax`.

Three shapes were tried and all three collapse to flat addressing: two named members
of a six-word class, the same with an initialiser list instead of assignments, and a
two-element array of it. Compile flags are not the lever either -- the sibling
thunk's `/GX- /O2 /Ob2` gives byte-identical output to `/EHsc` here. Whatever keeps
that pointer alive in retail is structural and is not any of those, so the row stays
a transcription rather than a 86-byte near-miss sitting in the tree.

Worth stating as a rule: a group of stores rebased onto a second register is
evidence about how the members are *nested*, not about how they are written. When
the flat version already gets every store right, stop varying the statements and go
looking for the sub-object.

## Two things stand between LifeEventModuleInfo's constructor and exact

`??0LifeEventModuleInfo@FXParticleSystem@@QAE@XZ` (0x005FC710, 90 bytes) is worth
writing down because the reconstruction is *known*, not guessed, and still does not
land. The class is a vtable, an int at +0x04, a `GameClientRandomVariable` at +0x08
and an int at +0x14; the three stores at `[esi+8..0x10]` are that variable's default
constructor zeroing `distribution`, `minimum` and `maximum`, and the call is
`setRange(0.0f, 0.0f, UNIFORM)`. All of that reproduces.

What does not:

  * **The unwind frame.** Written plainly the constructor compiles to 41 bytes with
    no SEH at all. Giving `GameClientRandomVariable` a declared destructor brings the
    frame in and gets to 85 of 90 with every store and the call present. The last
    five bytes are the state transition: retail writes `mov byte ptr [esp+0x1c], 1`
    after constructing the member, ours writes a dword zero and never transitions.
    So retail tracks one more constructed object than our shape does.

  * **The call goes through the export thunk.** Retail calls 0x00006C58, which is the
    `export_rva` on setRange's own functions.csv row; our build resolves the same
    name to the `target_rva` 0x00096F40 and emits a direct call. There is no
    symbols.csv pin for the thunk, and adding one under a name that already has a
    functions.csv row is not obviously safe, so this needs deciding rather than
    guessing.

The second point is general: a callee with both an export thunk and a body will be
reached by whichever the *call site* encodes, and rows carrying an export_rva do not
automatically make call sites use it.

## UnitCrateCollideModuleData's destructor: three bytes of EH state encoding

`??1UnitCrateCollideModuleData@@UAE@XZ` (0x001270F0, 83 bytes) reconstructs almost
completely. The body destroys two members at +0x58 then +0x44 -- reverse declaration
order, so +0x44 is declared first -- both through 0x00887940, which is
`StringBase<char>::releaseBuffer` and the body a dozen AsciiString-destructor rows
already alias. Afterwards the base vptr goes back at `[esi]` with no base destructor
call, so the base's destructor is trivial and inlined.

Two details that took a pass each to find, and both generalise:

  * The member class needs a name of its own. `??1AsciiString@@QAE@XZ` is a
    functions.csv row on the 5-byte jump at 0x0005EE90, so a member declared as
    AsciiString resolves to the jump rather than to the body. Aliasing under a
    distinct name with a symbols.csv pin at 0x00887940 is what
    BFMEPlayerTemplateAsciiString and its siblings already do.

  * `__declspec(novtable)` on the derived class is load-bearing, and the previous
    agent's naked stub already carried it. Without it MSVC stores the derived vptr
    at destructor entry, six bytes retail does not have; retail only restores the
    base vptr at the end.

With both, the body is 80 bytes against 83 and every instruction present. The
remainder is EH state encoding: retail writes state 0 then state 1, both as dwords,
where we write 1 as a dword then 0 as a byte. Increasing state indices in a
destructor is backwards from the usual pattern, and no arrangement of two members in
one class reproduces it -- swapping declaration order is impossible without moving
the offsets, and giving the two members distinct types changes nothing. Whatever
orders those states is structural, the same conclusion the StealthUpgradeModuleData
entry above reached from a different direction.

## The ModuleData destructor family: what reproduces and what does not

Three of these were attempted in one sitting and they fail in the same shape, so it
is worth one note rather than three. Each reconstructs to within a handful of bytes
with every instruction present, and the residue is always something the compiler
decides rather than something the source says.

`??1MinefieldBehaviorModuleData@@UAE@XZ` (0x0036CE20, 100 bytes) is one inlined WW3D
Release_Ref on a refcounted pointer at +0x24: null-check it, InterlockedDecrement its
counter at +0x04 through the IAT, and on reaching zero go through vtable slot 0 with
a 1, which is what `delete` on a polymorphic pointer compiles to. Unlike the
UnitCrate destructor this class is *not* novtable -- retail stores the derived vptr
at entry and the base vptr at the end, with no base destructor call.

That reconstructs to 96 of 100. The four bytes are a second `test esi,esi / je`
before the delete, on a pointer retail has already null-checked and cached in a
register. MSVC folds that check away for us under every spelling tried: `&&` versus
nested ifs, a local versus re-reading the member, an inline `Release_Ref` member, an
inline `Delete_Instance(p)` free function with the check written out explicitly, and
/Ob1 to hold inlining back. Retail keeps it every time.

Taken with the StealthUpgradeModuleData rebasing and the UnitCrate EH-state ordering,
the pattern across the family is that the last few bytes are never reachable by
rewriting the statements. They come from how the retail translation unit was
structured -- what was a separate function, what was in a header, what the inliner
saw -- and that is not recoverable by trying spellings. When a body of this kind
stalls within single digits of exact with all instructions present, stop varying the
source and record it; the next lever is evidence about the original TU, not another
rewrite.

## WW3DErrorType is not renumbered globally, whatever Save_Info looks like

`AggregateDefClass::Save_Info` (0x00980B90) reads unambiguously: `xor bl, bl` before
`Begin_Chunk`, `mov bl, 1` after a successful `Write`, and a subobject loop that runs
while `cmp bl, 1` holds. Taken alone that says BFME numbers the assume-error value 0
and `WW3D_ERROR_OK` 1 -- the reverse of Zero Hour -- and the appealing part is that
the Zero Hour source text would then already be correct with only the values changed.

It is refused by evidence elsewhere. Reordering the enum in
`Code/Libraries/Source/WWVegas/WW3D2/w3derr.h` breaks four matched rows in
meshmdlio.cpp -- `read_texture_stage`, `read_material_pass` and two neighbours --
each by a single byte in a jump displacement, meaning the Zero Hour numbering is what
those bodies were built against. A per-file enum is not a real thing, so one of the
two readings is wrong, and the four matched rows outweigh the one unmatched function.

The likeliest resolution is that `bl` in Save_Info is not a WW3DErrorType at all: the
virtual it calls through `[edx+0x24]` may return a Bool, with the 0/1 being FALSE and
TRUE and the conversion happening at the return. That would explain the byte-width
operations too, which are the other thing the enum theory never accounted for --
retail keeps this value in `bl` throughout while an int-sized enum gives `ebx`, and
the decorated name `?AW4WW3DErrorType@@` forbids changing the type to something
byte-sized.

So: do not renumber this enum, and treat a Save_/Load_ status variable held in a byte
register as evidence that the source variable is not the enum it is eventually
returned as.

## Save_Info's status is a byte, and that is the whole remaining gap

Following the entry above to its end: holding `ret_val` as `unsigned char` instead of
`WW3DErrorType` reproduces everything the enum theory could not. `xor bl, bl`,
`mov bl, 1`, `cmp bl, 1` and `mov bl, al` all match, and the subobject assignment is a
raw low-byte copy rather than a `test`/`setne` -- so `Save_Subobject`'s value is taken
as a byte, not converted from an int.

That leaves 111 bytes against 109, and the two are the return: retail does
`mov al, bl` and leaves the rest of eax alone, which is what MSVC emits when the
declared return type is byte-sized. Ours does `movzx eax, bl` because the declared
type is an int-sized enum. Both cannot be true of the same declaration, and the enum
cannot be byte-sized because meshmdlio.cpp's matched rows depend on the int one.

The reading that fits every observation is that BFME's Save_Info does not return
WW3DErrorType at all -- it returns a byte type, and the row's name came from Zero
Hour. If so the decorated name should be `_N` rather than `?AW4WW3DErrorType@@`, which
is checkable against the vtable slot and is the next step rather than another cast.
Reverted; a two-byte near-miss is still a near-miss.

## What actually blocks the naked backlog, counted

972 rows still carry a `__declspec(naked)` body. Sorting them by the first blocker
each one hits:

    625  64.3%  172,346B  SEH prologue -- needs unwind funclets
    224  23.0%   52,272B  no known blocker
     59   6.1%   27,352B  name contradicted by its own bytes (tools/screen_identity.py)
     44   4.5%   13,290B  by-value class stash, which no /EH setting reproduces
     20   2.1%    6,300B  ebp frame, so not /O2 as this build is configured

Two things worth taking from that. The SEH bucket is nearly two thirds of the backlog
and a third of its bytes, so learning to reproduce unwind funclets is worth more than
any number of individual conversions -- everything else is a rounding error beside it.

And the 224 unblocked rows are a real pool, not a residue. I had previously concluded
the easy candidates were exhausted; that was wrong, and wrong in an instructive way.
The sweep behind that claim also demanded a size window and an arity match, and the
arity check silently skips every row whose argument list cannot be sized from the name
-- classes by value, templates, varargs. Those skips are correct as "no opinion" for
flagging, but treating them as disqualifying turned a wide pool into a handful of rows.
A filter built from several signals inherits the narrowest one; check what it excluded,
not just what it returned.

## Probe in the context the code actually appears in -- and detect precisely

The blocker on two module-data constructors is that retail materialises each member's
address before storing -- `lea ecx,[esi+0x70]` then stores through ecx -- where my source
folds onto the object pointer. Probing source forms for this produced two wrong answers
in a row, each wrong for its own reason, and both are worth keeping.

The first probe compiled the constructor standalone and reported that several forms give
the register addressing. They do -- standalone, `this` already arrives in a register, so
the question was never asked. The real constructor is inlined into a factory after a
`new`, which is a different question entirely.

The second probe fixed the context but detected by searching the whole object for bytes
like `89 01`. Those occur in vtables and in neighbouring functions, so it reported success
for inline member constructors when there was none. Detecting the ABSENCE of the folded
form (`mov [esi+0x70], reg`) and counting `lea`s at the member offsets says the opposite:
across seven layouts -- same and different member types, int members, a nested type with
its own constructor, the +8 subobject as a base and as a member, with and without a
leading pad -- MSVC coalesces the two adjacent three-word members into one run of six
stores through the object pointer every single time. Retail keeps two groups, each with
its own `lea` and its own zeroing register.

So the state is: no source form tried reproduces this, and the reason is the coalesce, not
the addressing. Two rules fall out. Probe in the context the code actually appears in, and
search for the thing that would DISPROVE the result rather than the thing that would
confirm it -- a substring that can occur incidentally is not evidence.

## Group locals into the struct they came from to fix frame layout

W3DCameoMovieDraw came down to two displacement bytes: four out-parameters that retail
reaches high in the frame and my version placed the other way round. Written as four
loose Ints the pairs came out adjacent but in the wrong order, and swapping the
declaration order did not move them -- which looked like confirmation of the older note
here that local slot assignment is not steerable.

It is steerable, just not by declaration order. Declaring the position and size as two
ICoord2D structs -- which is what Zero Hour uses -- fixed it outright. A struct forces
both the adjacency and the relative order of its members, where separate locals leave
both to the allocator and it has its own opinion.

So when a body is otherwise byte-identical and only stack displacements differ, the
question is not what order the locals were declared in but whether they were locals at
all. Two Ints passed by address to a pair of accessors is very often one small struct in
the original, and the frame layout is the evidence for it.


## Repeated initialiser blocks are one member type, not many fields

ScriptList::updateDefaults allocates 0x4C bytes and then writes, in order, zero at +4
and +8, the vtable at +0, zero across +0x0C..+0x20, -1 at +0x24 and +0x28, zero across
+0x2C..+0x40, and -1 at +0x44 and +0x48. Written out as a flat class that is nineteen
fields to invent names and initialisers for, and getting any of their widths wrong
shifts everything after it.

Read as structure it is three declarations. The two 0x20-byte runs are byte-for-byte the
same initialiser -- six zeros then two -1s -- so they are one member type used twice, not
sixteen fields that happen to coincide. The stores at +4 and +8 land before the vtable
store, and MSVC always writes the vptr after the base constructors and before the member
initialisers, so those two belong to a base with no virtuals of its own, which MSVC
places at +4 with the derived vfptr taking offset 0. That leaves 4 + 8 + 0x20 + 0x20 =
0x4C exactly, so the size confirms the reading before anything is compiled.

The general rule: within a constructor the store order is base, then vptr, then members
in declaration order, and it is a total order you can invert. A store that precedes the
vptr came from a base; a repeated run of identical stores came from a repeated member
type. Both of those are structure the disassembly hands you for free, and both are the
kind of thing that costs several builds to find by trial if you start from a flat class.

Built byte-exact on the first attempt -- the first candidate this session chosen by
predicting which blocker family it would land in before writing any of it, rather than
discovering the blocker after two or three builds.


## A function-local static folds its own address, and that changes the whole body

ConcreteModuleClass<Tag>::getInstance is the MSVC function-local static idiom, and the
constructor it inlines is already byte-exact as its own row, so writing getInstance as
`static X theInstance; return theInstance;` looked like it should fall straight out.
It does not, and the reason generalises.

Retail materialises &theInstance into edx once and then stores from registers -- a3 for
the value in eax, 89 15 and 89 0d for edx and ecx. The rebuild folds the static's address
into every store as a c7 05 immediate, because to the compiler that address genuinely is
a compile-time constant. Fifteen bytes longer, every load otherwise identical and in the
same form.

The second-order effect is the interesting part. The constructor writes the base vtable
at +0 and then immediately overwrites it with the derived vtable. Retail eliminates the
first store; the rebuild keeps it. That is the same cause, not a separate one: once each
store is an independent absolute-address instruction rather than a chain through one
register, the redundant one no longer presents as dead in the same way. One allocation
decision moved both the encoding and the dead-store elimination.

So this joins the immediate-versus-register split as a blocker family, and it is worth
recognising early: whenever the target holds an object's address in a register across
several stores and the rebuild emits absolute forms, the difference is not going to be
fixed by rephrasing. Rewriting the inlined constructor to store through a named local
instead of `this` produced byte-identical output, which is the confirmation -- when two
genuinely different spellings compile to the same bytes, the lever is not in the source.

Also, second validation of the funclet re-key: tools/rekey_funclets.py reported RAGGED
again on this translation unit and was again correct, with all 559 other rows still
verifying. The warning flags a non-uniform shift, not a failure.


## Where a constant lives is the compiler's decision, and it cascades

removeAllShadows walks three shadow lists, clearing each head and setting a byte flag
on every node. The structure fell out of the disassembly immediately and the rebuild
reproduced all of it. The whole delta is that retail materialises zero into edx and uses
it nine times -- `cmp eax,edx` for six null tests and `mov [ecx+N],edx` for three head
clears -- where the rebuild emits `test eax,eax` and `c7` immediate stores.

The cascade is what makes this worth recording. Because retail spent edx on the zero,
the constant 1 for the flag had to go somewhere else, so it landed in ebx, so the
function pays a push and a pop it would not otherwise need. One allocation decision
changed the encoding of nine instructions, the choice of two registers, and the
prologue. Reading the diff as several independent problems would be wrong; it is one.

Three genuinely different source structures were tried: three inline loops, a named
null constant used by every site, and a helper taking the head by reference and inlined
three times. All three compiled to byte-identical output.

CORRECTION. This section originally went on to say that adding /O1 to the per-file cl
directive changed nothing either, and concluded the lever was not in the source. The
/O1 test was invalid: the file had been rewritten with PowerShell's
`Set-Content -Encoding UTF8`, which prepends a UTF-8 BOM, and a BOM stops build.py
matching `// cl:` on line 1, so the directive -- new flag and original flags alike --
was silently dropped. With /O1 actually applied the body changes substantially and
picks up retail's zero-in-register form: xor edx,edx, mov [ecx+N],edx, cmp eax,edx.
So this is a flag axis, not a dead end. See "The optimisation level decides which
constants get registers" below.

The source-spelling half of that still holds: three genuinely different spellings
compiling to identical bytes does mean no rephrasing will help. What does not follow --
and what was wrongly concluded here -- is that nothing will help. Identical output
across spellings only rules out the source; it says nothing about the flags, and the
flags turned out to be exactly where the difference lived.

Note also how the screening tool failed. tools/screen_blockers.py rejects rows carrying
a known blocker signature, and its first version matched the function-local static guard
as a byte load followed directly by `test al,cl`. MSVC puts `mov eax,1` in between, so
the pattern never matched and the entire family -- the one proven blocked an hour
earlier -- was reported as clear. It was caught only by running the screener against a
row already known to be blocked. A detector that has never been shown a true positive
is not yet evidence of anything.


## Check whether a family member is typical before reusing the family's template

friend_newModuleData is the largest family in the ledger: 269 rows across 141 source
files, and 140 of those files are already clean C++. Exactly one is still naked, which
looked like the easiest remaining conversion in the project -- copy the neighbour and
change the names.

It is not, and the reason is worth knowing before reaching for any family template. The
other 140 declare the module data constructor and never define it, so MSVC has nothing
to inline and emits a call, which is what their retail bodies contain. This one's retail
body inlines the constructor instead: the base sub-object is built through
lea ecx,[esi+8], the vtable goes in at +0, and two three-word member runs follow at
+0x70 and +0x7C. Same family, opposite requirement.

Defining the constructor in the translation unit did not produce the inlined form. MSVC
emitted an out-of-line call anyway and wrapped the allocation in an unwind frame so that
operator delete runs if a member constructor throws -- an SEH prologue retail does not
carry. Four builds, no movement.

One loose end recorded rather than asserted: removing /EHsc and then setting /EHsc-
explicitly changed the output by not one byte, which should not be true if the flag is
reaching the compiler. Worth confirming that the per-file `// cl:` directive is applied
before anyone spends more builds on the exception-handling axis, here or elsewhere.

The layout is settled and costs nothing to reuse when that is resolved: size 0x88, base
sub-object at +8 whose constructor is pinned at 0x0000F0A6, vtable 0x0108F4F0, field
parse table at 0x004102C6.

A separate process note. The cache line `Compile: 0 of 1 TU(s) (deps-cache: 1 current)`
appears when a re-run reuses an object, and it is easy to read a diagnostic re-run's
cache hit as evidence that an earlier real build never happened. build.py keys the cache
on the source hash and the full command fingerprint, so an edited source always
recompiles. Read that line against the run that actually did the work.


## The optimisation level decides which constants get registers

removeAllShadows differed from retail only in how constants were materialised: retail
holds zero in edx and one in bl, the rebuild emitted immediates. Three source spellings
could not move it. The optimisation flag moves it immediately, and not in the direction
a single switch would suggest:

  /O2 (base)   one in a register (mov dl,1), zero as c7 immediates, loops aligned
  /O1, /O2 /Os zero in a register (xor edx,edx, mov [ecx+N],edx), one as an immediate,
               no loop alignment
  retail       BOTH in registers, and loops aligned

So retail is not reproduced by either setting. Favour-size promotes the zero, favour-
speed promotes the one and aligns the loops, and retail has all three at once. /G6
changed nothing on this body. That is a real, narrow, still-open question, and it is
worth far more than another round of respelling: the same mixture shows up in the
immediate-versus-register family generally, which is the single largest blocker
recorded here after SEH.

Two process points came out of finding this.

A UTF-8 BOM silently disables the per-file `// cl:` directive, because build.py matched
`line.startswith("// cl:")` and the BOM sits in front of the slashes. Nothing warns; the
file simply compiles with base flags. Windows PowerShell's `Set-Content -Encoding UTF8`
writes a BOM by default, so any flag experiment driven from PowerShell was testing
nothing. build.py now reads with utf-8-sig, and the five files in the tree that already
carried a BOM -- every one of them with a `// cl:` line being ignored -- have been
stripped and reverified.

And the general lesson: an experiment that changes nothing is only evidence once the
experiment is known to have run. Four builds were spent concluding a flag did not
matter, when the flag was never passed. Before believing a negative result, prove the
input reached the thing under test -- here, a `#ifndef GUARD / #error` in the source
answered it in one build.


## A minimal reproducer is worth more than another blocked row

??0StealthUpgradeModuleData@@QAE@XZ is 90 bytes of straight-line stores with no calls
and no branches, and the rebuild gets 86 of them exactly right. The tail from +0x30
onward -- ten zeroed words, a byte store, a -1 written as an immediate, two more zeroed
words -- is byte-identical, which incidentally confirms the heuristic is not simply
"constants go in registers": retail keeps the zero it uses twenty-eight times in ecx and
still writes the single -1 as an immediate, exactly as the rebuild does.

The whole difference is four bytes. Retail walks the two six-word runs at +0 and +0x18
through a materialised pointer -- mov edx,eax, then lea edx,[eax+0x18] -- while the
rebuild folds both into [eax+disp] addressing off this. Nothing else differs anywhere in
the function.

That makes this row worth keeping as the reference case for the materialised-versus-
folded family, which is the same divergence that stopped friend_newModuleData. It is
far more useful than a normal blocked row: no calls to pin, no branches, no relocations,
no unwind, so a single build gives an unambiguous yes or no on any hypothesis. Anyone
testing a flag idea should try it here first and only then on a real candidate.

What has already been ruled out on it: two separately named members and a two-element
array of the same type both compile to byte-identical output, so the shape is not
source-steerable; and /EHsc, the base /O2, and the proven /GX- /O2 /Ob2 all produce the
same bytes, so it is not any of the settings the tree has already established.

Worth noting retail's form is the larger one -- 39 bytes against 35 -- so whatever
selects it is not favouring size, and /O1 is therefore unlikely to be the answer here
even though it was decisive on removeAllShadows.


## Two reusable levers: the element destructor, and signedness

??0FastAllocatorGeneral@@QAE@XZ went from nothing to three of its four divergences
solved in three builds, and two of the fixes generalise to any similar row.

The leading call is the vector constructor iterator ??_L. Its arguments are the whole
layout, free of charge: (this, 0x18, 0x80, ctor, dtor) says the first member is an array
of 128 objects of size 0x18 at offset 0, which is why the zeroed run that follows starts
at exactly +0xC00. Reading the helper's arguments settled the class in one step where
guessing offsets would have taken several builds.

Getting that helper emitted at all is the first lever. A member array of class type is
built with an inline loop calling the element constructor unless the element type has a
destructor -- then MSVC needs cleanup for a partially constructed array and switches to
??_L, passing the destructor as the fifth argument. So a call to ??_L in the target is
positive evidence that the element type has a declared destructor, and declaring one is
what makes the rebuild match.

The second lever is signedness, which is visible in a single byte. Retail compares the
running allocation size with jb, the unsigned branch; the same source with a signed int
gives jl. A `72` where the rebuild has `7c` is not a scheduling difference or a register
choice, it is the declared type of a local, and it is worth checking for directly
whenever a comparison is the only thing out of place.

What is still open is narrow and precisely stated: retail zeroes the 128-entry free list
with an explicit store loop -- lea, a down-counter in edx, then mov [eax],ecx / add
eax,4 / dec edx / jne -- while MSVC recognises the fill and emits rep stosd. An indexed
for loop, an explicit pointer walked with a do-while down-counter, and /Oi- all produce
rep stosd; /Oi- governs intrinsic functions like memcpy, not this loop-idiom
recognition, so it is the wrong knob. Everything else in the function, including the
whole second loop and the tail, already matches byte for byte.


## Bounding a blocker is a result: rep stosd lives inside /Og

The one thing still separating ??0FastAllocatorGeneral@@QAE@XZ from byte-exact is a
128-entry zero fill that retail writes as an explicit store loop and MSVC turns into
rep stosd. This pass bounded it rather than solved it, and the bound is worth recording
because it closes several axes at once.

Source form does not control it. An indexed for loop, an explicit pointer walked with a
do-while down-counter, and -- the most promising idea, since retail's shape is exactly
what MSVC's own array construction emits -- making the free list an array of a small
class whose constructor zeroes its member, all produce identical bytes. That last one is
the informative failure: MSVC builds the member array with an inline loop, inlines the
element constructor into it, and then recognises the resulting fill. The recognition
happens after inlining, so no amount of hiding the fill behind a constructor escapes it.

Flags do not control it either, within what is reachable. /Oi- governs intrinsic
functions like memcpy, not this loop idiom. /G5 changes nothing, so it is not a
processor-target decision. /Og- does remove the rep stosd -- which pins the transform
inside the global optimiser -- but /Og is load-bearing for everything else in the
function, and with it off the body degrades to an ebp frame with stack locals and
nothing else matches. There is no middle setting.

And the compiler itself is not an axis: only the vs2003 toolchain is vendored, so
"maybe this file was built with a different compiler" cannot be tested here even though
it remains the most likely explanation.

So the honest statement is that no configuration reachable from this tree reproduces
this loop, with everything else in the function -- the ??_L call, the four field stores,
the entire second loop and the tail -- already byte-identical. That is a much more
useful thing to leave behind than "blocked": it tells the next person which four ideas
not to spend builds on.


## The member-init list versus the constructor body is a real ordering lever

Every previous attempt to steer statement order in this project failed, and the note
here has been that the source cannot control scheduling. That is too strong. There is
one control that works, and W3DDebrisDraw's constructor is the demonstration.

Its retail body writes members at +0x10 through +0x24, then +0x34 through +0x44, and
only then +0x28 through +0x30. Those last three sit in the middle of the layout, so the
order is not declaration order and not address order. Writing every field as a plain
assignment in the constructor body reproduces none of it -- MSVC clusters the stores its
own way.

The explanation is that MSVC emits member-init list entries in declaration order, ahead
of the constructor body. So a field whose stores appear out of layout order in the
target was assigned in the body while its neighbours were in the init list. Moving
exactly those three fields into the body and leaving the rest in the init list
reproduced retail's ordering exactly, all fourteen stores in the right sequence.

That is worth remembering as a diagnostic and not just a fix: an out-of-order run of
stores in a constructor tells you which fields the original author assigned in the body.

Two smaller things fell out of the same row. A REL32 to a thunk resolves by decorated
name, so the base class has to be named for whatever is pinned at that address -- here
??0DrawableModule@@ among eight names ICF-folded onto 0x00002874. And an offset written
twice, first with one vtable and then another, means a base constructed inline: its own
vtable goes down first and the derived class overwrites it.

What remains is narrow and, again, scheduling. MSVC sinks every c7-form immediate store
-- both vtable pointers and the single -1 -- to the end of the function, where retail
leaves them in program order among the register-sourced zero stores. Both versions
contain the same instructions in the same count; only the order differs. /GX- /O2 /Ob2
does not change it. This is the immediate-versus-register family showing up a third way:
not encoding, not register allocation, but placement.


## vptr-store sinking is the blocker in front of the module-constructor family

Two constructors this session reached the same wall from different directions, and
together they characterise it well enough to name.

MSVC's canonical constructor order is: call the base constructors, write the derived
class's vtable pointers, then initialise members. Retail follows that exactly. The
rebuild instead sinks every compiler-generated vtable store past the member
initialisation to the end of the function, because nothing between them dispatches
virtually and the stores are free to move.

SlavedUpdate is the clean demonstration. It matches byte for byte from the prologue
through the last inlined base constructor -- the base call, three inlined base
constructors writing their own vtables at +0x0C, +0x10 and +0x20, the two -1s sharing
ecx through `or ecx,0xffffffff`, the zeros sharing eax -- and then diverges only in
where the four derived vtable stores sit. Same instructions, same count, same
registers. Placement alone.

W3DDebrisDraw shows the identical behaviour with two vtables rather than four, so this
is systematic rather than a scheduling coincidence. /EHsc, /O1 and the proven
/GX- /O2 /Ob2 all sink; /O1 additionally degrades the prologue, so it is strictly worse.

Two layout diagnostics are worth keeping from these rows, both free. An offset written
twice with two different vtable values is a base constructed inline: its own vtable
lands first and the derived class overwrites it -- so counting doubly-written offsets
counts the inline bases and gives their positions. And the gaps between those offsets
give each base's size, which fixes the whole layout before a line is written.

The scope matters for deciding whether to keep pushing: constructors of the form
??0X@@QAE@PAVThing@@PBVModuleData@@@Z number 240 rows across 222 source files, 139 of
them still naked. This one optimisation stands in front of most of that. It is a better
target than any individual row, and it is the strongest reason yet to suspect the
retail build used a compiler configuration this toolchain cannot express.


## Read a naked row's literals and its callers before trusting its name

A __declspec(naked) row byte-matches whatever name is attached to it, so the gate never
tests identity. tools/screen_identity.py catches the signature-level contradictions --
return width, stack cleanup -- but it cannot see meaning, and meaning is where this one
went wrong.

?validateAudio@ThingTemplate@@IAEXXZ at 0x0013E2F0 is sixty bytes that set the
AsciiString at +0x4c to "shadows" or "shadow" -- literals of length 7 and 6, passed to
?set@AsciiString@@QAEXPBDH@Z -- choosing between them on a test of a vector of 36-byte
elements. There is no audio anywhere in it. It is reachable only from
?parseObjectDefinition@INI@@ via the thunk at 0x0001D44E, and no vtable slot holds its
address. And Zero Hour's validateAudio is wholly inside #if defined(_DEBUG) ||
defined(_INTERNAL) and contains nothing but assertion macros, so a release build has no
such function at all.

Three cheap checks did that, and all three are worth running on any naked row before
spending build time on it: read its string literals, list its callers, and compare the
reference implementation's build-configuration guards. None of them needs a compile.

The row is flagged rather than tombstoned. The evidence does not support the pair, but
the correct name is not known yet, and tombstoning a row someone else may be anchored to
on the strength of "this looks wrong" would trade one error for another.

One mechanical trap found on the way. Function addresses in this project are RVAs, but
the absolute operands inside the instructions are virtual addresses, and the image base
is 0x00400000. Reading a string at the address printed in a disassembly listing without
subtracting the base silently lands outside every section -- which at least fails loudly.
Getting it wrong in the other direction, on an address that happens to map, would not.


## Two screeners that do not talk to each other will hand you a bad row

tools/screen_identity.py has been reporting ~60 naked rows whose bytes contradict their
own decorated names. tools/screen_blockers.py ranks naked rows by conversion difficulty.
Neither consulted the other, so a row already known to be misnamed was offered as a
clean candidate, chosen, and read in full before the contradiction surfaced.

?Unregister@SimpleSceneClass@@UAEXPAVRenderObjClass@@W4RegType@SceneClass@@@Z ends in
ret 4. Its name takes a pointer and a RegType enum, which is eight bytes of arguments,
and a callee-cleaned function pops exactly its argument list. The pair cannot be right,
and screen_identity had already said so. screen_blockers now runs that check and drops
such rows, which is a two-line change that would have saved most of a pass.

The body is not Unregister at all. It notifies the object through a virtual at +0x68,
removes it from lists at +0xbc, +0xd4, +0xec and +0x5c, and releases references twice.
Zero Hour's SimpleSceneClass::Remove_Render_Object is virtual, takes exactly one
RenderObjClass pointer, and does that work -- and that name appears nowhere in the
ledger. It is the obvious candidate.

It is recorded as a candidate and not applied. The arity contradiction is a proof that
the current name is wrong; it is not evidence that any particular replacement is right,
and those are different claims. Renaming on the strength of "this is the obvious one"
would replace a detectably wrong row with an undetectably wrong one -- strictly worse,
because the next screener pass would no longer flag it.

The general point, now true of three tools here: a check is only worth having if
whatever selects work actually consults it. screen_identity found this row weeks of
passes ago and nothing was reading it.


## A vtable slot plus its twin identifies a virtual almost for free

?Unregister@SimpleSceneClass@@ was provably misnamed -- ret 4 under a name whose
arguments size to 8 -- but knowing a name is wrong does not supply the right one. Four
cheap checks did, none of them a compile.

Search .rdata for the function's virtual address. It appeared at slot 3 of six
different vtables, and the neighbours were shared across all six while slot 1 varied,
which identifies slot 1 as the per-class destructor and everything below it as
inherited implementations. That fixes the slot numbering without needing to know how
many virtuals the base declares.

Then read the neighbours. Slot 2 notifies the object through a virtual at +0x64, calls
0x009DBF60, and increments the object's refcount. Slot 3 notifies through +0x68, calls
0x009DC100, and decrements it. Add and Remove, identified by behaviour rather than by
position -- which matters, because the position argument alone was ambiguous once BFME's
class turned out to declare more virtuals than Zero Hour's.

Then check what the body opens with. ?Remove_Render_Object@SceneClass@@ was already in
the ledger at 0x00942C20: fifteen bytes that tail-call the object's virtual at +0x68.
The body under investigation begins by doing exactly that inline, which is the base
class call the derived override is documented to make.

And confirm the gap. The SceneClass base was claimed; the SimpleSceneClass override was
absent. A body that behaves like the missing override, in the slot the missing override
would occupy, is the missing override.

Any one of those would be suggestive. Together they are a proof, and that distinction is
what separates a correction from a guess. The row was renamed, the impossible pair
tombstoned, and screen_identity's contradiction count went from 60 to 59.

The twin at 0x00942FA0 is still unclaimed, which is the obvious next thing to name.


## Vtable position identifies a function that is unidentifiable alone

Following one correction outward produced four functions over the last few passes, all
identified by position and by their twins rather than by disassembling them cold. That
is a method, not a coincidence, so it is now a tool: tools/vtable_gaps.py scans .rdata
for runs of code pointers, attributes each slot to a ledger row, and ranks the unclaimed
slots by how many named neighbours bound them.

One detail decides whether the output is usable. Most claimed rows in this image are
gen-thunks carrying synthetic names like ?j_00035eb8@@YAXXZ, and counting those as
"named" makes nearly every table look fully identified while burying the handful of gaps
that sit between real methods. Excluding them changed the top of the ranking completely.

Its first suggestion converted. Slot 2 of Pipe's vtable was unclaimed, bounded by Flush
at slot 1 and Put_To at slot 3. The body is five bytes -- load the vtable, jump to slot
1 -- and PIPE.H declares, inline, `virtual int End(void) {return(Flush());}`. Position
gave the candidate, the tail-call target confirmed it, and the reference header settled
the spelling. No disassembly of the body was needed to know what it was.

One MSVC detail cost the first build. Writing End inline in the class, exactly as the
header does, produced no symbol at all: an inline virtual is only emitted when something
forces it, and nothing in the translation unit constructs a Pipe. Defining it out of
line emits it, and the bytes are identical either way. So a faithful transcription of
the original declaration is not always the one that compiles to a checkable object --
match the header for layout, but define the function you are claiming.

Worth noting what this method is good for. It finds functions whose *identity* is the
obstacle, which is a different backlog from the one the byte-level blockers govern. 729
unclaimed slots currently sit next to a real name.


## A reciprocal multiply hands you sizeof(T) exactly

VectorClass<RenderDeviceDescClass>::ID has two overloads. Slot 4, taking a const
reference, was already claimed; slot 5 was not, and its body divides the byte distance
between a pointer argument and the Vector member by the element size -- which is the
pointer overload, `((unsigned long)ptr - (unsigned long)Vector) / sizeof(T)`.

Writing that byte-exact needs sizeof(T), and the division supplies it. MSVC compiles it
as a reciprocal multiply: load 0xB30F6353, multiply, keep the high dword, shift right by
ten. Only one divisor makes that sequence agree with integer division across the whole
range, and a short search finds it: 1464. Declaring RenderDeviceDescClass as 1464 bytes
of padding was enough; nothing about its actual members mattered.

So a magic constant is not an obstacle to reproducing a divide, it is a measurement of a
type whose definition you do not have. Solve for the divisor rather than trying to
reconstruct the class.

Two smaller results from the same pass.

vtable_gaps now rejects candidates whose first sixteen bytes carry an SEH prologue. An
identity found by position still has to be written as C++ afterwards, and the SEH family
has no source-level fix, so offering those wastes the pass -- which is exactly what
happened before the filter went in. Same integration mistake as screen_blockers not
consulting screen_identity, made twice now: a tool that selects work has to know what
the other tools already rule out.

And a caution about slot inference. SimpleVecClass<Vector3>::Resize looked like the
obvious name for an unclaimed slot bounded by that class's destructor -- but it is
already claimed, at a completely different address, because the same template is
instantiated in several translation units and the vtables hold different copies. Before
inferring a name from a slot, check the name is not already live somewhere else.


## Learn a template's vtable shape once and every instantiation opens up

VectorClass has a fixed six-slot vtable -- destructor, operator==, Resize, Clear,
ID(const T&), ID(const T*) -- and once that order is established from one vtable where
most slots are named, every other instantiation in the image can be read off by
position. Two more conversions came out of it this pass with no cold disassembly: slot 3
was Clear and slot 5 the pointer overload of ID, in a vtable whose other four slots were
already named.

Two details make the template case easier rather than harder.

The element size is visible in the divide. A pointer-element instantiation shifts right
by two; a class-element one does a reciprocal multiply whose divisor is recoverable, as
with the 1464-byte element earlier. So the same source text serves every instantiation
and the only thing to determine is sizeof(T), which the body states.

And identical instantiations fold. The bodies claimed here appear in several vtables at
once because pointer-element vectors compile to the same code, which is why a single
vtable can show Resize named for one instantiation and ID named for another -- the names
in a vtable listing are whichever instantiation happened to be claimed first, not
evidence about the class the table belongs to. Read the slot order, not the names.

The practical consequence: template families are the cheapest place to convert, because
the cost is understanding one class rather than one function. Worth preferring them over
individually-interesting rows while the ranking still has them.


## Template instantiation names are not reliably tied to addresses here

The last pass established VectorClass's six-slot vtable order and used it to convert two
slots, and the obvious next step was to scale it: 25 unclaimed ID(const T*) bodies sit in
the image, all byte-identical four-byte-element copies, each presumably belonging to a
different instantiation. Naming them needs the instantiation, and the method used so far
was to read it off a named neighbour in the same vtable. That method does not hold up.

Three findings, in order of how badly each damages it.

A single vtable carries names from four different instantiations. Table 0x011BC44C has
operator== named for VectorClass<int>, Resize for VectorClass<VertexMaterialClass*>, ID
for VectorClass<FontCharsBuffer*>. Identical instantiations fold, so the ledger name on
a slot records which instantiation somebody claimed first, not which class owns the
table.

The constructor evidence contradicts the body evidence. ??0?$VectorClass@G@@ stores that
same vtable -- unsigned short, a two-byte element -- while its slot 5 divides by four. A
two-byte element cannot do that, so at least one of those two attributions is wrong, and
nothing in the image says which.

And a claimed row can sit outside every vtable. Resize for VectorClass<FontCharsBuffer*>
is a genuine body at 0x0005E610, not a thunk, referenced by no vtable slot at all -- a
duplicate instantiation the linker kept while the vtables point at the folded copy.

RTTI would settle all of it, and is not available: the image is built with -GR-, so there
is no complete object locator behind these vtables.

The two rows already claimed this way are body-compatible -- Clear does not depend on the
element type at all, and the ID overload's shr 2 matches a four-byte element sitting at
slot 5 beside the slot 4 overload of the same name -- so they are recorded with the
caveat that the instantiation is inherited rather than proven, instead of being quietly
left to look verified.

The rule this leaves: vtable position is sound evidence for *which method* a body is, and
that is what it was introduced for. It is not evidence for *which instantiation* a
templated body belongs to. Twenty-five plausible-looking claims were one step away, and
plausible is the wrong standard for a ledger other people build on.


## Two more filters, and a way to tell a live body from a dead duplicate

vtable_gaps was reporting mostly noise, for two separate reasons now fixed.

Runs of .rdata dwords that merely fall inside the code range are not vtables. The tell is
free: a real vtable slot points at a function's entry, never into the middle of one. So
if any slot resolves to the interior of a claimed function, the whole run is data and gets
discarded. That alone took the candidate list from 432 to 113.

And template gaps are excluded by default now, per the previous pass: a slot identifies
which method a body is, not which instantiation it belongs to.

What the cleaned-up ranking then produced is worth recording as a technique in itself.
Vector3SolidSphereRandomizer had two gaps; v3_rnd.h gives the base's virtual order as
destructor, Class_ID, Get_Vector, Get_Maximum_Extent, Scale, Clone, so the slot after the
destructor is Class_ID and the one between Get_Vector and Scale is Get_Maximum_Extent.
Both bodies confirm it without reference to position -- one returns a constant unsigned
int, the other loads a float member onto the x87 stack, which is exactly how each
declared return type leaves a function.

Class_ID converted. Get_Maximum_Extent could not, because that name is already claimed --
at 0x0010BD90, a byte-identical four-byte body. Which raises the question of which copy is
real, and there is a clean answer: count vtable references. The claimed address is
referenced by no vtable slot anywhere in the image. The unclaimed one at 0x00B02050 is
referenced by exactly slot 10 of the SolidSphere vtable. The compiler emitted this
function in several translation units, the linker kept more than one copy, and only one of
them is ever dispatched to.

That generalises into an audit worth building: a claimed virtual method whose address
appears in no vtable, while an identical body elsewhere does appear in one, is anchored to
a dead duplicate. Recorded as a lead rather than acted on -- repointing another
contributor's row is not something to do on the strength of a single pass, and the
existing claim is not exactly wrong either, since both copies are genuinely that
function's code.


## Look for the reference header by class, not by the file you expect

GridCullSystemClass's vtable had three unclaimed slots after nine named ones, and the
obvious reference file -- cullsys.h, which defines the base CullSystemClass -- does not
mention the derived class at all. It would have been easy to conclude no reference
existed and either guess or move on. Grepping the whole tree for the class name found
gridcull.h immediately, and with it the declaration order.

That order settled slot 9 in one step: the header declares
`virtual int Get_Object_Count(void) const { return ObjCount; }` immediately after Save,
and slot 9 -- the first gap after Save at slot 8 -- is a four-byte getter returning the
int member at +0x54. Converted first build.

Two details from the same vtable worth keeping.

Overloads appear in reverse declaration order. The header declares Collect_Objects for
Vector3, AABox, OBBox then Frustum; the vtable holds Frustum, OBBox, AABox, Vector3.
That is normal for an overload group and would look like a mismatch to anyone checking
declaration order naively.

And slots 10 and 11 sit past the end of the reference's list, so they are additions this
build made and the reference cannot name them. Recognising where the reference stops
being evidence is as useful as reading it -- those two were left alone rather than
guessed at from their bodies.

Separately, the pre-commit hook now rejects a staged tools/*.py that will not parse. The
previous pass committed a tool with an unterminated string literal, cleanly, because the
hook byte-verifies Code/ sources and checks ledger integrity and a script is neither. One
ast.parse per staged tool closes it; verified by staging a deliberately broken file and
watching the commit fail with its filename and line number.


## An unclaimed vtable slot is not always unconverted work

ParticleEmitterDefClass looked like a rich seam: nine unclaimed slots in one vtable and a
reference header giving the full declaration order. Two of the gaps are thirteen-byte
inline setters sitting exactly where the header puts Set_Merge_Abort_Factor and
Set_Texture_Tile_Factor, writing consecutive floats at +0x214 and +0x218 -- confirmed by
the already-claimed Set_UV_Offset_Rate next door writing +0x21C and +0x220.

Both names are already in the ledger. Not at these addresses: Set_Merge_Abort_Factor is
claimed at 0x0021A220 and Set_Texture_Tile_Factor at 0x00253D20, and the bodies there are
byte-identical to the ones the vtable actually dispatches to. The same split shows up for
Set_Burst_Size, Set_Elasticity, Set_Emission_Rate and Set_Gravity.

So the seam is not new work at all. These functions are named; they are just named
against copies nothing calls, and the live copies then present as gaps. vtable_gaps now
detects that -- a slot whose bytes match an already-claimed row, ending at the same int3,
is labelled a duplicate and held back -- which takes its candidate list from 109 to 99.

Two things follow that are worth keeping separate.

The ranking overstated available work, and would have kept doing so. Ten of its
candidates were functions the project had already converted. Every filter added to this
tool so far has been of that kind: interior hits meant the run was not a vtable at all,
template neighbours meant the instantiation was unknowable, SEH meant the body was
unwritable. The tool is only as good as the things it knows to exclude, and each
exclusion was found by following a bad suggestion to the end.

And the Read_* group at slots 47 to 55 is genuinely unconverted -- but at 87 to 261 bytes
each they are chunk-loading routines, not the accessors this method has been landing.
Worth naming as a boundary: identifying a function by vtable position is cheap, and
writing it byte-exactly afterwards is not, so the two should be judged separately when
picking work.


## Rank by what a gap costs to write, not just by how identifiable it is

The vtable ranking sorted by how many named neighbours bounded a gap, which measures how
easy the function is to *identify* and says nothing about how hard it is to *reproduce*.
Those are unrelated: a four-byte accessor and a 260-byte chunk loader are equally
identifiable. Sorting by the distance from the entry to its trailing int3 puts the cheap
ones first, and the difference in what the tool offers is immediate.

The first two suggestions under the new order converted. HLodClass slots 100 and 101 are
seven-byte int getters bounded by Set_LOD_Level and Set_LOD_Bias, and hlod.h declares
exactly two virtuals in that gap -- Get_LOD_Level then Get_LOD_Count. Distinct names
rather than an overload group, so the vtable keeps declaration order, unlike the
Collect_Objects and Scale sets which appear reversed. Both first build.

Getting there meant lowering the duplicate filter from eight bytes to three. `ret 0xc`
and `xor eax,eax; ret` are entire functions in this image, and several are claimed
against copies nothing dispatches to, so the ranking kept offering
RenderObjClass::Scale(float,float,float) and Vector3SolidBoxRandomizer::Class_ID as
though they were unconverted work. Nineteen candidates are now held back on that basis,
up from ten.

At three bytes the anchoring question stops being answerable, and that is worth stating
plainly rather than papering over. Dozens of unrelated virtuals compile to `xor eax,eax;
ret`, ICF folds them onto one address, and which copy "belongs" to a given name is not a
question the image answers. Those rows are recorded as suspect and left alone. The
useful line is between a distinctive body claimed at a dead duplicate, which is a real
anchoring error worth fixing, and a generic stub, which is not an error at all.


## A returned constant can name the class, but only with a second witness

HLodClass::Class_ID is six bytes returning 0x19. Counting rendobj.h's ClassID enum from
CLASSID_MESH = 0 puts CLASSID_HLOD at 25, which is 0x19 -- so the constant identifies the
class outright, without reference to which slot the body sits in. That is a stronger kind
of evidence than position, because it survives the ICF folding that makes vtable slot
names unreliable.

It is also easy to over-apply, and the scan showed exactly how. Forty unclaimed bodies of
the form `mov eax,N; ret` sit in vtables with an N that lands inside that enum. Five of
them return 1. If all five were HModelClass::Class_ID they would have folded to one
address, so at most one is -- the rest are simply functions returning a small integer,
and the enum match is coincidence.

So the rule is two witnesses. CameraClass::Class_ID qualifies: the slots below it are
??_GCameraClass and Clone@CameraClass, rendobj.h declares destructor, Clone, Class_ID in
that order, and the value 8 is CLASSID_CAMERA. Both converted first build. The AABOX and
OBBOX candidates have only anonymous Gen_dtor neighbours, so the value stands alone and
they were left.

Worth noting what makes this pairing work: the two witnesses fail independently.
Position is corrupted by folding and by BFME's additions to the declaration lists; a
returned constant is corrupted by coincidence. Neither weakness touches the other, which
is why agreement between them is worth much more than either being individually
convincing.


## The two-witness rule, applied mechanically, converts three of forty

The previous pass established that a Class_ID override can be identified two ways --
by the constant it returns, mapped through rendobj.h's enum, and by its vtable position
-- and that neither is safe alone. Applying both mechanically across the whole image
turns out to be a short script and a sharp filter.

Forty unclaimed bodies of the form `mov eax,N; ret` sit in vtables with an N inside the
ClassID enum. Requiring that some class named in the three slots above also matches that
enum entry leaves three. All three converted first build, and all three have the same
shape: the class's own destructor two slots up, its Clone override one slot up, then the
candidate -- which is exactly rendobj.h's declaration order of destructor, Clone,
Class_ID.

The thirty-seven rejects are the useful part of the number. Five of them return 1, and
had they all been one class's Class_ID they would have folded to a single address, so at
most one is. The rest are ordinary functions returning a small integer, sitting in
vtables whose named slots say nothing about them. Each looked exactly as convincing as
the three that survived, right up until the second witness was demanded.

Worth stating as a rule of thumb for this project: when a body is small enough that its
bytes could belong to many functions, identification has to come from outside the body.
Two outside sources that fail for unrelated reasons are worth more than any amount of
staring at the disassembly, and the ratio here -- three of forty -- is a fair measure of
how often a single source would have been wrong.


## The constant-return trick needs a distinctive constant and a live body

Class_ID overrides fell to the two-witness rule, so the same treatment was tried on
Chunk_Type, which rendobj.h and hlod.h declare the same way -- inline, returning a
W3D_CHUNK constant. It produced nothing, and both reasons are worth keeping.

Most chunk ids are small. Scanning for bodies returning any W3D_CHUNK value found five
candidates, and one of them -- 0x009213D0, returning 2 -- had already appeared in the
Class_ID scan as CLASSID_DISTLOD. A constant of 2 belongs to every enum ever written. It
is only evidence when the value is large enough to be unusual, which for these means
0x100 and up.

Restricting to those leaves four bodies, returning W3D_CHUNK_LIGHTSCAPE, HIERARCHY,
LODMODEL and ANIMATION. All four have zero references anywhere in the image: no vtable
slot, no call site, no data pointer. They are copies the linker kept and nothing reaches.
So the second witness is not merely missing, it cannot exist, and naming them would
repeat the anchoring mistake this log has been documenting for several passes.

The zero-reference result was checked before being believed -- the same scanner reports
one reference for a Class_ID body known to sit in a vtable. A detector that has only
ever returned zero has not been shown to work.

The pass still converted CompositeRenderObjClass::Get_Name, which had three agreeing
witnesses: it sits between Class_ID and Set_Name exactly as rendobj.h orders them, it
reads the +0xC8 member that Set_Name writes, and the neighbouring slots hold
Get_Base_Model_Name and Set_Base_Model_Name of the same class. HLodClass derives from
CompositeRenderObjClass and does not override Get_Name, so the inherited implementation
is what the slot carries.


## A call through this-vtable pins the callee's slot, and overloads move it

RenderObjClass::Remove_Sub_Objects_From_Bone(const char *) is thirty-one bytes that
convert the argument through the virtual at vtable offset 0xC4 and pass the result to
the virtual at 0x9C. Those two offsets are the identification: a name-to-index
delegation, with the int overload it delegates to sitting in the adjacent slot.

They are also the whole difficulty. Reproducing the body means the placeholder class must
put Get_Bone_Index at slot 49 and the int overload at slot 39, because the emitted
instruction encodes the byte offset. Two MSVC behaviours interfere, and both took a
failed build to pin down.

An overload set occupies consecutive slots, placed where the *second* declaration
appears. Declaring the const char* version at the end of the class did not append it --
MSVC pulled it up beside the int version and pushed every later slot down by one, so both
call offsets came out four bytes high.

And within the group the order is reversed: the last declared overload takes the lower
slot. Declaring int then name put name at 39 and int at 40, so 0x9C was still wrong by
one slot after the first fix. Declaring name then int lands the int version at 0x9C, and
that reversal matches the image, where the name overload occupies the slot before the int
one.

The general point is that a virtual call at a fixed offset is strong evidence -- it names
the callee's slot exactly -- but cashing it in requires reproducing the class's vtable
layout, and the overload rules make that layout non-obvious. Both corrections showed up
as an offset wrong by exactly four, which is a useful signature: it means the slot
counting is off by one, not that the identification is wrong.

Separately, vtable_gaps offered 0x00007FD1 as a thirty-one byte candidate. It is an ILT
jump thunk, and the extent measure simply walked through the adjacent thunks to the next
int3. Thunk regions have no int3 padding between entries, so any size it reports there is
meaningless.


## A named local for an intermediate result can change register allocation

Add_Sub_Object_To_Bone's name overload is the three-argument sibling of the
Remove_Sub_Objects_From_Bone conversion: resolve the bone name through the virtual at
0xC4, forward object, index and offset to the int overload at 0x94. Both call offsets
matched immediately, so the identification was settled; what did not match was register
allocation. Retail re-reads the vtable pointer for each call, into eax and then edx.
Written as one nested expression, MSVC instead hoists it into edi and pays a push and pop
for the saved register.

Splitting it into two statements -- assign Get_Bone_Index's result to a named local,
then pass the local -- reproduces retail exactly.

What makes that worth recording is that the one-argument sibling matched with the nested
form. So this is not a style rule about how the original was written; it is register
pressure. With three arguments to marshal, keeping the vtable pointer live across both
calls costs a callee-saved register, and the source shape decides whether the compiler
takes that cost. Where a body differs only in which registers hold what, introducing or
removing a named temporary is a cheap thing to try before writing the row off.

Two smaller things from the same pass.

A parameter whose type is the enclosing class mangles as PAV1@, a backreference, not
PAVClassName@@. Spelling it out fails as "symbol not found in object" rather than as a
byte mismatch, which is a helpfully different error -- byte mismatches mean the code is
wrong, symbol-not-found means the name is.

And vtable_gaps was reporting ILT jump thunks with invented sizes, because thunk regions
have no int3 between entries and the extent walk ran through the neighbours. Resolving
the thunk to its target seemed like the fix but was worse: many claimed rows are the
thunks themselves, so rewriting slot addresses broke ownership and the candidate list
jumped from 84 to 427. Sorting thunks last instead leaves ownership alone and keeps them
out of the cheap end of the ranking.


## Half the remaining vtable gaps were not function entries

vtable_gaps already discarded runs containing an address interior to a claimed row, on
the grounds that a real vtable slot points at a function's entry. That test only sees
claimed rows, and most of the image is unclaimed, so it missed the commoner case: a run
whose first dword merely looks like a code pointer, landing partway into some unclaimed
body.

0x00184F42 was the example that surfaced it -- offered as slot 0 of a thirteen-slot
table, and actually the tail of another function, starting `mov ecx,edi` and popping ebp,
edi and ebx without ever pushing them. The five slots after it are genuine
VectorClass methods, so the table is real; it simply starts one dword later than the run
detector thought.

The fix is one line and does not need the ledger at all: a function entry in this image
is preceded by int3 padding. Requiring that took the candidate list from 83 to 38. More
than half of what remained was noise, and it had been at the top of the ranking for
several passes because the false entries tend to be small.

That is the fourth exclusion this tool has needed -- interior hits, template neighbours,
SEH bodies, duplicates of claimed rows, and now non-entries -- and every one was found by
following a bad suggestion far enough to see why it was bad. The ranking is only as
honest as the list of things it knows to leave out, and there is no way to enumerate
those in advance.

The pass converted nothing. Three candidates were examined and declined: two scalar
deleting destructors whose class is named only by a synthetic Gen_ symbol, so there is
nothing to call them; and a RenderObjClass slot whose body tests a virtual and two
members in a shape that matches none of the inline one-liners the header declares in that
range. Declining is the right outcome for all three -- what would have been wrong is
picking the closest-looking header declaration and calling it identified.


## One address fills 2519 vtable slots, and it is unclaimed

Chasing a filesystem vtable turned up seven consecutive slots all pointing at 0x0088C500.
Counting across the whole image, 2519 aligned .rdata slots hold that address. That is the
signature of the pure-virtual stub: MSVC puts one in every slot of an abstract class that
has no implementation, so a single body ends up referenced once per pure virtual in the
program.

It is unclaimed, and its body is not the three-instruction CRT stub -- it pushes an error
code, calls a reporter, then makes several virtual calls through a global at 0x01336E5C.
This build supplied its own handler.

Meanwhile __purecall is claimed, at 0x006CF680, three bytes, and its own ledger note
records icf-owner=?Get_Sort_Level@RenderObjClass@@UBEHXZ -- it is the shared
`xor eax,eax; ret` body. That cannot be a pure-virtual handler; returning zero is exactly
what such a stub must not do.

Not repointed. One name means one address, the existing row belongs to someone else, and
a 3-byte ICF-folded body is precisely the case established earlier as unadjudicable. But
the reference count is unusually strong evidence, so it is recorded as a correction
candidate rather than left to be rediscovered.

The same investigation exposed a limitation worth stating about vtable_gaps. A run of
consecutive code pointers spans several class vtables: run 0x01143AF8 begins with
??_GFile@@ and only reaches ArchiveFileSystem thirty slots later. So "slot k of n" is a
position in the run, not in any class's vtable, and neighbours several slots away may
belong to a different class entirely. Every conversion this method has produced relied on
immediate neighbours -- one or two slots either side -- which is the range where the run
and the real vtable still coincide. Distant neighbours in the tool's output are not
evidence.


## cmp al,1 is `== true`, and a bare if is test al,al

SimpleSceneClass::Add_Render_Object promoted from its byte dump to clean C++ in two
builds, and the second build turned on a single instruction pair. Everything matched
except the test after the first list insertion: retail has `cmp al,1; jne`, the rebuild
had `test al,al; je`.

Those are different source spellings. A bare `if (x)` on a bool compiles to test al,al;
writing `if (x == true)` compiles to cmp al,1. The original author wrote the comparison
out, and reproducing the byte requires writing it out too -- which looks redundant in C++
and is not.

Worth adding to the small list of source spellings that are visible in the output, beside
the named-temporary lever from the Add_Sub_Object_To_Bone pass. Both are cases where the
obvious way to write the code is not the way it was written, and both cost exactly one
build to find once the diff is down to a couple of bytes.

The rest of the function fell straight out of the layout the body dictates: the object
notified through the virtual at +0x64, three scene lists at this+0x5C, +0xBC and +0xD4,
a reference taken only when the first insertion reports the node was new, and the list
at +0xD4 fed only when the object's predicate at +0x19C agrees. Remove_Render_Object
does the mirror of all four, which is what made both safe to identify in the first place.

Separately, vtable_gaps now only reports neighbours within two slots. A run of code
pointers spans several class vtables, so a named slot thirty positions away belongs to a
different class and says nothing. That took the candidate list from 73 to 45 and removes
a class of suggestion that looked well-evidenced and was not.


## Census: what is actually left in the naked backlog

Both seams this session has worked -- vtable gaps and naked rows -- came up naming-limited
in the same pass, so it was worth measuring rather than guessing. Screening the first 400
naked rows by blocker signature:

    ~286  carry an SEH prologue (alone or with others)
      41  x87 only
      24  function-local static guard
      12  clear, every call pinned
       4  clear, but with unpinned call targets
    the rest  esp-stash, vptr-sink, ebp-frame, identity, in combination

Two things follow.

SEH is not one blocker among several, it is roughly seventy per cent of the remaining
work in this sample. Everything else put together is a minority. Any further large gain
in this backlog goes through unwind funclets, not through the codegen levers this session
has been accumulating.

And the clear-and-pinned pool is twelve rows, all of which have already been examined and
are blocked on codegen rather than on anything new: removeAllShadows, FastAllocatorGeneral,
StealthUpgradeModuleData and the two friend_newModuleData factories. There is no
unexplored cheap remainder; the cheap rows are done.

The census covers 400 of roughly 948 naked rows, so the proportions are a sample rather
than a total. That is worth stating rather than rounding away.

Concretely for the next attempt: Remove_Render_Object is fully understood -- its twin was
converted last pass and the class layout came with it -- and blocked on exactly one
unnamed callee, 0x00943430, a non-virtual helper on the object at SimpleSceneClass+0x34
that also serves Visibility_Check@RTS3DScene. Naming that one function converts a
134-byte row. It cannot be read off the reference, because this build's SimpleSceneClass
does not match it: lists sit at +0x5C, +0xBC, +0xD4 and +0xEC with an unidentified member
at +0x34, where the reference declares four adjacent lists and nothing else.


## The thunk question answered itself

The previous entry stopped short of pinning a real name at an ILT thunk because it was
unclear whether a second mapping would conflict with the functions.csv row at the body.
Reading tools/build.py rather than reasoning about it settled the matter in one look:
build_call_thunks discovers the thunks on its own, a matched function maps to the pair
[thunk, body], and the comparison picks whichever the target actually encoded. The pin
mechanism is additive besides -- each pinned address is one more candidate, so a matched
name and a hand-pinned thunk coexist without ambiguity.

So Unregister was never blocked. Written as ordinary C++ against a RefMultiListClass whose
Remove is out-of-line, it matched on the first build with no ledger change at all. The cost
of the wrong conclusion was a whole tick spent recording a blocker that did not exist. The
tool was already documented; guessing at its behaviour was the mistake, and it is cheaper
to read a hundred lines of build.py than to write a paragraph of speculation about it.

## Two ways to reach a protected member, and only one keeps the name

Register's five arms call Internal_Add and Internal_Add_Tail on lists that SimpleSceneClass
merely owns -- it does not derive from GenericMultiListClass, so protected access does not
apply. The obvious fix is to make the primitives public. That builds, and then the linker
cannot find them: MSVC encodes the access specifier in the mangled name, Q for public and
I for protected, so ?Internal_Add@GenericMultiListClass@@QAE... is a different symbol from
the ?Internal_Add@GenericMultiListClass@@IAE... the ledger already carries. The build
reported them as unresolved calls needing new symbols.csv rows -- two pins for names that
do not exist in retail.

friend class SimpleSceneClass grants exactly the same access and changes nothing about the
declaration, so the name stays IAE and resolves against the existing row. Access widening
is a rename; friendship is not. Worth remembering because the failure is quiet -- it looks
like a missing pin rather than like the modelling error it is.

## Retail's shape says the wrapper was not there

The first attempt at Register modelled the lists as RefMultiListClass and MultiListClass
with Add defined in-class, mirroring the Unregister file that had just matched. MSVC 7.1
declined to inline them and emitted a call per arm; retail has the whole thing flat, with
Internal_Add called directly from each case and the reference count incremented in line.

Given the same compiler and the same flags, an inline the compiler refuses is an inline
retail did not have either. That is a usable signal in both directions: where the target is
flat and the model is not, the model has invented a layer. Rewriting the arms as direct
primitive calls reproduced all 232 bytes including the jump table, differing only in the
four relocations, which is what an unresolved call looks like.


## A vtable run tells you where it breaks, if you ask the bodies

vtable_gaps offered 0x008DCCB0 as slot 10 of a twelve-slot run whose other names
are all GridCullSystemClass, which made it look like an unnamed GridCullSystemClass
method sitting two slots past Get_Object_Count. It is nothing of the kind. The body
stores 0x01137808 into its object, and 0x01137808 is the address of slot 10 -- the
slot the body itself occupies. A constructor or destructor installs the vptr of the
table its class owns, so a body whose vptr equals its own slot address is slot 0 of
a new table, not slot N of the old one.

That single test partitions the run: ten slots of GridCullSystemClass, then a
one-slot table at 0x01137808, then a one-slot table at 0x0113780C. It needs no
names and no reference header, only the bytes, and it is the missing half of the
??_G observation -- a scalar deleting destructor is almost always slot 0, so a ??_G
neighbour is a boundary marker rather than evidence about the slot beside it. Both
of the leads this run produced were on the far side of a boundary from the names
that recommended them.

Naming the two tables afterwards was ordinary work: 0x0113780C is installed by
??0GridLinkClass, so it is GridLinkClass, and the destructor in it delegates to the
one that installs 0x01137808, so that class is GridLinkClass's base. cullsys.h has
exactly one candidate, CullLinkClass, and the single-slot tables agree with it --
the destructor is the only virtual either class declares.


## Fixing the search cost me the thing it was finding

Partitioning vtable runs made every recommendation correct and, in the same
stroke, deleted the cheapest family of work from the listing. A scalar deleting
destructor is slot 0 of its table; once runs were split at their real boundaries,
every one of them became a first slot, and a first slot has no neighbour above it
to be identified by. The tool that had just been made right stopped offering the
bodies that had just been proved easy.

They never needed a neighbour. A constructor installs the vptr of its own class,
so the code that stores a table's address names the class, and slot 0 of that
table is that class's destructor. That is a different question put to the same
bytes, and tools/vtable_owner.py asks it: four tables, two of which converted on
the first build.

Worth noticing that the fix and the loss came from one change. A filter that
removes false leads removes true ones whenever the property it filters on is
shared, and "is the first slot of a table" was shared by every bad suggestion and
every cheap conversion at once. The answer was not to loosen the filter -- it was
right -- but to find the second route to the same targets.

## The name may be spent already

The first two candidates vtable_owner produced were ??_GWin32LocalFileSystem and
??_GDefaultStaticSortListClass, both 31 bytes, both the shape that had just gone
through first try. Both were traps. The names are already in functions.csv at
other addresses, and each existing row is anchored to a different table from the
one the candidate installs -- 0x01143B98 against 0x01143B78, twenty bytes apart.

One anchor in each pair is wrong, and which one is a real question, but it is a
ledger question. Writing the candidate would have claimed a name the image
already spends elsewhere and left two rows fighting over it. The tool checked
whether the address was claimed and not whether the name was, which are different
checks: ICF folding and duplicate emission mean a name and an address are many to
many here. It now checks both, and the listing went from four to two.


## The store at the top of a destructor does not always name it

Both anchor conflicts from last tick came from one wrong inference, and the
inference is nearly right. A destructor sets the vptr to its own class's table
before running its body, so a store in the first few bytes of ??1X is X's table.
That held for every case until it did not.

When X's destructor is trivial and calls nothing virtual, the store is dead --
nothing can observe the vptr between setting it and the object ceasing to exist --
and MSVC drops it. What remains in the body is the inlined base destructor's
store, which is now first by default and reads exactly like X's own.
??1Win32LocalFileSystem is that case: its only vptr store is 0x01143B78 at +2,
and 0x01143B78 is LocalFileSystem's. ??1DefaultStaticSortListClass is the milder
version, where the base store sits at +0x43 with nothing above it.

So the accusation I recorded last tick was wrong in both directions. The existing
ledger anchors are correct -- Win32LocalFileSystem's table is 0x01143B98,
installed at 0x009CDE14, and its deleting stub is slot 0 of that -- and the
candidates were never those classes' destructors. They are their BASES', which is
a better outcome than the conflict I thought I had: two new functions rather than
two disputed rows.

The confirming witness costs nothing once you look for it. Slots 1 through 7 of
0x01143B78 are all the same address, the shared __purecall handler. Seven pure
virtuals and a virtual destructor is an abstract base, and LocalFileSystem
declares exactly that.

## A name can be spent even when the function is unclaimed

StaticSortListClass went in on the first build. LocalFileSystem did not, and not
for any reason to do with its bytes: ??_GLocalFileSystem is already in the ledger
at 0x005BF290, recorded as a C++ alias for a CategoryModuleTemplate body that
folded with it. The ledger enforces one name to one address, so the name is gone
even though 0x009CDDF0 is unclaimed and, by position and by the pure-virtual
slots, is the function that deserves it.

Freeing it means repointing a row that fx_particle_system.cpp currently verifies,
which is a different job from writing a destructor. Left alone and logged. The
useful part is that "is this function claimed" and "is this name available" are
two questions, and under ICF the second is the one that stops you.


## A backlog nine thousand deep that carries no addresses

Chasing destructor/stub pairs turned up something larger than the pairs. There
are 9842 `present-unmatched` markers across Code -- functions already written in
C++ that do not yet compile to the retail bytes. Every row in functions.csv has
status `matched`, so none of these has a ledger row, and build.py only verifies
claimed rows, which means a file can carry forty of them and still report OK.

The thing that makes them hard is not the C++. It is that the marker names a
function and nothing tells you where it lives. A naked-asm row at least has an
address and a size to compare against; a present-unmatched marker has neither, so
there is nothing to iterate against even though the draft is right there.

Which is what makes the destructor pairing worth keeping despite a forward yield
of zero. A claimed ??_GX calls ??1X, so the stub hands over the destructor's
address, and that turns two of these markers from untestable drafts into ordinary
work. ??1DebugIOFlat is at 0x00889620 and ??1DX8FVFCategoryContainer at
0x00946B20, both already drafted in their files. add_match reverted both, so the
drafts are wrong -- but now they are wrong at a known address, which is the
difference between a bug and a blank.

## Alias rows lie about what their source emits

The one candidate the forward pass produced was ??_GAIUpdateModuleData, paired
with a ??1AIUpdateModuleData row in string_base.cpp. String_base.cpp has no such
class. The row is an alias -- its note records the object symbol as
?releaseBuffer@?$StringBase@D@@AAEXXZ -- so the name in the ledger is not the
symbol the source produces.

That is the second tool this has caught out, after vtable_owner. Under ICF a name
and a body are many to many, and these rows are exactly where the two come apart,
so anything reasoning from ledger names has to drop them first. add_match caught
it regardless: it appended, rebuilt, failed to find the symbol, and reverted
without touching anything.


## A silent no-op shipped a tool that did not match its message

The reverse pass described in the previous commit was not in it. The patch that
added it did a string replacement whose search text contained a backslash-n
inside an ordinary Python string, so it became a real newline and never matched
the literal two characters in the file. str.replace does not complain when it
replaces nothing, so the tool was written, run, committed and pushed still doing
only the forward pass -- and the forward pass returns zero, which looks exactly
like a tool that ran fine.

The output was there to be read: the mirror section prints unconditionally, so
its absence from the run was the whole answer. It went unnoticed because the run
was piped through tail alongside a commit in one command, and a zero-result tool
and a tool missing half its body print the same thing.

Two habits would each have caught it. Use the editor for edits to files already
in context rather than a replace script, since it fails loudly on a missed match.
And do not put a verification run in the same command as the commit that depends
on it -- when the check and the irreversible step share a command, the check
cannot gate anything.


## Two offsets that cannot both be right, and what that told me

The DX8FVFCategoryContainer destructor reads a refcounted pointer at +0xD8 and a
loop bound at +0xE4, where the ported header puts index_buffer at +0xD0 and passes
at +0xDC. Eight bytes short, uniformly, so I inserted two words ahead of
index_buffer. The destructor then matched -- and the constructor broke, because it
writes index_buffer at +0xD0 and my insertion moved it to +0xD8.

Both functions store the same vtable, 0x0113D024, so they are the same class, and
one class does not have two layouts. The contradiction is the useful part. If the
constructor is right that index_buffer sits at +0xD0, the eight bytes cannot go in
front of it; putting them after used_indices instead leaves index_buffer where the
constructor wants it and still moves FVF to +0xE0 and passes to +0xE4, which is
what the destructor reads.

That relocates the conclusion. The pointer released at +0xD8 is then not
index_buffer at all -- it is one of the two members this build added -- and the
ported draft, which releases index_buffer because that is what the Generals
destructor does, is releasing the wrong field. The draft looked structurally
perfect against the disassembly and the resemblance was luck: a refcount release
followed by a loop over passes looks the same whichever pointer it releases.

Reverted at three builds with 109/109 still matching. The next attempt has a
specific shape to test rather than a delta to nudge.

## A ported draft can be the wrong function entirely

??1DebugIOFlat was the other address recovered from a stub, and it is not a
matching problem. Retail stores a vptr and makes one call on a member at +0x9E6F
under an SEH frame. The draft walks two linked lists freeing entries, which is
what the Generals destructor does and bears no relation to the bytes.

Worth separating from the DX8 case. There the draft was the right function with
the wrong field; here the draft is the wrong implementation, and no amount of
adjustment converges. The tell is structural: when the target's instruction count
and the draft's statement count are not even the same order, stop reading the
diff and start reading the target.


## The function that would not move told me where the bytes go

The contradiction from last tick resolved on the first build once I asked which
function was the more constrained. Inserting eight bytes ahead of index_buffer
matched the destructor and broke the constructor; the constructor is the one that
cannot be argued with, because it writes +0xC8, +0xCC and +0xD0 and then stops. It
pins index_buffer at +0xD0 and says nothing whatever about what follows.

So the eight bytes had to go above index_buffer rather than below it, and putting
them between used_indices and FVF moves passes to +0xE4 where the destructor reads
it while leaving every offset the constructor touches alone. 110/110 in the
translation unit, and 428/428 across all twelve that include the header.

The part worth keeping is the second conclusion, which fell out of the first. If
the released pointer is at +0xD8 and index_buffer is at +0xD0, then this build's
destructor does not release index_buffer at all -- it releases one of the added
members. The ported draft releases index_buffer because that is what the Generals
destructor does, and it was never going to converge by nudging offsets. A
refcount release followed by a loop over passes looks identical whichever pointer
it releases, which is exactly why the draft looked so close.

Ask which field an access reaches before deciding a layout is off by N. The offset
delta was real and uniform and still pointed at the wrong edit.


## The delta gate cannot see what the full gate checks

Committing a header change ran the full gate for the first time in many ticks, and
it failed -- not on the header change, which matched 94152/94152, but on three
DIR32 consistency violations that had been sitting in master unnoticed. One was
mine: ??_7CullLinkClass@@6B@ resolves to 0x01137808 in the deleting destructor I
landed several ticks ago and to 0x00000000 in gridcull.cpp.

The per-source gate that runs on an ordinary commit verifies the staged sources
byte for byte, which is exactly what it promises, and cross-object properties are
not that. So a source-only commit can introduce a whole-image inconsistency and
report OK, and the next person to touch a header inherits the failure. Worth
knowing which commits are cheap and which are the ones that actually check.

All three turned out to be genuine and irreconcilable rather than bugs.
??0CullLinkClass at 0x00087A50 is an ICF alias -- its own ledger note says so --
and the folded body is a generic two-word stub that stores a literal zero where a
constructor would store the vtable, so it resolves the symbol to 0 and always
will. __imp__fopen and __imp__strstr have two IAT slots each in the image itself,
and different objects bind to different ones. Whitelisted with the reasoning
written down, which is what that file is for.


## Do not soften a guard to make a tool run

locate.py died with a traceback because reverse/ghidra_functions.csv is absent,
and its own docstring calls the inventory optional. The obvious fix -- load it if
present, carry on if not -- would have been wrong. That dict gates acceptance in
two places, and this tool lands claims: without it, plausible_small_start loses
the check that rejects a start sitting inside a recovered function, which is the
common tail-match false positive, and ghidra_boundary loses its evidence
entirely. Running would not have degraded the search, it would have removed the
reason to trust the result.

So it now exits with the message land_ambiguous.py already gives for the same
missing file. A tool that cannot be trusted should refuse, not proceed quietly.

The machine has no JDK and no Ghidra, so the inventory cannot be regenerated
here. Worth recording what that costs: locate.py, land_ambiguous.py and
next_work's third tier are all unavailable, and vtables.tsv would give BFME's
exact vtable slot order -- which is precisely what vtable_gaps and vtable_owner
reconstruct by hand from byte evidence.

## A work queue is a suggestion, not an address

next_work's first pick was ?AddCommands@Debug@@SA_NPBDPAVDebugCmdInterface@@@Z at
0x00891510, 83 bytes. What is actually there is a 31-byte thiscall deleting
destructor -- push esi, mov esi ecx, call the destructor, test the flag, ret 4 --
followed by int3 padding. A static function taking two pointers is cdecl and
returns with ret; this is neither, and the queue's own hint admitted it had
drift-corrected the address by -31 bytes.

It is not an isolated slip. parseData and getDataTemplate are both queued at
0x004850C0 with different sizes, and two ScriptActions entries share 0x006827A0.
The queue is useful for finding candidates and its hint line says "verify the
prologue" for a reason. Check the calling convention against the mangled name
before spending a build: SA is static, QAE and UAE are thiscall, and the
prologue and return instruction say which one the bytes are.


## Which direction the unwind state counts says where the members live

A naked ModuleData destructor: two string members destroyed at +0x58 then +0x44,
both calls landing on the same folded releaseBuffer body, then a vptr store.
Modelled as two members of one class it came out nearly right and stayed wrong in
one place -- retail sets the unwind state to 0 before the first destruction and 1
before the second, and mine set 1 then 0.

Down is what a destructor does across members of a single class: they die in
reverse declaration order and the state counts down with them. Up means the two
objects are not peers. A derived member destroyed before an inlined base's member
gives +0x58 first and the state ascending, because the two belong to different
unwind scopes rather than to one list. Splitting the strings across a two-level
hierarchy -- one in the base, one in the derived -- matched on the next build.

The direction is worth reading first. It costs nothing, it is visible in two
instructions, and it decides a structural question that is otherwise invisible:
both layouts destroy the higher address first, so the order alone cannot tell
them apart.

## The lift already knew something I threw away

The naked file declared the class __declspec(novtable) and I dropped it when
rewriting, on the grounds that a class with a real base does not need it. It is
load-bearing. novtable suppresses the vptr store MSVC puts at the top of every
constructor and destructor, and without it the compiled body opened with a store
retail does not have -- the only vptr store in the target is Snapshot's, arriving
last from the inlined base destructor.

Whoever lifted the bytes had already worked that out. A naked lift is not just a
byte dump waiting to be replaced; the declarations wrapped around it are evidence,
and dropping them costs a build to rediscover.


## Correction: the naked lift did not know about novtable

Last entry claimed the naked wrapper's __declspec(novtable) was evidence I had
carelessly discarded. It is not. All forty naked ModuleData destructor thunks
declare it, and eighteen of them emit an early vptr store -- exactly what
novtable suppresses. The attribute is boilerplate on a wrapper whose body is
__asm, where the declaration only has to compile, so it says nothing about the
class. It was right for UnitCrateCollideModuleData by coincidence.

The real discriminator is in the bytes and costs one regex. An early
mov [reg], imm32 means the class installs its own vptr and novtable is wrong.
Its absence, with a store of some other class's table at the end, means the only
surviving store is an inlined base destructor's and novtable is right.

Correcting this matters more than the usual slip because the wrong version told
future work to trust the declarations wrapped around a byte dump. Half of them
contradict their own bytes.

## The family, measured

Forty naked ModuleData destructors, and they are not one shape. Fifteen have no
lea-based member destruction at all -- they are inlined STL container teardown,
with vector deallocations and node-allocator calls, and are a different problem.
The remaining twenty-five destroy between one and eight members, and several
shapes repeat exactly: three files destroy two members at +0x18 and +0x14 with
states 4 then 3, two share (2,1,0), two share (1,0,2) at +0x74/+0x70/+0x8, two
share (6,5,0).

Repeated shapes are the point. A shape solved once should transfer to its
siblings, which is why the census is worth more than any single conversion in it.
What blocks the two nearest siblings is not their shape but their callees:
ProductionUpdate and CommandSetUpgrade each destroy a member whose destructor is
unclaimed, reachable only through an ILT thunk, so converting them means naming a
function this project has not named yet.


## A redundant null check names the function it came from

The last two instructions of difference on this destructor were a test the
compiler should not have emitted: after the interlocked decrement, retail tests
the pointer again before the virtual delete, although the same pointer was
already tested a few instructions above and nothing could have changed it. My
version, with both halves written in one destructor, correctly omitted it -- and
no rearrangement of that one function was going to put it back, because the
optimiser is right.

The check survives only if the two tests are in different functions. delete this
inside RefCountedThing::Release_Ref does it: once inlined, the callee's this is a
value MSVC does not connect to the pointer the caller tested, so the delete
expansion's own null check stays. Writing it that way matched on the next build,
and the register allocation fell into place with it -- this moved to edi and the
pointer to esi, exactly as retail has them, because the two now have different
live ranges.

So a check that looks redundant is a boundary. It marks where one function ended
and another began before the inliner ran, which is otherwise invisible in the
bytes.

## dllimport is visible in one byte of the call

The same function needed InterlockedDecrement declared __declspec(dllimport).
Plain, it compiles to a direct e8 to a local thunk; dllimport compiles to
call dword ptr [__imp__...], and retail has the indirect form. That is a
one-line source fact recoverable from the opcode, and worth checking first
whenever a call to an OS API does not line up.


## Three files, one body, one template

GettingBuiltBehaviorModuleData, HordeUpdateModuleData and W3DLaserDrawModuleData
all claim 0x001FE260. ICF folded them because their destructors are byte
identical, which means the three classes have the same member layout as far as
destruction is concerned: three references at +0x08, +0x0C and +0x10 and two
strings at +0x14 and +0x18. Each file still has to emit its own symbol, so the
source differs only in the class name.

They went in on the first build because the previous conversion had already paid
for the hard part -- delete this inside Release_Ref, and dllimport on
InterlockedDecrement. That is the argument for censusing a family before working
it: the second, third and fourth members of a shape cost almost nothing once the
first is understood, and the census is what tells you a shape has siblings.

One thing fell out rather than being written. With a single dllimport call site
the compiler emits call dword ptr [__imp__...]; with three it loads the import
table entry into ebx once and calls through the register. Nothing in the source
says that, and trying to force it would have been a mistake -- it follows from
the number of uses.

## A path that exists for bash need not exist for python

The template went to /tmp/tmpl.txt, written by a bash heredoc and read by
Windows Python, which cannot see that path. The write succeeded, the read threw,
and the build that followed in the same command reported OK 1/1 -- because it had
compiled the unchanged naked file, which of course still matches.

That is the same trap as the silent no-op patch a few ticks ago, wearing a
different coat: a verification step that passes because it verified the old
thing. The assert that now checks the rewritten files contain no __emit is the
cheap guard, and the scratchpad directory is the path both halves of this
environment agree on.


## One define decides whether the allocator is visible at all

The vector teardown in these destructors is STLport's size-dispatched deallocate:
subtract the vector's start from its end_of_storage, round to a multiple of the
element size, and send anything above 128 bytes to operator delete and the rest
to the node allocator's _M_deallocate. My first attempt produced the capacity
arithmetic exactly and then made a single indirect call where retail has the
whole dispatch.

_STLP_USE_STATIC_LIB is the difference. Without it STLport declares its allocator
entry points dllimport, so the dispatch lives behind an exported function and the
call comes out as call dword ptr [...]. With it the inline body is visible to the
compiler and lands byte for byte. Several thunks in the tree already carry the
define, which is where I found it -- worth reading the flags on files that match
before theorising about the ones that do not.

Two other numbers in that sequence are free information. The sar N / shl N pair
gives sizeof(T) directly: 3 for an eight-byte element, 2 for a four-byte one. And
whether the base destructor is called or inlined says how to declare it -- a call
means a non-inline base destructor and no vptr store in the derived function,
while an inline empty base puts its store at the end.

With those, the second of these two took one build and differed from the first
only in two constants.


## Offset zero with no vptr means it is not the class you were told

PlayerUpgradeSpecialPowerModuleData's destructor destroys a vector whose start
pointer is at offset 0 of the object, with no vptr store anywhere and no base
destructor call. A class with a virtual destructor -- and the mangled name says
UAE, so it has one -- puts its vptr at offset 0, which leaves nowhere for that
vector to live. The body is vector<AsciiString>::~vector, and the ModuleData name
is sitting on it because ICF folded the two.

That is worth checking before modelling anything: if the first member lands at
offset 0 in a function whose name claims a virtual destructor, the name and the
bytes belong to different functions. It cost nothing to notice and would have
cost several builds to discover by fitting layouts.

## Whether the vector destructor is called or inlined is the element type

Two of these conversions inline the whole STLport deallocate dispatch; two call
an out-of-line destructor instead. The difference is not the container or the
flags -- it is whether the element has a destructor. A POD element leaves only
the deallocate, small enough to inline; an element with a destructor needs a
loop over the range first, which MSVC emits once as a COMDAT and calls from
every instantiation.

So the call is not an obstacle to reproduce, it is a description of the element.
Seeing it means writing vector<something-with-a-destructor> and letting the
compiler make the same choice, which it did.

The name that call resolves to needed a pin, and the address was already claimed
under a different name -- the folded one above. symbols.csv being additive is
what makes that legal: the vector destructor's real mangled name and the
ModuleData name it folded with can both point at 0x000658A0.


## Six out of seven x87 blockers were not x87

OCLSpecialPowerModuleData was tagged x87 by list_naked_candidates and I skipped it
for that reason in an earlier tick. It contains no floating point whatever. The
byte that triggered the tag is the dc in e8 82 32 dc ff -- part of a call
displacement.

The test was `any byte in D8..DF`, and an x87 escape opcode only means anything
when it starts an instruction. Decoding the naked thunks properly puts the damage
at 753 functions flagged where 150 really use x87: 603 false positives, each one
carrying an eighteen-point ranking penalty that pushed convertible work to the
bottom of the queue. My own screen_blockers had the same test; it at least
labelled the result x87? and documented it as loose, which is why the tally in
the earlier backlog census -- 41 x87 rows out of 400 -- has to be retracted
rather than trusted.

Both now decode with capstone and fall back to the byte test only when the
decoder is missing, saying so in the label when they do. The general point is
duller than the number: a substring test on machine code finds opcodes inside
displacements, immediates and ModRM bytes, and the more common the opcode range
the worse it gets. D8..DF is eight of 256 values, so a hundred-byte function hits
it by chance more often than not.

## Two more shapes, both first build

PartTheHeavensUpdateModuleData is three vectors of sixteen-byte PODs and a
string; OCLSpecialPowerModuleData is a vector of PODs and a vector of strings
over an out-of-line base. Both landed on the first build with no new levers --
element size from the sar/shl pair, inlined-or-called from whether the element
has a destructor, novtable from the absence of an entry vptr store. The catalogue
is doing the work now.


## The corrected filter opened a pool of seventy

With x87 decoded rather than pattern-matched, seventy naked thunks of 140 bytes
or less turn out to have no floating point and every callee already named. That
pool is entirely an artefact of fixing the detector; none of it was visible last
tick.

Two attempts from it, both reverted at the build limit, both landing a few
instructions short in the same way.

UnicodeStringLessThan::operator() is compareNoCase followed by setl, and that
part reproduces byte for byte. What does not is the unwind bookkeeping: retail
writes state 0 at entry and -1 before the last destructor, while two by-value
class parameters give 1, 0, -1. Retail is protecting one of the two parameters,
not both, and I could not find the source form that says so.

StealthUpgradeModuleData's constructor matches from +0x30 onward -- ten words, a
byte, a -1, two more words, all off a single base register. The first two
sub-objects do not. Retail copies this into edx, writes six dwords through it,
then advances with lea edx,[eax+0x18] and writes six more; every form I tried
(two members, an array of two, an out-of-line element constructor) folds those
twelve writes into the flat run through eax and loses the cursor.

Both are the same open question in different clothes: what makes MSVC 7.1 keep a
separate pointer for an inlined sub-object rather than folding its stores into
the enclosing base register. Recording it as such is more useful than either
individual failure, because the answer would unlock a family rather than a
function.


## Half an answer to the cursor question

LifeEventModuleInfo's constructor has the same shape that defeated
StealthUpgradeModuleData: a sub-object whose words are written through a register
rather than off this. Here the reason is plain. ecx holds the sub-object's
address because it is the this for the setRange call two instructions later, and
the inlined constructor's stores simply use the register that is already being
set up. The cursor is a thiscall argument, not a pointer variable.

That does not transfer to StealthUpgradeModuleData, which has the same cursor and
makes no call at all. Five source forms are now eliminated there -- two separate
members, an array of two, an out-of-line element constructor, an explicit member
function call, and a loop over the array -- and all five fold the writes into the
flat run. The question stays open, narrower than it was.

## A constructor's EH frame counts its destructible members

Modelling the random-variable member as a plain struct produced no EH frame at
all where retail has one, because a constructor only needs unwind protection if
something already built has to be torn down when a later step throws. Giving the
member a destructor produced the frame. One unwind state remained missing, and
that was the second destructible member -- the four-byte one at +0x04 that I had
modelled as an int.

So the count is readable: the number of states in a constructor is the number of
destructible sub-objects built before the last thing that can throw. It took two
builds to walk from no frame to the right frame with the right state count, and
both steps were determined rather than guessed.

What stopped it was scheduling. The final version has retail's instruction
multiset, the same call displacement and the same epilogue, but retail interleaves
the argument pushes with the member's zero stores and the compiler emits the
zeros first. I went a build past my own limit chasing it and should not have --
the residual had no source-level lever left in it, and that was visible one build
earlier.


## Who owns offset zero is written in one lea

UpgradeModuleModuleData's constructor calls its base with this passed straight
through in ecx. My first version emitted lea ecx,[esi+4] before that call, and
the reason was a modelling choice I had made without noticing: I gave the derived
class a virtual of its own and left the base non-polymorphic, which puts the
vptr at offset 0 and pushes the base subobject to +4.

Retail has no lea, so the base owns offset 0 -- it is polymorphic itself and the
derived merely overwrites the vptr with its own table. Making the base's
destructor virtual and dropping the derived's invented virtual matched on the
next build.

It is a cheap check worth doing before writing anything: a base constructor call
with a bare ecx means the base is at offset 0, and any lea in front of it is the
compiler stepping over something the derived class put there first.

## Screening by shape beat screening by size

Two ticks went into functions whose sub-objects are zeroed through a register
cursor that no source form I tried reproduces. Rather than keep drawing from the
same pool, the shape itself is now a filter -- a lea into a register followed
within two bytes by a store through that register. It takes the 28 clean naked
candidates to 24, and the one picked from what remained went in on the second
build.

The two it rejected were worth rejecting. SabotageMilitaryFactoryCrateCollide's
factory carries the cursor twice, with different registers and different zero
registers for each sub-object and no call after either -- the same open question
with more of it. DeflectSpecialPower stores six vptrs, at +0, +0xC, +0x10, +0x20,
+0x24 and +0x38, so every base of a multiple-inheritance hierarchy would have to
be laid out correctly before a single byte matched.


## Three failures, one cause: the compiler sinks vptr stores

W3DDebrisDraw's constructor reproduces completely -- the base call and its
displacement, the second base's inlined vptr store, both vtable values, and all
fourteen field stores in retail's deliberately unsorted order. One thing is out
of place: my compile puts this class's own two vptr stores at the END of the
body, and retail has them immediately after the base constructor returns.

That is worth stating as a cause rather than a symptom, because it is the same
thing that stopped LifeEventModuleInfo and it is what the StealthUpgrade cursor
work kept bumping into. MSVC 7.1 sinks a constructor's vptr initialisation past
the body when nothing in the body dispatches virtually; retail's compile did not.
Three functions, one difference.

Two things it is not. /O1 is not the answer -- it changes the prologue to
push [esp+N] forms and turns the -1 store into or dword ptr [esi+0x14], -1, so
/O2 is right. And moving field assignments between the member initialiser list
and the body produces byte-identical output, so that is not a lever either; MSVC
treats the two the same once inlining has run.

Which leaves the question narrowed rather than answered, and narrowed usefully:
what makes the vptr live across the body. Something in retail's source must make
the object's dynamic type observable inside the constructor, and finding it once
would settle a family rather than a function.


## The compiler is not the problem, and the arithmetic says so

Four functions now reproduce completely except for instruction order, and the
tempting conclusion is that the vendored MSVC 7.1 is not quite the build EA used
-- a different point release with a different scheduler would explain all four at
once.

It cannot be. 94158 functions match byte for byte with this compiler. A scheduler
that ordered stores differently from retail's would not fail four functions, it
would fail thousands. Whatever is moving these instructions is in the source, not
the toolchain, and the hypothesis is retired before it costs a tick.

The processor-targeting flags are ruled out too: /G5, /G6 and /G7 all leave
W3DDebrisDraw's store order exactly as the default blended model does. Together
with /O1 and the initialiser-list test from last tick, that is four flag-level
explanations eliminated.

## One transposed pair

ScriptConditions' destructor is the closest miss so far. Every byte matches --
the EH funcinfo, both vptr values, the global's address, the delete expansion's
single null test, the base destructor call and its displacement -- with one pair
of instructions swapped: retail loads ecx with this before clearing the global,
and the compile clears the global first.

Worth recording precisely because it is nearly a proof by exhaustion. The
structure is right: two vptr stores mean an intermediate base whose destructor is
empty and inlined, since a direct base would write its own vptr inside its own
destructor and nothing would appear here. The body is right: one delete and one
assignment, and the single null test is the delete expansion's rather than a
source-level if, which would have produced two. What remains is two instructions
in the wrong order, and no source form I have tried moves them.


## The vector destructor iterator hands over the array

LANGameInfo's destructor went in on the first build, and the reason is that one
of its three members required no inference at all. The call to ??_M takes four
arguments and they are the array: the element destructor's address, the count,
the element size, and the base pointer. Eight elements of 0x68 bytes at +0x58,
read straight off the pushes.

Two other things were free. The mangled name is QAE rather than UAE, so the
destructor is not virtual, the class has no vtable, and the layout starts with
data at offset zero -- no vptr store to place and none of the sinking that has
blocked four other functions. And the unwind state counting down 1, 0, -1 says
three members of one class rather than anything inherited.

Worth contrasting with the last few attempts: nothing here had to be guessed and
adjusted. Where a function's structure is fully determined by its arguments and
its mangling, the conversion is transcription. Where it depends on how the
compiler chose to order stores, it has not gone in yet.

## A hundred and seventy-nine names on one body

??_GLocalFileSystem sits at 0x005BF290, which I had suspected of being a
mis-naming that could be corrected to free the name for the real function at
0x009CDDF0. It is not. That address carries 179 rows, every one an alias of a
single thirty-byte deleting-destructor body that ICF folded across 179 classes,
and the whole set was recorded deliberately.

So declining to claim the name several ticks ago was right, for a better reason
than the one I had then. It also means individual names in that set are weak
evidence about anything -- they were produced in bulk -- and the class owning
vtable 0x01143B78 stays unidentified rather than being assumed.


## Two bytes out of a hundred and six

Anim2DCollection::newTemplate came down to a single transposed pair. Everything
else matches: the EH funcinfo, the size pushed to operator new, the copy
constructor and the template constructor with their displacements, the list
link-in, the epilogue. What differs is that retail writes the temporary's address
into the EH slot and then loads ecx with it, while the compile loads ecx first.

Both fixes that got it there were free readings rather than guesses. The size
pushed to operator new is the class size exactly -- 0x1C said seven words where I
had four -- and `mov [eax+4], ecx` said the list link is the second word, not the
first. Neither needed a build to discover, only a build to confirm.

/EHa is not the lever. It does not nudge the ordering, it changes the exception
model outright: byte-sized state writes instead of dword, an extra jump around
the constructor, different use of the funcinfo. /EHsc is right and is now
recorded as such alongside /O1 and the /G flags.

That is three functions differing by one or two transposed instructions around
compiler-generated bookkeeping. Reverting each is correct -- a near miss is not a
match -- but the pattern is sharp enough now to be worth attacking directly
rather than one function at a time.


## The stand-in was the bug

Three ticks went into instruction orderings I could not reproduce, and the answer
was not a flag, a scheduler or a compiler build. It was that I had been writing
minimal hand-rolled classes -- a four-byte AsciiString with a declared copy
constructor, a base with the right size and one virtual -- which reproduce a
class's layout but not its code generation.

Anim2DCollection::newTemplate differed from retail by exactly one transposed
pair. Replacing the stand-in AsciiString with #include "PreRTS.h" and the real
Common/AsciiString.h matched on the first build, with nothing else changed.

The way to find it was a control experiment rather than another guess. Scanning
.text for the byte sequence I could not produce -- 89 64 24 xx 8b cc -- and
attributing each hit to its ledger row gave 348 matched functions that emit it.
Filtering out naked dumps, which match by construction and so demonstrate
nothing, left 110 clean C++ sources. Every one of them includes the real headers.
Reading a single file answered what four builds of guessing had not.

Two habits fall out. When a difference resists source-level explanation, look for
a function that already produces the thing you want and read how. And prefer the
real header to a stand-in whenever one exists -- a stand-in is a claim that only
layout matters, and for anything with a constructor, a destructor or a temporary,
that claim is wrong.


## Scoping the real-header lever before trusting it

Last tick's finding -- that a hand-rolled stand-in, not a compiler flag, caused an
ordering residual -- was worth generalising, so I tried it on the three functions
it seemed to explain. All three still fail, each for a different reason, and the
lever is narrower than one success suggested.

ScriptConditions was written against the real SubsystemInterface and did not
budge. The stand-in that matters there is the type of the global being deleted,
and 0x012F06AC is unnamed in both ledgers, so there is no real class to reach
for.

LifeEventModuleInfo got worse. The reference GameClientRandomVariable has no
zeroing constructor, where BFME's zeroes three words, so including the real
header removed instructions instead of reordering them. BFME's class is simply
not Generals' class.

Template did not change at all, because the stand-in was never its problem -- the
AsciiString constructor call already matched byte for byte, and the residual is
field stores interleaved around the ??_L call plus a zero constant split across
edi and ecx.

So the rule is: a stand-in explains a residual only when the class it stands in
for both exists in the reference with the same definition AND is the thing whose
codegen differs. That is what newTemplate had -- a by-value AsciiString temporary
whose copy construction and destruction are the whole reason the function has an
EH frame. Where the stand-in is peripheral, replacing it changes nothing, and
where BFME diverged from Generals, it makes things worse.


## Selecting for the lever rather than hoping for it

Last tick scoped the real-header lever to functions whose by-value class
temporaries are the reason they carry an EH frame. This tick selected for that
directly -- naked thunks whose mangled signature mentions AsciiString -- and the
first two both went in on the first build.

That is the whole method. Rather than draw a candidate and hope the levers apply,
filter the pool by the property the lever needs. The filter is a substring of the
mangled name, which costs nothing, and it turned a queue that had produced one
conversion in four ticks into two conversions in one.

Both functions also confirmed each other. setCachedStats reaches virtual slot 7
at +0x1C and getCachedStats reaches slot 6 at +0x18, on the same class. Neither
number was checkable alone; together they are, and converting a pair from one
class gets that verification for free.

One thing worth writing down about argument order: by-value class arguments are
constructed right to left, so the last argument's temporary is built first. Both
of these construct the value or the default before the key, and the unwind states
number in that same order -- which is how the two temporaries can be told apart
in the bytes at all.


## Sometimes the reference has already written it

OptionPreferences::setLANIPAddress and HotKeyManager::searchHotKey are both
declared verbatim in the reference headers, down to the parameter types. Including
the header rather than hand-rolling means the class, its base chain, its layout
and the signature all arrive correct at once, and the only thing left to write is
the body -- one line in each case.

Three conversions this tick, all on the first build, all from the same filter:
naked thunks whose mangled signature mentions a class the reference defines
unchanged. The pool of four such AsciiString functions is now empty.

## Reading a backreference before believing an overload

?searchHotKey@HotKeyManager@@QAE?AVAsciiString@@ABV2@@Z has two candidate
meanings, because the class declares both an AsciiString and a UnicodeString
overload. The ABV2@ settles it: 2 backreferences the return type, AsciiString, so
this is the AsciiString overload. The UnicodeString one is what it calls, not what
it is.

Getting that backwards would have modelled the wrong function and blamed the
mismatch on something else. Backreferences are cheap to resolve and worth
resolving whenever a class has overloads -- the numbering runs over every name
already seen in the mangling, return type included.


## A row whose name its own bytes refute

?getAlternateMouseModeEnabled@OptionPreferences@@QAE_NXZ is claimed at
0x00092670. QAE_NXZ is thiscall, no arguments, returning Bool, so the body should
end in a bare ret. It ends in ret 4, and what it does is build an AsciiString key
from a literal, subscript the preference map, and assign a by-value string into
it. That is a setter with one argument, and the key literal is GameSpyIPAddress,
which the reference header names setOnlineIPAddress.

The check that caught it costs nothing and I had already written it down two
ticks ago: compare the calling convention encoded in the mangled name against the
prologue and the return. XZ means no stack arguments; ret 4 means one. They
cannot both be right.

## Reference headers can be wrong about slots

WinInstanceData::setText reproduces completely once two vtable slots are
corrected: BFME reaches newDisplayString at +0x24 where the reference header puts
it at +0x18, and DisplayString::setText at +4 where the header puts it at +8.
Including those headers does not help, it actively supplies the wrong number.

So the real-header rule needs its own qualification. Including a reference header
is right when it fixes codegen -- a class's constructors, its temporaries, its
copy semantics -- and wrong when the thing you need from it is a vtable layout
BFME has changed. Here the answer was both at once: the real UnicodeString for
the temporary, hand-written interfaces for the two vtables.

And the lever is narrower than last tick suggested. The real UnicodeString did not
fix the transposition that the real AsciiString fixed in newTemplate, so
"include the real class" is not sufficient on its own.


## Retiring a name is three edits, not one

0x00092670 carried the name getAlternateMouseModeEnabled, which its own bytes
refute: QAE_NXZ promises no stack arguments and a Bool return, and the body ends
ret 4 having stored a by-value AsciiString into the preference map. The key is
GameSpyIPAddress, and the reference header ties that to setOnlineIPAddress.

Correcting it took three edits and all three matter. The row comes out of
functions.csv; the name and rva go into reverse/deleted_rows.csv; and only then
can the correct name be claimed. The tombstone is not bookkeeping -- functions.csv
merges with git's union driver, which has no concept of a deletion, so any branch
that forked before the removal silently resurrects the row. check_csv fails if a
tombstoned pair reappears, which is the only thing making the deletion stick.

The file was renamed too. A source called
OptionPreferences_getAlternateMouseModeEnabledMethodThunk.cpp defining
setOnlineIPAddress would be the next person's wrong turn.

## A note that argues with its own row

The retired row's note read "multi-xref Open-BFME4+Grok GameSpyIPAddress". Whoever
wrote it had already seen the key literal and recorded it, and still left the
getter's name on the row. The evidence for the correction was sitting in the
ledger the whole time.

Worth treating notes as claims rather than decoration. This one disagreed with
its own name field, and that disagreement was the finding.


## The easiest rows to check were the ones being skipped

audit_ret_arity compares the stack cleanup a decorated name implies against the
ret the retail body actually performs. It was checking 8636 rows and skipping
85522 as unparsable, and among the skipped were every constructor and every
destructor in the ledger.

The reason is small. A constructor or destructor encodes no return type -- the
convention letter is followed straight by '@' -- and handing that to the
return-type skipper drifts the parse, which the tool then correctly refuses to
accuse on. But these are the easiest rows in the whole ledger to check, not the
hardest: a destructor takes nothing and must pop nothing, and no parameter
parsing is needed to say so. Three lines later the tool checks 10852 rows and
reports 143 contradictions instead of 69.

Worth remembering that a conservative tool's skip list is where its blind spots
live. "Skipped 85522" reads like caution and was hiding a whole family.

## A destructor that returns this

??1SlavedUpdate@@UAE@XZ reads a stack argument, returns this in eax, and pops
eight bytes. Destructors do none of those things; constructors taking two
arguments do all three. The row is a constructor wearing a destructor's name.

It also settles something that had looked odd a few ticks earlier.
??0TensileFormationUpdate and ??0CritterEmitterUpdate both appeared to call
??1SlavedUpdate -- a constructor calling a destructor, which I noted as strange
and moved past. They were calling their base constructor all along, and the
strangeness was the name, not the code.


## The real header can delete calls the target makes

Two ticks ago including a reference header fixed a conversion; here it broke one,
and the rule that covers both is about what the header does rather than whether
it is authentic.

LANGameSlot::isUser calls GameSlot::getName and UnicodeString::compareNoCase out
of line. Both are declared inline in the reference headers, so including them
removes the two calls entirely and replaces them with inlined field reads and a
hand-written string comparison. Replacing both with plain declarations put the
calls back on the third build.

So: include the reference header when what you need from it is codegen the
compiler must see -- constructors, destructors, copy semantics of a temporary.
Declare it yourself when the target CALLS something the reference would inline.
The header is authoritative about Generals, and BFME moved several functions out
of line.

## When no evidence names a class

??1SlavedUpdate is a constructor by every available sign: it reads two stack
arguments, initialises members from them, stores a vptr, returns this in eax and
pops eight bytes. Destructors do none of that. But the obvious correct name,
??0SlavedUpdate with two parameters, is already claimed at another address, and
the vtable this function installs is stored nowhere else in the image, with slot
0 pointing at a synthetic thunk.

So the row is wrong and the right name is not recoverable from the binary. Worth
recording as exactly that rather than guessing: a wrong name with no evidence for
the right one is a different state from an unidentified function, and pretending
otherwise would put a fabricated name in a ledger that 94158 rows depend on.


## Two release idioms, told apart by one instruction

RenderObjClass releases its container with a plain dec of the count at +4 and, if
that reaches zero, a virtual call at slot 0 taking no argument. The ModuleData
family releases with InterlockedDecrement and then delete this. Both are
"Release_Ref", and the bytes tell them apart at a glance: dec versus an indirect
call through the import table, and a bare virtual call versus one preceded by a
push of 1 and a redundant null test.

Which matters because the second form's redundant null test is the inlining
boundary noted several ticks ago -- it is delete this inside the callee. The first
form has no such test because Delete_This is an ordinary virtual on a pointer the
caller already knows is good.

## A shape that failed once is not a shape that fails

ScriptConditions stalled on one transposed pair around its base destructor call,
and it would have been easy to write off the whole SubsystemInterface-derived
family. UpgradeCenter has the same base, the same out-of-line call, the same
entry vptr store, and matched on the first build.

So the residual there is specific to that function -- the global clear next to
the base call -- not to the shape. Worth checking a sibling before concluding a
family is blocked; two conversions this tick came from a list that included the
function I had failed on.


## A tool that reports 143 and prints 40

I grepped audit_ret_arity's output for ?onExit@AIAttackState, found nothing, and
concluded the audit had missed a contradiction I had just verified by hand. It had
not. The tool prints its first forty findings by default while its header reports
the true count, and onExit is there at --limit 200.

The mistake is worth recording because the output invites it: a header saying 143
above a list of 40 reads as a complete list unless you count. Anything scripted
against that output needs the limit raised first, and a negative result from a
truncated list is not a negative result.

## Screening candidates against the audit

Two of this tick's three picks were rows whose calling convention contradicts
their own name -- onExit pops nothing where its StateExitType parameter requires
four, and it is really an allocation of a 0x44-byte state machine built from
this+0x10 and a literal. No source can match a row like that, because the name it
must emit is not the name of the function that is there.

So candidate screens should subtract the audit's flagged set before ranking
anything. That is cheaper than discovering it one disassembly at a time, which is
what I did twice today.


## Screening against the audit, as promised

Last tick ended with two of three picks turning out to be rows whose calling
convention contradicts their own name -- functions no source can match, because
the name they must emit is not the name of the code that is there. The fix was to
subtract audit_ret_arity's flagged set from the candidate pool before ranking.

Done properly this tick, with the audit run at --limit 1000 so the list is
complete, it left 26 candidates out of the naked pool. The first pick converted,
and its sibling followed from the same source with the class name changed.

## The thunk already knows the base

The first build of the factory was byte-identical except one relocation: the base
constructor I had invented, ??0Module, resolves to nothing. Rather than pin a
name I made up, the answer was to look at what is already pinned at the
incremental-link thunk the call goes through. Eight module constructors share
0x00002874, and ClientUpdateModule is among them -- the right base for a client
behavior, and a name the ledger already carries.

Naming the base after one of those made the call resolve and the function match.
Inventing ??0Module and pinning it would also have "worked", and would have put a
fabricated symbol in symbols.csv forever.

The sibling then cost nothing. Its vtable addresses differ, but those are DIR32
relocations copied from the target, so the same source with one identifier
changed reproduces a different function exactly.


## Three in a row, and none of them needed a second build

Weapon's destructor, SlaughterHordeContainModuleData's constructor and
MaterialPassClass's constructor all went in first time, from the pool the audit
screen left behind. Nothing new was needed for any of them -- the levers already
written down did the work:

  - ??_L and ??_M spell an array out from their arguments: base, count, element
    size, constructor, destructor. Eight times twenty-four landing exactly on the
    next field is the confirmation that the reading was right.
  - The sar/shl pair after a vector's capacity subtraction gives sizeof(element),
    and no destroy loop before the free means the element has no destructor.
  - An entry vptr store means not novtable; a different vptr stored at the end
    means an inlined base destructor.
  - A refcount base whose constructor is inlined shows up as nothing more than
    the count at +4 set to one.

Two small things were new. MAE rather than UAE in the mangled name means a
protected member, and declaring the destructor public makes the symbol come out
UAE and vanish from the object -- a missing-symbol failure, not a byte mismatch.
And the tail fields have to be written in the order retail stores them:
MaterialPassClass writes +0x28, +0x2C, +0x34, then the byte at +0x30, and address
order would not reproduce it.

The screening is what made the difference rather than any single insight. Picking
from candidates that survive the convention audit means the remaining work is
modelling, and modelling is now mostly transcription.


## One load, two accessors

StructureBodyModuleData's constructor reads the global's string data pointer once
and does everything from that copy: tests it non-null, tests the length word at
+4, then adds eight to it or substitutes the empty literal. Written as two
separate inline accessor calls -- isNotEmpty() and str() on the same member --
that is exactly what MSVC produces, because it shares the load between them.

Which is why the shape is readable in the first place. A single register holding
the member across four uses looks like a hand-written temporary until you notice
the accessors would have produced it anyway.

The null test inside str() is worth pointing at again. The guard above already
proved the pointer good, and the test survives regardless, because str() is a
separate inline function and MSVC does not carry the fact across the boundary.
That is the same effect as delete this inside Release_Ref, seen from the other
side: a check that looks redundant marks where one function ended before the
inliner ran.

## An empty literal is still a literal

HeroModeSpecialAbilityUpdateModuleData pushes a pointer into .rdata and a length
of zero. The pointer is a real empty string, and writing set("", 0) reproduces
it -- the string-ref gate confirms it as an empty-string reference rather than a
literal, which is a distinction the gate makes and worth knowing before assuming
a zero length means no string at all.


## The transposition is a UnicodeString problem, not a stand-in problem

winSetText is the third function to come down to one transposed pair -- retail
writes the temporary's address into the EH slot then loads ecx with it, and the
compile does the reverse. newTemplate had exactly this and the real AsciiString
header fixed it. Here the real UnicodeString does not, and neither did it for
WinInstanceData::setText.

So the split is by type rather than by whether a stand-in was used: AsciiString
temporaries come out in retail's order with the reference header, UnicodeString
temporaries do not. Something about BFME's UnicodeString differs from the
reference's in a way the copy constructor's call site does not reveal -- the call
itself matches, only its surrounding order does not.

The practical response is to screen for it. A body containing mov [esp+N], esp
has a registered by-value temporary, and that is the family; removing those took
21 screened candidates to 17 and cost nothing.

## Offset zero rules out a class introducing its own vtable

Template's destructor destroys five things and the last of them sits at offset
zero, with no vptr stored anywhere in the function. Any class that introduces a
vtable puts the vptr at offset zero and pushes every member to +4, which is
precisely the error the first build produced -- every offset four too high.

Moving the data into a primary base does not rescue it: the base's implicit
destructor is non-trivial, so MSVC emits it out of line and the derived
destructor collapses to a thunk. And the mangling is MAE, protected virtual, so
the class certainly has a vtable somewhere.

Reverted with the constraint stated rather than a guess recorded: something owns
offset zero that is not a vptr, and the virtualness comes from elsewhere. Two
builds were enough to establish that much and not enough to place it.


## A store the optimizer is right to delete

WeaponChangeSpecialPowerModuleModuleData writes zero to +0x210 twice: once before
the two string members are constructed and once after. Moving the three words
into the initialiser list put the first group in the right place -- list entries
run in declaration order ahead of the body -- and reproduced everything except
that repeat, because MSVC eliminates the first store as dead.

It is right to. Nothing between the two writes is opaque: the string
constructors are inline stores through this, and the compiler can see straight
through them. For retail to keep both, something in the real source must break
that visibility, and it is not the member construction.

Recorded as an open question rather than guessed at. The alternative -- writing
the member twice and hoping -- produces a source that says something false about
the code even if the bytes were to line up.

## Choosing not to start

parseDrawCallback was the other candidate this tick and I read it without
building: two inline character loops, a quote scan and a strlen, a strstr through
the import table, and three globals. Every piece is recoverable and the whole is
a poor ratio of builds to bytes, which is the kind of function that has cost me
whole ticks before.

Worth noting the decision explicitly. Reading a disassembly costs one call;
discovering the same thing three builds in costs the tick.


## The arithmetic check I trusted cannot catch this

I have been reading ??_M's arguments as destructor, count, size, base and
confirming the reading by checking that count times size lands exactly on the
next member. For TeamTemplateInfo I read 4 elements of 0x20 where retail has 32
of 4 -- and the check passed, because 4 times 32 and 32 times 4 end in the same
place.

So the span landing correctly confirms the product and nothing else. When count
and size are both plausible sizes the two are indistinguishable that way, and the
only thing that separates them is the push order itself: destructor first, then
count, then size, then base.

Three builds went into structure before this surfaced, and it would have been the
first build if I had read the order rather than the product.

## A polymorphic member, not a polymorphic base

TeamTemplateInfo stores one vptr and stores it at the very end. Deriving from the
polymorphic type gives two stores -- the derived class gets its own table and
writes it at entry -- so the Snapshot at offset zero is a member, destroyed last
because it is declared first.

That alone was not enough. An implicit destructor on a polymorphic class is
trivial and emits nothing, so the member vanished from the output entirely.
Declaring it empty brings back both the vptr store and the twelfth unwind state,
which is how the state numbering starting at 0xB rather than 0xA gets explained
at the same time.

Two facts worth keeping together: where the single store falls says member versus
base, and whether it appears at all says declared versus implicit.


## One instruction separated two identical functions

SpecialPowerStore and RankInfoStore have the same destructor: delete every
element of a vector of pointers, clear it, let the member and base tear
themselves down. Both went in on the first build, and the only thing that had to
be read differently between them was the branch mnemonic.

jb and jbe mean the loop index is unsigned and compares directly against size().
jl and jle mean it is signed, which in source means the size was cast to int --
`i < (int)v.size()` rather than `i < v.size()`. The first test differs to match:
the unsigned form shifts the byte span right by two and tests the result, while
the signed form tests against 0xFFFFFFFC, masking the low two bits off before
checking the sign.

That is a satisfying kind of difference to find, because it is not a judgement
call. The mnemonic is either signed or it is not.

## What is left of a cleared vector

Both functions contain a compare of a register with itself followed by a branch
that can never be taken. That is vector::clear() after inlining --
erase(begin(), end()) reduces to a range copy whose two ends are the same
pointer, so the guard comparing them is trivially true and the copy path is dead
code the compiler kept anyway.

Worth recognising on sight rather than puzzling over: cmp eax,eax is not a
mistake in the disassembly, it is a container operation that optimised away to
almost nothing.


## Two categories of residual, and only one is worth another build

loadTable came down to a single instruction's register allocation: retail loads
the index into eax and this into ecx, the compile uses ecx and edx, and the store
is otherwise identical. Three builds got everything else -- the 0xC entry stride
with key before name, the table pointer at +8 behind a vptr, a named local rather
than an unnamed temporary so the string is read from its frame slot, and the loop
as a for so the next name loads before the pointer advances.

Stopping there was the call, and the reason is worth stating. TeamTemplateInfo
took four builds and the fourth was right, because its residual was a structural
misreading -- count and size swapped -- and structure is something source
controls. Register allocation is not. Across this session I have never moved a
register assignment from source, and every attempt has cost the rest of the tick.

So: a residual that names a structure is worth another build. A residual that
names a register is worth writing down.

## Screening on the byte before

??1Mission is claimed at 0x00BF4EB5, which is not a function start at all. The
byte before it is ff, where every real entry in this image is preceded by int3
padding, and the surrounding bytes repeat a fourteen-byte pattern -- load a
member, add a constant, jump -- so the row covers about fourteen small forwarding
stubs rather than one destructor.

The check is one byte and it would have dropped the row before it cost a
disassembly. It is now part of the screen, alongside the convention audit. Worth
noting that the naked dump still matches byte for byte, so nothing in the normal
gate could ever have flagged this.


## A name pinned to six addresses is a candidate set, not an identification

symbols.csv pins ??1DebugIOFlat to six addresses, all tagged "pinharvest x1
(body)". It pins ??1DebugIOOds to the same six. The harvest never separated the
DebugIO destructors from each other, so any row built by taking one of them is a
coin flip, and ??1DebugIOOds at 0x00890780 was exactly that -- backed by nothing
but a naked __emit dump, which carries no evidence about which class it is.

The bytes there free a split list, null m_firstSplit, then walk a stream list
calling OutputStream::Delete with m_copyDir at +0x114. That is DebugIOFlat's
layout and nothing else's, and the draft for it was already sitting in
debug_io_flat.cpp behind a present-unmatched marker.

## Compile the draft to get a fingerprint to search with

The route in was a wrong address. dtor_pairs' mirror pass follows the first call
in a claimed deleting stub, which pointed at 0x00889620, and the draft compiled
to something completely different. That failure was the useful part: it produced
142 bytes of real codegen, and the frame setup -- push ecx, push ebx, mov ebx ecx,
push esi, push edi, mov [ebp-0x10] ebx -- is a fingerprint that survives every
DIR32 difference. Matching that prefix against all six candidates hit 0x00890780
exactly, and the claim then verified 15/15 first try.

So when a name has an ambiguous pin set and a draft exists, compile the draft
first and let its prefix pick the address. It is cheaper than reading six bodies
and it does not depend on getting the vptr or literal addresses right beforehand.

## What the gate still cannot see

??_GDebugIOFlat at 0x0088A680 calls 0x00889620, not the address now claimed as
its destructor. Both rows verify. The stub is most likely another DebugIO class
wearing the name from the same harvest, but the byte gate has no way to notice
the disagreement, so it is logged rather than resolved.


## A check that had never fired once

find_declared_unmatched has always flagged a present-unmatched marker whose
function is matched from that same file -- the annotation is stale and the marker
lies about the state of the work. It compared the marker's label against ledger
names exactly, and across the whole tree it had reported zero.

Zero was wrong. There are 79 stale markers in 36 files, and every single one is
invisible to the exact test because the labels are abbreviated: the marker says
`??0OutputStream@@` where the ledger says
`??0OutputStream@DebugIOFlat@@AAE@PBDI@Z`. Not one marker in the tree uses the
full name, so the equality test never had a chance to match anything.

A check that has never fired is not evidence of a clean tree. It is equally
consistent with a check that cannot fire, and telling those apart costs one
query -- count what it would have caught under a looser rule.

The fix resolves the label by prefix, but only when the answer is unambiguous:
one marker carrying the label, and one matched row it could mean. Overloads
share an abbreviated label -- ?isPlayer@GameSlot@@ appears three times in
GameInfo.cpp -- and claiming one of them says nothing about the other two, so a
count mismatch is not evidence about any individual marker. GameInfo.cpp is
correctly silent under the new rule.

## What the markers were hiding

In debug_io_flat.cpp six of the nine markers were stale, and the file's real
state was three: one genuinely unmatched destructor, and two functions matched
from asm elsewhere, which is correct bookkeeping rather than pending work. The
count in the commit hook -- "9 unclaimed definition(s)" -- was inflated by two
thirds. cfind, the masked-body search, settled it in one run by placing every
compiled body at an address that was already claimed under its own name.


## Not inventing a symbol to get a match

SupplyTruckAIUpdateModuleData's constructor reads cleanly against the Generals
reference: three counters zeroed at 0x64, 0x68 and 0x6c, and
m_warehouseScanDistance holding 100.0f at 0x70 exactly as the reference
initialises it. BFME then adds a bool at 0x74, 50.0f at 0x78, and two ones at
0x7c and 0x80. All of that is solid.

It stops at the member at 0x84. The reference says AudioEventRTS, but the call
takes a global pointer and a zero, and the callee at 0x000B2CC0 carries only
?b_000b2cc0 -- a synthetic gen-thunk name, not an identification. Converting
would mean declaring a class and pinning a constructor signature I would be
guessing at.

A pin is an assertion about what a body is, and symbols.csv is consulted
project-wide. The DebugIOOds row cost a real correction precisely because
somebody wrote down a name that byte evidence did not support. A guessed
signature that happens to compile to the right bytes is the same mistake with
better luck, so this one is logged rather than forced.

## Where masked-body search pays and where it does not

cfind found nothing on hrawanim.cpp, debug_stack.cpp or camerashakesystem.cpp --
every compiled symbol was either already claimed or ambiguous. On parameter.cpp
the deleting stubs reported 2339 identical placements each. Under ICF a small
body is not a fingerprint at all.

It earns its keep on large distinctive bodies, which is how it settled
debug_io_flat.cpp in a single run. The 9729 unresolved drafts across 453 files
are concentrated in the big engine sources, and that is where to point it -- not
at files whose small functions have already been worked.


## The markers bind by position, not by label

Clearing markers whose label resolves to a matched row broke two files, and the
way it broke them is the useful part. Removing `??0MatBufferClass@@` from
meshmatdesc.cpp did not produce a complaint about MatBufferClass -- it produced
one about TexBufferClass::Get_Element. Removing `??0Format@@` from
debug_debug.cpp exposed Debug::StaticExit.

find_declared_unmatched associates a marker with the definition that follows it,
by position. The label is documentation and nothing checks that it names that
definition. So a marker can carry a label that is genuinely stale while still
being the only thing suppressing a different definition underneath it, and
removing it on the strength of the label alone uncovers work that was never
claimed.

The rule that survives: resolving the label is enough to suspect a marker, never
enough to delete one. Clear it, then run find_declared_unmatched --fail over the
changed files and restore anything that flips. That caught both of these; 29 of
31 removals in this batch were sound and the two that were not cost nothing
because the check ran before the commit.

## Silence from a search is not an answer

cfind on ScriptActions.cpp reported 770 defined symbols and printed 92 lines --
39 already claimed, 53 ambiguous. The other 678 produced no output whatsoever,
because a symbol with zero placements is simply not printed.

Read quickly, that looks like a file with 92 interesting symbols. It is really a
file where 678 compiled bodies do not appear in retail at all, which is a much
stronger statement about how far this source has drifted from the shipped one.
The same shape as the staleness check that had never fired: absence of output
and absence of findings are different claims, and only one of them was earned.


## A minimal reproduction of the by-value temporary transposition

AITunnelNetworkGuardState's constructor came within one transposition of exact.
51 of 53 bytes agree -- the string literal, the base call, the vptr store, the
member zero, the epilogue. The two that do not are adjacent and swapped: retail
runs `mov [esp+8],esp` then `mov ecx,esp`, the compile emits them the other way
round.

This is the same by-value temporary ordering that has blocked UnicodeString
arguments elsewhere, and it now has a 53-byte reproduction with nothing else
wrong, which is worth more than the conversion would have been.

Two things were settled on the way. The argument type is named AsciiString, not
the BFMERetailAsciiString stand-in used elsewhere in the tree -- the pinned
??0State@@QAE@PAVStateMachine@@VAsciiString@@@Z spells the parameter
VAsciiString@@, and the stand-in would encode VBFMERetailAsciiString@@ and miss
the call. And the temporary is owned by the callee: there is no unwind frame and
no destructor call on the way out. Dropping /EHsc, on the theory that the absent
EH frame meant the file should not opt into it, changed nothing at all.

## The ledger note is not the code

The AI state constructors carry notes reading "Open-BFME5 exact C++ isolated raw
AI state constructor". AIAttackAreaState is 54 bytes to this one's 53 and reads
as a sibling worth copying. It is a naked _emit dump. So are the rest of them.

The note describes an intention, not the file, and reading it as a description of
the source cost a detour. Open the file.


## The by-value transposition is not a source or a flag problem

Twelve builds against the 53-byte reproduction, all producing the same two
instructions in the same wrong order -- `mov ecx,esp` then `mov [esp+8],esp`
where retail has them reversed.

Source shapes tried: a declared destructor on AsciiString, a declared copy
constructor, and an explicit AsciiString(...) temporary rather than an implicit
conversion. The first two changed nothing at all. The explicit temporary changed
the frame instead, replacing `mov ecx,esp` with `lea ecx,[esp+8]` -- different,
and further away.

Flags tried: /O1, /Os, /Ox, /Oy-, /Gy, /GF, /Ob0, /MT. /O1, /Os and /Oy- add a
frame pointer the target does not have, which is strictly worse. The rest are
byte-identical to /O2.

So the ordering survives every source shape and every optimisation flag this
toolchain offers. That is worth knowing precisely because those are the two
things one would try first, and it points the remaining explanation somewhere
else -- a different compiler build for the shipped binary, or this function
having been compiled in a translation unit whose contents changed the schedule.
Both are testable, neither is testable from this file alone.

Also worth recording: the store is dead. It writes the temporary's address into
a slot nothing ever reads, in both retail and every compile here. The two
instructions disagree only about which order to be useless in.


## Aliasing keeps a dead store alive

The 50 ConcreteModuleClass::getInstance bodies in fx_particle_system_bulk.cpp are
all naked and none has been converted. The natural source -- a function-local
static and a return -- gets the hard parts right first time: the guard byte test,
the atexit registration, the instance address, the final vptr immediate.

It fails on one store. The constructor sets the base vptr 0x01110850 and then the
derived vptr 0x011113c4 into the same slot, and retail drops the first as dead.
The compile keeps it, and the reason is visible in the constructor's own source:
between the two vptr writes it stores through absolute addresses --
*(void **)0x012f64d0 = this and *(void **)0x012f64f4 = this. Nothing tells the
compiler those cannot be the object's first word, so the earlier store has to
stand.

That is not a fact about inlining, it is a fact about what the source says the
program might do. The idiom of writing globals as casts from integer literals is
what makes these functions tractable at all, and it is also what blocks this one.

Worth knowing before the next attempt: the constructor's standalone body is a
matched row, so the source that produces the aliasing cannot simply be reordered
to suit the inlined copy. Whatever fixes this has to leave the standalone
codegen alone.

## Cost of a build is part of the screen

That file verifies 560 rows on every build. A candidate inside it is not a
cheap three-build experiment, and that should be weighed before starting rather
than discovered halfway through.


## Screen on the things that actually blocked the last three attempts

Three ticks of picking uniformly at random hit three different walls, and all
three were visible in the bytes before a line of C++ was written. Six vptr
stores meant multiple inheritance. A callee whose only name was ?b_000b2cc0
meant pinning a guessed signature. A candidate inside a bulk file meant 560 rows
verified per build.

tools/screen_naked.py now ranks on exactly those: vtable stores in the body,
callees that resolve only to synthetic names, and how many rows the source file
carries. 240 candidates come back with at most one vtable, no synthetic callee,
and a single-row source. That is a queue where a three-build experiment costs
three short builds.

## Four ways not to get a sub-object cursor

StealthUpgradeModuleData zeroes two 0x18 blocks at 0 and 0x18 through a register
-- `mov edx,eax`, six stores, `lea edx,[eax+0x18]`, six more -- and then writes
everything from 0x30 up directly off the object pointer. The second half matches
byte for byte on the first build, including the byte at 0x58 and the -1 at 0x5c.

The cursor does not come from any of the obvious sources. A member type with an
inline constructor, the same constructor moved out of line, and an array of two
elements all produce byte-identical output: direct addressing off eax with no
cursor at all. Replacing the constructor with memset produces one merged 48-byte
rep stosd for both blocks, which is further away still.

That MSVC normalises all three of the first shapes to the same instructions is
the useful part -- it means the cursor is not a matter of how the sub-object's
initialisation is spelled, and the next hypothesis has to come from somewhere
else.

This took four builds against a three-build rule. The fourth was taken on a
specific stated hypothesis rather than another guess, and it was wrong; noting
the overrun because a limit that is quietly relaxed is not a limit.


## The same byte-matching mistake, made again

The first cut of screen_naked counted vtable stores by finding c7 and reading the
immediate four bytes later. That is only correct when the store has no
displacement. `mov [esi+0x38], imm32` encodes as c7 46 38 followed by the
immediate, so the read lands one byte early and returns garbage.

DeflectSpecialPower stores six vtables. The screen reported one, and it went
straight to the top of the queue as a clean candidate -- the exact failure the
screen was written to prevent, reintroduced by the screen itself.

This repository already learned this: the x87 detector in screen_blockers was
byte-matching and flagged 753 of 1041 naked thunks when only 150 really used x87,
and the fix was to decode with capstone. Screening on raw byte patterns for a
variable-length instruction set does not work, and knowing that in one file did
not stop me writing it in another.

Decoding dropped the queue from 240 to 143. Two other filters came out of the
same pass: calls through the import table, which an e8-only search cannot see and
which made a dynamic-import stub look call-free, and bodies with a frame pointer
and a stack frame, which were compiled without the project's -O2 and are a
different matching problem entirely.


## throw() is the lever that removes an EH frame from a new-expression

A factory that does `new T` gets an exception frame even under -EHsc-, because if
T's constructor throws the compiler must call operator delete. Retail's factory
at 0x0012B650 has no such frame, and the difference was worth 22 bytes of
prologue and a pile of state stores.

Declaring the constructors throw() removes it outright. The compile then matches
the allocation, the null check, the INI branch and the epilogue, and the target's
whole opening sequence appears where it should. Any constructor the factory can
reach has to be marked, including the one that is only declared -- an undefined
constructor is assumed to throw.

This generalises to every new-based factory in the tree, and friend_newModuleData
is a large family.

## What is left, and what did not move it

Retail inlines the module data constructor into the factory; MSVC emits a call to
it. __forceinline on the constructor changes nothing -- MSVC 7.1 will not inline
a constructor whose class has two bases, one of them with an out-of-line
constructor of its own.

The class identity came free from the call: the pushed pointer 0x004102C6 is an
ILT jump to ?buildFieldParse@StatusBitsUpgradeModuleData, so the object is that
module data whatever the row happens to be called. Layout follows from the
constructor -- a polymorphic 8-byte base at 0, StealthUpgradeModuleData as a
second base at +8 whose 0x68 bytes land the next store exactly on 0x70, then two
twelve-byte members, total 0x88. A base at +8 is ordinary multiple inheritance
and the existing row note calling it inexpressible is too pessimistic; the
inlining is the real obstacle.

## Read the build's own report before theorising

After editing the // cl: line the build printed "Compile: 0 of 1 TU(s)
(deps-cache: 1 current)" -- it had not recompiled, and I spent two exchanges
reasoning about bytes that came from the previous compile. Deleting the object
and forcing a rebuild produced identical bytes, so the flag was irrelevant
anyway, but that was luck rather than method. The line saying how many
translation units actually compiled is right there in the output.


## A raw address is honest where a name would be a guess

The FireWeaponCollide factory pushes a field-parse function pointer. It points at
an ILT jump whose target carries no name in the ledger, so declaring
`&FireWeaponCollideModuleData::buildFieldParse` would have meant inventing a
symbol and pinning it -- the thing declined on SupplyTruck.

Casting the address instead produces the identical instruction and asserts
nothing: `(void (*)(MultiIniFieldParse &))0x0043ABC0`. The byte `68 c0 ab 43 00`
matched first time. The tree already uses integer-literal casts for globals, and
it works the same way for code addresses.

Worth being clear about when this is right. It is right when the address is
evidence and the name is not. Where a name is already attested -- as
StatusBitsUpgradeModuleData was, by its own buildFieldParse symbol -- use the
name, because it carries information the literal throws away.

## throw() confirmed twice, inlining still open

Declaring the constructors throw() removed the exception frame again, on a second
factory in a different family. Everything outside the constructor now matches
byte for byte: the allocation, the null test, the branch, the pushed literal, the
call to initFromINIMultiProc, the epilogue.

What is left is that retail inlines the module data constructor and MSVC emits a
call to it. Defining the constructor inside the class body does not change that,
and __forceinline on a constructor is ignored outright by MSVC 7.1. Two different
classes now, one with two bases and one with a single base, so it is not about
the inheritance.

Stopping at three builds rather than taking a fourth on a stated hypothesis, as
happened last tick. The hypothesis is written down instead: an exception
specification may itself be what blocks the inliner, and __declspec(nothrow) is
the spelling that carries no specification. That is where the next attempt
starts.


## The constructor-into-new-expression inline is not reachable from source

Two ticks on it now. MSVC 7.1 emits a call to the constructor where retail has it
inlined, and none of these changes it: defining the constructor out of line,
defining it inside the class, __forceinline on it, throw(), __declspec(nothrow),
or giving the base a defined destructor rather than a declared one. Two different
classes, one with two bases and one with a single base.

The exception-specification hypothesis from last tick is refuted. Recording that
plainly because it was the reason for stopping at three builds then, and a
hypothesis worth deferring a tick for is worth reporting the answer to.

Factories of this shape are parked until someone finds the lever. What is not
parked is everything else about them -- throw() removing the exception frame, and
the address-literal for an unnamed field-parse pointer, both still hold.

## /O1 and /O2 each get half of removeAllShadows

Three lists walked identically: read the head, null it, follow the chain at
+0xd4 setting a byte at +4. The structure compiles exactly, alignment padding
included -- 8d a4 24 00 00 00 00 in the right places.

What differs is how the constants are held. Retail keeps 0 in edx and 1 in bl,
pushing ebx to afford the second register, and stores registers rather than
immediates. Under /O2 the compile uses immediates throughout. Under /O1 and /Os
it produces retail's register form exactly -- 33 d2, then 89 51 0c -- but
rotates the loops differently and drops the alignment padding.

So retail is neither: /O2's rotation with /O1's constants. That is worth knowing
because it means the flag sweep cannot settle this one, and the next thing to try
is a source change that raises the constant's value to the compiler -- a static
helper called three times, so the 1 is shared across three inlined copies and
earns a callee-saved register on merit.


## Factor the repetition and the constants find registers

removeAllShadows matched on the first build of this tick, from the hypothesis
written down at the end of the last one.

Three lists are walked identically. Written out as three loops, the compile is
structurally exact -- right rotation, right alignment padding -- but materialises
0 and 1 fresh in each loop as immediates. Written as one static helper called
three times, the same two values are live across all three inlined bodies, so
they earn registers on merit: edx for the zero, bl for the one, with ebx pushed
to afford the second. That is precisely what retail holds them in.

The general shape: when the residual is that retail keeps a constant in a
register and the compile uses immediates, the question is not which flag to pass.
It is whether the source gives that constant a longer life. Repetition written
out three times has three short lives; repetition factored into a callee has one
long one.

This also explains why the flag sweep could not settle it. /O1 and /Os produced
the register form but changed the rotation, /O2 kept the rotation but used
immediates, and retail wanted both -- because the difference was never about the
optimisation level, it was about how many times the source said the same thing.

## Deferring a hypothesis is not the same as abandoning it

Two ticks running I stopped at the build limit and wrote the next hypothesis into
the log instead of spending one more build on it. The first, that an exception
specification blocked the inliner, was wrong. The second was this one, and it
landed on the first attempt.

Both were worth deferring. Stopping preserved the rule, and writing the
hypothesis down meant the next tick opened with a specific test rather than a
fresh guess -- which is the whole value the rule was costing before.


## The vector constructor iterator names the element type for free

FastAllocatorGeneral's constructor starts with a call to ??_L, and its arguments
answer three questions at once. The count and size, 0x80 and 0x18, multiply to
0xC00, which is exactly where the next initialisation begins -- so the array
spans the whole front of the object and nothing has to be inferred about its
extent. The two function pointers it is handed are ??_F and ??1 of
FastFixedAllocator, so the element type is named outright rather than guessed.

??_F is the default constructor closure. It does not get written; declaring the
member array is enough for the compiler to emit it and reference it.

## Unsigned is visible in the branch

The clamp compiled to jl where retail has jb. Making the running size unsigned
fixed it in one build. That is the same signed-versus-unsigned tell already
recorded for loop indices, and it applies just as well to a clamp: jb and jbe
mean the source type was unsigned, jl and jle mean it was signed.

Worth noting the clamp is not dead code even though the running size starts at 16
and only grows. The compiler cannot prove that, so it emits the comparison, and a
source without the clamp would not match.

## rep stosd is an optimiser rewrite, not an intrinsic

The 128-dword zero loop compiles to rep stosd; retail runs an explicit pointer
and counter. /Oi-, which disables intrinsic expansion, changes nothing -- so the
rewrite happens in the optimiser rather than at the memset intrinsic, and no
flag reachable from here turns it off.

The sharing half of the problem did work. Declaring a local zero and assigning
every scalar from it puts the value in one register, and the compile uses al for
the byte at 0xe00 and eax for the three dwords above it, which is what retail
does with cl and ecx. Only the loop form is left.


## rep stosd survives every source shape tried

The do-while pointer walk was the recorded hypothesis and it is refuted: MSVC
still rewrites it. Across two ticks the rewrite has survived an indexed loop, a
pointer walk with a counted do-while, and /Oi-. Retail runs the explicit loop, so
its build did not do this, but nothing reachable from source or flags here
reproduces that.

Two of three hypotheses deferred this way have now landed and one has not. That
is a reasonable rate for something that costs nothing but a line in the log.

## A dead loop is a source construct, not dead code to delete

ProductionPrerequisite's constructor ends with a loop whose trip count is
computed as `mov ecx,eax` then `sub ecx,eax` -- zero, always, and the branch over
it is always taken. It is tempting to read that as garbage.

It is erase(begin(), end()) on a vector of a 4-byte POD, inlined. The copy that
would move the tail down has nothing to move, so the count folds to zero while
the loop survives; the `sar ecx,2` still names the element size, and the final
store of the begin pointer into the end slot is the clear itself. Writing a
source without that erase would lose the whole tail of the function.

The other vector in the same constructor is cleared by a real call, because its
element type is not POD. One class, two vectors, two entirely different shapes
for the same operation -- which is the tell for whether an element has a
destructor.

## Not every synthetic name looks like Gen_<hex>

The screen excluded callees named Gen_ followed by hex. MultiplayerSettings'
destructor calls Gen_setmd_0008eb60, which has a word in the middle and passed
straight through, so a candidate blocked on an unnamed member destructor reached
the top of the queue. Widened to any Gen_ prefix; the queue went from 136 to 134.


## memmove or a copy loop tells you whether the element is a POD

ProductionPrerequisite's second clear runs an element-wise dword loop -- mov edi,
[eax] then mov [edx],edi. STLport only does that when the element is not
trivially copyable; a plain enum or int gets memmove instead. So the science
entry is a four-byte class with its own assignment operator, not the bare enum
the Generals reference declares, and giving it one took the compile from a folded
`cmp eax,eax` with no loop at all to retail's exact sequence.

That is a second, independent reading of the same vector alongside the one
already recorded. The element's destructor decides whether erase is a call or is
inlined; the element's copy assignment decides whether the inlined form is
memmove or a loop. Both are visible without knowing the type's name.

## clear() folds harder than erase(begin(), end())

Written as clear(), the compile folded the whole tail away -- the trip count
became `cmp eax,eax`, the copy loop vanished, and forty bytes of retail had no
counterpart. Written as an explicit erase(begin(), end()) the arithmetic
survives: the subtraction, the sar that names the element size, and the guarded
loop.

They are the same call in STLport. The difference is only how much the optimiser
sees through, and the more explicit spelling is the one that reproduces retail
here.

## Three separate things, each necessary

Getting this to one register pair took stlport with a real std::vector, the
explicit erase spelling, and a non-trivially-copyable element. None of the three
would have shown up as an obvious next step from the others, and each was
readable from the bytes: the mangled erase name demanded the real container, the
surviving arithmetic demanded the explicit spelling, and the copy loop demanded
the non-POD element.


## A constructor's exception frame comes from members, not from the class

SegLineRendererClass's copy constructor has an SEH frame and one unwind state.
Declaring a destructor on the class itself does not produce one, which is right --
destroying a complete object is the caller's job. Declaring a destructor on a
member does, immediately, because now the constructor owns cleanup for what it
has already built if the body throws.

So the presence of a frame in a constructor is a statement about the members, and
the number of states counts the destructible ones. One state here means exactly
one member has a destructor.

## Where the frame-slot store sits says which member it is

With the destructor on the member at offset 4, everything matched except one
instruction's position: retail writes this into the frame slot immediately after
zeroing the register, before the first member store, while the compile writes it
two instructions later, after the member at offset 4 is loaded.

That store is the registration, and it is emitted before the first destructible
sub-object is constructed. Retail registers before the store to offset 0, which
puts the destructor on the member at offset 0 -- the texture pointer, held by
something with a destructor rather than being a raw pointer. The reference's
operator= uses REF_PTR_SET on it and the destructor uses REF_PTR_RELEASE, which
fits.

The general point is that the registration's position is evidence, not noise. It
localises which sub-object owns the cleanup, the same way the state count says
how many there are.


## The frame-slot store localises the unwind owner, confirmed

SegLineRendererClass matched on the first build of this tick, from the hypothesis
recorded at the end of the last one: move the declared destructor off the member
at offset 4 and onto the member at offset 0.

The reasoning was that the store of this into the frame slot is emitted before
the first destructible sub-object is constructed. Retail emits it before the
store to offset 0; with the destructor at offset 4 the compile emitted it two
instructions later, after offset 4 was loaded. Nothing else in 148 bytes
differed, so the position was the only evidence available -- and it was enough.

Three readings of a constructor's exception frame now stand together. Whether a
frame exists at all says some member has a destructor, since a destructor on the
class itself produces none. How many states there are counts the destructible
members. And where the frame slot is written says which member owns the state.

Three of four deferred hypotheses have now landed.


## A stack local's size is a fact about the class, and it shows in one instruction

CampaignManager::init is three lines and it failed on `sub esp`. Retail reserves
0x84C; the compile reserved 0x2438 and took a __chkstk probe, because every INI
header in this tree carries an 8K read buffer. BFME's INI does not have one: 0x848
is the two 1028-byte line buffers plus about sixty bytes.

Declaring INI in the function's own translation unit fixed it without disturbing
CampaignManager.cpp, which needs the real header for field-parse tables
referencing INI::parseAsciiString and INI::parseBool. Shadowing a header for a
whole TU to fix one function is the wrong shape when the rest of the TU depends
on it.


## The string-ref check catches what the byte gate cannot

CampaignManager::init passed the byte gate while its source literal read
DataINICampaign.ini. The backslashes had been lost, MSVC dropped them as unknown
escapes, and the bytes still matched because what the instruction encodes is the
literal's ADDRESS, not its text -- and the address is copied from the target.

The string-ref verifier compares the text and failed the commit. Without it the
row would have been recorded as clean C++ that produces a different string, which
is worse than a naked dump: it looks correct and is not.

Two things follow. A literal that only appears as a relocation is not verified by
byte equality, so the string check is doing real work and a failure there is not
a formality. And when a heredoc collapses backslashes -- as one did here, twice,
making a search string and its replacement identical so the fix silently no-opped
while reporting success -- build the strings from character codes and assert the
two differ before replacing.


## A magic divide names the element size

PropagandaTowerBehaviorModuleData's destructor tears down a vector inline and the
arithmetic says exactly what is in it. Multiply-high by 0x2AAAAAAB then sar 3 is
a divide by 48, and the lea eax,[eax+eax*2] with shl 4 that follows multiplies
the count straight back to bytes. Forty-eight byte elements, and no destroy loop
survives, so they are trivially destructible.

The other vector in the same class is destroyed by an out-of-line call, which
says its element has a destructor. One class, two vectors, and both element types
readable without a single name.

Landed on the first build by composing two existing conversions -- the POD-vector
base and novtable shape from HealContainModuleData, the vector<AsciiString>
member from AnimalAIUpdateModuleData. When the shape is already solved twice,
the work is picking the right two files.


## Assignment order in the body is not declaration order

WaterTransparencySetting assigns the river multiplier at 0x34 before the blend
flag at 0x2c, which is the reverse of how the members are declared. Member
construction follows declaration order and is not negotiable, but statements in
the body are emitted in the order written, so the two can disagree and the bytes
show which is which.

The same function also shows what a constructor does not do. The two words at
0x38 and 0x3c are members, and retail never writes them -- they take no INI field
and are runtime-only state. A source that helpfully zeroes them would be three
stores longer than retail and would not match. Absence of a store is evidence as
much as a store is.

## Three conversions off one triage pass

CampaignManager::init, PropagandaTowerBehaviorModuleData and
WaterTransparencySetting all landed on the first or second build, in one tick,
having been picked by a fan-out that classified twelve queue candidates against
the levers and blockers already on record.

The contrast with the preceding ticks is the point. Sampling the queue uniformly
kept landing on the FXParticleSystem ModuleInfo family, on mis-anchored rows and
on the by-value transposition -- all already known-blocked, none of which the
size-ordered screen could see. Screening on structure got the pool down to 133;
classifying against what is already known got three conversions out of the next
three attempts.


## Statement order in a constructor body is recoverable from the schedule

ToppleUpdateModuleData needed two builds and the second changed nothing but the
order of five assignments. MSVC groups stores that share a value -- the two 0.2f
fields go out together through eax, the four false flags through bl -- but it does
not reorder across those groups. So the emitted order is the source order with
same-valued stores coalesced, and reading it back gives the statement order
directly: the flag at 0x24 sits between the bl run and the two float immediates,
so it is written there.

That makes body order a recoverable fact rather than a guess, which is worth
knowing because it is otherwise the sort of residual that reads as scheduling
noise and gets abandoned.

## Four conversions from one triage pass

CampaignManager::init, PropagandaTowerBehaviorModuleData, WaterTransparencySetting
and ToppleUpdateModuleData, all in two ticks, all first or second build. The
preceding six ticks landed one conversion between them while sampling the queue
uniformly at random.

The difference is not effort, it is that candidates are now rejected on evidence
before a build is spent: the ModuleInfo family on vptr sinking, mis-anchored rows
on their own arity, unnamed callees on the naming rule. Screening on structure
got the pool to 133; classifying that pool against what is already known is what
turned it into conversions.


## A recipe is worth more than a conversion

CampaignManager::init took a tick to work out: TU-local INI at 0x848 so the frame
does not take a __chkstk probe, and the shim AsciiString so the by-value
temporary comes out in retail's order. ControlBarResizer::init is the same
function with a different literal and took one build and no thinking.

So after landing something, ask what else has that shape. Here the answer was
small -- three functions in the image build a stack-local INI and call load -- but
finding that out cost one query and closed the family for good. Two converted,
one blocked, nothing left to rediscover later.

## Dead code that survives in retail and not in the compile

ControlBarSchemeManager::init loads two INI files, which reproduces exactly, and
then walks its scheme list counting nodes into edx and never stores the count.
It is size() with the result discarded, and MSVC deletes it.

The knock-on is what makes it unfixable from source rather than merely different:
with the count gone, `this` is unused, so the push esi that saves it disappears
and every stack offset in the function shifts by four. One eliminated loop moves
the whole frame.

This is the same class as the duplicate zero store in
WeaponChangeSpecialPowerModuleModuleData -- retail's build kept dead code that
this toolchain removes. Two functions now, so it is worth naming as a family
rather than filing twice as a curiosity.


## Run the control before believing a negative

A triage pass argued that ??1Template@@MAE@XZ is a mis-named row, partly because
no vtable anywhere references its address. Checking the same property on
??1PlayerUpgradeSpecialPowerModuleData gave the same answer, which looked like
confirmation of a pattern.

It is not. The control settles it: ??1PropagandaTowerBehaviorModuleData, which is
genuinely a virtual destructor and was converted byte-exact this session, also has
zero references in every section of the image. Vtable slots hold the deleting
stub ??_G, and ??_G calls ??1 -- so a virtual destructor is never referenced from
a vtable, and finding no references says nothing at all.

The cost of the control was one line added to a query I was already running. The
cost of skipping it would have been retiring a correctly-named row on reasoning
that proves nothing, which is precisely the mistake the DebugIOOds correction was
about.

## A body that no class can produce

PlayerUpgradeSpecialPowerModuleData's destructor tears down a vector<AsciiString>
whose begin, end and capacity sit at 0, 4 and 8, and it stores no vptr anywhere.
A UAE destructor means the class is polymorphic, which puts the vptr at offset 0
and every member after it; __declspec(novtable) suppresses the store but not the
slot. So no faithful class definition produces these bytes.

That makes it an ICF-folded ~vector<AsciiString> wearing a retail name rather
than a conversion candidate, and the ledger holds only the one name because that
is all the harvest recovered. Landing it would mean the alias mechanism, not a
class -- worth recognising early, because the body reads as a perfectly ordinary
destructor right up until the offsets are checked against what the mangling
implies.

## The stash without the frame

Two facts about GameLODManager::findStaticLODLevel looked contradictory. Retail
emits `mov [esp+0xC],esp` before setting up the by-value AsciiString argument --
the /EHsc temporary stash, reusing the dead key slot -- and retail carries no SEH
prologue at all. /EHs-c- reproduces everything except the stash and lands four
bytes short; /EHsc reproduces the stash and adds a 78-byte frame.

They are only contradictory if the frame is unavoidable under /EHsc. It is not.
The frame exists to destroy the inner-scope key if the lookup throws, so the frame
is a property of what the lookup is allowed to do, not of the exception model.
Declaring the find shim `throw()` removes the reason for the frame and leaves the
stash, and the function matched at 106 bytes on that build.

This is the residue the sibling OptionPreferences::getIdealStaticGameDetail was
reverted over, logged in re_attempts as "not EH bookkeeping: /EHsc adds a full SEH
prologue retail does not have". The conclusion was half right -- it is EH
bookkeeping, and the prologue is separable from it. That accessor has the same
shape around the "IdealStaticGameLOD" key and should now go in the same way.

The general form: /EHsc versus /EHs-c- is not one lever but two, the temporary
bookkeeping and the unwind frame. When retail shows one without the other, the
throw-specifications on the callees are what tell them apart, and they are worth
reaching for before concluding the exception model is wrong.

## Three LOD rows look rotated

Converting 0x00090970 turned up an identity problem in its neighbours, and the
evidence is worth banking even though the fix is not yet determined.

0x0007E0F0, filed as OptionPreferences::getIdealStaticGameDetail, is Zero Hour's
GameLODManager::findStaticLODLevel almost line for line: `cmp [esi+0x1708],-1`
is `m_idealDetailLevel == STATIC_GAME_LOD_UNKNOWN`, the six pushes plus
`lea edi,[esi+0x1710]` and `add esp,0x1C` are the seven-argument
`testMinimumRequirements(&m_videoChipType,NULL,...)`, `mov [esi+0x1708],0` is the
assignment to STATIC_GAME_LOD_LOW, and `mov eax,[edi]; test eax,eax; jne;
mov [edi],1` is the DC_UNKNOWN-to-DC_TNT2 fixup. A 942-byte hardware benchmark is
also not a shape any preferences accessor takes.

That matters because 0x00090970 is filed as GameLODManager::findStaticLODLevel,
and one binary cannot hold that name twice. 0x00090970 keys a map at this+4 --
the OptionPreferences/CustomMatchPreferences skeleton, not GameLODManager -- so it
reads as a preferences accessor for "StaticGameLOD". Its neighbour 0x00090900 has
the identical shape over "IdealStaticGameLOD" and returns -1 on a miss, which is
an Int return, not the _N its useCameraInReplays row claims.

So the three rows appear rotated one step. What blocks fixing it is that only two
of the three destinations are known: 0x0007E0F0 is findStaticLODLevel and
0x00090900 is getIdealStaticGameDetail, but nothing in symbols.csv or exports.csv
names the "StaticGameLOD" accessor at 0x00090970, and repointing 0x0007E0F0 while
0x00090970 still carries the name would put findStaticLODLevel on two addresses.
Retiring 0x00090970's name without a replacement also drops a byte-verified claim.

0x00090970 is converted and byte-exact regardless -- the offsets it encodes are
literal, so only the row's name is in question, and that name predates the
conversion. The next step is xref work on 0x00090970's callers to name it, after
which all three can move together.

## novtable hides a base's unwind entry

BuildListInfo's destructor tracks unwind states 3/2/1/0 for three AsciiString
members. Three members should give 2/1/0/-1, so the extra state is the base
subobject, and getting the count wrong is what made a first attempt three bytes
short rather than merely mis-registered.

The cause was `__declspec(novtable)` on the stand-in base. It suppresses the
vptr store, and with it the base's entry in the unwind table, so every state
number shifts down by one. Dropping novtable restored 3/2/1/0 and the size.

Worth knowing as a diagnostic in both directions: if compiled EH states are
uniformly one below retail's, look for a base whose destructor the compiler
decided it need not unwind, and novtable is the usual reason. The state numbers
are a member count you can read straight off the disassembly before writing any
source -- retail's highest state plus one is how many destructible subobjects the
class has, bases included.

## novtable is the switch for interim vtable stores

A module constructor that delegates to a base and then carries interface bases
writes each interface vtable twice: once as the interface subobject is
constructed, once when the most-derived class installs its own. Retail's
ObjectWeaponStatusHelper writes each only once, and the compile was 14 bytes
long -- exactly the two extra 7-byte stores.

`__declspec(novtable)` on the interface bases removes them. It tells the compiler
the base is never instantiated on its own, so the interim initialisation is
dropped and only the most-derived stores remain. With it the ctor matched at
107/107.

Two of these now point the same way, in opposite directions. Here novtable was
needed to remove stores; on BuildListInfo's destructor novtable had to be removed
to restore a base's unwind entry. So read it as one knob with two visible
effects -- the interim vptr store and the unwind entry -- and set it by which of
those retail shows, not by habit.

This matters beyond one function: the (Thing *, const ModuleData *) module ctors
are a large family with the same skeleton, an SEH frame, a base call through an
ILT thunk, and three vtable stores at +0/+0xC/+0x10. The recipe is a
single-virtual anchor on the module base, two novtable interface bases, a
<Name>Base holding the ctor declaration pinned to the thunk in symbols.csv, and
the real body from the Zero Hour header.

## Where a store sits tells you which class owns the member

Module constructors write their interface vtables twice when the interface bases
are not novtable: once as each subobject is constructed, once for the
most-derived set. Any member store that lands *between* those two groups cannot
be in the constructor body, because the body runs after the most-derived vtables
are installed. It is a base subobject's member initialiser.

BridgeTowerBehavior matched at 96/96 on that reading alone: the two zeroed words
at +0x1C/+0x20 sit between the interim and most-derived groups, so they belong to
the fourth interface base and are initialised in its constructor, and the derived
body is empty.

The reading has a limit worth knowing. SiegeDeploySpecialPower has four zero
stores before the vtable group and eleven after; moving the first four onto the
last base is right, but the eleven in the body then hoist up to join them,
because they all share the one zeroed register and MSVC groups such stores freely
across the vtable writes. So the rule places members reliably only when nothing
remains on the other side to be hoisted. Where stores appear on both sides of the
vtable group, source ordering does not reach it.

## Which module ctors are reachable: look for a call after the vtables

Seven module constructors in, the failures separate from the successes on one
observable, and it can be read off the disassembly before writing any source.

MSVC will hoist the constructor body's member stores above the most-derived
vtable writes. Retail does not. So a conversion only lands when nothing needs to
sit after those writes, or when something anchors it there.

  matched   ObjectWeaponStatusHelper   no member stores, call after
  matched   GeometryUpgrade            string ctor + releaseBuffer call after
  matched   WeaponModeSpecialPowerUpdate  one byte store, call after
  matched   BridgeTowerBehavior        nothing after the vtables at all
  reverted  TensileFormationUpdate     three stores after, no call
  reverted  SiegeDeploySpecialPower     eleven stores after, no call

A call after the vtable group pins the stores before it; with no call they float
up and no source arrangement -- body assignment or member-init list -- brings
them back down.

So when picking from the family, disassemble first and take the ones whose member
stores are either absent after the vtable group or followed by a call. The ones
with bare trailing stores need a different lever than source ordering, and there
is no point spending builds on them until someone finds it.

## Split the vtable base from the field base

AnimalAIUpdate came down to one instruction out of place: retail stores the
+0x340 interface vtable and only then materialises the zero it uses for six
member writes, while the compile hoisted `xor eax,eax` above the vtable store.

No ordering inside a single class reaches that, because the vtable write and the
member initialisers both belong to the same subobject and MSVC schedules them
together. Splitting them into two bases does: a four-byte polymorphic base
carrying the vtable at +0x340, then a non-polymorphic base holding the fields and
zeroing them in its constructor. Base subobjects are constructed in declaration
order, so the vtable write is pinned ahead of the zero. 118/118 on that build.

Generalises the same way as the earlier reading: when two groups of stores must
stay in a fixed order and no source ordering inside one class produces it, ask
whether retail's layout is telling you they belong to different subobjects.

## Refining the tail-store rule: immediates do not hoist

The post-vtable-store rule said trailing member stores float above the vtable
group unless a call anchors them. HordeTransportContain has two trailing stores
and no call, and matched anyway.

The difference is what they store. TensileFormationUpdate and
SiegeDeploySpecialPower write a shared zeroed register, and MSVC groups every
such store together, which is what carries them over the vtable writes.
HordeTransportContain writes two immediates -- a byte 0 and -1000 -- so there is
no shared register and nothing to group with, and they stay where the source puts
them.

So the rule reads: trailing stores are safe when they are immediates or when a
call follows, and unreachable when they share a materialised constant with stores
on the other side of the vtable group.

## A node allocation size fixes the element type

HotKeyManager's constructor has an empty body; everything is member
construction. Each of its two maps allocates a single 0x1c node and wires it as
its own header -- colour byte zeroed, parent null, left and right pointing back
at the node.

Twenty-eight bytes is the arithmetic that names the element. Sixteen of those are
the red-black node header (colour plus three pointers), so the value type is
twelve, which beside a four-byte key fixes the mapped type at eight. No element is
ever inserted, so nothing else in the function constrains it -- the allocation
size is the only evidence, and it is enough.

That is the same move as reading a vector's element size off its magic divide,
applied to a tree instead.


## Two sessions, one ledger

Another session pushed seventy-seven commits while this one worked, and the
rebase surfaced exactly one conflict: docs/lessons.md. functions.csv and
re_attempts.log merged silently because .gitattributes gives them merge=union,
and lessons.md is append-only in the same way but was never listed. It is now.

The mistake worth recording is mine rather than the tooling's. My resolver's
pattern did not match CRLF line endings, so it asserted and changed nothing --
and I ran git add and rebase --continue anyway, committing three conflict
markers into the file. The assert did its job; I ignored it because it was two
commands earlier in the same block.

An assert that fires and a command that proceeds regardless is worse than no
assert, because the failure is now silent at the point it matters. When a guard
fires in a batch, the rest of the batch is void.


## A zero displacement means the symbol, not the code

friend_makeVeterancyUpgrade compiled to retail's exact instruction sequence with
one call left as e8 00 00 00 00. A zero REL32 is not a scheduling difference or a
wrong address -- it is the linker having nothing to resolve, because the symbol
the source declared is not the symbol that is pinned.

Here the culprit was a return type. nameToKey mangles as
?nameToKey@NameKeyGenerator@@QAE?AW4NameKeyType@@PBD@Z, where ?AW4NameKeyType@@
says the return is an enum. Declaring NameKeyType as a typedef to unsigned int
mangles the same function as ...QAEIPBD@Z and nothing matches. Making it an enum
fixed it in one build.

So when a call comes out zeroed, stop reading the disassembly and read the
mangled name of the callee instead. W4 is an enum, I is unsigned int, H is int,
and they are three different functions as far as the linker is concerned.


## Output parameters are not initialised, and that shows

calcDeltaScroll passes two Vector3 locals to CameraClass::Project as destinations.
Giving them a zero constructor added six stores retail does not have. They are
output parameters -- the callee fills them -- so the source declares them and
says nothing more, which needs a do-nothing default constructor rather than the
three-float one.

That is the same rule as the untouched words in WaterTransparencySetting, in a
different costume: what a function does not write is as much a constraint as what
it does. Here it also decides the shape of the class being modelled, because a
Vector3 with only a three-argument constructor cannot express an uninitialised
local at all.

## Symbol-not-found is an access-modifier message

The first build failed with "symbol not found in object" rather than a byte
mismatch, because the method was declared public. The row's name says AAE, which
is private; public mangles QAE and nothing in the object matches.

Worth separating the two failure modes when reading build output. A byte
mismatch means the code is wrong. Symbol-not-found means the declaration is
wrong -- access, return type, constness or parameter types -- and no amount of
staring at the disassembly will help until the mangled name is read back.


## The vptr-sinking blocker is narrower than recorded

ParticleSystemTemplate's constructor sits in the FXParticleSystem family that
vptr sinking was recorded as blocking wholesale, and it converted on the first
build with the vptr store exactly where retail has it, ahead of the member copy
constructor.

The difference from the family members that really are stuck is what the body
contains. LifeEventModuleInfo and DefaultPhysicsModuleInfo call setRange three
times and their vptr stores sink past those calls. This one's body is nothing but
stores, and the store stays put.

Working hypothesis from one positive case rather than a proof: the sink needs a
call in the body to move past, not merely statements. Worth acting on, because it
means the family should be re-screened on what its bodies call instead of skipped
by name. A blocker recorded at family granularity is cheap to write and expensive
to believe.

## open(path, "wb") truncates before the argument is evaluated

This emptied functions.csv -- all 94171 rows -- in a single statement:

    io.open(p, "wb").write(raw.replace(m.group(0), new, 1))

A regex had missed, so m was None and m.group(0) raised. But Python evaluates
io.open(p, "wb") first, and opening for write truncates immediately; the
exception then landed after the file was already zero bytes. The assert I would
normally have written was not there, and the guard that did exist -- the crash
itself -- arrived too late to protect anything.

Compute the new bytes into a variable, assert on them, and only then open the
file. The pattern that is safe reads:

    out = raw.replace(old, new, 1)
    assert len(out) > len(raw)
    io.open(p, "wb").write(out)

Recovery was one git checkout because the file is tracked, which is the only
reason this cost minutes rather than the session.


## The shim closes the by-value transposition for good

AITunnelNetworkGuardState sat parked for several ticks on the `mov [esp+8],esp` /
`mov ecx,esp` pair, and the note said the transposition survived every source
shape. It did not survive using the real shim AsciiString instead of a
hand-rolled four-byte stand-in. Five 46-byte State constructors -- AIBusyState,
FailureState, ContinueState, AIWaitState, AIDeadState -- then converted on the
first build each.

Two ticks ago I recorded this correction for CampaignManager and did not go back
and re-try the functions I had already parked on it. Parked rows should be
re-queued when the blocker that parked them is retired; that is a cheap sweep and
it was worth five conversions here.

## A shape screen hides exactly what it matches on

Seven candidates were selected because their bytes matched the family pattern
byte for byte. Three of them failed, and the difference was a single call
displacement -- the base constructor. They resolve to 0x0014F280 and 0x0018D890
where the others resolve to State's 0x000A19E0, so those classes derive from an
intermediate class rather than from State directly.

The relocated operand is excluded from a shape match by construction: that is what
makes the screen useful across a family, and it is also the one field that can
hide a structural difference. When a shape-selected batch fails, look at the
relocations first, because they are the part the screen was blind to by design.

My first reading of this was that retail used a different ILT thunk for the same
function. That was wrong -- only one thunk targets State's constructor -- and
resolving the jump chain took one query that I should have run before forming the
theory.


## Screen on behaviour, not on byte shape

The first pass at this family screened on the exact 46-byte pattern and found
seven, three of which had the wrong base class. Screening instead on what the
body does -- an AsciiString constructor call followed by exactly one more call,
with a literal pushed -- found thirty-one across every size from 46 to 124 bytes,
and grouped them by the address of that second call.

Grouping by the base's address is what makes the batch safe. Thirteen call
State's constructor, thirteen call 0x0014F280 and five call 0x0018D890, and those
last two groups are the ones that failed when a shape screen lumped them in with
the first. The property that decides whether a source compiles is the base class,
and it is directly observable; matching bytes around it is not a proxy for it.

## The vptr store scheduled itself

Retail puts the vptr store first in the 53-byte members of this family and last
in the 54-byte ones. Writing the added members as initialisers in both cases
produced retail's order each time without the source saying anything about it --
MSVC sinks the store past a run of same-valued member stores and leaves it in
front of a single immediate one.

Worth knowing because vptr placement has been treated here as a blocker to be
worked around. In this family it is simply a consequence of what the members are,
and the source that describes the members correctly gets the placement for free.


## Naming a base class from thirteen callers and a reference header

Thirteen retail State subclasses call 0x0014F280 as their base constructor, and
it has no ledger row. The reference declares AIInternalMoveToState with exactly
that set of children -- AIMoveToState, AIMoveOutOfTheWayState, AIEnterState and
the rest -- and its constructor takes StateMachine* and an AsciiString by value,
which is precisely why the body at that address copy-constructs the string a
second time before calling State.

That is enough to pin the name. It is not an invention: the caller set, the
signature and the by-value copy all agree, and any one of them alone would not
have been. Four conversions followed immediately.

## Correcting the vptr-sinking narrowing

Two ticks ago I proposed that the sink needs a call in the body to move past,
from one positive case. That is wrong. AIMoveAndEvacuateState has no call after
its base constructor and MSVC still sinks the vptr store past three member
stores, where retail keeps it in front.

What the evidence actually supports: with a single added member, compiler and
retail agree on placement. With several, MSVC always sinks and retail sometimes
does -- AIMoveAndTightenState sinks in retail too, AIMoveAndEvacuateState does
not, from sources that look the same shape. So the rule is not about calls and
is not yet known; the honest statement is that one member is safe and more than
one is a coin toss.

A hypothesis from one positive case earned a re-test, got one, and lost. That is
the cheap outcome -- the expensive one would have been screening the family on it.


## Two base classes named the same way, and one access modifier that mattered

TurretState was recovered exactly as AIInternalMoveToState was: five retail
subclasses call one unnamed address, the reference declares a class with exactly
that set of children, and its constructor signature matches what the body does.
All five converted on the first build.

The difference between the two was the access modifier. AIInternalMoveToState's
constructor is public and mangles QAE; TurretState's is protected and mangles
IAE. Pinning the public spelling would have produced a symbol nothing calls, and
the failure would have read as symbol-not-found rather than as a byte mismatch --
which is the tell for a declaration problem, already recorded. Reading the
reference's access specifier before writing the pin cost nothing and saved a
build.

## The class name is not the state name

TurretAIHoldTurretState passes "AIHoldTurretState" as its state name. The class
and the string disagree, and nothing but the pushed literal shows it -- every
other member of the family passes its own class name, so a generator that
assumes the two are equal produces five correct files and one that fails.

Worth checking per candidate rather than deriving, because it is exactly the kind
of detail a family template makes invisible.


## The vptr blocker is only the disagreement, not the sink

AIAttackSquadState has two zeroed members and retail sinks its vptr store past
them. MSVC sinks identically, and it matched on the first build.

That sharpens what was recorded last tick. The blocker is not "more than one
member" -- it is only the subset where retail keeps the store in front and MSVC
sinks it anyway. Where retail sinks, the compiler agrees for free and there is
nothing to work around. AIMoveAndEvacuateState is blocked because retail does not
sink; AIAttackSquadState is not blocked because retail does.

So the screen for this family is: read whether the vptr store precedes or follows
the member stores in retail, and only park the ones where it precedes them and
there is more than one member.

## A parameter that is never stored

AIAttackSquadState takes an AttackExitConditionsInterface* and does nothing with
it -- retail zeroes both members and ignores the argument. The signature is not
optional, because it is in the mangled name and the caller pushes it, but the
body must not use it.

Writing the obvious source, which assigns the parameter to the member at 0x24,
would have produced a store retail does not have. The argument being present in
the signature says nothing about whether the body touches it.


## Half the parked cases were not blocked at all

Last tick four constructors were parked as vptr-sinking failures. Applying the
sharpened screen -- park only where retail keeps the store in FRONT of several
member stores -- showed two of them have retail sinking as well, so the compiler
was never disagreeing about placement.

Their actual defect was store order. Retail writes the flag at 0x54 before the
word at 0x50, and an initialiser list emits members in declaration order, which
cannot express that. Moving the two assignments into the body, in retail's order,
matched both on the first build.

Two lessons already recorded separately turn out to compose: body statements are
emitted as written, and the vptr blocker is only the disagreement. Neither alone
would have unparked these; the combination did, and the cost was one build each.

Worth being blunt about the failure mode. Attributing a failure to a known
blocker is the cheapest possible explanation and it is wrong half the time here.
A blocker should be assigned only after the specific evidence for it -- in this
case which side of the member stores the vptr sits on -- has actually been
checked.


## The vptr disagreement has a third form: how far it sinks

AIIdleState writes five members and its body order already matches retail store
for store. The only difference is where the vptr lands: retail sinks it past all
four of the leading member stores, MSVC sinks it past the two that share the
zeroed byte register and emits it there.

So the disagreement is not simply in-front versus behind. It is how far the store
travels, and the compiler stops at the end of a same-valued run while retail
carries on past stores of different values. Two of this family are blocked
because retail keeps the store in front, and this one because retail moves it
further -- same underlying cause, three surface forms.

That also means the screen needs stating more carefully than last tick: compare
the vptr's position against the member stores exactly, not just which side it
falls on.


## What the vptr sink actually does

Enough cases have now been measured to state the compiler's half exactly. MSVC
sinks a constructor's vptr store to the end of the leading run of member stores
that share a value, and no further. AIWanderState zeroes ten members and then
writes a byte to 1; the store lands after the ten and before the one. AIIdleState
zeroes two bytes and then writes 1 and 0xffff; the store lands after the two.

Retail's half is not predictable from anything measured so far. It sometimes puts
the store ahead of every member store, sometimes after all of them including
differing values. A function matches when the two happen to coincide -- which is
why single-member cases and uniform-value tails nearly always work, and why a
tail with a differently-valued store at the end nearly always fails.

That turns the blocker into a screen rather than a mystery. Before writing a
constructor in this family, compare retail's vptr position with the end of the
leading same-valued run. If they agree the function is convertible; if not, it is
parked and no ordering of the source will change it, because the source cannot
address vptr placement at all.


## Turning the vptr rule into a screen

The characterisation from last tick is mechanical enough to run: predict MSVC's
vptr position as the end of the leading run of same-valued member stores, treat a
run shorter than two as no sink at all, and compare against where retail actually
put it. tools/screen_vptr.py does that and splits the naked constructor pool into
16 convertible and 35 parked.

It is calibrated against every case measured by hand -- the single-member ones
that agreed at position zero, the uniform-value tails that matched, and
AIWanderState, AIIdleState and AIMoveAndEvacuateState which did not. That is the
part worth insisting on: a screen built from the successes alone would have had
no way to be wrong.

The value is not the sixteen it found. It is that thirty-five constructors now
have a reason not to be attempted, and the reason is checkable rather than
remembered.

## An unwritten word is still a member

PhysicsBehaviorModuleData writes twenty-four members and every offset was four
too low. The vptr sits at 0 and the first written member at 8, so a word lies
between them that the constructor never touches -- and it still has to be
declared, because everything after it depends on where it ends.

The same reading as the untouched tail words in WaterTransparencySetting, from
the opposite direction: there, absence of a store meant do not initialise; here it
means do not forget to declare.


## The screen's two verdicts are not equally sound

GarrisonContainModuleData was the screen's pick and it failed. Base pinned,
all eighteen member offsets right, and the vptr still landed two stores late.

The cause is in the screen itself. It predicts where MSVC will sink the store by
reading retail's instruction stream, which means it inherits retail's register
allocation. Retail keeps 1.0f in ecx beside a zero run in eax, so its run of
register-sourced stores ends at eleven. The compile put both constants in eax,
making the run thirteen, and the store travelled two further.

That asymmetry is worth stating in the tool and not just here. A "parked" verdict
is sound: retail puts the store where no allocation of registers could place it,
so the function cannot match. A "convertible" verdict only means nothing in
retail's own bytes rules it out -- the compiler still gets a vote, and it votes
with its allocator.

Half a screen that is reliable is still worth having. The thirty-five parked
constructors are genuinely not worth a build; the sixteen are worth exactly one
each.


## Floats reach the FPU by being passed, not by being assigned

Get_Diffuse copies three floats and retail does it on the x87 stack: three loads,
an exchange to undo the stack's reversal, three stores. Writing three field
assignments gives integer moves instead, and so does a whole-struct copy -- MSVC
treats a float lvalue copy as a bit pattern.

What does put them on the FPU is passing them by value into an inlined setter.
That produced real fld and fstp instructions in the right places. It still was not
exact: MSVC folded one of the three back to an integer move where retail kept all
three on the stack, and that is instruction selection rather than anything the
source can express.

The transferable part is the mechanism. If retail uses x87 for something that
looks like a plain copy, the source is passing the values somewhere, not
assigning them.

## Calling convention is part of the name, and can be wrong in the ledger

getListboxBottomEntry reads its parameter from ecx in the first instruction and
returns with a bare ret. That is __fastcall. The row calls it
?getListboxBottomEntry@@YAHPAU_ListboxData@@@Z, where YA is cdecl and the
argument would live at [esp+4].

Both cannot be true, and the bytes win. The row needs repairing to YI before the
function can be attempted -- writing it as declared produces a source that reads
the wrong location, and writing it as __fastcall produces a symbol the row does
not name. This is the third mis-named row found by reading arity and convention
off the body rather than trusting the mangled name.


## Put last tick's failures into the screen, not just the log

Two builds were lost last tick to an x87 float copy and to a row whose calling
convention did not match its name. Both are cheap to test for, so both went into
the non-constructor screen: exclude bodies containing x87 instructions, and
exclude free functions whose name says cdecl while the body reads an argument out
of ecx. Thirteen and one candidate respectively, and getListboxBottomEntry -- the
one that cost the build -- is gone from the list.

The first pick after that filtering, HideDiplomacy, matched on the first build.
That is the argument for spending the failure: a build lost to a cause you then
encode is cheaper than the same build lost twice.

## The same name can be two functions

?HideDiplomacy@@YAXXZ takes no arguments. Diplomacy.cpp already contains a clean
HideDiplomacy(Bool), which is a different overload with a different mangled name,
and reading that file to understand the naked row was wasted effort -- the two
share a name and nothing else.

Check the mangled signature before going to look for the source. XZ means no
arguments and it is right there in the row.


## The by-value transposition is closed for UnicodeString too

ResetInGameChat passes a UnicodeString by value and matched on the first build
using the shim's class from reference/shims/languagefilter. The blocker that was
recorded as surviving every source shape, and later narrowed to "only the
UnicodeString flavour remains open", is now closed on both sides.

The rule was the same both times and it was already written down: use the real
StringBase-backed class, not a four-byte stand-in of your own. AsciiString is
StringBase<D> and UnicodeString is StringBase<G> -- the same template, so it was
never plausible that one would need a different fix than the other, and treating
them as separate problems cost several ticks.

Every row parked on this blocker is now worth re-queueing: resetIdleWorker,
GadgetComboBoxSetText, isUser@LANGameSlot, amIHost@GameSpyStagingRoom. Retiring
a blocker means sweeping what it parked, which is the same lesson the AsciiString
closure taught and which I again did not act on immediately.

## A reloaded global is a second read in the source

HideSaveLoadMenu writes three fields and retail reloads the menu pointer from its
global before the middle one, despite holding it in a register from the null
check two instructions earlier.

That is not a spill. It is the source naming the global again instead of the
local it already has, and writing it through the local produces one fewer load.
The register the compiler happens to have is not evidence about what the source
said.


## Sweeping a retired blocker pays immediately

Closing the by-value transposition parked four rows that were waiting on it.
Three of them converted this tick -- amIHost and resetIdleWorker on the first
build, GadgetComboBoxSetText on the third.

This is the second time the sweep has been worth running and the second time I
had to be reminded to run it. When a blocker retires, the rows it parked are the
best-understood candidates available: each already has a disassembly, a diagnosis
and a reason it failed. They should be the next thing attempted, not something
noticed later.

## Hoisting a call out of an argument list changes when it runs

GadgetComboBoxSetText builds a string copy for its second argument and calls
winGetUserData for its first. Retail evaluates right to left, so the copy is
built first and the accessor runs after it.

Writing the accessor as its own statement before the call inverts that, and the
two are not interchangeable: a call in an argument list is sequenced with the
other arguments, a call in a preceding statement is not. Putting it back inside
-- via a small inlined helper, since MSVC rejects assignment-in-condition as
C4706 here -- matched.

So when a temporary appears earlier in retail than the source suggests, look at
which expressions are arguments and which have been lifted into locals. Lifting
is not free.


## throw() also removes unwind states for temporaries, not just EH frames

The known form of this lever was: put `throw()` on a constructor a
`new`-expression reaches, and MSVC stops building the EH frame that exists only
to run `operator delete`. isUser generalises it.

isUser evaluates `!userName.compareNoCase(getName())`. The `getName()` temporary
is conditionally constructed -- `&&` short-circuits -- so it needs a
did-we-construct-it flag either way. Retail keeps that flag in ebx and never
touches the unwind state. My build kept the flag in a separate stack dword *and*
bumped the unwind state to 1, costing an extra local.

The unwind state exists to destroy the temporary if something throws while it is
alive. The only thing that runs while it is alive is compareNoCase. Declaring
that `throw()` makes the window provably exception-free, the state bump
disappears, and the flag collapses into ebx. Byte-exact.

So the rule is wider than constructors: `throw()` on **whatever executes between
a temporary's construction and its destruction** removes that temporary's unwind
state. When retail guards a temporary with a plain flag and no state transition,
look at what runs in that window and try marking it non-throwing.

The ledger corroborated this before the build did -- the function has exactly one
generated unwind funclet, and one funclet cannot cover both the by-value argument
and an EH-protected temporary. Counting funclets is a cheap check on how many
things retail unwinds.


## Touching a shim runs the full gate, which is where latent problems surface

Adding one declaration to the languagefilter shim tripped the pre-commit rule
that any header change runs the full gate instead of the delta verify. It found
six DIR32 inconsistencies that had nothing to do with the change -- none of the
files involved include that header.

They had been latent because the full gate almost never runs. Delta verify sees
only the sources you touched, so a cross-source inconsistency introduced by one
commit stays invisible until somebody edits a header months later.

The finding itself: constructors of behaviors implementing two module interfaces
disagree with single-interface classes about where an interface vtable lives.
The sources name the vptr after the base (??_7UpdateModuleInterface@@6B@) when
each derived class has its own vtable for that base sub-object, so N classes
claim one symbol at N addresses. Nine single-interface Die constructors agree
only because ICF folds identical vtables -- agreement by coincidence, not by
correctness.

Two things worth keeping. A gate that runs rarely accumulates debt silently, so
the rare run is worth reading carefully rather than clearing. And when a majority
of references agree on an address, check whether they agree for a reason or
because the linker folded them -- ICF makes wrong names look consistent.


## Do not derive from StringBase when retail inlines the default construction

isPlayer builds a local UnicodeString and translates into it. Deriving
UnicodeString from StringBase<G> is the obvious spelling and it costs a call:
the real StringBase default ctor is declared out of line, so construction emits
one, where retail inlines a single zero store and shares that zero with the EH
state register.

The campaignmanagerascii AsciiString shim already has the right shape -- a
standalone class with its own inline `m_text = 0` ctor, an undefined destructor
that is pinned to releaseBuffer's address, and every real operation reached by
casting to StringBase<T>*. Copying that shape matched. Reach for it whenever
retail inlines part of a string class and calls out for the rest.

Two smaller notes from the same file. wchar_t is not a keyword under
/Zc:wchar_t- and nothing in that include set declares it, so the template
argument has to be spelled `unsigned short` -- which is what G means in the
mangling anyway. And guessing a function's RVA to disassemble it produces a
plausible-looking listing with every call annotation silently wrong; the
instruction sequence still reads correctly, which is what makes it dangerous.
Look the address up.

## The throw() lever is blocked when the declaration is in real source

getSlotNum shows the same unwind-state bump isUser had, for the by-value copy
passed to the inlined isPlayer. The fix that worked for isUser -- declare the
only call in that window throw() -- is not available the same way here: isUser
went through the languagefilter shim, which is TU-scoped, while getSlotNum uses
the real Code/Libraries/.../string_base.h that hundreds of TUs include.

Editing it is a legitimate experiment and the full gate would arbitrate, but it
belongs in its own tick rather than inside a conversion. Worth doing: if retail's
compareNoCase really is non-throwing, the declaration is simply more accurate,
and every string-heavy function with this shape unblocks at once.

getSlotNum stays parked regardless, because it also has esi and edi swapped
against retail for this-versus-loop-counter, which is the register allocation
residual and not something the source can address.


## A virtual destructor always stores a vptr, so its absence disproves the name

The ledger had Template's destructor as ??1Template@@MAE@XZ, where M means
protected *virtual*. But retail calls releaseBuffer on this+0, which leaves no
room for a vptr, and the already-dumped constructor builds an AsciiString there
from a literal rather than storing a vtable.

Building it as declared settled it: MSVC emitted `c7 06 <vtable>` at the top and
shifted every subsequent member offset by four. So the class is not polymorphic
and the name could not be right. Renamed to IAE -- non-virtual from this
evidence, protected from the reference, where MEMORY_POOL_GLUE and EMPTY_DTOR
put Template's destructor there. Byte-exact immediately after.

Worth generalising: the access letter in a mangled name is invisible to the byte
gate, but the *virtual* bit is not. M/U/E versus I/Q/A is testable, because a
virtual destructor cannot avoid its vptr store. When a destructor row will not
convert and the first member looks like real data, check that bit before
anything else.

The reference also explained why the name was plausible. Generals' Template
derives from MemoryPoolObject and does have a virtual destructor; BFME's does
not. Inheriting a name from the reference is a good first guess and a bad last
word.

## Two candidates rejected by reading before building

AIAttackState::onExit ends in a bare `ret`. A one-argument thiscall must `ret 4`,
so the declared W4StateExitType parameter is wrong -- the body takes nothing.
Logged as suspect rather than attempted.

ProductionPrerequisite's constructor contains `mov ecx,eax` immediately followed
by `sub ecx,eax`, so the shift and compare that follow work on a provable zero
and the copy loop below can never execute. That is the dead-code-retail-keeps
family, which no source spelling reproduces.

Both cost one disassembly and no builds. The screen ranks candidates by shape;
it cannot see either of these, and a minute of reading is cheaper than three
builds discovering the same thing.


## Correction: a virtual destructor does NOT always store a vptr

Last tick I wrote that a virtual destructor always emits a vptr store, and used
that to prove Template's row was mis-named. The conclusion was right; the rule
as stated is wrong, and stated that way it would condemn a lot of correct rows.

Screening every naked single-row destructor with a virtual access letter turned
up 29 of 134 with no vptr store. Classes like MultiplayerSettings and
StealthUpdate are certainly polymorphic, so the rule cannot be that strong.

What MultiplayerSettings shows is the real shape: it ends by calling
??1SubsystemInterface@@UAE@XZ, its base destructor. When ~Derived runs, the
object's vptr already holds Derived's vtable -- the constructor put it there, or
a more-derived destructor reset it on the way down -- so storing it again is
redundant and MSVC elides it. The base destructor still stores the *base*
vtable, because after ~Derived's body the dynamic type really does change.

So the store survives only where it is not redundant: in a **root** polymorphic
class's destructor. That is exactly the case Template presented, which is why
building it as MAE emitted one.

The usable test is therefore a conjunction: no vptr store AND no base-destructor
call. Neither half alone means anything. Even that over-reports here, because
base destructor calls often go through synthetic j_ thunks whose targets the
name resolver does not follow, so 25 of the 29 survive a check that should
eliminate most of them.

The wider lesson is about how I generalised. One positive case -- Template
emitting the store -- became "always". The screen that should have tested the
rule was written after the rule was published, and it immediately refuted it.
Run the screen first when the claim is cheap to check across the whole ledger.

## TooltipUpgrade's row is not a destructor

??1TooltipUpgrade@@UAE@XZ ends in `ret 4`. A destructor takes no arguments, so
that alone settles it. The body builds an AsciiString from a literal, then
either releases a UnicodeString at this+0x2d4 or calls set@UnicodeString on it
with the argument -- a setter taking a const UnicodeString reference.

Logged rather than repaired: the address and size are probably fine, but the
true name is not derivable from the body, and inventing one is worse than
leaving the row visibly wrong.


## The new-expression blocker is two problems, and throw() solves one of them

"Constructor inlined into a new-expression" has been recorded as one blocker with
throw() among its refuted fixes. The Sabotage factory shows that is wrong: it is
two independent problems, and throw() solves the first cleanly.

Without it MSVC wraps the whole factory in an EH frame -- push -1, the handler,
the fs:[0] chain -- so operator delete can run if a constructor throws. Retail
has no frame at all. Putting throw() on every constructor the new-expression
reaches (the class, both bases, and the two member sub-objects) removed it, and
the prologue then matched retail instruction for instruction.

What remains is narrower: MSVC emits a call to the derived constructor where
retail inlines it. Three further shapes produced byte-identical output -- the
constructor defined in-class, both destructors defined rather than merely
declared, and no user-declared constructor at all so MSVC synthesises one. So
the refuted list for the *inlining* half now also covers defined-own-destructor
and implicit-constructor.

Recording the split matters because the EH frame was the visible symptom. Any
future row of this shape should get throw() first and be judged on what is left.

Two things read off retail on the way. Base constructors run before the
most-derived vptr store, so a constructor call at a non-zero offset appearing
*before* that store is a second base under multiple inheritance -- here
UpgradeModuleDataSub at +8, which the reference confirms does not inherit from
ModuleData. And a member zeroed via `lea reg,[obj+N]` then stores at [reg],
[reg+4], [reg+8] is a sub-object with its own inlined constructor, not a plain
array; an array member would be stored through the object register directly.

FireWeaponCollide's factory, the same shape, zeroes 0x0c through 0x24 twice
over. That is the duplicate-zero-store family, so it was not attempted.


## A naked source passes the byte gate, so OK N/N can be a false positive

Writing seven cloned files and building them reported `Functions: OK 7/7
matched`. No files had been written -- an assertion earlier in the same script
had fired and stopped it. The seven sources were still `__declspec(naked)`
dumps, and a naked dump reproduces its own bytes by construction.

The gate answers "do these bytes match", which is the right question only once
the source is real C++. It cannot tell a correct conversion from an unconverted
one. Every batch that writes sources should assert afterwards that none of the
targets still contains `__declspec(naked)`, and that is now in the clone script.

This is the second time in two ticks that an assertion fired mid-batch and the
rest of the batch ran anyway. The rule already existed. What was missing was a
post-condition that would have caught it regardless of why the write did not
happen.

## Matching normalised bodies finds work that needs no analysis

Two ticks of picking candidates by shape produced no conversions. Normalising
every naked single-row body instead -- zeroing rel32 operands and any four-byte
immediate that looks like an image address -- and hashing it against the bodies
of already-converted rows found 20 exact twins out of 982.

Twelve converted immediately, most by substituting one class name into an
existing model, because ICF folds identical bodies and the ledger carries a row
per name. Seven UpgradeModuleData constructors are literally one body at
0x129C10 with seven names.

Only the final class name reaches the mangled symbol, so helper classes in a
model can keep their original names; a token substitution on the one name that
matters is enough. One of the twenty did not clone -- DynamicPortalBehaviour's
constructor against QueueProductionExitUpdate's -- so an exact normalised match
is a strong lead rather than a guarantee.

Worth doing again whenever a batch of conversions lands: each newly converted
body becomes a model for whatever still matches it.

## Survey the flag sets already proven in the tree before inventing one

Two functions were written off this session as blocked on "constant materialisation",
with the reasoning that no source spelling moved them. That reasoning was sound and the
conclusion was still wrong, because the per-file `// cl:` directive is a second axis and
it had never been searched.

There is no need to search it blind. The tree already records every flag set that has
been proven to reproduce retail bytes, one per source file, and counting them takes a
second:

    1704  /DNDEBUG /MD /EHsc
     118  /DNDEBUG /MD /GX- /O2 /Ob2
      59  /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
       1  /DNDEBUG /MD /EHsc /Og-

That /GX- /O2 /Ob2 line is 118 files' worth of evidence that some of this binary was
built with exceptions off and aggressive inlining on. Applied to
SabotageMilitaryFactoryCrateCollide::friend_newModuleData it removed both of that
function's recorded blockers at once -- the SEH prologue that /EHsc wraps around a new
expression, and the out-of-line constructor call that no amount of defining the
constructor in the translation unit would inline.

What is left there is narrower and worth stating precisely, because it is the same shape
seen elsewhere: retail checks the allocation with test esi,esi and then builds each of
the two member runs independently, a fresh xor for its zero and its own lea'd this
pointer. The rebuild finds the common zero, hoists it into edi at the cost of saving the
register, and folds both lea's into [esi+disp] addressing. Splitting the two runs into
distinct struct types did not stop the merge, so that part genuinely is not source-
steerable -- but note that this is the mirror image of removeAllShadows, where the
rebuild refused to share a zero that retail did share. Same flags, opposite decisions,
which is what makes it a heuristic rather than a switch.

/Og- is not the answer either: it overshoots, stopping inlining altogether and producing
an ebp frame with stack locals.

The general point: when the source has been ruled out, the flags are the next axis, and
the cheapest move is to sort the existing directives by frequency and try the ones the
project has already proven rather than reasoning from first principles about /O1 versus
/O2.

## A call through an ILT thunk needs the name pinned at the thunk

Remove_Render_Object turned out to be blocked on a helper that is not what it looks like.
The body at 0x00943430 decodes its argument's +0x94 field as three signed ten-bit
quantities -- a packed grid cell address -- and unlinks the object from cell lists, which
reads exactly like GridCullSystemClass::unlink_object. It is not: that name is already
claimed at 0x008DDC60, and every other GridCullSystemClass method sits in the 0x8D
region while this one is at 0x94. The object at SimpleSceneClass+0x34 is a second spatial
grid this build added, with no counterpart in the reference. So the row stays blocked, but
on a definite answer rather than an open question.

Unregister, in the same neighbourhood and already understood, is blocked differently and
more interestingly. Three of its five switch arms call 0x00018EC6, an ILT jump thunk
whose target 0x00711B70 is claimed as
?Remove@?$RefMultiListClass@VRenderObjClass@@@@QAE_NPAVRenderObjClass@@@Z. Writing that
call in C++ emits a call to whatever address that name resolves to -- the body -- while
the retail bytes target the thunk five bytes of displacement away.

The project already handles this: eight real names are pinned at 0x00002874, itself a
thunk, and ??0DrawableModule@@ among them is how the W3DDebrisDraw conversion resolved
its base constructor. So the mechanism is to pin the real name at the thunk address. What
is not obvious, and not something to guess at, is what happens when that name is already
mapped to the body in functions.csv -- whether a second mapping in symbols.csv is
intended or would make resolution ambiguous.

Recorded rather than attempted. The remaining two arms of Unregister call Internal_Remove
directly and would reproduce; it is only the thunked three that need this settled.

## Where an unwind state sits tells you whether a subobject is a base or a base's member

CritterEmitterUpdateModuleData's destructor destroys five things: four at unwind states
3, 2, 1, 0 and the subobject at 0x08 last, at state 4. Reading that as "four members and
a base" and writing `class X : public RootBase, public Base08 { ...four members... }`
reproduces every instruction and gets the numbering exactly backwards -- MSVC emits it as
base 0, members 1..4, because bases are constructed before members and numbered in
construction order.

The shape that does reproduce it is an intermediate class with an inline destructor:

    class Mid : public RootBase { InnerAt08 m_at08; public: virtual ~Mid() {} };
    class X : public Mid { AsciiString a; vector b; UnknownB4 c; AsciiString d; };

~Mid is inlined into ~X, so its member's cleanup is emitted after X's own members and
numbered after them. State 4 running last is therefore not "a base numbered oddly", it is
positive evidence that 0x08 belongs to an intermediate class rather than to this one --
the numbering distinguishes two hierarchies that produce identical instructions.

The same function needed __declspec(novtable) on both the intermediate and the derived
class. Retail stores exactly one vptr, the root base's restore at the very end; without
novtable MSVC opens the destructor by storing the derived vptr and stores the
intermediate's again before its member. That is the same lever as the two vptr sections
above, applied to a class that is not the most-derived one at runtime.

## A byte-exact conversion can silently break rows in its own translation unit

Converting a body to real C++ changes the whole TU's codegen, and the rows most
exposed are the `gen-funclet` unwind stubs, because their `object-symbol=` is a
compiler-assigned `$L` label with no stable meaning. Landing one conversion
renumbers every label after it, and each orphaned row then fails the gate with
`symbol not found in object`, not with a byte mismatch.

The renumbering is a **constant shift per translation unit**, and that is what
makes the repair mechanical rather than a guess. Measured across seven files
whose gate had gone red: -124 in GameState.cpp, -223 in BattlePlanUpdate.cpp,
-374 in W3DVolumetricShadow.cpp, -710 in LANAPIhandlers.cpp, -1657 in
AIPathfind.cpp, +2457 in fx_particle_system_bulk.cpp, -24566 in W3DModelDraw.cpp.
Take the rows whose new label is unambiguous, read the shift off them, apply it
to the rest, and re-verify each one byte-for-byte; 43 of 67 broken rows came
back that way.

Two traps in the diagnosis:

* Comparing retail bytes against **raw** object bytes proves nothing, because a
  relocated field is zero in the object and resolved in retail. An 8-byte
  funclet is `mov ecx,[ebp-X]; jmp <rel32>`, so four of its eight bytes are the
  relocation. Resolve first, exactly as `compile_function` does, then compare —
  a raw comparison reports every row as unrepairable and sends you to retract
  rows that were only renumbered.
* Because the resolver *searches* symbols.csv for a displacement that
  reproduces retail, a tiny funclet can be "matched" by several different
  labels. Ambiguity there is not evidence of anything; use the TU's shift to
  choose, not the first hit.

What does not come back is a row whose function the source no longer emits at
all — an unreferenced template instantiation, a constructor that became trivial,
or an identity that was wrong to begin with. Retract those rather than adding a
reference or an explicit instantiation to force emission: fitting the source to
the ledger makes the gate green without proving anything about retail.

## The pre-push hook only verifies outgoing sources, so cross-TU rot lands unseen

`verify_pr.sh` byte-verifies the sources a push touches. That is sound for the
pusher's own rows and blind to everyone else's: a conversion that shifts codegen
breaks rows in the same TU that the pusher never re-verifies, and nothing looks
at them again until somebody runs a full gate. Sixty-seven rows across ten files
accumulated this way, and the count grew from 42 to 63 over about an hour of
fleet pushes while the breakage was being diagnosed.

The tell is that the full gate dies on the *first* broken row, so the visible
symptom is one `ValueError` naming one label, and the actual population is
whatever a full sweep finds. Before concluding a red gate is a single bad row,
sweep every row and count: `compile_function` over the whole ledger reports the
unresolvable and the mismatching separately, and they have different causes.


## Widening the clone screen's size window found three more clusters

The first run of the normalised-body screen capped candidates at 600 bytes and
found 20 twins. Raising the cap to 900 found 22 -- and the additions were not
stragglers, they were two whole clusters the window had cut in half: nine 283-byte
ModuleData constructors and six 169-byte preference setters.

An arbitrary bound chosen for speed hid more work than it saved. When a screen
is cheap, run it wide.

## A cloned body can still need per-instance data read from the binary

The six preference setters share one body: format an int into an AsciiString and
store it into the preferences map under a literal key. Only the key differs, and
because a string literal is a DIR32 whose address is copied from the target, the
byte gate passes whatever text you write. The string-ref verifier is what
catches a wrong key.

So the clone was not a pure substitution: each key had to be read out of the
binary first, by disassembling the target and following its pushed addresses
into the data section. All six came back cleanly -- CampaignDifficulty,
MaxDisconnects, MaxPoints, MinPoints, NumPlayers, WaitTime -- and all twenty
literals across the batch verify.

Worth remembering as the general shape: identical code plus differing data is
still clonable, but the data has to come from the target rather than the model.

## Worktree isolation needs the session cwd to be the repo

A thirteen-agent fan-out died instantly with "not in a git repository". The
session's working directory is D:\BFME1 while the repo is D:\Open-BFME-1, and
worktree isolation resolves against the former.

Without worktrees the agents share one checkout, which is safe only because each
one edits a distinct file and the one genuinely shared mutable artifact -- the
deps cache -- is untracked and self-healing. The protection that matters is
re-verifying every claimed match centrally before committing, since a stale
cache could in principle hand an agent a false OK.


## Parallel agents need a central re-verify, and it earned its keep immediately

Thirteen agents each converted one naked function in the shared checkout. Twelve
removed the naked dump from their file and reported a match. Re-running the gate
centrally over all twelve found that two of them did not match.

Both had been instructed to confirm the gate printed OK and that the naked
marker was gone, and both reported doing so. Whatever happened -- a stale deps
cache handing back another agent's object, or simply an over-eager report -- the
failure mode is the one already recorded from my own mistake: the gate answers
"do these bytes match" and cannot, on its own, tell you the answer came from the
source you think it did.

So the rule for any fan-out is that an agent's verdict is a claim, not a result.
Ten landed; the two false positives were reverted and cost nothing, because
nothing was committed on an agent's word alone.

The cheap structural protection is that each agent owns exactly one file. That
makes reverting a bad claim a one-line operation and keeps a wrong answer from
contaminating anything else.


## The byte gate does not catch a naked body wrapped as non-naked

A swarm agent found that removing only the `__declspec(naked)` keyword from a
function whose body is purely `__asm { __emit ... }` still passes the byte
gate: MSVC 7.1 does not force a stack frame around a plain function whose body
is an inline-asm block with no locals, so the emitted bytes are unchanged.
`grep -c "__declspec(naked)"` then reports 0 and `Functions: OK 1/1 matched`
still prints, even though nothing was actually converted -- the naked marker
check I added as a swarm safeguard is necessary but not sufficient on its own;
what actually matters is "no __asm/__emit anywhere in the file", and that is
what the check needs to be, not just the naked keyword.

Confirmed by sweeping the whole tree: this was the only non-naked file, out of
several thousand, still containing __emit. Rejected regardless of the byte
match and reverted.

The underlying disassembly finding is worth keeping even though the
conversion isn't: the retail bytes at this address are 18 back-to-back E9 jmp
instructions to unrelated targets, 17 of them unreachable dead code after the
first. That is not a shape any compiler emits for a real function body -- it
reads like an ILT thunk table or jump-table data captured as if it were code,
and whoever attempts this row next should start from that theory rather than
re-deriving it.

## A ledger's existing status/notes can predate real conversion and be stale

The rejected row's own functions.csv entry already said status=matched with
notes claiming "exact C++ __emit thunk converted from MASM dump" -- before the
swarm ever touched it. Git history showed why: the file was committed already
naked, by the same commit that added the row, with that boilerplate note. A
naked dump trivially matches the byte gate (documented earlier this session),
so "status=matched" on a ledger row is not itself proof a real conversion
happened -- it can be the leftover state from the initial dump commit. Check
what is actually on disk, not just what the ledger claims about it.

## Failed agents can be more valuable than agents that report a match

Five of eight agents in this swarm self-reported matched:false with precise,
independently-verified residuals rather than guessing a fourth build. Two of
those diagnoses are new, real findings, not restatements of known blockers:

- MeshMatDescClass's constructor implies Texture/TextureArray are a small
  ref-counting smart pointer type, not the plain TextureClass* the shared
  header currently declares, based on an eh_vector_constructor_iterator call
  and per-element Release_Ref that only exist for a non-trivial element type.
- DequePartitionCellInitializeMap's ledger pin forces an extern "C" free
  function (cdecl), but the target bytes are thiscall shape. No MSVC 7.1
  calling-convention keyword produces both the pinned plain symbol name and
  thiscall ABI at once -- __thiscall is illegal on free functions (C4234),
  __fastcall decorates the symbol with @N even under extern "C". This is a
  ledger-level conflict, not a source-level one.

Neither of these would have surfaced from a screen; both came from an agent
reading its own compiled .obj's actual symbol and relocation tables rather
than trusting build.py's summary line, after exhausting the build budget
honestly instead of padding a report.


## A recurring EH-bookkeeping scheduling artifact now has a name and four instances

ParticleSystemInfo's copy constructor failed on exactly one residual: retail
stores the this-pointer to its EH-frame stack slot as the very first
instruction after the prologue's initial push, before loading the source
object pointer or the vptr. Every source shape compiled instead defers that
store to immediately before the first call that could throw, a few bytes
later, shifting the whole function's length.

This is not a one-off. The same shape is already on record for addRadar@Player,
getIdealStaticGameDetail@OptionPreferences, and two destructors elsewhere in
this project. Four independent sightings across unrelated functions makes this
a real, recognized residual class -- MSVC 7.1 choosing to schedule the
EH-frame's this-store at the top of the function in some cases and just before
first use in others, for reasons not yet tied to anything expressible in
source. Worth a dedicated screen once enough instances accumulate to look for
what they have in common.

## Not every naked function has a discoverable fix, and that is a legitimate outcome

A 4-agent swarm this tick landed zero conversions -- all four candidates were
diagnosed precisely and reverted cleanly, no exceptions. Two hit the
calling-convention/ledger-ABI conflict already on record (this is now three
occurrences: DequePartitionCellInitializeMap, VectorICoord2D::_M_insert_overflow,
and by the same shape likely more waiting in the pool). One hit a
register-allocation residual. One found a genuinely new structural fact --
MapMetaDataReader has an 8-element array of an unidentified 20-byte "slot
record" type nobody has named in this codebase yet -- and reported that instead
of inventing a plausible-sounding class to paper over it.

The pool of readily-available naked functions at the size/call-count tier this
swarm searched is thinning out: what is left after three swarm runs skews
toward known-hard categories rather than easy wins. Future candidate selection
should either widen further (larger functions, more calls) or specifically hunt
for instances of the already-named blocker classes, since those are at least
diagnosable even when not fixable from a single file.


## Same target address means a clone is a pure rename; a different one means check the calls

Three clones this tick split cleanly along that line. GettingBuiltBehaviorModuleData
and HordeUpdateModuleData share W3DLaserDrawModuleData's exact target address --
ICF folded them onto one body -- so substituting the class name was the whole job
and both matched first build.

DelayedLuaEventUpdate matched the normalised body of PassiveAreaEffectBehavior's
destructor but sits at a different address, and there the clone was not free: the
sole differing byte region in the whole 116 bytes was one call's rel32. Its member
at 0x24 is not the model's list<int>; its destructor is a different instantiation
entirely.

So the address relationship tells you in advance which kind of clone you have.
Same address, rename and go. Different address, the structure is shared but every
call target is an independent question -- diff first and expect to retarget.

The fix also shows when a synthetic name is legitimate to use. The real destructor
here is only pinned under generated names (??1Gen_uw_00013156 and a Gen_dtor
sibling), and declaring a member typed to that existing pin is the same convention
the model file itself already uses for Gen_dtor_00113d40. That is reusing a pin,
not inventing a signature for an unnamed callee.


## When cloning, rename the target class and nothing else

DynamicPortalBehaviour was on record as a clone that did not reproduce from
QueueProductionExitUpdate despite matching its normalised body. That diagnosis
was wrong, and the real cause is worth more than the conversion.

They are ICF-folded onto one address, so the bytes are identical and a rename
should have been the whole job. The failure came from doing the rename with a
blind token substitution, which also renamed the helper class
QueueProductionExitUpdateBase -- whose construct() the constructor calls. That
changed the helper's mangled name, so it no longer resolved to the pinned
symbol, and the call's rel32 came out different.

Renaming only the target class, leaving every helper name untouched, matched on
the first build.

So the clone rule has two halves that pull in opposite directions. Same address
means every call target must stay exactly as it is -- rename the one class the
row names and nothing else. Different address means the shared structure is only
a starting point and call targets are independent questions to re-derive. Getting
these backwards produces exactly the failure logged here, and it looks like an
unfixable codegen difference rather than a self-inflicted one.
