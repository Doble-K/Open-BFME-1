// ?bfmeAllocAndCopyWord_000A7820@@YGPAHIPBH0@Z
// partial score=0.97 date=2026-08-25
// Ten allocate-and-copy bodies: six over four-byte elements and four over
// eight-byte ones.
//
// The size dispatch is the caller's, not the allocator's: the byte count is
// pushed ONCE and both arms call with it, the small arm below 0x80 going to
// the node allocator and the large arm to the plain one, with a zero count
// short-circuiting to a null result before either. That shared push is why the
// two calls each clean four bytes of their own.
//
// The copy loop tracks only the source pointer and forms the destination as
// result - first + p each time round -- the compiler's own strength reduction
// from two parallel pointers -- and the null test in front of each element is
// placement-new codegen, not a test the source writes.
//
// The element width is the shift: shl 2 for the six, shl 3 for the four, and
// in the wider case the copy moves two dwords, so the element is a POD pair.

inline void *operator new(unsigned int, void *place)
{
	return place;
}

void *bfmeNewAlloc(unsigned int bytes);				// retail 0x00881F30
void *bfmeAllocNode(unsigned int bytes);			// retail 0x0082E540

inline void *bfmeAllocate(unsigned int bytes)
{
	if (bytes > 0x80)
		return bfmeNewAlloc(bytes);

	return bfmeAllocNode(bytes);
}

struct BfmePair
{
	BfmePair(const BfmePair &other)
	{
		m_bfmeFirst = other.m_bfmeFirst;
		m_bfmeSecond = other.m_bfmeSecond;
	}

	int m_bfmeFirst;
	int m_bfmeSecond;
};


// ?bfmeAllocAndCopyWord_000A7820@@YGPAHIPBH0@Z
int *__stdcall bfmeAllocAndCopyWord_000A7820(unsigned int count, const int *first, const int *last)
{
	int *result = count ? (int *)bfmeAllocate(count * sizeof(int)) : 0;
	if (first != last)
	{
		char *base = (char *)result - (long)first;
		long address = (long)first;

		do
		{
			new ((int *)(base + address)) int(*(const int *)address);
			address += sizeof(int);
		}
		while (address != (long)last);
	}

	return result;
}

// ?bfmeAllocAndCopyWord_000BB620@@YGPAHIPBH0@Z
int *__stdcall bfmeAllocAndCopyWord_000BB620(unsigned int count, const int *first, const int *last)
{
	int *result = count ? (int *)bfmeAllocate(count * sizeof(int)) : 0;
	if (first != last)
	{
		char *base = (char *)result - (long)first;
		long address = (long)first;

		do
		{
			new ((int *)(base + address)) int(*(const int *)address);
			address += sizeof(int);
		}
		while (address != (long)last);
	}

	return result;
}

// ?bfmeAllocAndCopyWord_000CD450@@YGPAHIPBH0@Z
int *__stdcall bfmeAllocAndCopyWord_000CD450(unsigned int count, const int *first, const int *last)
{
	int *result = count ? (int *)bfmeAllocate(count * sizeof(int)) : 0;
	if (first != last)
	{
		char *base = (char *)result - (long)first;
		long address = (long)first;

		do
		{
			new ((int *)(base + address)) int(*(const int *)address);
			address += sizeof(int);
		}
		while (address != (long)last);
	}

	return result;
}

// ?bfmeAllocAndCopyWord_00134C90@@YGPAHIPBH0@Z
int *__stdcall bfmeAllocAndCopyWord_00134C90(unsigned int count, const int *first, const int *last)
{
	int *result = count ? (int *)bfmeAllocate(count * sizeof(int)) : 0;
	if (first != last)
	{
		char *base = (char *)result - (long)first;
		long address = (long)first;

		do
		{
			new ((int *)(base + address)) int(*(const int *)address);
			address += sizeof(int);
		}
		while (address != (long)last);
	}

	return result;
}

