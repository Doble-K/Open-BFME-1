// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /Code/GameEngine/Include /Code/GameEngine/Include/Precompiled /Code/Libraries/Source/WWVegas/WWLib

class FirewallHelperClass
{
public:
    bool sendToManglerFromPort(unsigned int, unsigned short, unsigned short, bool);
};

class FirewallHelperClassSendToManglerFromPortShim
{
public:
    bool sendToManglerFromPort(unsigned int, unsigned short, unsigned short, bool);
};

bool FirewallHelperClass::sendToManglerFromPort(unsigned int address, unsigned short port, unsigned short sourcePort, bool useMangler)
{
    return ((FirewallHelperClassSendToManglerFromPortShim *)this)->sendToManglerFromPort(address, port, sourcePort, useMangler);
}
