// Eight two-field setup stubs.
//
// The longer sibling of the setup stubs at 0x007E95A0: same opening -- a
// global read into a callee-saved register, a no-argument member call, a
// FourCC stamped into +0x1C -- but two writes instead of one, the second
// carrying the stub's own second argument.
//
// The tags read as ASCII little-endian, "acct" for five of them and "rank" for
// three, which is the only thing that separates the two halves of the family.
// Every string and global is a relocation, so a single extern per role serves
// all eight: the build copies the real address in per call site.

struct BfmeSetupRecord
{
	void bfmeBegin(void);					// retail 0x007E8AC0
	void bfmeWrite(const char *text, int value);		// retail 0x007E8A10
	void bfmeWriteAlt(const char *text, int value);		// retail 0x007E88D0

	char m_bfmeHead[0x1C];
	unsigned int m_bfmeTag;					// +0x1C
};

extern const char TheBfmeSetupFirstText[];
extern const char TheBfmeSetupSecondText[];
extern int TheBfmeSetupGlobal;


// ?bfmeSetupPair_007E94A0@@YGXPAUBfmeSetupRecord@@H@Z
void __stdcall bfmeSetupPair_007E94A0(BfmeSetupRecord *record, int second)
{
	int value = TheBfmeSetupGlobal;

	record->bfmeBegin();

	record->m_bfmeTag = 0x61636374;					// 'acct'

	record->bfmeWrite(TheBfmeSetupFirstText, value);
	record->bfmeWrite(TheBfmeSetupSecondText, second);
}

// ?bfmeSetupPair_007E94E0@@YGXPAUBfmeSetupRecord@@H@Z
void __stdcall bfmeSetupPair_007E94E0(BfmeSetupRecord *record, int second)
{
	int value = TheBfmeSetupGlobal;

	record->bfmeBegin();

	record->m_bfmeTag = 0x61636374;					// 'acct'

	record->bfmeWrite(TheBfmeSetupFirstText, value);
	record->bfmeWrite(TheBfmeSetupSecondText, second);
}

// ?bfmeSetupPair_007E9520@@YGXPAUBfmeSetupRecord@@H@Z
void __stdcall bfmeSetupPair_007E9520(BfmeSetupRecord *record, int second)
{
	int value = TheBfmeSetupGlobal;

	record->bfmeBegin();

	record->m_bfmeTag = 0x61636374;					// 'acct'

	record->bfmeWrite(TheBfmeSetupFirstText, value);
	record->bfmeWrite(TheBfmeSetupSecondText, second);
}

// ?bfmeSetupPair_007E9560@@YGXPAUBfmeSetupRecord@@H@Z
void __stdcall bfmeSetupPair_007E9560(BfmeSetupRecord *record, int second)
{
	int value = TheBfmeSetupGlobal;

	record->bfmeBegin();

	record->m_bfmeTag = 0x61636374;					// 'acct'

	record->bfmeWrite(TheBfmeSetupFirstText, value);
	record->bfmeWrite(TheBfmeSetupSecondText, second);
}

// ?bfmeSetupPair_007E9860@@YGXPAUBfmeSetupRecord@@H@Z
void __stdcall bfmeSetupPair_007E9860(BfmeSetupRecord *record, int second)
{
	int value = TheBfmeSetupGlobal;

	record->bfmeBegin();

	record->m_bfmeTag = 0x61636374;					// 'acct'

	record->bfmeWrite(TheBfmeSetupFirstText, value);
	record->bfmeWrite(TheBfmeSetupSecondText, second);
}

// ?bfmeSetupPair_007F26A0@@YGXPAUBfmeSetupRecord@@H@Z
void __stdcall bfmeSetupPair_007F26A0(BfmeSetupRecord *record, int second)
{
	int value = TheBfmeSetupGlobal;

	record->bfmeBegin();

	record->m_bfmeTag = 0x72616E6B;					// 'rank'

	record->bfmeWrite(TheBfmeSetupFirstText, value);
	record->bfmeWriteAlt(TheBfmeSetupSecondText, second);
}

// ?bfmeSetupPair_007F26E0@@YGXPAUBfmeSetupRecord@@H@Z
void __stdcall bfmeSetupPair_007F26E0(BfmeSetupRecord *record, int second)
{
	int value = TheBfmeSetupGlobal;

	record->bfmeBegin();

	record->m_bfmeTag = 0x72616E6B;					// 'rank'

	record->bfmeWrite(TheBfmeSetupFirstText, value);
	record->bfmeWrite(TheBfmeSetupSecondText, second);
}

// ?bfmeSetupPair_007F2720@@YGXPAUBfmeSetupRecord@@H@Z
void __stdcall bfmeSetupPair_007F2720(BfmeSetupRecord *record, int second)
{
	int value = TheBfmeSetupGlobal;

	record->bfmeBegin();

	record->m_bfmeTag = 0x72616E6B;					// 'rank'

	record->bfmeWrite(TheBfmeSetupFirstText, value);
	record->bfmeWrite(TheBfmeSetupSecondText, second);
}
