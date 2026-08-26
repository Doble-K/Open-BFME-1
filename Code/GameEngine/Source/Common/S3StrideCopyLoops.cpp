// Eight element copy loops.
//
// Each turns a pointer range into a count, walks it, and hands every source
// element to a member of the matching destination element, returning the
// advanced destination. The empty case returns the destination argument
// untouched.
//
// The element width is not in the code as a constant to read off directly: the
// count comes from a magic-multiply division of the byte difference, and it is
// the ADD at the bottom of the loop that names the stride. Six widths appear
// across the eight bodies -- 0x38, 0x5C, 0x70, 0x8C, 0xB4 and 0xB8 -- and the
// three that need a dword displacement for that add are the six bytes longer.


struct BfmeCopyElementA
{
	void bfmeAssign(BfmeCopyElementA *source);		// retail 0x00003828

	char m_bfmeBytes[0x5C];
};

struct BfmeCopyElementB
{
	void bfmeAssign(BfmeCopyElementB *source);		// retail 0x0000D4CC

	char m_bfmeBytes[0x8C];
};

struct BfmeCopyElementC
{
	void bfmeAssign(BfmeCopyElementC *source);		// retail 0x000470F0

	char m_bfmeBytes[0xB4];
};

struct BfmeCopyElementD
{
	void bfmeAssign(BfmeCopyElementD *source);		// retail 0x00024BA9

	char m_bfmeBytes[0xB8];
};

struct BfmeCopyElementE
{
	void bfmeAssign(BfmeCopyElementE *source);		// retail 0x0001F753

	char m_bfmeBytes[0x70];
};

struct BfmeCopyElementF
{
	void bfmeAssign(BfmeCopyElementF *source);		// retail 0x0001B1D5

	char m_bfmeBytes[0x38];
};

// ?bfmeCopy_00138800@@YAPAUBfmeCopyElementA@@PAU1@00@Z
BfmeCopyElementA *bfmeCopy_00138800(BfmeCopyElementA *first, BfmeCopyElementA *last, BfmeCopyElementA *dest)
{
	int count = last - first;

	while (count > 0)
	{
		dest->bfmeAssign(first);

		++first;
		++dest;
		--count;
	}

	return dest;
}

// ?bfmeCopy_00146720@@YAPAUBfmeCopyElementA@@PAU1@00@Z
BfmeCopyElementA *bfmeCopy_00146720(BfmeCopyElementA *first, BfmeCopyElementA *last, BfmeCopyElementA *dest)
{
	int count = last - first;

	while (count > 0)
	{
		dest->bfmeAssign(first);

		++first;
		++dest;
		--count;
	}

	return dest;
}

// ?bfmeCopy_00193AF0@@YAPAUBfmeCopyElementB@@PAU1@00@Z
BfmeCopyElementB *bfmeCopy_00193AF0(BfmeCopyElementB *first, BfmeCopyElementB *last, BfmeCopyElementB *dest)
{
	int count = last - first;

	while (count > 0)
	{
		dest->bfmeAssign(first);

		++first;
		++dest;
		--count;
	}

	return dest;
}

// ?bfmeCopy_00362250@@YAPAUBfmeCopyElementC@@PAU1@00@Z
BfmeCopyElementC *bfmeCopy_00362250(BfmeCopyElementC *first, BfmeCopyElementC *last, BfmeCopyElementC *dest)
{
	int count = last - first;

	while (count > 0)
	{
		dest->bfmeAssign(first);

		++first;
		++dest;
		--count;
	}

	return dest;
}

// ?bfmeCopy_003622F0@@YAPAUBfmeCopyElementC@@PAU1@00@Z
BfmeCopyElementC *bfmeCopy_003622F0(BfmeCopyElementC *first, BfmeCopyElementC *last, BfmeCopyElementC *dest)
{
	int count = last - first;

	while (count > 0)
	{
		dest->bfmeAssign(first);

		++first;
		++dest;
		--count;
	}

	return dest;
}

// ?bfmeCopy_003A1450@@YAPAUBfmeCopyElementD@@PAU1@00@Z
BfmeCopyElementD *bfmeCopy_003A1450(BfmeCopyElementD *first, BfmeCopyElementD *last, BfmeCopyElementD *dest)
{
	int count = last - first;

	while (count > 0)
	{
		dest->bfmeAssign(first);

		++first;
		++dest;
		--count;
	}

	return dest;
}

// ?bfmeCopy_0049D5D0@@YAPAUBfmeCopyElementE@@PAU1@00@Z
BfmeCopyElementE *bfmeCopy_0049D5D0(BfmeCopyElementE *first, BfmeCopyElementE *last, BfmeCopyElementE *dest)
{
	int count = last - first;

	while (count > 0)
	{
		dest->bfmeAssign(first);

		++first;
		++dest;
		--count;
	}

	return dest;
}

// ?bfmeCopy_0075EAA0@@YAPAUBfmeCopyElementF@@PAU1@00@Z
BfmeCopyElementF *bfmeCopy_0075EAA0(BfmeCopyElementF *first, BfmeCopyElementF *last, BfmeCopyElementF *dest)
{
	int count = last - first;

	while (count > 0)
	{
		dest->bfmeAssign(first);

		++first;
		++dest;
		--count;
	}

	return dest;
}
