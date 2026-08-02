// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

enum ScienceType
{
    ScienceType_Thunk
};

class Player
{
    bool addScience(ScienceType);
};

class PlayerAddScienceShim
{
public:
    bool add(ScienceType science);
};

bool Player::addScience(ScienceType science)
{
    return ((PlayerAddScienceShim *)this)->add(science);
}
