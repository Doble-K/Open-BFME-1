// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

class UDP
{
public:
    __declspec(dllexport) int Bind(unsigned int, unsigned short);
};

class UDPBindShim
{
public:
    int bind(unsigned int ip, unsigned short port);
};

int UDP::Bind(unsigned int ip, unsigned short port)
{
    return ((UDPBindShim *)this)->bind(ip, port);
}
