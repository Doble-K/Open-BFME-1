// ??4Gen_00087750@@QAEAAV0@ABV0@@Z
// partial score=0.95 date=2026-08-25
// cl: /DNDEBUG /MD /EHs-c-

extern "C" __declspec(dllimport) long __stdcall InterlockedIncrement(long *addend);
extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(long *addend);

class BfmeCounted
{
public:
	virtual ~BfmeCounted();

	long m_bfmeRefCount;						// +0x04
};

class Gen_00087750
{
public:
	Gen_00087750 &operator=(const Gen_00087750 &other);

	BfmeCounted *m_bfmePtr;						// +0x00
};

Gen_00087750 &Gen_00087750::operator=(const Gen_00087750 &other)
{
	if (this != &other)
	{
		if (other.m_bfmePtr)
			InterlockedIncrement(&other.m_bfmePtr->m_bfmeRefCount);

		BfmeCounted *previous = m_bfmePtr;

		if (previous)
		{
			if (InterlockedDecrement(&previous->m_bfmeRefCount) <= 0)
				delete previous;
		}

		m_bfmePtr = other.m_bfmePtr;
	}

	return *this;
}
