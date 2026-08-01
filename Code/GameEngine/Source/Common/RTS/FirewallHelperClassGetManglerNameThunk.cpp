// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /Code/GameEngine/Include /Code/GameEngine/Include/Precompiled /Code/Libraries/Source/WWVegas/WWLib

class FirewallHelperClass
{
public:
    static void getManglerName(int, char *);
};

__declspec(naked) void FirewallHelperClass::getManglerName(int, char *)
{
    __asm {
        _emit 0E9h
        _emit 07Ah
        _emit 031h
        _emit 063h
        _emit 000h
    }
}
