// ?testSetAndClear@BitFlags116TestSetAndClearShim@@QBE_NABV?$BitFlags@$0HE@@@0@Z
// partial score=0.8 date=2026-08-25
// Retail 0x000E9910, 230 bytes: the target of the BitFlags testSetAndClear
// incremental-link thunk.
//
// The mask is six dwords, not the four a 116-bit bitset would need, and the
// flip sanitises the last word with 0x1FFFFF -- twenty-one bits, so the real
// width is 181. The thunk's shim spelling is kept verbatim so it still
// resolves; only the storage is written to what the body reads.
//
// The two intersections are unrolled while the two any() scans stay as
// indexed loops with an early exit, which is exactly how an inline word loop
// with a return inside it compiles. The sanitising mask is applied to the
// flipped word before it meets mustBeSet, in that order.

typedef unsigned int UnsignedInt;

template <int NUMBITS>
class BitFlags
{
public:
	UnsignedInt m_bits[6];
};

class BitFlags116TestSetAndClearShim
{
public:
	bool testSetAndClear(const BitFlags<116> &mustBeSet, const BitFlags<116> &mustBeClear) const;

private:
	enum { BFME_WORDS = 6, BFME_LAST_MASK = 0x1FFFFF };

	BitFlags<116> m_bfmeFlags;
};

// ?testSetAndClear@BitFlags116TestSetAndClearShim@@QBE_NABV?$BitFlags@$0HE@@@0@Z
bool BitFlags116TestSetAndClearShim::testSetAndClear(const BitFlags<116> &mustBeSet,
	const BitFlags<116> &mustBeClear) const
{
	BitFlags<116> tmp = m_bfmeFlags;
	UnsignedInt i;

	for (i = 0; i < BFME_WORDS; ++i)
		tmp.m_bits[i] &= mustBeClear.m_bits[i];

	i = 0;

	do
	{
		if (tmp.m_bits[i])
			return false;
	}
	while (++i < BFME_WORDS);

	tmp = m_bfmeFlags;

	for (i = 0; i < BFME_WORDS - 1; ++i)
		tmp.m_bits[i] = ~tmp.m_bits[i];

	tmp.m_bits[BFME_WORDS - 1] = ~tmp.m_bits[BFME_WORDS - 1] & BFME_LAST_MASK;

	for (i = 0; i < BFME_WORDS; ++i)
		tmp.m_bits[i] &= mustBeSet.m_bits[i];

	i = 0;

	do
	{
		if (tmp.m_bits[i])
			return false;
	}
	while (++i < BFME_WORDS);

	return true;
}
