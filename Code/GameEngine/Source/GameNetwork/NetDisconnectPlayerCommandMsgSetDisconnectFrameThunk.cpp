// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /Code/GameEngine/Include/Precompiled /Code/Libraries/Source/WWVegas/WWLib

typedef unsigned int UnsignedInt;

class NetDisconnectPlayerCommandMsg
{
public:
    void setDisconnectFrame(UnsignedInt frame);
};

__declspec(naked) void NetDisconnectPlayerCommandMsg::setDisconnectFrame(UnsignedInt)
{
    __asm {
        _emit 0E9h
        _emit 0ADh
        _emit 0C8h
        _emit 062h
        _emit 000h
    }
}
