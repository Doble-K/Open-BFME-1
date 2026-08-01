// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

#include "PreRTS.h"

class GameWindow;

class Radar
{
public:
    bool isRadarWindow(GameWindow *);
};

__declspec(naked) bool Radar::isRadarWindow(GameWindow *)
{
    __asm {
        _emit 08Bh
        _emit 081h
        _emit 038h
        _emit 014h
        _emit 000h
        _emit 000h
        _emit 03Bh
        _emit 044h
        _emit 024h
        _emit 004h
        _emit 075h
        _emit 00Ch
        _emit 085h
        _emit 0C0h
        _emit 074h
        _emit 008h
        _emit 0B8h
        _emit 001h
        _emit 000h
        _emit 000h
        _emit 000h
        _emit 0C2h
        _emit 004h
        _emit 000h
        _emit 033h
        _emit 0C0h
        _emit 0C2h
        _emit 004h
        _emit 000h
    }
}
