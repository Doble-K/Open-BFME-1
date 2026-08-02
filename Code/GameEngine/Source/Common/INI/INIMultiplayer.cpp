// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/multiplayer /Ireference/shims/ini /Ireference/shims/iniexception /Ireference/shims/ini_noinline /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
//
// The "MultiplayerSettings" and "MultiplayerColor" blocks. Both are Zero Hour's
// INIMultiplayer.cpp bodies unchanged, and MultiplayerColorDefinition's layout
// is identical too: retail reaches m_rgbValue at +4 and m_rgbValueNight at +0x14,
// which is exactly where ZH's AsciiString/RGBColor/Color/RGBColor/Color ordering
// puts them.
//
// MultiplayerSettings itself is NOT ZH's -- retail news 0x88 bytes for it where
// ZH compiles to 0x90, and its INI fields land at different offsets. The BFME
// layout, decoded from the retail field table, is in reference/shims/multiplayer.
#include "PreRTS.h"
#include "Common/INI.h"
#include "Common/MultiplayerSettings.h"

void INI::parseMultiplayerSettingsDefinition( INI* ini )
{
	if( TheMultiplayerSettings )
	{
	}
	else
	{
		TheMultiplayerSettings = new MultiplayerSettings;
	}

	ini->initFromINI( TheMultiplayerSettings, TheMultiplayerSettings->getFieldParse() );
}

void INI::parseMultiplayerColorDefinition( INI* ini )
{
	const char *c;
	AsciiString name;
	MultiplayerColorDefinition *multiplayerColorDefinition;

	c = ini->getNextToken();
	// BFME assigns rather than calling set(c): retail inlines strlen and calls
	// the two-argument set, which is what operator=(const char *) expands to.
	name = c;

	multiplayerColorDefinition = TheMultiplayerSettings->findMultiplayerColorDefinitionByName( name );
	if( multiplayerColorDefinition == NULL )
		multiplayerColorDefinition = TheMultiplayerSettings->newMultiplayerColorDefinition( name );

	ini->initFromINI( multiplayerColorDefinition, multiplayerColorDefinition->getFieldParse() );

	multiplayerColorDefinition->setColor(multiplayerColorDefinition->getRGBValue());
	multiplayerColorDefinition->setNightColor(multiplayerColorDefinition->getRGBNightValue());
}
