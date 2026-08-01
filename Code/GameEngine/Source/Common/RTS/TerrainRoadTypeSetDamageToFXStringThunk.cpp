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

__declspec(naked) void TerrainRoadType::friend_setDamageToFXString(BodyDamageType, int, AsciiString)
{
    __asm {
        _emit 0E9h
        _emit 040h
        _emit 0CDh
        _emit 05Dh
        _emit 000h
    }
}
