// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib
#include "PreRTS.h"

class FireWeaponUpdateModuleData
{
public:
    FireWeaponUpdateModuleData();
};

__declspec(naked) FireWeaponUpdateModuleData::FireWeaponUpdateModuleData()
{
    __asm {
        _emit 08Bh
        _emit 0C1h
        _emit 033h
        _emit 0C9h
        _emit 0C7h
        _emit 000h
        _emit 068h
        _emit 0EDh
        _emit 00Bh
        _emit 001h
        _emit 089h
        _emit 048h
        _emit 008h
        _emit 088h
        _emit 048h
        _emit 00Ch
        _emit 088h
        _emit 048h
        _emit 00Dh
        _emit 088h
        _emit 048h
        _emit 00Eh
        _emit 0C3h
    }
}
