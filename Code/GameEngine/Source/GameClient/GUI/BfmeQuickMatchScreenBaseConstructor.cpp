// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: BfmeQuickMatchScreenBase's constructor, retail 0x00470620, 86
// bytes. The body carried only a machine byte-dump row; reverse/reloc_names.csv
// holds the name with identity=real, and the member it ends with is pinned with
// this row.
//
// The vtable goes in, five fields from +0x04 out to the byte at +0x14 are
// cleared, and the argument is handed straight on. Only one of those five is
// written before the unwind state: that is the member whose destructor the
// frame exists for, and its constructor is nothing but the null. The rest are
// body assignments.

typedef int Int;

class BfmeQuickMatchSlot
{
public:
	BfmeQuickMatchSlot() { m_bfmePointer = 0; }
	~BfmeQuickMatchSlot();

private:
	void *m_bfmePointer;
};

class BfmeQuickMatchScreenBase
{
public:
	BfmeQuickMatchScreenBase(void *screen);

	virtual void bfmeSlot0(void);

private:
	void bfmeAttach(void *screen);				// ILT 0x0000C0A4

	BfmeQuickMatchSlot m_bfmeSlot;				// +0x04
	Int m_bfme08;						// +0x08
	Int m_bfme0C;						// +0x0C
	Int m_bfme10;						// +0x10
	char m_bfme14;						// +0x14
};

// ??0BfmeQuickMatchScreenBase@@QAE@PAX@Z
BfmeQuickMatchScreenBase::BfmeQuickMatchScreenBase(void *screen)
{
	m_bfme08 = 0;
	m_bfme0C = 0;
	m_bfme10 = 0;
	m_bfme14 = 0;

	bfmeAttach(screen);
}
