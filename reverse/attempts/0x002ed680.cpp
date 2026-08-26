// ?bfmeForward@Gen_002ED680@@QAEXPAUBfmeFieldSource@@@Z
// partial score=0.95 date=2026-08-26
// Retail 0x002ED680, 19 bytes.
//
// Reads a field at +0x20 of its argument, rewrites the argument slot with it,
// and tail-jumps through virtual slot 42. The slot rewrite is what keeps the
// jump legal -- the callee sees one argument in the position it expects -- and
// the two-step load, argument then vptr, marks the call as virtual rather than
// resolved at link time.

struct BfmeFieldSource
{
	char m_bfmeHead[0x20];
	void *m_bfmeField;					// +0x20
};

class Gen_002ED680
{
public:
	void bfmeForward(BfmeFieldSource *source);

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
	virtual void bfmeSlot10(void);
	virtual void bfmeSlot11(void);
	virtual void bfmeSlot12(void);
	virtual void bfmeSlot13(void);
	virtual void bfmeSlot14(void);
	virtual void bfmeSlot15(void);
	virtual void bfmeSlot16(void);
	virtual void bfmeSlot17(void);
	virtual void bfmeSlot18(void);
	virtual void bfmeSlot19(void);
	virtual void bfmeSlot20(void);
	virtual void bfmeSlot21(void);
	virtual void bfmeSlot22(void);
	virtual void bfmeSlot23(void);
	virtual void bfmeSlot24(void);
	virtual void bfmeSlot25(void);
	virtual void bfmeSlot26(void);
	virtual void bfmeSlot27(void);
	virtual void bfmeSlot28(void);
	virtual void bfmeSlot29(void);
	virtual void bfmeSlot30(void);
	virtual void bfmeSlot31(void);
	virtual void bfmeSlot32(void);
	virtual void bfmeSlot33(void);
	virtual void bfmeSlot34(void);
	virtual void bfmeSlot35(void);
	virtual void bfmeSlot36(void);
	virtual void bfmeSlot37(void);
	virtual void bfmeSlot38(void);
	virtual void bfmeSlot39(void);
	virtual void bfmeSlot40(void);
	virtual void bfmeSlot41(void);
	virtual void bfmeTake(void *field);			// slot 42, vtable+0xA8
};

// ?bfmeForward@Gen_002ED680@@QAEXPAUBfmeFieldSource@@@Z
void Gen_002ED680::bfmeForward(BfmeFieldSource *source)
{
	bfmeTake(source->m_bfmeField);
}
