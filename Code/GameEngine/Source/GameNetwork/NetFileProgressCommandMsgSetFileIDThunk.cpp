// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /Code/GameEngine/Include/Precompiled /Code/Libraries/Source/WWVegas/WWLib

typedef unsigned short UnsignedShort;

class NetFileProgressCommandMsg
{
public:
    void setFileID(UnsignedShort fileID);
};

__declspec(naked) void NetFileProgressCommandMsg::setFileID(UnsignedShort)
{
    __asm {
        _emit 0E9h
        _emit 09Dh
        _emit 0F8h
        _emit 064h
        _emit 000h
    }
}
