// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /Code/GameEngine/Include/Precompiled /Code/Libraries/Source/WWVegas/WWLib

class NetFileProgressCommandMsg
{
public:
    void setProgress(int percentage);
};

__declspec(naked) void NetFileProgressCommandMsg::setProgress(int)
{
    __asm {
        _emit 0E9h
        _emit 0F5h
        _emit 0ECh
        _emit 065h
        _emit 000h
    }
}
