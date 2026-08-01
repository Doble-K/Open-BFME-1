// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib
#include "PreRTS.h"

class DestroyEnvironmentUpdateModuleData
{
public:
    DestroyEnvironmentUpdateModuleData();
};

__declspec(naked) DestroyEnvironmentUpdateModuleData::DestroyEnvironmentUpdateModuleData()
{
    __asm {
        _emit 08Bh
        _emit 0C1h
        _emit 0C7h
        _emit 000h
        _emit 000h
        _emit 0DAh
        _emit 00Bh
        _emit 001h
        _emit 0C7h
        _emit 040h
        _emit 008h
        _emit 000h
        _emit 000h
        _emit 000h
        _emit 000h
        _emit 0C7h
        _emit 040h
        _emit 00Ch
        _emit 064h
        _emit 000h
        _emit 000h
        _emit 000h
        _emit 0C3h
    }
}
