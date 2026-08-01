// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

class INI
{
public:
    __declspec(dllexport) static void parseScienceVector(INI *, void *, void *, const void *);
};

__declspec(naked) void INI::parseScienceVector(INI *, void *, void *, const void *)
{
    __asm {
        _emit 0E9h
        _emit 072h
        _emit 0A7h
        _emit 007h
        _emit 000h
    }
}
