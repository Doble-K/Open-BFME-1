// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /Code/GameEngine/Include/Precompiled /Code/Libraries/Source/WWVegas/WWLib

class Transport
{
public:
    bool doSend();
};

__declspec(naked) bool Transport::doSend()
{
    __asm {
        _emit 0E9h
        _emit 06Dh
        _emit 0D7h
        _emit 066h
        _emit 000h
    }
}
