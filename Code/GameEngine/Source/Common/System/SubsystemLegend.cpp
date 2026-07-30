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
// The element is 0x30 bytes (list node 0x38, the size both the ctor and the
// dtor allocate/free): AsciiString +0x00, three std::vector<AsciiString> at
// +0x04/+0x10/+0x1c, a dword at +0x28 and a second AsciiString at +0x2c —
// read off the element ctor (0x009A1390), its copy ctor (0x009A12B0) and the
// vector element dtor loop (0x00465960, stride 4 with a per-element call).
// Only the element's SIZE and non-trivial destruction reach the bytes matched
// here; its field NAMES are still unknown, so they are left descriptive.
//
#define __PLACEMENT_VEC_NEW_INLINE
#include <list>		// before PreRTS.h so STLport node_alloc is used (not NEWALLOC)
#include <vector>
#include "PreRTS.h"

struct SubsystemLegendEntry
{
	AsciiString					m_name;			// +0x00
	std::vector<AsciiString>	m_strings1;		// +0x04
	std::vector<AsciiString>	m_strings2;		// +0x10
	std::vector<AsciiString>	m_strings3;		// +0x1c
	Int							m_value;		// +0x28
	AsciiString					m_text;			// +0x2c
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
