// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class NetCommandMsg;
class ConnectionManager;

class DisconnectManager
{
protected:
    void processDisconnectVote(NetCommandMsg *msg, ConnectionManager *conMgr);
};

// ?processDisconnectVote@DisconnectManager@@IAEXPAVNetCommandMsg@@PAVConnectionManager@@@Z
__declspec(naked) void DisconnectManager::processDisconnectVote(NetCommandMsg *msg, ConnectionManager *conMgr)
{
    __asm {
        __emit 0x53
        __emit 0x55
        __emit 0x8b
        __emit 0x6c
        __emit 0x24
        __emit 0x10
        __emit 0x56
        __emit 0x57
        __emit 0x8b
        __emit 0x7c
        __emit 0x24
        __emit 0x14
        __emit 0x8b
        __emit 0x77
        __emit 0x0c
        __emit 0x8b
        __emit 0xd9
        __emit 0x8b
        __emit 0xcd
        __emit 0xe8
        __emit 0x69
        __emit 0xe5
        __emit 0x9d
        __emit 0xff
        __emit 0x3b
        __emit 0xf0
        __emit 0x7c
        __emit 0x08
        __emit 0x75
        __emit 0x05
        __emit 0x83
        __emit 0xce
        __emit 0xff
        __emit 0xeb
        __emit 0x01
        __emit 0x4e
        __emit 0x55
        __emit 0x56
        __emit 0x8b
        __emit 0xcb
        __emit 0xe8
        __emit 0x0b
        __emit 0xe9
        __emit 0x9c
        __emit 0xff
        __emit 0x84
        __emit 0xc0
        __emit 0x74
        __emit 0x1f
        __emit 0x8b
        __emit 0x47
        __emit 0x0c
        __emit 0x55
        __emit 0x50
        __emit 0x8b
        __emit 0xcf
        __emit 0xe8
        __emit 0xd3
        __emit 0x81
        __emit 0x9a
        __emit 0xff
        __emit 0x50
        __emit 0x8b
        __emit 0xcf
        __emit 0xe8
        __emit 0x62
        __emit 0x9b
        __emit 0x99
        __emit 0xff
        __emit 0x0f
        __emit 0xb6
        __emit 0xc0
        __emit 0x50
        __emit 0x8b
        __emit 0xcb
        __emit 0xe8
        __emit 0x4d
        __emit 0x58
        __emit 0x9b
        __emit 0xff
        __emit 0x5f
        __emit 0x5e
        __emit 0x5d
        __emit 0x5b
        __emit 0xc2
        __emit 0x08
        __emit 0x00
    }
}
