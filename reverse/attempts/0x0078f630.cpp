// ?bfmeSelect_0078F630@@YAXPAUBfmeSelectable@@@Z
// partial score=0.95 date=2026-08-26
// Eight handler selectors.
//
// Each reads a signed byte at +0x04 of its argument, stores one of two
// addresses into +0x18 depending on its sign, and tail-jumps to a common
// routine with the same argument.
//
// The test is jns on a byte, so the field is a SIGNED char and the condition
// is "< 0", not a flag test against a mask. The mov [esp+4],eax before each
// jump re-stores the unchanged argument, which is what the tail call needs to
// leave the frame exactly as the callee expects.

struct BfmeSelectable
{
	char m_bfmeHead[4];
	char m_bfmeSign;					// +0x04
	char m_bfmeGap[0x18 - 5];
	void *m_bfmeHandler;					// +0x18
};


extern char TheBfmeNegative_0078F630[];
extern char TheBfmePositive_0078F630[];

void bfmeSelect_0078F630(BfmeSelectable *item);		// tail-jumps to 0x000352DD

extern char TheBfmeNegative_0078F670[];
extern char TheBfmePositive_0078F670[];

void bfmeSelect_0078F670(BfmeSelectable *item);		// tail-jumps to 0x00024014

extern char TheBfmeNegative_0078F6B0[];
extern char TheBfmePositive_0078F6B0[];

void bfmeSelect_0078F6B0(BfmeSelectable *item);		// tail-jumps to 0x0000C608

extern char TheBfmeNegative_0078F6F0[];
extern char TheBfmePositive_0078F6F0[];

void bfmeSelect_0078F6F0(BfmeSelectable *item);		// tail-jumps to 0x00037B0F

extern char TheBfmeNegative_0078F730[];
extern char TheBfmePositive_0078F730[];

void bfmeSelect_0078F730(BfmeSelectable *item);		// tail-jumps to 0x0000EA8E

extern char TheBfmeNegative_0078F8D0[];
extern char TheBfmePositive_0078F8D0[];

void bfmeSelect_0078F8D0(BfmeSelectable *item);		// tail-jumps to 0x000178FA

extern char TheBfmeNegative_0078F910[];
extern char TheBfmePositive_0078F910[];

void bfmeSelect_0078F910(BfmeSelectable *item);		// tail-jumps to 0x0003598B

extern char TheBfmeNegative_0078F950[];
extern char TheBfmePositive_0078F950[];

void bfmeSelect_0078F950(BfmeSelectable *item);		// tail-jumps to 0x0001E4DE

void bfmeApply_0078F630(BfmeSelectable *item);		// ILT 0x000352DD

// ?bfmeSelect_0078F630@@YAXPAUBfmeSelectable@@@Z
void bfmeSelect_0078F630(BfmeSelectable *item)
{
	if ((item->m_bfmeSign & 0x80) != 0)
		item->m_bfmeHandler = TheBfmeNegative_0078F630;
	else
		item->m_bfmeHandler = TheBfmePositive_0078F630;

	bfmeApply_0078F630(item);
}

void bfmeApply_0078F670(BfmeSelectable *item);		// ILT 0x00024014

// ?bfmeSelect_0078F670@@YAXPAUBfmeSelectable@@@Z
void bfmeSelect_0078F670(BfmeSelectable *item)
{
	if ((item->m_bfmeSign & 0x80) != 0)
		item->m_bfmeHandler = TheBfmeNegative_0078F670;
	else
		item->m_bfmeHandler = TheBfmePositive_0078F670;

	bfmeApply_0078F670(item);
}

void bfmeApply_0078F6B0(BfmeSelectable *item);		// ILT 0x0000C608

// ?bfmeSelect_0078F6B0@@YAXPAUBfmeSelectable@@@Z
void bfmeSelect_0078F6B0(BfmeSelectable *item)
{
	if ((item->m_bfmeSign & 0x80) != 0)
		item->m_bfmeHandler = TheBfmeNegative_0078F6B0;
	else
		item->m_bfmeHandler = TheBfmePositive_0078F6B0;

	bfmeApply_0078F6B0(item);
}

void bfmeApply_0078F6F0(BfmeSelectable *item);		// ILT 0x00037B0F

// ?bfmeSelect_0078F6F0@@YAXPAUBfmeSelectable@@@Z
void bfmeSelect_0078F6F0(BfmeSelectable *item)
{
	if ((item->m_bfmeSign & 0x80) != 0)
		item->m_bfmeHandler = TheBfmeNegative_0078F6F0;
	else
		item->m_bfmeHandler = TheBfmePositive_0078F6F0;

	bfmeApply_0078F6F0(item);
}

void bfmeApply_0078F730(BfmeSelectable *item);		// ILT 0x0000EA8E

// ?bfmeSelect_0078F730@@YAXPAUBfmeSelectable@@@Z
void bfmeSelect_0078F730(BfmeSelectable *item)
{
	if ((item->m_bfmeSign & 0x80) != 0)
		item->m_bfmeHandler = TheBfmeNegative_0078F730;
	else
		item->m_bfmeHandler = TheBfmePositive_0078F730;

	bfmeApply_0078F730(item);
}

void bfmeApply_0078F8D0(BfmeSelectable *item);		// ILT 0x000178FA

// ?bfmeSelect_0078F8D0@@YAXPAUBfmeSelectable@@@Z
void bfmeSelect_0078F8D0(BfmeSelectable *item)
{
	if ((item->m_bfmeSign & 0x80) != 0)
		item->m_bfmeHandler = TheBfmeNegative_0078F8D0;
	else
		item->m_bfmeHandler = TheBfmePositive_0078F8D0;

	bfmeApply_0078F8D0(item);
}

void bfmeApply_0078F910(BfmeSelectable *item);		// ILT 0x0003598B

// ?bfmeSelect_0078F910@@YAXPAUBfmeSelectable@@@Z
void bfmeSelect_0078F910(BfmeSelectable *item)
{
	if ((item->m_bfmeSign & 0x80) != 0)
		item->m_bfmeHandler = TheBfmeNegative_0078F910;
	else
		item->m_bfmeHandler = TheBfmePositive_0078F910;

	bfmeApply_0078F910(item);
}

void bfmeApply_0078F950(BfmeSelectable *item);		// ILT 0x0001E4DE

// ?bfmeSelect_0078F950@@YAXPAUBfmeSelectable@@@Z
void bfmeSelect_0078F950(BfmeSelectable *item)
{
	if ((item->m_bfmeSign & 0x80) != 0)
		item->m_bfmeHandler = TheBfmeNegative_0078F950;
	else
		item->m_bfmeHandler = TheBfmePositive_0078F950;

	bfmeApply_0078F950(item);
}
