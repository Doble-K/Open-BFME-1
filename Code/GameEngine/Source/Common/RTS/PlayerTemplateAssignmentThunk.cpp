// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

class PlayerTemplate
{
public:
    PlayerTemplate &operator=(const PlayerTemplate &);
};

__declspec(naked) PlayerTemplate &PlayerTemplate::operator=(const PlayerTemplate &)
{
    __asm {
        _emit 0E9h
        _emit 0D5h
        _emit 0E1h
        _emit 00Dh
        _emit 000h
    }
}
