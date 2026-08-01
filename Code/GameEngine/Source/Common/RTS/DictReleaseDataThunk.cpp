// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /Code/GameEngine/Include/Precompiled /Code/Libraries/Source/WWVegas/WWLib

class Dict
{
    void releaseData();
};

__declspec(naked) void Dict::releaseData()
{
    __asm {
        _emit 0E9h
        _emit 046h
        _emit 03Dh
        _emit 005h
        _emit 000h
    }
}
