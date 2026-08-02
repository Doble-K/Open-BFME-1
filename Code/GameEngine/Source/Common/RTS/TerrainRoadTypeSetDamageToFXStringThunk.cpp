// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /Code/GameEngine/Include /Code/GameEngine/Include/Precompiled /Code/Libraries/Source/WWVegas/WWLib

class AsciiString
{
};

enum BodyDamageType
{
    BodyDamageType_Thunk
};

class TerrainRoadType
{
public:
    void friend_setDamageToFXString(BodyDamageType, int, AsciiString);
};

class TerrainRoadTypeSetDamageToFXStringShim
{
public:
    void set(BodyDamageType type, int index, AsciiString name);
};

void TerrainRoadType::friend_setDamageToFXString(BodyDamageType type, int index, AsciiString name)
{
    ((TerrainRoadTypeSetDamageToFXStringShim *)this)->set(type, index, name);
}
