// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

#include "PreRTS.h"

class MetaMapRec
{
public:
    MetaMapRec();
};

__declspec(naked) MetaMapRec::MetaMapRec()
{
    __asm {
        _emit 08Bh
        _emit 0C1h
        _emit 033h
        _emit 0C9h
        _emit 089h
        _emit 048h
        _emit 01Ch
        _emit 089h
        _emit 048h
        _emit 020h
        _emit 0C3h
    }
}
