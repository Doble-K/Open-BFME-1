// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /Code/GameEngine/Include /Code/GameEngine/Include/Precompiled /Code/Libraries/Source/WWVegas/WWLib

struct Coord3D;
enum PathfindLayerEnum { PATHFIND_LAYER_DUMMY };

class Path
{
public:
    void appendNode(const Coord3D *position, PathfindLayerEnum layer);
};

__declspec(naked) void Path::appendNode(const Coord3D *, PathfindLayerEnum)
{
    __asm {
        _emit 0E9h
        _emit 06Dh
        _emit 021h
        _emit 013h
        _emit 000h
    }
}
