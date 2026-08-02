// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /Code/GameEngine/Include /Code/GameEngine/Include/Precompiled /Code/Libraries/Source/WWVegas/WWLib

class FirewallHelperClass
{
    int getNATPortAllocationScheme(int, unsigned short *, unsigned short *, bool &, bool &);
};

class FirewallHelperClassGetNATPortAllocationSchemeShim
{
public:
    int getNATPortAllocationScheme(int, unsigned short *, unsigned short *, bool &, bool &);
};

int FirewallHelperClass::getNATPortAllocationScheme(int scheme, unsigned short *port1, unsigned short *port2, bool &flag1, bool &flag2)
{
    return ((FirewallHelperClassGetNATPortAllocationSchemeShim *)this)->getNATPortAllocationScheme(scheme, port1, port2, flag1, flag2);
}
