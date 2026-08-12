// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// TeamFactory's default constructor, lifted from its MASM dump to C++.
//
// Retail body @ 0x000F2250 (130B):
//   - calls SubsystemInterface::SubsystemInterface() (0x009A1A30, already
//     matched in Code/GameEngine/Source/Common/System/SubsystemInterface.cpp)
//     to build the first base (vptr + AsciiString m_name, 8 bytes @ +0x00).
//   - inlines a second, trivial base ctor (no call reaches the bytes) that
//     just stores its own identity vptr @ +0x08 -- this is Snapshot, whose
//     real ctor (Common/System/Snapshot.cpp) is an empty {} body, so the
//     compiler folds it away and only its vptr store survives.
//   - stores TeamFactory's own vtables over both subobjects (+0x00, +0x08),
//     which only happens because TeamFactory overrides virtuals from each
//     base -- forcing a distinct combined vtable per polymorphic subobject.
//   - default-constructs an STLport std::map member @ +0x0c: allocates a
//     0x1c-byte header node (color + parent/left/right + a 12-byte unused
//     value slot), then links left/right back to itself for an empty tree.
//     The 0x1c node size keys the map by a 2-word (8-byte) type, matching
//     TeamFactoryList.cpp's independently-established finding that BFME's
//     m_prototypes is keyed by pair<NameKeyType,NameKeyType> (not the single
//     NameKeyType key ZH's Team.h declares). The exact key/value C++ types
//     don't affect this constructor's bytes (default ctor never compares
//     keys), only their combined size, so plain ints stand in here.
//   - zero-initializes two trailing Int members @ +0x18 / +0x1c
//     (m_uniqueTeamPrototypeID, m_uniqueTeamID). The map's own third
//     (empty, comparator) word @ +0x14 is a real member but is never
//     written -- an empty functor has no state to store.
//
// Object layout: SubsystemInterface(0x08) + Snapshot(0x04) + map(0x0c) +
// 2 Ints(0x08) = 0x20 total.
//
#define __PLACEMENT_VEC_NEW_INLINE
#include <map>		// before PreRTS.h so STLport node_alloc is used (not NEWALLOC)

// Modelled first base: only its ABI shape (vptr + one pointer-sized data
// member) and its ctor's mangled name matter here -- the real body lives in
// Code/GameEngine/Source/Common/System/SubsystemInterface.cpp (already
// matched), so the ctor below is declared, never defined, and resolves
// there as an external call.
class SubsystemInterface
{
public:
	SubsystemInterface();
	virtual ~SubsystemInterface();

	virtual void init(void);
	virtual void reset(void);
	virtual void update(void);

private:
	void *m_name;
};

// Modelled second base: matches Snapshot's shape. Its ctor is trivial and
// defined right here (inline) so the compiler folds the call away, exactly
// as retail's bytes show -- only the resulting vptr store reaches the
// target function.
class Snapshot
{
public:
	Snapshot() {}
	// Defined inline for the same reason the constructor is: retail's
	// ~TeamFactory @0x000F7512 restores this subobject's vtable and then calls
	// only ~SubsystemInterface, so Snapshot's destructor is folded away too.
	virtual ~Snapshot() {}

	virtual void crc(void);
	virtual void xfer(void);
	virtual void loadPostProcess(void);
};

// The map's value is anonymous in retail; the ledger already carries its
// _Rb_tree instantiation under the generated payload name gen_dump.py minted
// for it, so use that name and the destructor resolves to the matched row.
// The map is keyed by a two-word key with a plain pointer value, not by an int
// with an eight-byte value: addTeamPrototypeToList @0x000F3DA0 builds the key
// from two NAMEKEY calls before looking it up. Both shapes give the same 0x1C
// node, which is why the constructor, destructor and clear all match either
// way - only a body that uses the key can tell them apart.
class BfmeTeamPrototype
{
public:
	virtual ~BfmeTeamPrototype();
};
typedef std::pair<int, int> BfmeTeamPrototypeKey;

class TeamFactory : public SubsystemInterface, public Snapshot
{
public:
	TeamFactory();
	virtual ~TeamFactory();

	virtual void init(void);
	virtual void reset(void);
	virtual void update(void);

	void clear(void);

protected:
	virtual void crc(void);
	virtual void xfer(void);
	virtual void loadPostProcess(void);

private:
	// Keyed by int with an eight-byte value, not by a two-word key: the
	// destructor at 0x000F750B calls
	// _Rb_tree<H, pair<$$CBH, <8 bytes>>>::~_Rb_tree, which names the key type
	// directly. The node is 0x1C either way - 0x10 of links plus a 0xC value -
	// so the constructor's bytes are unchanged.
	std::map<BfmeTeamPrototypeKey, BfmeTeamPrototype *, std::less<BfmeTeamPrototypeKey> > m_prototypes;
	int m_uniqueTeamPrototypeID;
	int m_uniqueTeamID;
};

// ??0TeamFactory@@QAE@XZ
TeamFactory::TeamFactory()
	: m_uniqueTeamPrototypeID(0), m_uniqueTeamID(0)
{
}

// BFME nulls its singleton in the destructor; the store lands between clear()
// and the map teardown at 0x000F7500.
extern TeamFactory *TheTeamFactory;

// ??1TeamFactory@@UAE@XZ
TeamFactory::~TeamFactory()
{
	clear();
	TheTeamFactory = NULL;
}

// ?clear@TeamFactory@@QAEXXZ
void TeamFactory::clear()
{
	// must remove it from the map before deleting the TeamProto, since
	// the TeamProto will try to remove itself from the list when it goes away
	std::map<BfmeTeamPrototypeKey, BfmeTeamPrototype *, std::less<BfmeTeamPrototypeKey> > tmp = m_prototypes;
	m_prototypes.clear();
	for (std::map<BfmeTeamPrototypeKey, BfmeTeamPrototype *, std::less<BfmeTeamPrototypeKey> >::iterator it = tmp.begin(); it != tmp.end(); ++it)
	{
		delete it->second;
	}
}
