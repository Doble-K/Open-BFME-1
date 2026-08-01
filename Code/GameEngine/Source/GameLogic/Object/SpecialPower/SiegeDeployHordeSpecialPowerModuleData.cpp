// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib
#include "PreRTS.h"

class SiegeDeployHordeSpecialPowerModuleData
{
public:
    SiegeDeployHordeSpecialPowerModuleData();
};

__declspec(naked) SiegeDeployHordeSpecialPowerModuleData::SiegeDeployHordeSpecialPowerModuleData()
{
    __asm {
        _emit 056h
        _emit 08Bh
        _emit 0F1h
        _emit 0E8h
        _emit 04Fh
        _emit 0E2h
        _emit 0DBh
        _emit 0FFh
        _emit 0C7h
        _emit 006h
        _emit 040h
        _emit 072h
        _emit 00Bh
        _emit 001h
        _emit 0C6h
        _emit 086h
        _emit 0D0h
        _emit 001h
        _emit 000h
        _emit 000h
        _emit 000h
        _emit 08Bh
        _emit 0C6h
        _emit 05Eh
        _emit 0C3h
    }
}
