// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/fullfade /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#define Matrix4x4 Matrix4

#include "PreRTS.h"
#include "GameClient/GameWindowTransitions.h"

__declspec(noinline) Bool TransitionGroup::isFinished(void)
{
	// The BFME STLPort list layout is preserved here because the ZH shim's iterator ABI differs.
	struct TransitionNode
	{
		TransitionNode *next;
		TransitionNode *previous;
		TransitionWindow *window;
	};

	TransitionNode *sentinel = *reinterpret_cast<TransitionNode **>(
		reinterpret_cast<unsigned char *>(this) + 4);
	for (TransitionNode *node = sentinel->next; node != sentinel; node = node->next)
	{
		unsigned char *window = reinterpret_cast<unsigned char *>(node->window);
		unsigned char *transition = *reinterpret_cast<unsigned char **>(window + 0x10);
		if (transition && !*reinterpret_cast<Bool *>(transition + 8))
			return FALSE;
	}
	return TRUE;
}

Bool GameWindowTransitionsHandler::isFinished(void)
{
	// BFME serializes transition queries with a critical section absent from the ZH class.
	CRITICAL_SECTION *lock = reinterpret_cast<CRITICAL_SECTION *>(
		reinterpret_cast<unsigned char *>(this) + 0x34);
	EnterCriticalSection(lock);

	TransitionGroup *group = *reinterpret_cast<TransitionGroup **>(
		reinterpret_cast<unsigned char *>(this) + 0x20);
	if (group)
	{
		Bool finished = group->isFinished();
		LeaveCriticalSection(lock);
		return finished;
	}

	LeaveCriticalSection(lock);
	return TRUE;
}
