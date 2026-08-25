// ?bfmeRelease@Gen_000877E0@@QAEXXZ
// partial score=0.9 date=2026-08-25
// Six reference-count releases.
//
// The counter is decremented through an import slot rather than a plain dec,
// and the answer is tested with jg, so the source keeps the returned value and
// asks whether it is still positive. The pointer is tested TWICE -- once
// before the decrement and again before the destroy -- which is two separate
// guards in the source and not one the compiler duplicated.
//
// The destroy is virtual slot zero carrying a literal one.
//
// 0x000877E0, 0x000878F0 and 0x006968A0 are members and clear the holder
// afterwards; the clear sits inside the outer guard, since the first je jumps
// past it. 0x000BA810, 0x0069C2D0 and 0x0069CEB0 are the __cdecl form that
// takes the holder as an argument and does not clear it.

extern long (__stdcall *TheBfmeInterlockedDecrement)(long *value);	// import slot 0x01358E54

class BfmeCounted
{
public:
	virtual ~BfmeCounted(void);				// slot 0 is its scalar deleting form

	void bfmeRelease(void)
	{
		if (TheBfmeInterlockedDecrement(&m_bfmeRefCount) <= 0)
			delete this;
	}

	long m_bfmeRefCount;					// +0x04
};

struct BfmeCountedHolder
{
	BfmeCounted *m_bfmeObject;
};


class Gen_000877E0
{
public:
	void bfmeRelease(void);

private:
	BfmeCounted *m_bfmeObject;
};

class Gen_000878F0
{
public:
	void bfmeRelease(void);

private:
	BfmeCounted *m_bfmeObject;
};

class Gen_006968A0
{
public:
	void bfmeRelease(void);

private:
	BfmeCounted *m_bfmeObject;
};

// ?bfmeRelease@Gen_000877E0@@QAEXXZ
void Gen_000877E0::bfmeRelease(void)
{
	BfmeCounted *object = m_bfmeObject;

	if (object)
	{
		object->bfmeRelease();

		m_bfmeObject = 0;
	}
}

// ?bfmeRelease@Gen_000878F0@@QAEXXZ
void Gen_000878F0::bfmeRelease(void)
{
	BfmeCounted *object = m_bfmeObject;

	if (object)
	{
		object->bfmeRelease();

		m_bfmeObject = 0;
	}
}

// ?bfmeRelease@Gen_006968A0@@QAEXXZ
void Gen_006968A0::bfmeRelease(void)
{
	BfmeCounted *object = m_bfmeObject;

	if (object)
	{
		object->bfmeRelease();

		m_bfmeObject = 0;
	}
}

// ?bfmeReleaseHolder_000BA810@@YAXPAUBfmeCountedHolder@@@Z
void bfmeReleaseHolder_000BA810(BfmeCountedHolder *holder)
{
	BfmeCounted *object = holder->m_bfmeObject;

	if (object)
	{
		object->bfmeRelease();
	}
}

// ?bfmeReleaseHolder_0069C2D0@@YAXPAUBfmeCountedHolder@@@Z
void bfmeReleaseHolder_0069C2D0(BfmeCountedHolder *holder)
{
	BfmeCounted *object = holder->m_bfmeObject;

	if (object)
	{
		object->bfmeRelease();
	}
}

// ?bfmeReleaseHolder_0069CEB0@@YAXPAUBfmeCountedHolder@@@Z
void bfmeReleaseHolder_0069CEB0(BfmeCountedHolder *holder)
{
	BfmeCounted *object = holder->m_bfmeObject;

	if (object)
	{
		object->bfmeRelease();
	}
}
