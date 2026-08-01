// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /Code/GameEngine/Include /Code/GameEngine/Include/Precompiled /Code/Libraries/Source/WWVegas/WWLib

struct sockaddr_in;

class UDP
{
public:
    int Read(unsigned char *msg, unsigned int len, sockaddr_in *from);
};

__declspec(naked) int UDP::Read(unsigned char *, unsigned int, sockaddr_in *)
{
    __asm {
        _emit 0E9h
        _emit 06Dh
        _emit 0A7h
        _emit 064h
        _emit 000h
    }
}
