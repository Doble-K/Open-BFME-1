// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath
// stlport
#include "PreRTS.h"

#include "GameLogic/GameLogic.h"
#include "GameLogic/Object.h"
#include "GameLogic/Module/DeletionUpdate.h"

void DeletionUpdate::setLifetimeRange(UnsignedInt minFrames, UnsignedInt maxFrames)
{
	UnsignedInt delay = calcSleepDelay(minFrames, maxFrames);
	Object *object = *reinterpret_cast<Object **>(reinterpret_cast<char *>(this) + 0x08);
	setWakeFrame(object, UPDATE_SLEEP(delay));
}

UnsignedInt DeletionUpdate::calcSleepDelay(UnsignedInt minFrames, UnsignedInt maxFrames)
{
#line 55 "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Update\\DeletionUpdate.cpp"
	UnsignedInt delay = GameLogicRandomValue(minFrames, maxFrames);
	if (delay < 1)
		delay = 1;
	m_dieFrame = TheGameLogic->getFrame() + delay;
	return delay;
}
