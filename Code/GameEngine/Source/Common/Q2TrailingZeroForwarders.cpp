// Seven 31-byte __cdecl forwarders that pass their four arguments straight
// through to a five-argument __cdecl callee and supply 0 for the fifth:
//
//   mov eax,[esp+0x10] / mov ecx,[esp+0xC] / mov edx,[esp+8]
//   push 0 / push eax / mov eax,[esp+0xC] / push ecx / push edx / push eax
//   call <REL32> / add esp,0x14 / ret
//
// WHAT THE BYTES SHOW.  No `ret n` and no use of ecx on entry, so both this
// function and its callee are __cdecl free functions -- the caller's own
// `add esp,0x14` cleans all five pushed dwords.  Counting the pushes against
// the frame gives the argument count on both sides: four in, five out.  The
// three loads before the first push are [esp+8], [esp+0xC] and [esp+0x10],
// which are arguments two, three and four; argument one is re-loaded at
// [esp+0xC] AFTER two pushes have moved esp, which is the same slot.  So the
// pushed order is (a0, a1, a2, a3, 0) and the appended constant is last.
//
// ONE AXIS: the callee.  27 of the 31 bytes are concrete; only the call
// displacement is resolved, from an address-derived pin.
//
// WHAT THE BYTES DO NOT DECIDE.  Whether the trailing 0 is a null pointer, an
// int, or an enumerator -- all push as `6a 00`.  Whether the callee returns
// anything: nothing touches eax after the call, and `return f(...);` for an
// int-returning callee would compile identically, so void is the weaker
// reading and is what is written.  The four argument types are pointers here
// only because every 4-byte type pushes the same way.  Nothing says this is a
// default-argument wrapper rather than a hand-written one.
//
// IDENTITY IS NOT RECOVERED.  Both the forwarders and the callees are named
// for addresses; the callee names are pinned at the body each REL32 resolves
// through.

#define Q2_TRAILING_ZERO_CALLEE( BODY )                                   \
	void Gen##BODY( void *a0, void *a1, void *a2, void *a3, void *a4 );

#define Q2_TRAILING_ZERO_FORWARDER( NAME, CALLEE )                        \
	void NAME( void *a0, void *a1, void *a2, void *a3 )                   \
	{                                                                     \
		CALLEE( a0, a1, a2, a3, 0 );                                      \
	}

Q2_TRAILING_ZERO_CALLEE( 00069DF0 )
Q2_TRAILING_ZERO_CALLEE( 00069E60 )
Q2_TRAILING_ZERO_CALLEE( 002DFFD0 )
Q2_TRAILING_ZERO_CALLEE( 002E7EE0 )
Q2_TRAILING_ZERO_CALLEE( 004371E0 )
Q2_TRAILING_ZERO_CALLEE( 00437260 )
Q2_TRAILING_ZERO_CALLEE( 00473A40 )

Q2_TRAILING_ZERO_FORWARDER( Rva00069FB0, Gen00069DF0 )
Q2_TRAILING_ZERO_FORWARDER( Rva0006A030, Gen00069E60 )
Q2_TRAILING_ZERO_FORWARDER( Rva002E0530, Gen002DFFD0 )
Q2_TRAILING_ZERO_FORWARDER( Rva002E8F90, Gen002E7EE0 )
Q2_TRAILING_ZERO_FORWARDER( Rva004378C0, Gen004371E0 )
Q2_TRAILING_ZERO_FORWARDER( Rva004378F0, Gen00437260 )
Q2_TRAILING_ZERO_FORWARDER( Rva00474060, Gen00473A40 )
