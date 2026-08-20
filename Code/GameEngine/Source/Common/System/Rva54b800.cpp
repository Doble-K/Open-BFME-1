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
