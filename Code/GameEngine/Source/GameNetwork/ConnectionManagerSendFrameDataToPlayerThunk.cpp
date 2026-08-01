// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /Code/GameEngine/Include /Code/GameEngine/Include/Precompiled /Code/Libraries/Source/WWVegas/WWLib

class ConnectionManager
{
public:
    void sendFrameDataToPlayer(unsigned int playerID, unsigned int frame);
};

__declspec(naked) void ConnectionManager::sendFrameDataToPlayer(unsigned int, unsigned int)
{
    __asm {
        _emit 0E9h
        _emit 00Bh
        _emit 08Fh
        _emit 065h
        _emit 000h
    }
}
