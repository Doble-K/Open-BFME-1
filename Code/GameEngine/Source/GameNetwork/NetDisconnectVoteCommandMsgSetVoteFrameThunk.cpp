// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /Code/GameEngine/Include/Precompiled /Code/Libraries/Source/WWVegas/WWLib

typedef unsigned int UnsignedInt;

class NetDisconnectVoteCommandMsg
{
public:
    void setVoteFrame(UnsignedInt frame);
};

__declspec(naked) void NetDisconnectVoteCommandMsg::setVoteFrame(UnsignedInt)
{
    __asm {
        _emit 0E9h
        _emit 08Ah
        _emit 006h
        _emit 063h
        _emit 000h
    }
}
