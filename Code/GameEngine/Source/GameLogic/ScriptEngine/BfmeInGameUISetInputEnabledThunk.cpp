// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

#include "PreRTS.h"

class BfmeInGameUI_setInputEnabled
{
public:
    void setInputEnabled(bool);
};

__declspec(naked) void BfmeInGameUI_setInputEnabled::setInputEnabled(bool)
{
    __asm {
        _emit 08Bh
        _emit 001h
        _emit 08Dh
        _emit 051h
        _emit 00Eh
        _emit 052h
        _emit 08Bh
        _emit 054h
        _emit 024h
        _emit 008h
        _emit 052h
        _emit 0FFh
        _emit 090h
        _emit 020h
        _emit 001h
        _emit 000h
        _emit 000h
        _emit 0C2h
        _emit 004h
        _emit 000h
    }
}
