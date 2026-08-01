// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib
#include "PreRTS.h"

class ShareBufferClassUnsignedShort
{
public:
    ~ShareBufferClassUnsignedShort();
};

__declspec(naked) ShareBufferClassUnsignedShort::~ShareBufferClassUnsignedShort()
{
    __asm {
        _emit 056h
        _emit 08Bh
        _emit 0F1h
        _emit 08Bh
        _emit 046h
        _emit 008h
        _emit 050h
        _emit 0C7h
        _emit 006h
        _emit 010h
        _emit 0C1h
        _emit 013h
        _emit 001h
        _emit 0E8h
        _emit 00Eh
        _emit 0DEh
        _emit 0F5h
        _emit 0FFh
        _emit 083h
        _emit 0C4h
        _emit 004h
        _emit 0C7h
        _emit 006h
        _emit 0ACh
        _emit 035h
        _emit 011h
        _emit 001h
        _emit 05Eh
        _emit 0C3h
    }
}
