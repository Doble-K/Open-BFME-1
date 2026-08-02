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

## BFME's WW3DFormat is D3DFORMAT, and that is why the texture pipeline will not scan

`locate.py` places nothing from `texture.cpp` or `textureloader.cpp` -- 0
located, 53 unlocated -- and `anchor_by_string.py` finds no anchors in either,
or in `ddsfile.cpp`. The reason is not that the bodies were rewritten. It is
that Zero Hour's `WW3DFormat` is a dense enum numbered from zero with its own
ordering, and BFME replaced it with Direct3D's own enumeration: retail's
`Get_Bits_Per_Pixel` (0x0090C400, matched) switches on 20 through 30, 40, 41, 50
through 52 and the four-character codes 'DXT1' through 'DXT5', which are
`D3DFMT_` values exactly. Every format switch in the ported sources is therefore
built on the wrong numbers and cannot byte-match however faithfully it was
ported.

Zero Hour's nearest equivalent is `Get_Bytes_Per_Pixel`, which cannot express
DXT1 at half a byte per pixel; BFME moved to bits.

`ww3dformat.h` still carries the Zero Hour numbering and other matched files
depend on those constants, so `ww3dformat_bits.cpp` declares the retail values
locally rather than changing the header. Anything new in the texture pipeline
needs the retail numbering.

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

## The RenderObjClass vtable is still five slots long above slot 96

The slot-40 fix corrected slots 40 through 47. There is a second divergence
further down, and it is now measured rather than suspected:

- slot 96 is right. `Animatable3DObjClass::Render` matches, and it reaches
  `Is_Not_Hidden_At_All` as `call [eax+0x180]`.
- slot 133 is five too high. Writing the two-argument
  `Simple_Evaluate_Bone` produced a body identical to retail except for one
  displacement: it forwards to the three-argument overload as
  `call [edx+0x228]` where retail has `call [edx+0x214]` -- 138 against 133.

So the headers carry five virtuals that retail does not, somewhere between slots
97 and 132. Retail's own layout in that range, read off the
`Animatable3DObjClass` vtable at 0x0113F148, is: 97 unnamed, 98 `Set_Visible`,
99..110 the Is_/Set_ flag pairs through `Set_Additive`, 111..118 the eight
`_bfme_ro_flag*` placeholders, 119 `Get_Collision_Type`, 120
`Set_Collision_Type`, 121 `Is_Complete`, 122 `Is_In_Scene`, 123
`Get_Native_Screen_Size`, 124 `Set_Native_Screen_Size`, 125 `Create_Decal`, 126
and 127 unnamed, 128 `Update_Cached_Bounding_Volumes`, 129
`Update_Sub_Object_Bits`, then Animatable3DObjClass's own five: 130
`Set_Animation_Frame_Rate_Multiplier`, 131 `Peek_Animation_And_Info`, 132
`Is_Animation_Complete`, 133 and 134 the two `Simple_Evaluate_Bone` overloads.
The vtable is 136 slots.

Anything that calls a slot above 96 through a render object is blocked on this.
The cheapest way to find the five is a probe translation unit that includes the
real headers and calls a handful of virtuals, then reading the displacements out
of the object file -- one compile answers it, where guessing costs a build each.

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
