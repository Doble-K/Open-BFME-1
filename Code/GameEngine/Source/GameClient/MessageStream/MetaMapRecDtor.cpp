// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// FILE: MetaMapRecDtor.cpp ///////////////////////////////////////////////////
//
// MetaMapRec::~MetaMapRec, retail 0x0060A330.
//
// MetaEvent.cpp compiles this destructor at 84 of 86 bytes through the
// reference GameClient/MetaEvent.h; both disagreements are the two member
// offsets it destroys.  There m_description and m_displayName are the last two
// members and land adjacent at +0x20 and +0x24, and retail destroys +0x18 then
// +0x0C -- twelve bytes apart, with three fields of something else wedged
// between them.  BFME reordered MetaMapRec, so the layout is spelled here
// rather than in a header MetaEvent.cpp and its neighbours share.
//
// The two members are AsciiString, not the UnicodeString the reference header
// declares.  Both destructor calls land on 0x00887940, which the ledger already
// names ?releaseBuffer@?$StringBase@D@@AAEXXZ -- the narrow one.  The wide
// StringBase<unsigned short> copy is a different body at 0x008881D0, so a
// UnicodeString member here misses by exactly that displacement.
//
// Only the two offsets and that width are evidence.  What sits at +0x10 and
// +0x14 this body does not say, so it is left as unnamed filler.
//
///////////////////////////////////////////////////////////////////////////////

class AsciiString
{
public:
	// Declared, never defined: only the .obj is produced and the call resolves
	// by name against the ledger.
	~AsciiString();
private:
	void *m_data;
};

class MemoryPoolObject
{
protected:
	// Inline and empty, which is all retail keeps of it: the vtable store that
	// follows the two member destructors is this destructor.
	virtual ~MemoryPoolObject() {}
};

class MetaMapRec : public MemoryPoolObject
{
public:

	// vptr @0x0
	MetaMapRec *m_next;											// @0x4
	int m_meta;															// @0x8
	AsciiString m_description;						// @0xc
	int m_bfmeUnknown10;										// @0x10
	int m_bfmeUnknown14;										// @0x14
	AsciiString m_displayName;						// @0x18

protected:

	virtual ~MetaMapRec();

};

MetaMapRec::~MetaMapRec()
{
}
