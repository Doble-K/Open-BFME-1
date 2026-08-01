// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /Code/GameEngine/Include /Code/GameEngine/Include/Precompiled /Code/Libraries/Source/WWVegas/WWLib

class FirewallHelperClass
{
    int getNATPortAllocationScheme(int, unsigned short *, unsigned short *, bool &, bool &);
};

__declspec(naked) int FirewallHelperClass::getNATPortAllocationScheme(int, unsigned short *, unsigned short *, bool &, bool &)
{
    __asm {
        _emit 0E9h
        _emit 02Ch
        _emit 0B9h
        _emit 065h
        _emit 000h
    }
}
