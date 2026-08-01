// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

#include "PreRTS.h"

extern "C" __declspec(naked) int _atexit(void (__cdecl *)())
{
    __asm {
        _emit 0FFh
        _emit 074h
        _emit 024h
        _emit 004h
        _emit 0E8h
        _emit 0D1h
        _emit 0FFh
        _emit 0FFh
        _emit 0FFh
        _emit 0F7h
        _emit 0D8h
        _emit 01Bh
        _emit 0C0h
        _emit 0F7h
        _emit 0D8h
        _emit 059h
        _emit 048h
        _emit 0C3h
    }
}
