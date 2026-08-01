// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib
#include "PreRTS.h"

class ExperienceScalarUpgradeModuleData
{
public:
    ExperienceScalarUpgradeModuleData();
};

__declspec(naked) ExperienceScalarUpgradeModuleData::ExperienceScalarUpgradeModuleData()
{
    __asm {
        _emit 056h
        _emit 08Bh
        _emit 0F1h
        _emit 08Dh
        _emit 04Eh
        _emit 008h
        _emit 0E8h
        _emit 01Bh
        _emit 09Fh
        _emit 0D3h
        _emit 0FFh
        _emit 0C7h
        _emit 006h
        _emit 0D8h
        _emit 0C9h
        _emit 00Ch
        _emit 001h
        _emit 0C7h
        _emit 046h
        _emit 070h
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
