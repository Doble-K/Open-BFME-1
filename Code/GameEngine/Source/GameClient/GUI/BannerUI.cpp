// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
//
// The BannerUI block -- BFME's unit banners, which Zero Hour has no equivalent
// for. One global settings object, parsed straight into.
//
// Two names here are ours rather than retail's, and it is worth being explicit
// about which. The block keyword "BannerUI" comes from the registry, so the
// settings class is named. The pointer at 0x012F4B70 is not: nothing in the
// image names it, and the only matched rows that touch it are InGameUI's
// constructor, destructor and update, which say where it is owned but not what
// it is called. Both the variable name and the parse function's name are
// therefore chosen to match the keyword. Neither affects the bytes -- the global
// is a DIR32 the verifier fills in from the target -- which is exactly why they
// are called out instead of being left to look proven.
#include "PreRTS.h"
#include "Common/INI.h"

class BannerUI
{
public:
	static const FieldParse m_fieldParseTable[];
};

extern BannerUI *TheBannerUI;

void parseBannerUI( INI *ini )
{
	ini->initFromINI( TheBannerUI, BannerUI::m_fieldParseTable );
}
