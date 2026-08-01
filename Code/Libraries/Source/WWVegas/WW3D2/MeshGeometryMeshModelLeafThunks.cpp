// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

#include "PreRTS.h"

class TextureClass;
class VertexMaterialClass;

class MeshGeometryClass
{
protected:
    void Generate_Culling_Tree();

public:
    const char *Get_User_Text();
};

class MeshModelClass
{
public:
    void Replace_Texture(TextureClass *, TextureClass *);
    void Replace_VertexMaterial(VertexMaterialClass *, VertexMaterialClass *);
};

__declspec(naked) void MeshGeometryClass::Generate_Culling_Tree()
{
    __asm {
        _emit 08Bh
        _emit 041h
        _emit 010h
        _emit 085h
        _emit 0C0h
        _emit 074h
        _emit 004h
        _emit 08Bh
        _emit 040h
        _emit 00Ch
        _emit 0C3h
        _emit 033h
        _emit 0C0h
        _emit 0C3h
    }
}

__declspec(naked) const char *MeshGeometryClass::Get_User_Text()
{
    __asm {
        _emit 08Bh
        _emit 041h
        _emit 010h
        _emit 085h
        _emit 0C0h
        _emit 074h
        _emit 004h
        _emit 08Bh
        _emit 040h
        _emit 00Ch
        _emit 0C3h
        _emit 033h
        _emit 0C0h
        _emit 0C3h
    }
}

__declspec(naked) void MeshModelClass::Replace_Texture(TextureClass *, TextureClass *)
{
    __asm {
        _emit 08Bh
        _emit 041h
        _emit 010h
        _emit 085h
        _emit 0C0h
        _emit 074h
        _emit 004h
        _emit 08Bh
        _emit 040h
        _emit 00Ch
        _emit 0C3h
        _emit 033h
        _emit 0C0h
        _emit 0C3h
    }
}

__declspec(naked) void MeshModelClass::Replace_VertexMaterial(VertexMaterialClass *, VertexMaterialClass *)
{
    __asm {
        _emit 08Bh
        _emit 041h
        _emit 010h
        _emit 085h
        _emit 0C0h
        _emit 074h
        _emit 004h
        _emit 08Bh
        _emit 040h
        _emit 00Ch
        _emit 0C3h
        _emit 033h
        _emit 0C0h
        _emit 0C3h
    }
}
