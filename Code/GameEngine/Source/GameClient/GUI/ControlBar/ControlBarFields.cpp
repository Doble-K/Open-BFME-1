// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/controlbar /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
//
// ControlBar member functions byte-matched against the reconstructed BFME
// field boundary (reference/shims/controlbar/GameClient/ControlBar.h):
// m_specialPowerShortcutParent@0xFC (ZH header has it at 0x184).
//
// They live here rather than in GUI/ControlBar/ControlBar.cpp because that
// TU resolves GameClient/ControlBar.h to the ZH-layout reference header (40+
// already-matched functions there depend on that layout for fields before
// this boundary, which are not yet reconstructed); the private
// /Ireference/shims/controlbar above makes only this TU see the true BFME
// offset, so converting this leaf here does not disturb ControlBar.cpp.
#include "PreRTS.h"
#include "GameClient/ControlBar.h"
#include "GameClient/GameWindow.h"

// ?hideSpecialPowerShortcut@ControlBar@@QAEXXZ
void ControlBar::hideSpecialPowerShortcut( void )
{
	if( !m_specialPowerShortcutParent )
		return;

	m_specialPowerShortcutParent->winHide( TRUE );

}

// AsciiString's only member is a StringBase<char>::Header* even though
// ascii_string.h names it m_text (see BFMEStringHeader's comment in the
// shim header). It's private there; alias its layout locally instead of
// touching that shared header for one field read.
struct AsciiStringRaw
{
	BFMEStringHeader *header;
};

static inline int headerLength( const BFMEStringHeader *header )
{
	return header ? header->length : 0;
}

static inline const char *headerStr( const BFMEStringHeader *header )
{
	return header ? header->data : "";
}

// ?findNonConstCommandButton@ControlBar@@IAEPAVCommandButton@@ABVAsciiString@@@Z present-unmatched
//
// m_commandButtons@0x2c IS proven by this body's first instruction
// (`mov eax,[ecx+0x2c]`, retail RVA 0x4A0270) independent of everything
// below; see reference/shims/controlbar/GameClient/ControlBar.h. The
// function itself does NOT byte-verify: this reproduces the traversal and
// the inlined AsciiString-header compare (raw StringBase<char>::Header
// memcmp, no CALL -- matches target exactly for the name-side null-check)
// but is 8 bytes short of the retail 126B body in two spots that no source
// rewrite reproduced (ternary/if-else, combined vs separate null-check
// helpers, nested-if vs &&, sub-in-place vs fresh var, /Oi -- all tried,
// see reverse/re_attempts.log): (1) retail re-checks command->getName()'s
// header for null TWICE (once for length, once for the data pointer; our
// compiler always CSEs that into one shared check), and (2) retail computes
// the final cmdLen==nameLen via sub+mov+test+je where our compiler always
// fuses the sub into the je directly. Both read as MSVC 7.1 register-
// pressure/CSE nondeterminism, not a real source-shape difference. Do not
// re-attempt the same variants; a fresh idea is needed.
CommandButton *ControlBar::findNonConstCommandButton( const AsciiString& name )
{
	for( const CommandButton *command = m_commandButtons; command; command = command->getNext() )
	{
		const BFMEStringHeader *nameHeader = reinterpret_cast<const AsciiStringRaw &>( name ).header;
		int nameLen = headerLength( nameHeader );
		const char *nameChars = headerStr( nameHeader );

		const BFMEStringHeader *cmdHeader = reinterpret_cast<const AsciiStringRaw &>( command->getName() ).header;
		int cmdLen = headerLength( cmdHeader );
		const char *cmdChars = headerStr( cmdHeader );

		int minLen = cmdLen < nameLen ? cmdLen : nameLen;
		int result = memcmp( cmdChars, nameChars, minLen );
		if( result == 0 && cmdLen == nameLen )
			return const_cast<CommandButton *>( command );
	}

	return NULL;
}
