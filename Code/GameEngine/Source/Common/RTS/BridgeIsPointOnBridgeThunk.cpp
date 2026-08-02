// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

struct Coord3D;

class Bridge
{
public:
    bool isPointOnBridge(const Coord3D *);
};

class BridgePointOnBridgeShim
{
public:
    bool test(const Coord3D *point);
};

bool Bridge::isPointOnBridge(const Coord3D *point)
{
    return ((BridgePointOnBridgeShim *)this)->test(point);
}
