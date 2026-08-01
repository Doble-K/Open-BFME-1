// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib
#include "PreRTS.h"

enum TimeOfDay { TIME_OF_DAY_INVALID = 0 };

class ControlBar
{
public:
    void preloadAssets(TimeOfDay timeOfDay);
};

__declspec(naked) void ControlBar::preloadAssets(TimeOfDay)
{
    __asm {
        _emit 08Bh
        _emit 049h
        _emit 030h
        _emit 085h
        _emit 0C9h
        _emit 074h
        _emit 005h
        _emit 0E9h
        _emit 00Ah
        _emit 078h
        _emit 0DBh
        _emit 0FFh
        _emit 0C3h
    }
}
