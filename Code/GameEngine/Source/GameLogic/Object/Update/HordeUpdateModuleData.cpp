// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib
#include "PreRTS.h"

class HordeContainModuleData
{
public:
    HordeContainModuleData();
};

__declspec(naked) HordeContainModuleData::HordeContainModuleData()
{
    __asm {
        _emit 056h
        _emit 08Bh
        _emit 0F1h
        _emit 0E8h
        _emit 0F8h
        _emit 03Ah
        _emit 0E2h
        _emit 0FFh
        _emit 0C7h
        _emit 006h
        _emit 0F8h
        _emit 0BCh
        _emit 00Ah
        _emit 001h
        _emit 0C7h
        _emit 086h
        _emit 068h
        _emit 001h
        _emit 000h
        _emit 000h
        _emit 000h
        _emit 000h
        _emit 000h
        _emit 000h
        _emit 08Bh
        _emit 0C6h
        _emit 05Eh
        _emit 0C3h
    }
}
