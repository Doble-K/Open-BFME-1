// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /Code/GameEngine/Include /Code/GameEngine/Include/Precompiled /Code/Libraries/Source/WWVegas/WWLib

struct Coord3D;

class BFMERopeDrawable
{
public:
    const Coord3D *getPosition() const;
};

class BFMERopeDrawableGetPositionShim
{
public:
    const Coord3D *get() const;
};

const Coord3D *BFMERopeDrawable::getPosition() const
{
    return ((const BFMERopeDrawableGetPositionShim *)this)->get();
}
