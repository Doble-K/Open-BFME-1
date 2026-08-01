// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

class Object;

class Player
{
public:
    void disableRadar();
    void enableRadar();
    void iterateObjects(void (*)(Object *, void *), void *) const;
};

__declspec(naked) void Player::disableRadar()
{
    __asm {
        _emit 0E9h
        _emit 0FEh
        _emit 0FEh
        _emit 008h
        _emit 000h
    }
}

__declspec(naked) void Player::enableRadar()
{
    __asm {
        _emit 0E9h
        _emit 0B4h
        _emit 090h
        _emit 008h
        _emit 000h
    }
}

__declspec(naked) void Player::iterateObjects(void (*)(Object *, void *), void *) const
{
    __asm {
        _emit 0E9h
        _emit 020h
        _emit 0EBh
        _emit 009h
        _emit 000h
    }
}
