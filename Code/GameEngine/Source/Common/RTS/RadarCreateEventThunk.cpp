// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

struct Coord3D;
enum RadarEventType
{
    RadarEventType_Thunk
};

class Radar
{
public:
    void createEvent(const Coord3D *, RadarEventType, float);
};

class RadarCreateEventShim
{
public:
    void create(const Coord3D *pos, RadarEventType type, float duration);
};

void Radar::createEvent(const Coord3D *pos, RadarEventType type, float duration)
{
    ((RadarCreateEventShim *)this)->create(pos, type, duration);
}
