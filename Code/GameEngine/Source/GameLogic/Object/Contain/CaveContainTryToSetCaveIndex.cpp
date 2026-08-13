// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#include "PreRTS.h"
#include "Common/TunnelTracker.h"
#include "GameLogic/Module/CaveContain.h"
#include "GameLogic/CaveSystem.h"
#include "GameLogic/Object.h"

void CaveContain::tryToSetCaveIndex(Int newIndex)
{
	if (TheCaveSystem->canSwitchIndexToIndex(m_caveIndex, newIndex)) {
		TunnelTracker *oldTracker = TheCaveSystem->getTunnelTrackerForCaveIndex(m_caveIndex);
		TheCaveSystem->unregisterCave(m_caveIndex);
		oldTracker->onTunnelDestroyed(*(Object **)((unsigned)this + 0x5cc));

		m_caveIndex = newIndex;
		TheCaveSystem->registerNewCave(m_caveIndex);
		TunnelTracker *newTracker = TheCaveSystem->getTunnelTrackerForCaveIndex(m_caveIndex);
		newTracker->onTunnelCreated(*(Object **)((unsigned)this + 0x5cc));
	}
}
