// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib
#include "PreRTS.h"

class Vector3
{
};

class VertexMaterialClass
{
public:
    void Get_Diffuse(Vector3 *diffuse) const;
};

__declspec(naked) void VertexMaterialClass::Get_Diffuse(Vector3 *) const
{
    __asm {
        _emit 08Bh
        _emit 041h
        _emit 008h
        _emit 0D9h
        _emit 000h
        _emit 0D9h
        _emit 040h
        _emit 004h
        _emit 0D9h
        _emit 040h
        _emit 008h
        _emit 08Bh
        _emit 044h
        _emit 024h
        _emit 004h
        _emit 0D9h
        _emit 0CAh
        _emit 0D9h
        _emit 018h
        _emit 0D9h
        _emit 058h
        _emit 004h
        _emit 0D9h
        _emit 058h
        _emit 008h
        _emit 0C2h
        _emit 004h
        _emit 000h
    }
}
