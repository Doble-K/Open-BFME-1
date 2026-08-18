// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/stringbaseascii /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /ICode/Libraries/Source/WWVegas/WWLib
// stlport
//
// The EmotionNugget block, retail 0x0037B8A0. BFME-only.
//
// Both names come from the binary: GameEngine::init passes the literal
// "TheEmotionSystem" immediately before pushing 0x012F0878, and the registrar it
// calls is initSubsystem<EmotionSystem>.
//
// The nugget itself is only its size, 0xF8, and the fact that its first member
// is the AsciiString the parser fills from the block keyword. Retail reaches
// StringBase<char>::set(const char *, int) there with the length computed
// inline, which is what BFME's AsciiString::set(const char *) compiles to - so
// the call is spelled through StringBase directly rather than through a shim,
// because that symbol is already in the ledger.
#include "PreRTS.h"
#include "Common/INI.h"
#include "string_base.h"

class EmotionNugget
{
public:
	EmotionNugget();

	static const FieldParse m_fieldParseTable[];

private:
	char m_unmodelled[ 0xF8 ];
};

class EmotionSystem
{
public:
	void addNugget( EmotionNugget *nugget );
};

extern EmotionSystem *TheEmotionSystem;			// 0x012F0878

// ?parseEmotionNugget@@YAXPAVINI@@@Z
void parseEmotionNugget( INI *ini )
{
	if( !TheEmotionSystem )
		return;

	const char *name = ini->getNextToken();

	EmotionNugget *nugget = new EmotionNugget();

	((StringBase<char> *)nugget)->set( name, name ? (int)strlen( name ) : 0 );

	ini->initFromINI( nugget, EmotionNugget::m_fieldParseTable );

	TheEmotionSystem->addNugget( nugget );
}
