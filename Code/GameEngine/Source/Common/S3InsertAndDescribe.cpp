// Eight more bodies in two shapes.
//
// 0x00340860, 0x00452910, 0x00452970 and 0x00753460 are the unguarded linear
// insert of an insertion sort. The comparator arrives BY VALUE as the third
// argument -- lea ecx,[esp+0x20] takes the address of that argument slot, it
// is not a local -- and it is called with the pending value first and the
// element second. The loop is rotated: the element for the next comparison is
// loaded before the call, and the walk runs backwards four bytes at a time.
//
// 0x00881040, 0x008F7650, 0x009A2700 and 0x009F2880 fill a two-byte pair with
// true and hand its address to virtual slot ten of the argument, then pass the
// argument on to the member at +0x04. Both bytes come from one mov al,1, and
// the pair lives in the four bytes reserved by the push ecx in the prologue.

struct BfmeFlagPair
{
	bool m_bfmeFirst;
	bool m_bfmeSecond;
};


struct BfmeInsertCompareA
{
	bool operator()(void *pending, void *element);		// ILT 0x00024B81
};

struct BfmeInsertCompareB
{
	bool operator()(void *pending, void *element);		// ILT 0x00024055
};

struct BfmeInsertCompareC
{
	bool operator()(void *pending, void *element);		// ILT 0x00039CB1
};

struct BfmeInsertCompareD
{
	bool operator()(void *pending, void *element);		// ILT 0x0002952D
};

// ?bfmeLinearInsert_00340860@@YAXPAPAXPAXUBfmeInsertCompareA@@@Z
void bfmeLinearInsert_00340860(void **last, void *pending, BfmeInsertCompareA compare)
{
	void **previous = last - 1;

	while (compare(pending, *previous))
	{
		*last = *previous;
		last = previous;
		--previous;
	}

	*last = pending;
}

// ?bfmeLinearInsert_00452910@@YAXPAPAXPAXUBfmeInsertCompareB@@@Z
void bfmeLinearInsert_00452910(void **last, void *pending, BfmeInsertCompareB compare)
{
	void **previous = last - 1;

	while (compare(pending, *previous))
	{
		*last = *previous;
		last = previous;
		--previous;
	}

	*last = pending;
}

// ?bfmeLinearInsert_00452970@@YAXPAPAXPAXUBfmeInsertCompareC@@@Z
void bfmeLinearInsert_00452970(void **last, void *pending, BfmeInsertCompareC compare)
{
	void **previous = last - 1;

	while (compare(pending, *previous))
	{
		*last = *previous;
		last = previous;
		--previous;
	}

	*last = pending;
}

// ?bfmeLinearInsert_00753460@@YAXPAPAXPAXUBfmeInsertCompareD@@@Z
void bfmeLinearInsert_00753460(void **last, void *pending, BfmeInsertCompareD compare)
{
	void **previous = last - 1;

	while (compare(pending, *previous))
	{
		*last = *previous;
		last = previous;
		--previous;
	}

	*last = pending;
}

class BfmeFlagTarget
{
public:
	virtual void bfmeSlot0(void);
	virtual void bfmeSlot1(void);
	virtual void bfmeSlot2(void);
	virtual void bfmeSlot3(void);
	virtual void bfmeSlot4(void);
	virtual void bfmeSlot5(void);
	virtual void bfmeSlot6(void);
	virtual void bfmeSlot7(void);
	virtual void bfmeSlot8(void);
	virtual void bfmeSlot9(void);
	virtual void bfmeDescribe(BfmeFlagPair *flags);		// slot 10, vtable+0x28
};

class BfmeSinkA
{
public:
	void bfmeAccept(BfmeFlagTarget *target);		// retail 0x008815A0
};

class Gen_00881040
{
public:
	void bfmeDescribe(BfmeFlagTarget *target);

private:
	char m_bfmeHead[4];
	BfmeSinkA *m_bfmeSink;					// +0x04
};

class BfmeSinkB
{
public:
	void bfmeAccept(BfmeFlagTarget *target);		// retail 0x008FB0B0
};

class Gen_008F7650
{
public:
	void bfmeDescribe(BfmeFlagTarget *target);

private:
	char m_bfmeHead[4];
	BfmeSinkB *m_bfmeSink;					// +0x04
};

class BfmeSinkC
{
public:
	void bfmeAccept(BfmeFlagTarget *target);		// retail 0x009A2FC0
};

class Gen_009A2700
{
public:
	void bfmeDescribe(BfmeFlagTarget *target);

private:
	char m_bfmeHead[4];
	BfmeSinkC *m_bfmeSink;					// +0x04
};

class BfmeSinkD
{
public:
	void bfmeAccept(BfmeFlagTarget *target);		// retail 0x009F49F0
};

class Gen_009F2880
{
public:
	void bfmeDescribe(BfmeFlagTarget *target);

private:
	char m_bfmeHead[4];
	BfmeSinkD *m_bfmeSink;					// +0x04
};

// ?bfmeDescribe@Gen_00881040@@QAEXPAVBfmeFlagTarget@@@Z
void Gen_00881040::bfmeDescribe(BfmeFlagTarget *target)
{
	BfmeFlagPair flags;

	flags.m_bfmeFirst = true;
	flags.m_bfmeSecond = true;

	target->bfmeDescribe(&flags);

	m_bfmeSink->bfmeAccept(target);
}

// ?bfmeDescribe@Gen_008F7650@@QAEXPAVBfmeFlagTarget@@@Z
void Gen_008F7650::bfmeDescribe(BfmeFlagTarget *target)
{
	BfmeFlagPair flags;

	flags.m_bfmeFirst = true;
	flags.m_bfmeSecond = true;

	target->bfmeDescribe(&flags);

	m_bfmeSink->bfmeAccept(target);
}

// ?bfmeDescribe@Gen_009A2700@@QAEXPAVBfmeFlagTarget@@@Z
void Gen_009A2700::bfmeDescribe(BfmeFlagTarget *target)
{
	BfmeFlagPair flags;

	flags.m_bfmeFirst = true;
	flags.m_bfmeSecond = true;

	target->bfmeDescribe(&flags);

	m_bfmeSink->bfmeAccept(target);
}

// ?bfmeDescribe@Gen_009F2880@@QAEXPAVBfmeFlagTarget@@@Z
void Gen_009F2880::bfmeDescribe(BfmeFlagTarget *target)
{
	BfmeFlagPair flags;

	flags.m_bfmeFirst = true;
	flags.m_bfmeSecond = true;

	target->bfmeDescribe(&flags);

	m_bfmeSink->bfmeAccept(target);
}
