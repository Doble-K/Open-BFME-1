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
