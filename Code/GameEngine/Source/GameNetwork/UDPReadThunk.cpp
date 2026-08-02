// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /Code/GameEngine/Include /Code/GameEngine/Include/Precompiled /Code/Libraries/Source/WWVegas/WWLib

struct sockaddr_in;

class UDP
{
public:
    int Read(unsigned char *msg, unsigned int len, sockaddr_in *from);
};

class UDPReadShim
{
public:
    int read(unsigned char *msg, unsigned int len, sockaddr_in *from);
};

int UDP::Read(unsigned char *msg, unsigned int len, sockaddr_in *from)
{
    return ((UDPReadShim *)this)->read(msg, len, from);
}
