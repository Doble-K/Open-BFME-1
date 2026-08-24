// ??0AttackNugget@@QAE@XZ
// partial score=0.9 date=2026-08-24
// cl: /DNDEBUG /MD /EHs-c-

// Retail 0x0059EB00, 74 bytes. reverse/reloc_names.csv names it with
// identity=real, but that name already sits on the 90-byte body at
// 0x001D6CD0, so this row goes in as dup_0059eb00.
//
// One base four bytes wide, its constructor reached through ILT 0x0001B522,
// and this class's vftable pointer straight over the slot at +0x00. Then the
// twelve words from +0x10 to +0x3C -- all zero out of a single xor except
// +0x20, which takes an immediate -1 -- and finally +0x0C, +0x04 and +0x09.
//
// Every store is a body assignment, not an initialiser list. Two things say
// so: +0x04 is the first member declared and would have to come first in a
// list, and a list lets the compiler sort the stores by the value they share,
// which pulls all eleven zeros together and pushes the -1 and the vftable
// pointer past them. Written as statements they keep source order, which is
// the order retail has.

typedef int Int;

class BfmeAttackNuggetBase
{
public:
	BfmeAttackNuggetBase();						// ILT 0x0001B522

	virtual void bfmeNuggetSlot(void) = 0;
};

class AttackNugget : public BfmeAttackNuggetBase
{
public:
	AttackNugget();

	virtual void bfmeNuggetSlot(void) { }

	Int m_bfme0004;							// +0x04
	char m_bfme0008;						// +0x08
	char m_bfme0009;						// +0x09
	char m_bfme000A[2];
	Int m_bfme000C;							// +0x0C
	Int m_bfme0010;						// +0x10
	Int m_bfme0014;						// +0x14
	Int m_bfme0018;						// +0x18
	Int m_bfme001C;						// +0x1C
	Int m_bfme0020;						// +0x20
	Int m_bfme0024;						// +0x24
	Int m_bfme0028;						// +0x28
	Int m_bfme002C;						// +0x2C
	Int m_bfme0030;						// +0x30
	Int m_bfme0034;						// +0x34
	Int m_bfme0038;						// +0x38
	Int m_bfme003C;						// +0x3C
};

// the constructor
AttackNugget::AttackNugget()
{
	m_bfme0010 = 0;
	m_bfme0014 = 0;
	m_bfme0018 = 0;
	m_bfme001C = 0;
	m_bfme0020 = -1;
	m_bfme0024 = 0;
	m_bfme0028 = 0;
	m_bfme002C = 0;
	m_bfme0030 = 0;
	m_bfme0034 = 0;
	m_bfme0038 = 0;
	m_bfme003C = 0;
	m_bfme000C = 0;
	m_bfme0004 = 6;
	m_bfme0009 = 1;
}
