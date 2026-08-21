// Twelve rows over 0x00832800-0x00834B60, in two shapes that share one callee
// signature.  Every one of them is a __thiscall member that never reads ecx and
// returns an eight-byte object through the hidden return-value pointer at
// [esp+4]; all twelve end in `ret 0x20`, so the argument list is exactly seven
// dwords wide.
//
// THE ARGUMENT LAYOUT IS READ OFF THE PUSHES, not assumed.  In the 47-byte
// shape the callee receives, right to left: a literal 0, the three trailing
// argument dwords BY VALUE, `lea` of the argument at +0x10, `lea` of the
// argument at +8, and the caller's own return slot.  Two `lea`s of argument
// slots are two by-value parameters passed on BY CONST REFERENCE -- a reference
// parameter would already be a pointer and would be re-pushed, not lea'd -- and
// the first of them starts at +8 while the second starts at +0x10, which is
// what fixes the leading parameter at EIGHT bytes wide rather than four.  That
// leaves 2 + 2 + 3 = seven dwords, and the first `lea` proves there is no
// unused trailing argument: the three by-value dwords are the last three.
//
// The caller's return slot being handed to the callee as ITS return slot is why
// the wrapper is only 47 bytes: the result is built straight into the caller's
// storage and `mov eax,esi` just hands the pointer back.
//
// THE 83-BYTE SHAPE (0x008330E0, 0x00834580) is the same call with a local
// eight-byte temporary in place of the last argument dword and a check after
// it: the fifth argument is a pointer whose byte 0 is tested against 4, and
// when that bit is CLEAR the first dword of the temporary is stored through the
// sixth argument.  The 0x10 of locals is what says the temporary is eight bytes
// and not four -- a four-byte temporary next to the eight-byte return temporary
// compiles to `sub esp,8` and puts the value in a different slot.  The result
// is copied out at the end rather than built in place, because the check sits
// between the call and the return.
//
// TEN CLASSES, NOT ONE.  Each row calls a DIFFERENT callee, always the body
// that begins 0x30 bytes after the row itself, and those callees are ten
// distinct unnamed dumps; ten different callees mean ten different classes.
// The two 83-byte rows are the evidence for pairing rather than separating:
// 0x008330E0 calls the same 0x00832830 as 0x00832800, and 0x00834580 calls the
// same 0x00833C80 as 0x00833C50, so those two classes publish both members and
// the other eight publish one.  Identity is not recovered; every name here is
// derived from its callee's address, and the callees are pinned by that name.

struct U2PutIter
{
	void *m_first;
	void *m_second;
	U2PutIter();
};

struct U2PutFlags
{
	int m_a;
	int m_b;
};

struct U2PutState
{
	void *m_first;
	void *m_second;
};

struct U2PutSink
{
	char m_flags;
};

#define U2_PUT_FACET( NAME )                                                   \
	extern U2PutIter NAME##_do(const U2PutIter &s, const U2PutFlags &f,        \
	                           int width, void *from, void *to, int mode);     \
	struct NAME                                                                \
	{                                                                          \
		U2PutIter put(U2PutIter s, U2PutFlags f, int width,                    \
		              void *from, void *to) const;                             \
	};                                                                         \
	U2PutIter NAME::put(U2PutIter s, U2PutFlags f, int width,                  \
	                    void *from, void *to) const                            \
	{                                                                          \
		return NAME##_do(s, f, width, from, to, 0);                            \
	}

#define U2_PUT_FACET_CHECKED( NAME )                                           \
	U2PutIter NAME::putChecked(U2PutIter s, U2PutFlags f, int width,           \
	                           U2PutSink *sink, void **out) const              \
	{                                                                          \
		U2PutState tmp;                                                        \
		U2PutIter r = NAME##_do(s, f, width, sink, &tmp, 0);                    \
		if ((sink->m_flags & 4) == 0)                                          \
			*out = tmp.m_first;                                                \
		return r;                                                              \
	}

// The two classes that publish both members declare them together.
extern U2PutIter U2Put00832830_do(const U2PutIter &s, const U2PutFlags &f,
                                  int width, void *from, void *to, int mode);
struct U2Put00832830
{
	U2PutIter put(U2PutIter s, U2PutFlags f, int width, void *from, void *to) const;
	U2PutIter putChecked(U2PutIter s, U2PutFlags f, int width,
	                     U2PutSink *sink, void **out) const;
};
U2PutIter U2Put00832830::put(U2PutIter s, U2PutFlags f, int width,
                             void *from, void *to) const
{
	return U2Put00832830_do(s, f, width, from, to, 0);
}
U2_PUT_FACET_CHECKED( U2Put00832830 )

extern U2PutIter U2Put00833C80_do(const U2PutIter &s, const U2PutFlags &f,
                                  int width, void *from, void *to, int mode);
struct U2Put00833C80
{
	U2PutIter put(U2PutIter s, U2PutFlags f, int width, void *from, void *to) const;
	U2PutIter putChecked(U2PutIter s, U2PutFlags f, int width,
	                     U2PutSink *sink, void **out) const;
};
U2PutIter U2Put00833C80::put(U2PutIter s, U2PutFlags f, int width,
                             void *from, void *to) const
{
	return U2Put00833C80_do(s, f, width, from, to, 0);
}
U2_PUT_FACET_CHECKED( U2Put00833C80 )

U2_PUT_FACET( U2Put00832DB0 )
U2_PUT_FACET( U2Put00833170 )
U2_PUT_FACET( U2Put00833430 )
U2_PUT_FACET( U2Put008336F0 )
U2_PUT_FACET( U2Put00834250 )
U2_PUT_FACET( U2Put00834610 )
U2_PUT_FACET( U2Put008348D0 )
U2_PUT_FACET( U2Put00834B90 )

// THREE MORE, ONE SHAPE WIDER (0x0083BAE0, 0x0083C0C0, 0x0083C550).  Same
// forwarder, 50 bytes, `ret 0x1C`: the callee gets the caller's return slot,
// then FOUR argument dwords BY VALUE -- no `lea` anywhere, so nothing here is
// passed by reference -- and finally an eight-byte value the wrapper reloads
// through the x87 stack (`fld qword [esp+0x18] / sub esp,8 / fstp [esp]`).
// An x87 load/store pair for an argument that is only being forwarded is what a
// `double` parameter compiles to; an eight-byte integer or struct would have
// been copied as two dwords like everything else in this file.  That fixes the
// argument list at 2 + 2 + 8 bytes after the return slot, which is the 7 dwords
// `ret 0x1C` pops.  Three rows, three distinct callees, three classes.

#define U2_PUT_DOUBLE_FACET( NAME )                                            \
	extern U2PutIter NAME##_do(U2PutIter s, void *from, void *to, double v);   \
	struct NAME                                                                \
	{                                                                          \
		U2PutIter put(U2PutIter s, void *from, void *to, double v) const;      \
	};                                                                         \
	U2PutIter NAME::put(U2PutIter s, void *from, void *to, double v) const     \
	{                                                                          \
		return NAME##_do(s, from, to, v);                                      \
	}

U2_PUT_DOUBLE_FACET( U2Put0083BB20 )
U2_PUT_DOUBLE_FACET( U2Put0083C100 )
U2_PUT_DOUBLE_FACET( U2Put0083C590 )
