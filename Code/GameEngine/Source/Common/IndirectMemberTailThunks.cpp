// Twenty-four tiny __thiscall members that load a pointer held at a fixed
// offset in the object and tail-jump to a __thiscall member of what it points
// at:
//
//     mov ecx,[ecx+<OFFSET>] / jmp <REL32>
//
// WHAT THE BYTES SHOW.  Unlike the add-offset thunks, ecx is REPLACED by a
// dword read out of the object, so the receiver is a stored pointer, not a
// sub-object.  Control leaves through a jmp, so the callee's `ret` returns to
// OUR caller and its stack pop is this function's: a bare `ret` at the callee
// makes both sides __thiscall with no stack arguments.
//
// TWO AXES, BOTH READ DIRECTLY: the REL32 target and the load offset.
// Twenty-four members over twenty-three callees at eight distinct offsets;
// every (callee, offset) pair is distinct.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address; the callee
// pins are address-derived and additive.

#define BFME_POINTER_TAIL_CALLEE( ADDR )                                  \
	class Gen##ADDR                                                       \
	{                                                                     \
	public:                                                               \
		void handle();                                                    \
	};

#define BFME_POINTER_TAIL_THUNK( NAME, CALLEE, OFFSET )                   \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		void invoke();                                                    \
		char m_lead[ OFFSET ];                                            \
		CALLEE *m_receiver;                                               \
	};                                                                    \
	void NAME::invoke()                                                   \
	{                                                                     \
		m_receiver->handle();                                             \
	}

#define BFME_POINTER_TAIL_THUNK_HEAD( NAME, CALLEE )                      \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		void invoke();                                                    \
		CALLEE *m_receiver;                                               \
	};                                                                    \
	void NAME::invoke()                                                   \
	{                                                                     \
		m_receiver->handle();                                             \
	}

BFME_POINTER_TAIL_CALLEE( 000A1490 )
BFME_POINTER_TAIL_CALLEE( 001E1760 )
BFME_POINTER_TAIL_CALLEE( 001E1770 )
BFME_POINTER_TAIL_CALLEE( 001E1780 )
BFME_POINTER_TAIL_CALLEE( 001E1790 )
BFME_POINTER_TAIL_CALLEE( 0041D090 )
BFME_POINTER_TAIL_CALLEE( 004503C0 )
BFME_POINTER_TAIL_CALLEE( 00478C70 )
BFME_POINTER_TAIL_CALLEE( 0055C1C0 )
BFME_POINTER_TAIL_CALLEE( 00662DF0 )
BFME_POINTER_TAIL_CALLEE( 00665D10 )
BFME_POINTER_TAIL_CALLEE( 0074ECD0 )
BFME_POINTER_TAIL_CALLEE( 0074EF50 )
BFME_POINTER_TAIL_CALLEE( 0074F1F0 )
BFME_POINTER_TAIL_CALLEE( 00752F40 )
BFME_POINTER_TAIL_CALLEE( 00765B70 )
BFME_POINTER_TAIL_CALLEE( 00765DC0 )
BFME_POINTER_TAIL_CALLEE( 0080AB50 )
BFME_POINTER_TAIL_CALLEE( 008811D0 )
BFME_POINTER_TAIL_CALLEE( 008FAFD0 )
BFME_POINTER_TAIL_CALLEE( 009A4A30 )
BFME_POINTER_TAIL_CALLEE( 009F1510 )
BFME_POINTER_TAIL_CALLEE( 009F5040 )

BFME_POINTER_TAIL_THUNK( Rva000C3DB0, Gen000A1490, 48 )
BFME_POINTER_TAIL_THUNK( Rva00149E20, Gen001E1770, 4 )
BFME_POINTER_TAIL_THUNK( Rva0014E620, Gen000A1490, 28 )
BFME_POINTER_TAIL_THUNK( Rva0016A960, Gen001E1760, 4 )
BFME_POINTER_TAIL_THUNK( Rva0016A970, Gen001E1780, 4 )
BFME_POINTER_TAIL_THUNK( Rva0016A980, Gen001E1790, 4 )
BFME_POINTER_TAIL_THUNK_HEAD( Rva001B0CA0, Gen0041D090 )
BFME_POINTER_TAIL_THUNK( Rva00450550, Gen004503C0, 12 )
BFME_POINTER_TAIL_THUNK_HEAD( Rva004B5A00, Gen00478C70 )
BFME_POINTER_TAIL_THUNK( Rva0052CC90, Gen0055C1C0, 52 )
BFME_POINTER_TAIL_THUNK( Rva00681A10, Gen00662DF0, 8 )
BFME_POINTER_TAIL_THUNK( Rva00682310, Gen00665D10, 8 )
BFME_POINTER_TAIL_THUNK( Rva0074FF10, Gen0074ECD0, 12 )
BFME_POINTER_TAIL_THUNK( Rva0074FF20, Gen0074EF50, 12 )
BFME_POINTER_TAIL_THUNK( Rva0074FF30, Gen0074F1F0, 12 )
BFME_POINTER_TAIL_THUNK( Rva00753030, Gen00752F40, 4 )
BFME_POINTER_TAIL_THUNK( Rva00767D90, Gen00765B70, 4 )
BFME_POINTER_TAIL_THUNK( Rva00767DA0, Gen00765DC0, 4 )
BFME_POINTER_TAIL_THUNK( Rva008035A0, Gen0080AB50, 24 )
BFME_POINTER_TAIL_THUNK( Rva00880E00, Gen008811D0, 12 )
BFME_POINTER_TAIL_THUNK( Rva008F7360, Gen008FAFD0, 12 )
BFME_POINTER_TAIL_THUNK( Rva009A2560, Gen009A4A30, 12 )
BFME_POINTER_TAIL_THUNK( Rva009EBA30, Gen009F1510, 8 )
BFME_POINTER_TAIL_THUNK( Rva009F2630, Gen009F5040, 12 )
