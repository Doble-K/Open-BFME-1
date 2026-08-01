// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib
#include "PreRTS.h"

extern "C" __declspec(naked) int IsStatsConnected()
{
    __asm {
        _emit 08Bh
        _emit 00Dh
        _emit 038h
        _emit 090h
        _emit 02Dh
        _emit 001h
        _emit 033h
        _emit 0C0h
        _emit 083h
        _emit 0F9h
        _emit 0FFh
        _emit 00Fh
        _emit 095h
        _emit 0C0h
        _emit 0C3h
    }
}
