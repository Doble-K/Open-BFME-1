// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

#include "PreRTS.h"

__declspec(naked) void Log_DX8_ErrorCode(unsigned int errorCode)
{
    __asm {
        _emit 056h
        _emit 08Bh
        _emit 074h
        _emit 024h
        _emit 008h
        _emit 08Bh
        _emit 006h
        _emit 050h
        _emit 0E8h
        _emit 0E3h
        _emit 0D5h
        _emit 0FEh
        _emit 0FFh
        _emit 056h
        _emit 0FFh
        _emit 015h
        _emit 0D4h
        _emit 093h
        _emit 035h
        _emit 001h
        _emit 083h
        _emit 0C4h
        _emit 008h
        _emit 05Eh
        _emit 0C3h
    }
}
