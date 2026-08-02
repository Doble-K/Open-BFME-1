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
