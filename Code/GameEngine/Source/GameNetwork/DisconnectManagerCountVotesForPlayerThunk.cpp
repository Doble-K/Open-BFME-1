// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /Code/GameEngine/Include/Precompiled /Code/Libraries/Source/WWVegas/WWLib

class DisconnectManager
{
protected:
    int countVotesForPlayer(int playerIndex);
};

__declspec(naked) int DisconnectManager::countVotesForPlayer(int)
{
    __asm {
        _emit 0E9h
        _emit 0CAh
        _emit 07Fh
        _emit 066h
        _emit 000h
    }
}
