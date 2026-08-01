// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

#include "PreRTS.h"

class OCLUpdateModuleData
{
public:
    ~OCLUpdateModuleData();
};

__declspec(naked) OCLUpdateModuleData::~OCLUpdateModuleData()
{
    __asm {
        _emit 0C7h
        _emit 001h
        _emit 044h
        _emit 037h
        _emit 007h
        _emit 001h
        _emit 0C3h
    }
}
