// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

struct Region2D;

class Bridge
{
public:
    bool isCellOnEnd(const Region2D *);
};

class BridgeCellOnEndShim
{
public:
    bool test(const Region2D *region);
};

bool Bridge::isCellOnEnd(const Region2D *region)
{
    return ((BridgeCellOnEndShim *)this)->test(region);
}
