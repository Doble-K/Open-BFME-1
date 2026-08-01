// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /Code/GameEngine/Include /Code/GameEngine/Include/Precompiled /Code/Libraries/Source/WWVegas/WWLib

class Transport
{
public:
    bool queueSend(unsigned int ip, unsigned short port, const unsigned char *data, int length);
};

__declspec(naked) bool Transport::queueSend(unsigned int, unsigned short, const unsigned char *, int)
{
    __asm {
        _emit 0E9h
        _emit 0ABh
        _emit 098h
        _emit 063h
        _emit 000h
    }
}
