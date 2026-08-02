// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /Code/GameEngine/Include/Precompiled /Code/Libraries/Source/WWVegas/WWLib

class DisconnectManager
{
protected:
    int countVotesForPlayer(int playerIndex);
};

class DisconnectManagerCountVotesShim
{
public:
    int count(int playerIndex);
};

int DisconnectManager::countVotesForPlayer(int playerIndex)
{
    return ((DisconnectManagerCountVotesShim *)this)->count(playerIndex);
}
