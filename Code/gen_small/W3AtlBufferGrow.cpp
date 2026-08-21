// cl: /DNDEBUG /MD /EHs-c-
// Open-BFME-1: the out-of-line growth routine the two 0x80-byte stack buffers in
// U3_arena_alloc.cpp tail into. It has to live in its own translation unit --
// putting it beside its callers inlines it, and retail's `call 0x0005CBD0` from
// both reserve bodies proves it stayed an opaque declaration there.
//
// The body asks the CRT for the requested size through `ff 15 [__imp__malloc]`,
// the dllimport form the real vendored <stdlib.h> emits under /MD, and on
// failure pushes E_OUTOFMEMORY into the ATL-style throw helper reached via the
// low-RVA ILT thunk at 0x00019ACE (real body 0x0005BA40, which tails into
// _CxxThrowException). The store of the new pointer is on the join path, not
// duplicated into the failure arm -- the failure arm simply falls into it, which
// is what a noreturn helper lets the compiler emit.
//
// Identity is address-derived.

#include <stdlib.h>

typedef unsigned int UnsignedInt;
typedef long HRESULT;

#define W3_E_OUTOFMEMORY ((HRESULT)0x8007000EL)

extern "C" __declspec(noreturn) void __stdcall W3AtlThrow(HRESULT hr);

class Rva0005CBD0Buffer
{
public:
	void grow(UnsignedInt size);

	char *m_cursor;										///< retail this+0x00
	char m_buffer[0x80];								///< retail this+0x04
};

void Rva0005CBD0Buffer::grow(UnsignedInt size)
{
	char *block = (char *)malloc(size);

	if (block == 0)
	{
		W3AtlThrow(W3_E_OUTOFMEMORY);
	}

	m_cursor = block;
}
