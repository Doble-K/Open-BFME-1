// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

class Radar
{
protected:
    void deleteListResources();
};

__declspec(naked) void Radar::deleteListResources()
{
    __asm {
        _emit 0E9h
        _emit 015h
        _emit 0A1h
        _emit 00Dh
        _emit 000h
    }
}
