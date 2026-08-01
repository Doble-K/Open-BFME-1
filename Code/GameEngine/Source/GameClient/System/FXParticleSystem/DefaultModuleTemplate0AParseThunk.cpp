// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

#include "PreRTS.h"

class INI;

namespace FXParticleSystem
{
template<int Category> class DefaultModuleTemplate { public: void parse(INI *); };

template<int Category>
__declspec(naked) void DefaultModuleTemplate<Category>::parse(INI *)
{
    __asm {
        _emit 068h
        _emit 060h
        _emit 034h
        _emit 011h
        _emit 001h
        _emit 051h
        _emit 08Bh
        _emit 04Ch
        _emit 024h
        _emit 00Ch
        _emit 0E8h
        _emit 061h
        _emit 02Eh
        _emit 026h
        _emit 000h
        _emit 0C2h
        _emit 004h
        _emit 000h
    }
}

template void DefaultModuleTemplate<0>::parse(INI *);
}
