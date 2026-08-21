// 26 identical 18-byte __thiscall constructors:
//
//     push esi / mov esi,ecx / call <REL32> / mov dword ptr [esi],<DIR32>
//     mov eax,esi / pop esi / ret
//
// WHAT THE BYTES SHOW.  ecx is saved once, a single subobject constructor runs
// on the SAME pointer (no `lea`, so the base sits at offset 0), the vptr slot at
// offset 0 is then overwritten with this class's own vftable, and `this` is
// returned in eax.  A base at offset 0 whose vptr slot is rewritten afterwards
// means the BASE is already polymorphic; the derived class adds no data members
// of its own -- any member initialiser would appear as a further store here, and
// none does.
//
// TWO AXES, both read directly: the REL32 base constructor and the DIR32
// vftable.  Thirteen distinct base constructors are shared across the 26
// members, so each base class below is declared once and the pin is reused.
// The vftable operand is compiler-generated per class and needs no pin.
//
// Eight of the twenty-six call their base through a low-RVA incremental-link
// thunk; the pins name the BODY, which is what build_call_thunks() expands.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address.

#define BFME_VPTR_BASE( NAME )                                            \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		NAME();                                                           \
		virtual void handle();                                            \
	};

#define BFME_VPTR_DERIVED( NAME, BASE )                                   \
	class NAME : public BASE                                              \
	{                                                                     \
	public:                                                               \
		NAME();                                                           \
		virtual void handle();                                            \
	};                                                                    \
	NAME::NAME()                                                          \
	{                                                                     \
	}

BFME_VPTR_BASE( GenBase00101D50 )
BFME_VPTR_BASE( GenBase00101E20 )
BFME_VPTR_BASE( GenBase00138960 )
BFME_VPTR_BASE( GenBase002DF2B0 )
BFME_VPTR_BASE( GenBase003BB1E0 )
BFME_VPTR_BASE( GenBase0046E5E0 )
BFME_VPTR_BASE( GenBase00479230 )
BFME_VPTR_BASE( GenBase004B2C80 )
BFME_VPTR_BASE( GenBase008AD3F0 )
BFME_VPTR_BASE( GenBase00944940 )
BFME_VPTR_BASE( GenBase009A1A30 )
BFME_VPTR_BASE( GenBase009CA9E0 )
BFME_VPTR_BASE( GenBase009EB7D0 )

BFME_VPTR_DERIVED( Rva0006B0D0, GenBase009A1A30 )
BFME_VPTR_DERIVED( Rva000C3FF0, GenBase009A1A30 )
BFME_VPTR_DERIVED( Rva002DCE70, GenBase002DF2B0 )
BFME_VPTR_DERIVED( Rva002ED840, GenBase009A1A30 )
BFME_VPTR_DERIVED( Rva00322090, GenBase009A1A30 )
BFME_VPTR_DERIVED( Rva00324490, GenBase009A1A30 )
BFME_VPTR_DERIVED( Rva003BB2E0, GenBase003BB1E0 )
BFME_VPTR_DERIVED( Rva003BB310, GenBase003BB1E0 )
BFME_VPTR_DERIVED( Rva0048CD10, GenBase009A1A30 )
BFME_VPTR_DERIVED( Rva005166B0, GenBase00479230 )
BFME_VPTR_DERIVED( Rva0063FCF0, GenBase009A1A30 )
BFME_VPTR_DERIVED( Rva006709F0, GenBase004B2C80 )
BFME_VPTR_DERIVED( Rva00670A10, GenBase004B2C80 )
BFME_VPTR_DERIVED( Rva006BA440, GenBase00101E20 )
BFME_VPTR_DERIVED( Rva006BA470, GenBase00101D50 )
BFME_VPTR_DERIVED( Rva006C0570, GenBase00138960 )
BFME_VPTR_DERIVED( Rva006FCAD0, GenBase00944940 )
BFME_VPTR_DERIVED( Rva00711B00, GenBase00944940 )
BFME_VPTR_DERIVED( Rva00789650, GenBase00944940 )
BFME_VPTR_DERIVED( Rva0078ABB0, GenBase0046E5E0 )
BFME_VPTR_DERIVED( Rva0079D030, GenBase00944940 )
BFME_VPTR_DERIVED( Rva0081C500, GenBase009A1A30 )
BFME_VPTR_DERIVED( Rva008BD2B0, GenBase008AD3F0 )
BFME_VPTR_DERIVED( Rva008FEB20, GenBase009EB7D0 )
BFME_VPTR_DERIVED( Rva00972880, GenBase009EB7D0 )
BFME_VPTR_DERIVED( Rva009CC350, GenBase009CA9E0 )
