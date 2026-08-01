// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /Code/GameEngine/Include/Precompiled /Code/Libraries/Source/WWVegas/WWLib

typedef unsigned char UnsignedByte;

class NetDisconnectPlayerCommandMsg
{
public:
    UnsignedByte getDisconnectSlot();
};

__declspec(naked) UnsignedByte NetDisconnectPlayerCommandMsg::getDisconnectSlot()
{
    __asm {
        _emit 0E9h
        _emit 04Ch
        _emit 0B2h
        _emit 064h
        _emit 000h
    }
}
