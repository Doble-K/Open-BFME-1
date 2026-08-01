// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

class UDP
{
public:
    __declspec(dllexport) int Bind(unsigned int, unsigned short);
};

__declspec(naked) int UDP::Bind(unsigned int, unsigned short)
{
    __asm {
        _emit 0E9h
        _emit 05Bh
        _emit 0C9h
        _emit 063h
        _emit 000h
    }
}
