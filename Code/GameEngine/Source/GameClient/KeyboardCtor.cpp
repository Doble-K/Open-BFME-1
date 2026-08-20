// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: Keyboard::Keyboard at retail 0x005A3AC0 (69B).
//
// Structure, unchanged from the two earlier attempts: SubsystemInterface is
// eight bytes (vptr plus the AsciiString its constructor at 0x009A1A30 writes
// at +0x04), Keyboard is 0xE1C, and the write order is the three dwords at
// +0x0C/+0x10/+0x14, a 0x800 clear at +0x18, the word at +0x08 and byte at
// +0x0A, a 0x600 clear at +0x818, and the dword at +0xE18 last.
//
// THE RECORDED BLOCKER -- "xor eax,eax for the rep-stos fill is hoisted beside
// xor edx,edx where retail materialises it at its use; the two zeros are one
// CSE'd constant split by the allocator" -- IS REFUTED.  Nothing about the
// CLEAR reaches it, which is why memset, a dword store loop and value-
// initialising a POD sub-object all behaved identically: the lever is on the
// SCALAR side.  Retail's vftable store sits BEFORE the register-store group,
// which is the vptr-FIRST case, and its recipe moves the fill zero on its own:
// __declspec(novtable) to suppress the compiler's own vptr store, the vftable
// written by hand at retail's position, and the scalar zeros written through
// volatile lvalues.  Serialising the scalars leaves the fill's zero nothing to
// group with, so MSVC materialises it at the `lea` exactly as retail does.
//
// ONE REFINEMENT TO THAT RECORDED RECIPE, worth inheriting: "EVERY store
// volatile" is one store pair too many here.  The word at +0x08 and byte at
// +0x0A must be PLAIN.  Retail hoists the second clear's
// `lea edi,[esi+0x818]` ABOVE that pair; a volatile pair pins them ahead of
// the lea and costs the last two instructions.  Everything else stays
// volatile.

#include <string.h>

class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();
	void *m_name;
	SubsystemInterface();
};

extern "C" char Keyboard_vtbl;

class __declspec(novtable) Keyboard : public SubsystemInterface
{
public:
	unsigned short m_modifiers;
	unsigned char  m_shift2Key;
	char           m_pad0b;
	int            m_inputFrame;
	int            m_shiftExKey;
	int            m_shiftExCount;
	int            m_keys[0x200];
	int            m_keyStatus[0x180];
	int            m_tail;

	Keyboard();
};

Keyboard::Keyboard()
{
	*reinterpret_cast<char *volatile *>( this ) = &Keyboard_vtbl;
	*reinterpret_cast<int volatile *>( &m_inputFrame ) = 0;
	*reinterpret_cast<int volatile *>( &m_shiftExKey ) = 0;
	*reinterpret_cast<int volatile *>( &m_shiftExCount ) = 0;
	memset( m_keys, 0, sizeof( m_keys ) );
	m_modifiers = 0;
	m_shift2Key = 0;
	memset( m_keyStatus, 0, sizeof( m_keyStatus ) );
	*reinterpret_cast<int volatile *>( &m_tail ) = 0;
}
