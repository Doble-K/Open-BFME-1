// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /Code/GameEngine/Include/Precompiled /Code/Libraries/Source/WWVegas/WWLib

typedef unsigned int UnsignedInt;

class NetDisconnectScreenOffCommandMsg
{
public:
    UnsignedInt getNewFrame();
};

__declspec(naked) UnsignedInt NetDisconnectScreenOffCommandMsg::getNewFrame()
{
    __asm {
        _emit 0E9h
        _emit 069h
        _emit 0A1h
        _emit 063h
        _emit 000h
    }
}
