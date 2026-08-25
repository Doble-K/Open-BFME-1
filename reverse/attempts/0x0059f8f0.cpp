// ??0S4Parsed0059F980@@QAE@XZ
// partial score=0.9 date=2026-08-25
// Retail 0x0059F8F0, 69 bytes, from reverse/reloc_names.csv with identity=real.
//
// A constructor over the same four-byte base AttackNugget uses, reached
// through the same thunk. Thirteen members, and the emission order is entirely
// MSVC grouping stores by the register that holds their value: six zeroes out
// of eax, three byte zeroes out of al, then the vftable pointer, then the two
// thirties out of ecx, and finally the two lone immediates. In declaration
// order the fields run +0x04, +0x09, +0x0C, +0x10, +0x14, +0x28, +0x2C, +0x30,
// +0x34, +0x38, +0x3C, +0x3D, +0x3E.
//
// The three bytes at the end and the one at +0x09 are written with al and an
// immediate byte respectively, so they are bools; +0x2C takes -1 as a full
// word.

class BfmeAttackNuggetBase
{
public:
	BfmeAttackNuggetBase(void);					// ILT 0x0001B522

	virtual void bfmeNuggetSlot(void) = 0;
};

class S4Parsed0059F980 : public BfmeAttackNuggetBase
{
public:
	S4Parsed0059F980(void);

	virtual void bfmeNuggetSlot(void) { }

private:
	int m_bfme0004;							// +0x04
	char m_bfme0008;						// +0x08
	bool m_bfme0009;						// +0x09
	char m_bfme000A[2];
	int m_bfme000C;							// +0x0C
	int m_bfme0010;							// +0x10
	int m_bfme0014;							// +0x14
	char m_bfme0018[0x28 - 0x18];
	int m_bfme0028;							// +0x28
	int m_bfme002C;							// +0x2C
	int m_bfme0030;							// +0x30
	int m_bfme0034;							// +0x34
	int m_bfme0038;							// +0x38
	bool m_bfme003C;						// +0x3C
	bool m_bfme003D;						// +0x3D
	bool m_bfme003E;						// +0x3E
};

// ??0S4Parsed0059F980@@QAE@XZ
S4Parsed0059F980::S4Parsed0059F980(void)
	: m_bfme0004(30),
	  m_bfme0009(true),
	  m_bfme000C(0),
	  m_bfme0010(0),
	  m_bfme0014(30),
	  m_bfme0028(0),
	  m_bfme002C(-1),
	  m_bfme0030(0),
	  m_bfme0034(0),
	  m_bfme0038(0),
	  m_bfme003C(false),
	  m_bfme003D(false),
	  m_bfme003E(false)
{
}
