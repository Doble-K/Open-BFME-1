// Six 47-byte bodies with one shape:
//
//     if (!allocate(a, b)) return false;
//     if (m_0008 < m_0010) m_0010 = m_0008;
//     return true;
//
// The callee takes both arguments back in the order they arrived and runs with
// ecx untouched, so it is a member of the same class. test al,al says it hands
// back a byte, and the two exits set al alone, so these return a byte-wide
// bool as well. The compare is jge-skips, which is a less-than that lowers a
// high-water mark at +0x10 to the value at +0x08.
//
// The success path has to be written inside the if, with the plain return
// false last. Written the other way round -- an early return on failure --
// MSVC notices the callee already left zero in al, drops the xor entirely and
// puts the exit inline, which is two bytes short.
//
// One of the six callees is named: 0x0003FC7E is ShadowPool::allocate(int, int)
// returning bool, which fixes the argument types for all of them. The other
// five are known only by address and are pinned here.

class Gen_007b9e80
{
public:
	bool bfmeReserve(int first, int second);

private:
	bool bfmeAllocate(int first, int second);			// retail 0x0003FC7E

	char m_bfmeHead[0x08];
	int m_bfme0008;							// +0x08
	char m_bfmeMid[0x10 - 0x0C];
	int m_bfme0010;							// +0x10
};

class Gen_009073d0
{
public:
	bool bfmeReserve(int first, int second);

private:
	bool bfmeAllocate(int first, int second);			// retail 0x00905DC0

	char m_bfmeHead[0x08];
	int m_bfme0008;							// +0x08
	char m_bfmeMid[0x10 - 0x0C];
	int m_bfme0010;							// +0x10
};

class Gen_00930d00
{
public:
	bool bfmeReserve(int first, int second);

private:
	bool bfmeAllocate(int first, int second);			// retail 0x009304A0

	char m_bfmeHead[0x08];
	int m_bfme0008;							// +0x08
	char m_bfmeMid[0x10 - 0x0C];
	int m_bfme0010;							// +0x10
};

class Gen_009408d0
{
public:
	bool bfmeReserve(int first, int second);

private:
	bool bfmeAllocate(int first, int second);			// retail 0x00940450

	char m_bfmeHead[0x08];
	int m_bfme0008;							// +0x08
	char m_bfmeMid[0x10 - 0x0C];
	int m_bfme0010;							// +0x10
};

class Gen_0094e310
{
public:
	bool bfmeReserve(int first, int second);

private:
	bool bfmeAllocate(int first, int second);			// retail 0x009131E0

	char m_bfmeHead[0x08];
	int m_bfme0008;							// +0x08
	char m_bfmeMid[0x10 - 0x0C];
	int m_bfme0010;							// +0x10
};

class Gen_0097c8e0
{
public:
	bool bfmeReserve(int first, int second);

private:
	bool bfmeAllocate(int first, int second);			// retail 0x0097ADF0

	char m_bfmeHead[0x08];
	int m_bfme0008;							// +0x08
	char m_bfmeMid[0x10 - 0x0C];
	int m_bfme0010;							// +0x10
};

// ?bfmeReserve@Gen_007b9e80@@QAE_NHH@Z
bool Gen_007b9e80::bfmeReserve(int first, int second)
{
	if (bfmeAllocate(first, second))
	{
		if (m_bfme0008 < m_bfme0010)
			m_bfme0010 = m_bfme0008;

		return true;
	}

	return false;
}

// ?bfmeReserve@Gen_009073d0@@QAE_NHH@Z
bool Gen_009073d0::bfmeReserve(int first, int second)
{
	if (bfmeAllocate(first, second))
	{
		if (m_bfme0008 < m_bfme0010)
			m_bfme0010 = m_bfme0008;

		return true;
	}

	return false;
}

// ?bfmeReserve@Gen_00930d00@@QAE_NHH@Z
bool Gen_00930d00::bfmeReserve(int first, int second)
{
	if (bfmeAllocate(first, second))
	{
		if (m_bfme0008 < m_bfme0010)
			m_bfme0010 = m_bfme0008;

		return true;
	}

	return false;
}

// ?bfmeReserve@Gen_009408d0@@QAE_NHH@Z
bool Gen_009408d0::bfmeReserve(int first, int second)
{
	if (bfmeAllocate(first, second))
	{
		if (m_bfme0008 < m_bfme0010)
			m_bfme0010 = m_bfme0008;

		return true;
	}

	return false;
}

// ?bfmeReserve@Gen_0094e310@@QAE_NHH@Z
bool Gen_0094e310::bfmeReserve(int first, int second)
{
	if (bfmeAllocate(first, second))
	{
		if (m_bfme0008 < m_bfme0010)
			m_bfme0010 = m_bfme0008;

		return true;
	}

	return false;
}

// ?bfmeReserve@Gen_0097c8e0@@QAE_NHH@Z
bool Gen_0097c8e0::bfmeReserve(int first, int second)
{
	if (bfmeAllocate(first, second))
	{
		if (m_bfme0008 < m_bfme0010)
			m_bfme0010 = m_bfme0008;

		return true;
	}

	return false;
}
