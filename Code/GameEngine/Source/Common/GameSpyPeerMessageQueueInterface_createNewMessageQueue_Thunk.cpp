// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift createNewMessageQueue __emit thunk to clean C++. Retail is
// a plain new-expression: operator new(0x78), EH-guarded ctor call, null passthrough.

class GameSpyPeerMessageQueueInterface
{
public:
    GameSpyPeerMessageQueueInterface();
    static GameSpyPeerMessageQueueInterface *createNewMessageQueue();

private:
    unsigned char m_pad[0x78];
};

// ?createNewMessageQueue@GameSpyPeerMessageQueueInterface@@SAPAV1@XZ
GameSpyPeerMessageQueueInterface *GameSpyPeerMessageQueueInterface::createNewMessageQueue()
{
    return new GameSpyPeerMessageQueueInterface;
}
