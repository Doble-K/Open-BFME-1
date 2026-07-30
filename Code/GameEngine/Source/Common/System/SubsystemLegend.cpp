// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
//
// SubsystemLegend — a BFME-only engine subsystem with no ZH counterpart.
// GameEngine::init registers it as "TheSubsystemLegend" (global 0x0134C6C4)
// and feeds it Data\INI\Default\SubsystemLegend.ini; the initSubsystem site
// (0x00079272) news 0x0c bytes and calls the ctor matched below.
//
// Layout recovered from retail, all offsets proven by the bodies here:
//   +0x00  SubsystemInterface base (vptr; AsciiString m_name at +0x04 — the
//          base ctor 0x009A1A30 writes exactly those two words)
//   +0x08  std::list<SubsystemLegendEntry> m_entries
// The element is 0x30 bytes (list node 0x38, the size the ctor and dtor
// allocate/free). Its dtor (0x00078210) destroys, in reverse declaration order,
// +0x2c, +0x1c, +0x10, +0x04, +0x00 — which pins the field layout below; the
// copy ctor (0x009A12B0) confirms it independently, copying +0x28 as a plain
// dword between two StringBase copy-ctor calls. Field NAMES are still unknown,
// so they are left descriptive.
//
#define __PLACEMENT_VEC_NEW_INLINE
#include <list>		// before PreRTS.h so STLport node_alloc is used (not NEWALLOC)
#include "PreRTS.h"

// Retail destroys both member types out-of-line, while the ZH AsciiString header
// and STLport's vector inline their release paths — that inlining is what blew
// the element dtor's register allocation. These stand-ins carry the same size
// and a declared-but-undefined dtor, so the call survives to be pinned in
// reverse/symbols.csv against the retail body it folds to.
struct BfmeLegendString			// AsciiString, 4B  -> dtor 0x00887940
{
	char *m_data;
	~BfmeLegendString();
};

struct BfmeLegendStringVec		// std::vector<AsciiString>, 12B -> dtor 0x000658A0
{
	void *m_start, *m_finish, *m_endOfStorage;
	~BfmeLegendStringVec();
};

struct SubsystemLegendEntry
{
	BfmeLegendString			m_name;			// +0x00
	BfmeLegendStringVec			m_strings1;		// +0x04
	BfmeLegendStringVec			m_strings2;		// +0x10
	BfmeLegendStringVec			m_strings3;		// +0x1c
	Int							m_value;		// +0x28
	BfmeLegendString			m_text;			// +0x2c
};

class SubsystemLegend : public SubsystemInterface
{
public:
	SubsystemLegend();
	virtual ~SubsystemLegend();

	virtual void init();
	virtual void reset();
	virtual void update();

private:
	std::list<SubsystemLegendEntry> m_entries;	// +0x08
};

// ??0SubsystemLegend@@QAE@XZ
SubsystemLegend::SubsystemLegend()
{
}

// ??1SubsystemLegend@@UAE@XZ
SubsystemLegend::~SubsystemLegend()
{
	m_entries.clear();
}

// ?init@SubsystemLegend@@UAEXXZ
void SubsystemLegend::init()
{
	m_entries.clear();
}

// ?reset@SubsystemLegend@@UAEXXZ
void SubsystemLegend::reset()
{
	m_entries.clear();
}

// ?update@SubsystemLegend@@UAEXXZ
void SubsystemLegend::update()
{
}
