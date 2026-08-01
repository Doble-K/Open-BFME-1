// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /Code/GameEngine/Include/Precompiled /Code/Libraries/Source/WWVegas/WWLib

typedef unsigned char UnsignedByte;

class NetDisconnectVoteCommandMsg
{
public:
    void setSlot(UnsignedByte slot);
};

__declspec(naked) void NetDisconnectVoteCommandMsg::setSlot(UnsignedByte)
{
    __asm {
        _emit 0E9h
        _emit 0E2h
        _emit 035h
        _emit 065h
        _emit 000h
    }
}
