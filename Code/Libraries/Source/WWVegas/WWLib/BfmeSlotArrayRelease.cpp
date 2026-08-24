// cl: /DNDEBUG /MD /EHs-c-

// Retail 0x00410970, 50 bytes, carried only a machine byte-dump row. Two names
// are pinned at the address -- Clear on VectorClass<float> and on
// VectorClass<TCBClass> -- but neither can be what compiled: VectorClass::Clear
// frees one block and zeroes two words, and this walks fourteen entries. They
// are identical-code-folding aliases parked on the ILT, so the row gets a
// shape-honest name instead.
//
// The counter starts at 0x0E and the pointer walks up from this+0x04 by four
// each turn, so the first array is fourteen pointers at +0x04 and runs to
// +0x3C. The second store is at +0x38 past the walking pointer, which is
// exactly where the second array's matching entry lands -- so it is fourteen
// more pointers starting at +0x3C.
//
// Each live entry goes through vtable slot 0 with an argument of 1: that is
// the scalar deleting destructor, i.e. a plain delete on a pointer whose class
// has a virtual destructor. The null test in front of it is the one delete
// does for itself.

typedef int Int;

class BfmeSlotEntry
{
public:
	virtual ~BfmeSlotEntry();
};

class BfmeSlotArrayHolder
{
public:
	void bfmeReleaseSlots(void);

private:
	char m_bfmeHead[0x04];
	BfmeSlotEntry *m_bfmeSlots[14];					// +0x04
	void *m_bfmeSlotAux[14];					// +0x3C
};

// ?bfmeReleaseSlots@BfmeSlotArrayHolder@@QAEXXZ
void BfmeSlotArrayHolder::bfmeReleaseSlots(void)
{
	for (Int i = 0; i < 14; i++)
	{
		delete m_bfmeSlots[i];

		m_bfmeSlots[i] = 0;
		m_bfmeSlotAux[i] = 0;
	}
}
