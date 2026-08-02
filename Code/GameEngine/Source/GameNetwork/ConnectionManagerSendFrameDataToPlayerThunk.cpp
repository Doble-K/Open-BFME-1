// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /Code/GameEngine/Include /Code/GameEngine/Include/Precompiled /Code/Libraries/Source/WWVegas/WWLib

class ConnectionManager
{
public:
    void sendFrameDataToPlayer(unsigned int playerID, unsigned int frame);
};

class ConnectionManagerSendFrameDataShim
{
public:
    void send(unsigned int playerID, unsigned int frame);
};

void ConnectionManager::sendFrameDataToPlayer(unsigned int playerID, unsigned int frame)
{
    ((ConnectionManagerSendFrameDataShim *)this)->send(playerID, frame);
}
