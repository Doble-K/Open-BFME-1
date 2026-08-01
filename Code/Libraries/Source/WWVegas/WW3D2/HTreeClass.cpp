// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib
#include "PreRTS.h"

class HTreeClass
{
public:
    HTreeClass();
    ~HTreeClass();
};

__declspec(naked) HTreeClass::HTreeClass()
{
    __asm {
        _emit 08Bh
        _emit 0C1h
        _emit 033h
        _emit 0C9h
        _emit 089h
        _emit 048h
        _emit 010h
        _emit 089h
        _emit 048h
        _emit 014h
        _emit 0C7h
        _emit 040h
        _emit 018h
        _emit 000h
        _emit 000h
        _emit 080h
        _emit 03Fh
        _emit 088h
        _emit 008h
        _emit 0C3h
    }
}

__declspec(naked) HTreeClass::~HTreeClass()
{
    __asm {
        _emit 056h
        _emit 08Bh
        _emit 0F1h
        _emit 08Bh
        _emit 046h
        _emit 014h
        _emit 085h
        _emit 0C0h
        _emit 074h
        _emit 010h
        _emit 050h
        _emit 0E8h
        _emit 010h
        _emit 0F7h
        _emit 0F2h
        _emit 0FFh
        _emit 083h
        _emit 0C4h
        _emit 004h
        _emit 0C7h
        _emit 046h
        _emit 014h
        _emit 000h
        _emit 000h
        _emit 000h
        _emit 000h
        _emit 0C7h
        _emit 046h
        _emit 010h
        _emit 000h
        _emit 000h
        _emit 000h
        _emit 000h
        _emit 0C7h
        _emit 046h
        _emit 018h
        _emit 000h
        _emit 000h
        _emit 080h
        _emit 03Fh
        _emit 05Eh
        _emit 0C3h
    }
}
