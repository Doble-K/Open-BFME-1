// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/sweep /Ireference/shims/locomotor /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#include "PreRTS.h"
#include "Common/Player.h"
#include "Common/PlayerList.h"
#include "GameClient/ControlBar.h"
#include "GameClient/Drawable.h"
#include "GameClient/View.h"

static Object *validUnderCursor(const ICoord2D *mouse, const CommandButton *command, PickType pickType)
{
	Object *pickObj = NULL;
	Drawable *pick = TheTacticalView->pickDrawable(mouse, FALSE, pickType);

	Object *pickedObject = pick ? *reinterpret_cast<Object **>(reinterpret_cast<char *>(pick) + 0xFC) : NULL;
	if (pickedObject) {
		Player *player = ThePlayerList->getLocalPlayer();
		pickObj = pickedObject;
		if (!command->isValidObjectTarget(player, pickObj))
			pickObj = NULL;
	}

	return pickObj;
}

Object *BFME_Valid_Under_Cursor(const ICoord2D *mouse, const CommandButton *command, PickType pickType)
{
	return validUnderCursor(mouse, command, pickType);
}
