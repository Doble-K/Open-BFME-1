// The insertion sort itself: for every element after the first, hand it to the
// linear insert with the range that is already in order.
//
// The distance from the cursor back to the first element is kept as a base
// held in a callee-saved register -- four minus the first pointer -- so the
// byte count for the move-up is one lea per pass.
//
// The other two are linear inserts whose comparator is inlined: an entry with
// nothing attached sorts ahead of one that has something, and otherwise the
// names decide. The "exactly one of them" test is written with a bitwise xor
// of the two flags -- an inequality of the two comparisons compiles to a cmp
// and loses the xor retail has.

extern "C" __declspec(dllimport) void * __cdecl memmove(void *destination, const void *source, unsigned int bytes);

inline int *bfmeCopyBackward(int *first, int *last, int *result)
{
	int bytes = (char *)last - (char *)first;

	if (bytes > 0)
		memmove((char *)result - bytes, first, bytes);

	return (int *)((char *)result - bytes);
}

inline void bfmeUnguardedLinearInsert(int *last, int value)
{
	int *next = last - 1;

	while (value < *next)
	{
		*last = *next;

		last = next;

		--next;
	}

	*last = value;
}

__forceinline void bfmeLinearInsert(int *first, int *last, int value)
{
	if (value < *first)
	{
		bfmeCopyBackward(first, last, last + 1);

		*first = value;
	}
	else
	{
		bfmeUnguardedLinearInsert(last, value);
	}
}

// ?bfmeInsertionSort@@YAXPAH0@Z
void __cdecl bfmeInsertionSort(int *first, int *last)
{
	if (first == last)
		return;

	for (int *cursor = first + 1; cursor != last; ++cursor)
		bfmeLinearInsert(first, cursor, *cursor);
}

class BfmeNameAU
{
public:
	int bfmeCompare(const BfmeNameAU *other) const;		// retail thunk 0x00027471 -> 0x00427471

	int m_bfmeData[3];					// +0x00
};

class BfmeRecAU
{
public:
	int m_bfmeTag;						// +0x00
	BfmeNameAU m_bfmeName;					// +0x04
	void *m_bfmeThing;					// +0x10
};

class BfmeCompAU
{
public:
	bool operator()(const BfmeRecAU *left, const BfmeRecAU *right) const
	{
		if ((left->m_bfmeThing == 0) ^ (right->m_bfmeThing == 0))
			return right->m_bfmeThing == 0;

		return left->m_bfmeName.bfmeCompare(&right->m_bfmeName) < 0;
	}

	int m_bfmeState;					// +0x00
};

inline BfmeRecAU **bfmeCopyBackwardAU(BfmeRecAU **first, BfmeRecAU **last, BfmeRecAU **result)
{
	int bytes = (char *)last - (char *)first;

	if (bytes > 0)
		memmove((char *)result - bytes, first, bytes);

	return (BfmeRecAU **)((char *)result - bytes);
}

void __cdecl bfmeUnguardedInsertAU(BfmeRecAU **last, BfmeRecAU *value, BfmeCompAU comp);
								// retail thunk 0x00016275 -> 0x00416275

// ?bfmeLinearInsertAU@@YAXPAPAVBfmeRecAU@@0PAV1@VBfmeCompAU@@@Z
void __cdecl bfmeLinearInsertAU(BfmeRecAU **first, BfmeRecAU **last, BfmeRecAU *value, BfmeCompAU comp)
{
	if (comp(value, *first))
	{
		bfmeCopyBackwardAU(first, last, last + 1);

		*first = value;
	}
	else
	{
		bfmeUnguardedInsertAU(last, value, comp);
	}
}

void __cdecl bfmeUnguardedInsertAV(BfmeRecAU **last, BfmeRecAU *value, BfmeCompAU comp);
								// retail thunk 0x000044EE -> 0x004044EE

// ?bfmeLinearInsertAV@@YAXPAPAVBfmeRecAU@@0PAV1@VBfmeCompAU@@@Z
void __cdecl bfmeLinearInsertAV(BfmeRecAU **first, BfmeRecAU **last, BfmeRecAU *value, BfmeCompAU comp)
{
	if (comp(value, *first))
	{
		bfmeCopyBackwardAU(first, last, last + 1);

		*first = value;
	}
	else
	{
		bfmeUnguardedInsertAV(last, value, comp);
	}
}
