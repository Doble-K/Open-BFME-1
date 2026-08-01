// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /Code/GameEngine/Include/Precompiled /Code/Libraries/Source/WWVegas/WWLib

typedef unsigned char UnsignedByte;

class NetDisconnectPlayerCommandMsg
{
public:
    void setDisconnectSlot(UnsignedByte slot);
};

__declspec(naked) void NetDisconnectPlayerCommandMsg::setDisconnectSlot(UnsignedByte)
{
    __asm {
        _emit 0E9h
        _emit 007h
        _emit 0B0h
        _emit 066h
        _emit 000h
    }
}
