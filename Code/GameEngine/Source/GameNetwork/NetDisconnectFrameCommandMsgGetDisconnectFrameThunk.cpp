// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /Code/GameEngine/Include/Precompiled /Code/Libraries/Source/WWVegas/WWLib

typedef unsigned int UnsignedInt;

class NetDisconnectFrameCommandMsg
{
public:
    UnsignedInt getDisconnectFrame();
};

__declspec(naked) UnsignedInt NetDisconnectFrameCommandMsg::getDisconnectFrame()
{
    __asm {
        _emit 0E9h
        _emit 01Bh
        _emit 06Bh
        _emit 063h
        _emit 000h
    }
}
