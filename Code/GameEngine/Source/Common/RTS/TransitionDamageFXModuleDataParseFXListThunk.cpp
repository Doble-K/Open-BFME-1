// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

class INI;

class TransitionDamageFXModuleData
{
public:
    __declspec(dllexport) static void parseFXList(INI *, void *, void *, const void *);
};

__declspec(naked) void TransitionDamageFXModuleData::parseFXList(INI *, void *, void *, const void *)
{
    __asm {
        _emit 0E9h
        _emit 020h
        _emit 079h
        _emit 024h
        _emit 000h
    }
}
