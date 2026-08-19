// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/stringbaseascii /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /ICode/Libraries/Source/WWVegas/WWLib
// stlport
//
// The SkyboxTextureSet block, retail 0x000B8C90. BFME-only; the INI block table
// in .data names it.
//
// The store is a global hash_map keyed by the block name, sitting at 0x012F1404
// as an object rather than behind a pointer - retail loads its address as an
// immediate into ecx at all three call sites.
//
// A name that is already in the map is skipped WHOLE: retail tests find()
// against end() and jumps past the allocation, the insert and the field parse
// alike, so a second SkyboxTextureSet block of the same name is not an override
// but a no-op. Only the AsciiString it built is unwound.
//
// The set itself is 0x18 bytes with a vtable at +0 and five zeroed dwords after
// it; the constructor at 0x000B83B0 is left to its own name rather than modelled
// here, because nothing in this block reads a field of it.
//
// The keyword goes through StringBase<char>::set(const char *, int) with the
// length computed inline, which is what BFME's AsciiString::set(const char *)
// compiles to - the same shape INIEmotion.cpp lands.
#include "PreRTS.h"
#include "Common/INI.h"
#include "Common/STLTypedefs.h"
#include "string_base.h"

class SkyboxTextureSet
{
public:
	SkyboxTextureSet();

	static const FieldParse m_fieldParseTable[];

private:
	char m_unmodelled[ 0x18 ];
};

typedef std::hash_map< AsciiString, SkyboxTextureSet *, rts::hash<AsciiString>, rts::equal_to<AsciiString> > SkyboxTextureSetMap;

extern SkyboxTextureSetMap TheSkyboxTextureSets;		// 0x012F1404

// ?parseSkyboxTextureSet@@YAXPAVINI@@@Z
void parseSkyboxTextureSet( INI *ini )
{
	AsciiString name;

	const char *token = ini->getNextToken();
	((StringBase<char> *)&name)->set( token, token ? (int)strlen( token ) : 0 );

	if( TheSkyboxTextureSets.find( name ) == TheSkyboxTextureSets.end() )
	{
		SkyboxTextureSet *set = new SkyboxTextureSet();

		TheSkyboxTextureSets[ name ] = set;

		ini->initFromINI( TheSkyboxTextureSets[ name ], SkyboxTextureSet::m_fieldParseTable );
	}
}
