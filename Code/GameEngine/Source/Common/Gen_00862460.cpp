// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: the 90-byte argument forwarder at 0x00862460, address-derived
// name. Converted out of Code/gen_asm/d_00861370.asm.
//
// IDENTITY IS NOT ASSERTED. The whole body is one __cdecl call: thirteen
// incoming dwords are spread across a twenty-one dword argument list, with a
// leading literal 3 and eight zero slots, and the caller cleans 0x54 bytes.
// The interleaved mov/push shuffle is entirely MSVC 7.1 /O2 codegen for
// forwarding stack parameters; it reproduced on the first compile.
//
// Relocation note: the call at 0x008624B1 is a DIRECT rel32 to 0x00861ED0
// (no ILT thunk). That body is still an unconverted gen_asm dump, and its
// ledger name `?d_00861ed0@@YAXXZ` mangles a zero-argument signature, so it
// cannot be spelled at a 21-argument call site. One additive address-derived
// pin with the right arity, `?g_00861ed0@@YAX<21x H>@Z`, was all it took --
// the callee did not have to be converted or identified first.

void g_00861ed0(int, int, int, int, int, int, int, int, int, int, int,
		int, int, int, int, int, int, int, int, int, int);

void gen_00862460(int a1, int a2, int a3, int a4, int a5, int a6, int a7,
		int a8, int a9, int a10, int a11, int a12, int a13)
{
	g_00861ed0(3, a1, a2, 0, 0, a5, 0, 0, 0, 0, 0,
		a3, a4, a6, a7, a8, a9, a10, a11, a12, a13);
}
