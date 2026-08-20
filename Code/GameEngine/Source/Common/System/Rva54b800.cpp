// cl: /DNDEBUG /MD /EHsc

// The 16-byte body at retail 0x0054B800. IDENTITY IS NOT RECOVERED -- no named
// caller reaches it, so the name is an address-derived placeholder -- but the
// SHAPE is settled. The `mov [esp], esp` at +8 is not reachable from any C++
// spelling of `&local`: MSVC 7.1 always materialises the address of an
// address-taken local into a register at the top of the function (`lea eax,
// [esp]`), and thirteen spellings across six ideas -- volatile local, split
// declaration, cast lvalue, array decay, self-pointing struct, indirect pointer
// variable, reference, __forceinline helper, memset init -- all reproduce that
// same hoisted lea. What does produce it is MSVC inline assembly naming the
// local directly: `__asm mov stackPtr, esp` assembles to `mov DWORD PTR
// stackPtr$[esp], esp`, which is 89 24 24 exactly because the slot sits at
// displacement zero.
//
// That also explains the shape of the evidence: this body occurs ~44 times over
// .text as an identical 16-byte copy, because MSVC 7.1 refuses to inline a
// function containing inline assembly, so a small helper in a widely included
// header lands out of line once per translation unit.

void *rva54b800( void )
{
	void *stackPtr = 0;

	__asm mov stackPtr, esp

	return stackPtr;
}

// ---------------------------------------------------------------------------
// THE OTHER TWO HELPERS OF THE SAME TRIO.  The out-of-line copies of the body
// above do not stand alone: over and over, at a fixed 0x20 stride, they sit
// between two more inline-asm one-liners.  At 0x0054B6E0/0x0054B700/0x0054B720,
// again at 0x0054B760/0x0054B780/0x0054B7A0, and so on through six consecutive
// slots in that TU, the layout is
//
//     +0x00  18 bytes  push ecx / mov [esp],0 / rdtsc      / mov [esp],eax /
//                      mov eax,[esp] / pop ecx / ret
//     +0x20  16 bytes  the `mov [esp],esp` body above
//     +0x40  16 bytes  push ecx / mov [esp],0 / mov [esp],ebp /
//                      mov eax,[esp] / pop ecx / ret
//
// -- three helpers emitted together, once per translation unit, for the same
// reason: each contains inline assembly, so MSVC 7.1 will not inline it, and a
// header that defines all three lands all three out of line in every TU that
// includes it.  Corpus-wide the counts are 32, 44 and 25.
//
// Neither of the two added here has a C++ spelling at all.  `rdtsc` is not
// expressible outside `__asm` in VC7.1 (no intrinsic; `__rdtsc` arrives with
// VC8), and reading `ebp` as a value is not expressible in C++ in any compiler.
// So there is no lift question to answer for them the way there was for the
// stack-pointer body: inline assembly is the only thing the original could have
// been.  The dead `mov [esp],0` in front of each is the same artefact the file
// documents above -- the local's zero-initialiser, which survives /O2 only
// because an `__asm` block follows it and the optimiser stops tracking the
// slot.
//
// Both reproduce on the first spelling, and four spellings each (block form,
// statement form, braces on one line, signed and unsigned return types) all
// assemble to the identical bytes, so the shape is not sensitive to how the
// asm is written.
//
// IDENTITY IS NOT RECOVERED for either.  No named caller reaches them and no
// string or RTTI descriptor in the image names them, so both names are
// address-derived placeholders exactly like `rva54b800`.  A profiler or
// stack-walker header is the obvious home for the trio, but "obvious" is not
// evidence and no such name survives in the image.

unsigned int rva61ae0( void )
{
	unsigned int cycles = 0;

	__asm
	{
		rdtsc
		mov cycles, eax
	}

	return cycles;
}

void *rva61b20( void )
{
	void *framePtr = 0;

	__asm mov framePtr, ebp

	return framePtr;
}
