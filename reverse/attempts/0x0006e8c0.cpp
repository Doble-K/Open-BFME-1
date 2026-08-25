// ?bfmeUpdateRatio@Gen_0006e8c0@@QAEXXZ
// partial score=0.95 date=2026-08-25
// cl: /DNDEBUG /MD /EHs-c- /Os
// Retail 0x0006E8C0, 59 bytes, which the ledger had in three pieces: the
// division and first test, an eight-byte arm claimed as an alias of
// DX8TextureCategoryClass::Clear_Render_List, and a byte-dump row for the
// rest.
//
// fild followed by fidiv means both operands are integer members -- the
// quotient is formed in the x87 stack and never round-trips through memory as
// an int. The result is stored at +0x38 with a non-popping fst before either
// comparison, so the assignment comes first in the source and the clamps
// overwrite it.
//
// Both bounds are compared with fcom against memory, so they are named
// constants rather than literals; a literal zero would come out as fldz. The
// clamped values themselves are stored as plain integer moves of their bit
// patterns, which is what MSVC does for a float constant assigned to memory.
//
// The two clamp arms pop with fstp st(0) and store the constant; the in-range
// arm pops with the store itself.

typedef float Real;

extern const Real TheBfmeRatioLow;					// 0x01075350
extern const Real TheBfmeRatioHigh;					// 0x01075334

class Gen_0006e8c0
{
public:
	void bfmeUpdateRatio(void);

private:
	char m_bfmeHead[0x30];
	int m_bfmeDone;							// +0x30
	int m_bfmeTotal;						// +0x34
	Real m_bfmeRatio;						// +0x38
};

// ?bfmeUpdateRatio@Gen_0006e8c0@@QAEXXZ
void Gen_0006e8c0::bfmeUpdateRatio(void)
{
	Real value = (Real)m_bfmeDone / m_bfmeTotal;

	m_bfmeRatio = value;

	if (value < TheBfmeRatioLow)
		m_bfmeRatio = 0.0f;
	else if (value > TheBfmeRatioHigh)
		m_bfmeRatio = 1.0f;
	else
		m_bfmeRatio = value;
}
