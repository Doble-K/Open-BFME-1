// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /Code/GameEngine/Include /Code/GameEngine/Include/Precompiled /Code/Libraries/Source/WWVegas/WWLib

class GameSlot;

class NAT
{
protected:
    void sendMangledPortNumberToTarget(unsigned short mangledPort, GameSlot *targetSlot);
};

__declspec(naked) void NAT::sendMangledPortNumberToTarget(unsigned short, GameSlot *)
{
    __asm {
        _emit 0E9h
        _emit 0D1h
        _emit 06Bh
        _emit 064h
        _emit 000h
    }
}
