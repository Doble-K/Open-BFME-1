// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /Code/GameEngine/Include /Code/GameEngine/Include/Precompiled /Code/Libraries/Source/WWVegas/WWLib

struct Coord3D;

class ToppleUpdate
{
public:
    void applyTopplingForce(const Coord3D *, float, unsigned int);
};

class ToppleUpdateApplyTopplingForceShim
{
public:
    void apply(const Coord3D *dir, float speed, unsigned int options);
};

void ToppleUpdate::applyTopplingForce(const Coord3D *dir, float speed, unsigned int options)
{
    ((ToppleUpdateApplyTopplingForceShim *)this)->apply(dir, speed, options);
}
