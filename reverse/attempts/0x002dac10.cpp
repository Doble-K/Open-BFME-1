// ??0Made001E5A20@@QAE@XZ
// partial score=0.95 date=2026-08-25
// Two constructors from reverse/reloc_names.csv, both identity=real.
//
// 0x002DAC10 calls a base constructor through ILT 0x00010D07 and then fills
// four members. The two zeroes share one xor and come out together ahead of
// the two immediates, which is MSVC grouping stores by the register they use;
// in declaration order the fields are +0x58, +0x5C, +0x60, +0x64. The last is
// 0x40490FDB, which is pi as a float, so that member is a Real.
//
// 0x00490420 has no call at all: its base constructor is inline and consists
// of storing the base vftable and pushing this onto a global singly-linked
// list at +0x04. The derived vftable then overwrites the base's, which is the
// ordinary two-vptr-store shape of a constructor with a polymorphic base. The
// flag at +0x0C is written as a byte, so it is a bool.

typedef float Real;

class Made002DF2B0
{
public:
	Made002DF2B0(void);						// ILT 0x00010D07

	virtual void bfmeSlot00(void);

private:
	char m_bfmeTail[0x58 - 0x04];
};

class Made001E5A20 : public Made002DF2B0
{
public:
	Made001E5A20(void);

	virtual void bfmeSlot00(void);

private:
	int m_bfme0058;							// +0x58
	int m_bfme005C;							// +0x5C
	int m_bfme0060;							// +0x60
	Real m_bfme0064;						// +0x64
};

class BfmeLinkedSingleton
{
public:
	BfmeLinkedSingleton(void);

	virtual void bfmeSlot00(void);

	BfmeLinkedSingleton *m_bfmeNext;				// +0x04
};

extern BfmeLinkedSingleton *TheBfmeSingletonHead;			// 0x012F3350

inline BfmeLinkedSingleton::BfmeLinkedSingleton(void)
{
	m_bfmeNext = TheBfmeSingletonHead;

	TheBfmeSingletonHead = this;
}

class Gen_00490420 : public BfmeLinkedSingleton
{
public:
	Gen_00490420(void);

	virtual void bfmeSlot00(void);

private:
	int m_bfme0008;							// +0x08
	bool m_bfme000C;						// +0x0C
};

// ??0Made001E5A20@@QAE@XZ
Made001E5A20::Made001E5A20(void)
{
	m_bfme0058 = 0;
	m_bfme005C = 15;
	m_bfme0060 = 0;
	m_bfme0064 = 3.14159274f;
}

// ??0Gen_00490420@@QAE@XZ
Gen_00490420::Gen_00490420(void)
	: m_bfme0008(0),
	  m_bfme000C(true)
{
}
