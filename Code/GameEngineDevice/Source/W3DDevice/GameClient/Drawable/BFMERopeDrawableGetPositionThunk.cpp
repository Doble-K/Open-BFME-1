// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /Code/GameEngine/Include /Code/GameEngine/Include/Precompiled /Code/Libraries/Source/WWVegas/WWLib

struct Coord3D;

class BFMERopeDrawable
{
public:
    const Coord3D *getPosition() const;
};

__declspec(naked) const Coord3D *BFMERopeDrawable::getPosition() const
{
    __asm {
        _emit 0E9h
        _emit 05Eh
        _emit 01Fh
        _emit 03Dh
        _emit 000h
    }
}
