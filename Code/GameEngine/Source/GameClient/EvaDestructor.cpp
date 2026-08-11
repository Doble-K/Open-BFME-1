// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME5: Eva::~Eva, spelled against the retail BFME layout.
//
// Retail's Eva is a SubsystemInterface and a Snapshot: two vtable pointers, one
// at +0x00 and one at +0x08, both of which this body installs before it unwinds
// its own members and both of which the Eva constructor at 0x004271B0 installs
// the same way.  The four parsed-table containers at +0x0c/+0x18/+0x24/+0x38
// destroy through out-of-line calls; the +0x4c check vector is a POD
// std::vector whose STLport node_alloc deallocation is inlined at the 0x80
// threshold.  Zero Hour's Eva has neither the default-copy halves nor the
// second base, so the class is spelled against the retail layout in its own
// translation unit (AGENTS.md, "Placement and integrity").
//
// Identity: it writes the same two vtables, 0x010F1FA8 at +0x00 and 0x010F1F94
// at +0x08, that every other Eva body is dispatched through -- slot 1 of the
// first is Eva::init, slot 4 is the matched reset body and slot 5 the matched
// update body -- and it tears down exactly the members those bodies use.
// Snapshot's own vtable at 0x01073744 is restored at +0x08 before the
// SubsystemInterface destructor at 0x009A1A40 runs, which is the inline empty
// ~Snapshot that pins the second base.

#include <vector>

// Retail per-message check record, 24 bytes of POD: two millisecond countdowns
// and a played flag at +0x14.
struct EvaCheck
{
	float m_timeUntilExpire;
	float m_timeUntilNextCheck;
	char  m_rest[ 0x10 ];
};

// vector<EvaCheckInfo>, 12 bytes.  Its element type owns storage, so retail's
// destructor is a loop and stays out of line at 0x00426220.
class EvaCheckInfoVec
{
public:
	~EvaCheckInfoVec( void );

private:
	char m_raw[ 0x0c ];
};

// The 20-byte per-side sound container; destructor out of line at 0x00424890.
class EvaSideSoundsVec
{
public:
	~EvaSideSoundsVec( void );

private:
	char m_raw[ 0x14 ];
};

// The +0x08 base.  Its destructor is inline and empty in retail -- the body
// only restores the vtable pointer -- which is why no second base destructor
// call appears.
class Snapshot
{
public:
	virtual ~Snapshot( void ) {}
	virtual void crc( void ) = 0;
	virtual void xfer( void ) = 0;
	virtual void loadPostProcess( void ) = 0;
};

// The primary base: vtable pointer at +0x00 and the subsystem name at +0x04,
// destroyed out of line at 0x009A1A40.
class SubsystemInterface
{
public:
	virtual ~SubsystemInterface( void );
	virtual void init( void ) = 0;

private:
	void *m_name;				// +0x04
};

class Eva : public SubsystemInterface, public Snapshot
{
public:
	virtual ~Eva( void );

private:
	EvaCheckInfoVec       m_checkInfos;		// +0x0c
	EvaCheckInfoVec       m_defaultCheckInfos;	// +0x18
	EvaSideSoundsVec      m_sideSounds;		// +0x24
	EvaSideSoundsVec      m_defaultSideSounds;	// +0x38
	std::vector<EvaCheck> m_checks;			// +0x4c
	int                   m_speechHandle;		// +0x58
	bool                  m_enabled;		// +0x5c
};

Eva::~Eva( void )
{
}