// ?bfmeAllocAndCopyWord_0016FF30@@YGPAHIPBH0@Z
int *__stdcall bfmeAllocAndCopyWord_0016FF30(unsigned int count, const int *first, const int *last)
{
	int *result = count ? (int *)bfmeAllocate(count * sizeof(int)) : 0;
	if (first != last)
	{
		char *base = (char *)result - (long)first;
		long address = (long)first;

		do
		{
			new ((int *)(base + address)) int(*(const int *)address);
			address += sizeof(int);
		}
		while (address != (long)last);
	}

	return result;
}

// ?bfmeAllocAndCopyWord_0036CA60@@YGPAHIPBH0@Z
int *__stdcall bfmeAllocAndCopyWord_0036CA60(unsigned int count, const int *first, const int *last)
{
	int *result = count ? (int *)bfmeAllocate(count * sizeof(int)) : 0;
	if (first != last)
	{
		char *base = (char *)result - (long)first;
		long address = (long)first;

		do
		{
			new ((int *)(base + address)) int(*(const int *)address);
			address += sizeof(int);
		}
		while (address != (long)last);
	}

	return result;
}

// ?bfmeAllocAndCopyPair_000B0200@@YGPAUBfmePair@@IPBU1@0@Z
BfmePair *__stdcall bfmeAllocAndCopyPair_000B0200(unsigned int count, const BfmePair *first, const BfmePair *last)
{
	BfmePair *result = count ? (BfmePair *)bfmeAllocate(count * sizeof(BfmePair)) : 0;
	if (first != last)
	{
		char *base = (char *)result - (long)first;
		long address = (long)first;

		do
		{
			new ((BfmePair *)(base + address)) BfmePair(*(const BfmePair *)address);
			address += sizeof(BfmePair);
		}
		while (address != (long)last);
	}

	return result;
}

// ?bfmeAllocAndCopyPair_003CDA80@@YGPAUBfmePair@@IPBU1@0@Z
BfmePair *__stdcall bfmeAllocAndCopyPair_003CDA80(unsigned int count, const BfmePair *first, const BfmePair *last)
{
	BfmePair *result = count ? (BfmePair *)bfmeAllocate(count * sizeof(BfmePair)) : 0;
	if (first != last)
	{
		char *base = (char *)result - (long)first;
		long address = (long)first;

		do
		{
			new ((BfmePair *)(base + address)) BfmePair(*(const BfmePair *)address);
			address += sizeof(BfmePair);
		}
		while (address != (long)last);
	}

	return result;
}

// ?bfmeAllocAndCopyPair_00698B50@@YGPAUBfmePair@@IPBU1@0@Z
BfmePair *__stdcall bfmeAllocAndCopyPair_00698B50(unsigned int count, const BfmePair *first, const BfmePair *last)
{
	BfmePair *result = count ? (BfmePair *)bfmeAllocate(count * sizeof(BfmePair)) : 0;
	if (first != last)
	{
		char *base = (char *)result - (long)first;
		long address = (long)first;

		do
		{
			new ((BfmePair *)(base + address)) BfmePair(*(const BfmePair *)address);
			address += sizeof(BfmePair);
		}
		while (address != (long)last);
	}

	return result;
}

// ?bfmeAllocAndCopyPair_006BE9C0@@YGPAUBfmePair@@IPBU1@0@Z
BfmePair *__stdcall bfmeAllocAndCopyPair_006BE9C0(unsigned int count, const BfmePair *first, const BfmePair *last)
{
	BfmePair *result = count ? (BfmePair *)bfmeAllocate(count * sizeof(BfmePair)) : 0;
	if (first != last)
	{
		char *base = (char *)result - (long)first;
		long address = (long)first;

		do
		{
			new ((BfmePair *)(base + address)) BfmePair(*(const BfmePair *)address);
			address += sizeof(BfmePair);
		}
		while (address != (long)last);
	}

	return result;
}
