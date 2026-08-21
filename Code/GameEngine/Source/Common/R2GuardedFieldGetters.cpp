// Twenty-three tiny __thiscall accessors that read a pointer out of the object,
// return zero when it is null, and otherwise return ONE field of what it points
// at.  Retail, in the two encodings that occur:
//
//     mov eax,[ecx+<OFF>] / test eax,eax / je zero
//     mov eax,[eax+<FIELD>] / ret            (four-byte result)
//     zero: xor eax,eax / ret
//
//     ... mov al,[eax+<FIELD>] / ret / zero: xor al,al / ret   (one-byte result)
//
// WHAT THE BYTES SHOW.  `this` in ecx and a bare `ret`: __thiscall, no stack
// arguments.  NOTHING IS RELOCATED anywhere in any of the twenty-three bodies --
// every byte is concrete, so the comparison is total.
//
// THE RESULT WIDTH IS SOURCE EVIDENCE, not scheduling.  `mov al,[eax+F]` paired
// with `xor al,al` is a one-byte result and `mov eax,[eax+F]` paired with
// `xor eax,eax` is a four-byte one; the two differ in length and in opcode, so
// the gate separates them and the table below records which is which.  The
// one-byte form is written as bool; a one-byte integer would serve equally and
// the bytes do not choose between them.
//
// THE GUARD IS AN EARLY RETURN.  The two exits land on SEPARATE `ret`s, the
// taken arm falling out past the untaken one, which is what
// `if (p) { return p->f; } return 0;` produces.
//
// THREE MEMBERS READ THE POINTER AT A NEGATIVE DISPLACEMENT off `this`
// (-0x1C twice, -0xE0 once) and all three then read the same field at +0x168.
// A negative displacement cannot be spelled as a member, so those three are
// written the way the same construct is written in BackPointerGuardedDispatch:
// a fixed byte offset back out of the object.  THE BYTES DECIDE THE OFFSET AND
// NOTHING ELSE -- whether the source reached that pointer through a back
// reference, a multiple-inheritance base or something else is not recovered.
//
// SEPARATE FUNCTIONS, NOT ALIASES.  Three pairs are byte-identical
// (0x001BDFF0/0x001BE010, 0x0022A4F0/0x0022CFF0, 0x0063A870/0x00642C80); they
// are distinct rows in the retail image at distinct addresses and each is
// instantiated separately here.
//
// IDENTITY IS NOT RECOVERED.  Every name is address-derived.  The bytes name
// neither the holder, the pointee, nor the field.

#define R2_GUARDED_FIELD_GET( NAME, OFF, FIELD, TYPE )  \
	class NAME##Pointee                                 \
	{                                                   \
	public:                                             \
		char m_leading[ FIELD ];                        \
		TYPE m_field;                                   \
	};                                                  \
	class NAME                                          \
	{                                                   \
	public:                                             \
		char m_leading[ OFF ];                          \
		NAME##Pointee *m_pointee;                       \
		TYPE get();                                     \
	};                                                  \
	TYPE NAME::get()                                    \
	{                                                   \
		if ( m_pointee )                                \
		{                                               \
			return m_pointee->m_field;                  \
		}                                               \
		return 0;                                       \
	}

#define R2_GUARDED_FIELD_GET_HEAD( NAME, FIELD, TYPE )  \
	class NAME##Pointee                                 \
	{                                                   \
	public:                                             \
		char m_leading[ FIELD ];                        \
		TYPE m_field;                                   \
	};                                                  \
	class NAME                                          \
	{                                                   \
	public:                                             \
		NAME##Pointee *m_pointee;                       \
		TYPE get();                                     \
	};                                                  \
	TYPE NAME::get()                                    \
	{                                                   \
		if ( m_pointee )                                \
		{                                               \
			return m_pointee->m_field;                  \
		}                                               \
		return 0;                                       \
	}

#define R2_GUARDED_FIELD_GET_BACK( NAME, BACK, FIELD, TYPE )  \
	class NAME##Pointee                                       \
	{                                                         \
	public:                                                   \
		char m_leading[ FIELD ];                              \
		TYPE m_field;                                         \
	};                                                        \
	class NAME                                                \
	{                                                         \
	public:                                                   \
		TYPE get();                                           \
	};                                                        \
	TYPE NAME::get()                                          \
	{                                                         \
		NAME##Pointee *pointee =                              \
			*(NAME##Pointee **)( (char *)this - BACK );       \
		if ( pointee )                                        \
		{                                                     \
			return pointee->m_field;                          \
		}                                                     \
		return 0;                                             \
	}

R2_GUARDED_FIELD_GET( Rva001BDFF0, 0x204, 0x1CC, int )
R2_GUARDED_FIELD_GET( Rva001BE010, 0x204, 0x1CC, int )
R2_GUARDED_FIELD_GET( Rva001BE3B0, 0x1EC, 0x24, int )
R2_GUARDED_FIELD_GET( Rva001EB140, 0x4, 0xE8, bool )
R2_GUARDED_FIELD_GET( Rva00267FA0, 0x4, 0x118, bool )
R2_GUARDED_FIELD_GET( Rva003BCBF0, 0x28, 0x3C, int )
R2_GUARDED_FIELD_GET( Rva003C6360, 0x4, 0x4C, int )
R2_GUARDED_FIELD_GET( Rva003C6380, 0x4, 0x50, int )
R2_GUARDED_FIELD_GET_HEAD( Rva003D4A50, 0x14, int )
R2_GUARDED_FIELD_GET_HEAD( Rva003D4AA0, 0xC, int )
R2_GUARDED_FIELD_GET( Rva004C1160, 0x8, 0x1C8, int )
R2_GUARDED_FIELD_GET( Rva005C3530, 0x1CC, 0x20, int )
R2_GUARDED_FIELD_GET( Rva0063A850, 0x64, 0x52, bool )
R2_GUARDED_FIELD_GET( Rva0063A870, 0x64, 0x51, bool )
R2_GUARDED_FIELD_GET( Rva0063A8A0, 0x64, 0x54, int )
R2_GUARDED_FIELD_GET( Rva00642C80, 0x64, 0x51, bool )
R2_GUARDED_FIELD_GET( Rva00642CA0, 0x64, 0x50, bool )
R2_GUARDED_FIELD_GET_HEAD( Rva00694900, 0x2C, int )
R2_GUARDED_FIELD_GET_HEAD( Rva00694AA0, 0x41, bool )
R2_GUARDED_FIELD_GET_HEAD( Rva00694AD0, 0x3C, int )

// The three back-reference members.

R2_GUARDED_FIELD_GET_BACK( Rva0022A4F0, 0x1C, 0x168, int )
R2_GUARDED_FIELD_GET_BACK( Rva0022CFF0, 0x1C, 0x168, int )
R2_GUARDED_FIELD_GET_BACK( Rva00234020, 0xE0, 0x168, int )
