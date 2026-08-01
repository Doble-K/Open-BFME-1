// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib
#include "PreRTS.h"

class OCLUpdateModuleData
{
public:
    OCLUpdateModuleData();
};

__declspec(naked) OCLUpdateModuleData::OCLUpdateModuleData()
{
    __asm {
        _emit 08Bh
        _emit 0C1h
        _emit 033h
        _emit 0C9h
        _emit 0C7h
        _emit 000h
        _emit 0C0h
        _emit 001h
        _emit 00Ch
        _emit 001h
        _emit 089h
        _emit 048h
        _emit 00Ch
        _emit 089h
        _emit 048h
        _emit 010h
        _emit 089h
        _emit 048h
        _emit 008h
        _emit 088h
        _emit 048h
        _emit 014h
        _emit 0C3h
    }
}
