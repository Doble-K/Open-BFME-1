// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /Code/GameEngine/Include/Precompiled /Code/Libraries/Source/WWVegas/WWLib

class INI;

class Eva
{
public:
    __declspec(dllexport) static void parseEvaMessageFromIni(INI *, void *, void *, const void *);
};

__declspec(naked) void Eva::parseEvaMessageFromIni(INI *, void *, void *, const void *)
{
    __asm {
        _emit 0E9h
        _emit 016h
        _emit 010h
        _emit 042h
        _emit 000h
    }
}
