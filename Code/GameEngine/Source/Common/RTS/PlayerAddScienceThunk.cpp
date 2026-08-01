// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

enum ScienceType
{
    ScienceType_Thunk
};

class Player
{
    bool addScience(ScienceType);
};

__declspec(naked) bool Player::addScience(ScienceType)
{
    __asm {
        _emit 0E9h
        _emit 024h
        _emit 0F3h
        _emit 009h
        _emit 000h
    }
}
