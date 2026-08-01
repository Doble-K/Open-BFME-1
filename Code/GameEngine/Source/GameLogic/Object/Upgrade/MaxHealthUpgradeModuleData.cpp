// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib
#include "PreRTS.h"

class MaxHealthUpgradeModuleData
{
public:
    MaxHealthUpgradeModuleData();
};

__declspec(naked) MaxHealthUpgradeModuleData::MaxHealthUpgradeModuleData()
{
    __asm {
        _emit 056h
        _emit 08Bh
        _emit 0F1h
        _emit 08Dh
        _emit 04Eh
        _emit 008h
        _emit 0E8h
        _emit 00Bh
        _emit 08Bh
        _emit 0D3h
        _emit 0FFh
        _emit 033h
        _emit 0C0h
        _emit 089h
        _emit 046h
        _emit 070h
        _emit 089h
        _emit 046h
        _emit 074h
        _emit 0C7h
        _emit 006h
        _emit 0A0h
        _emit 0D2h
        _emit 00Ch
        _emit 001h
        _emit 08Bh
        _emit 0C6h
        _emit 05Eh
        _emit 0C3h
    }
}
