// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /Code/GameEngine/Include /Code/GameEngine/Include/Precompiled /Code/Libraries/Source/WWVegas/WWLib

struct Coord3D;

class ToppleUpdate
{
public:
    void applyTopplingForce(const Coord3D *, float, unsigned int);
};

__declspec(naked) void ToppleUpdate::applyTopplingForce(const Coord3D *, float, unsigned int)
{
    __asm {
        _emit 0E9h
        _emit 024h
        _emit 01Fh
        _emit 027h
        _emit 000h
    }
}
