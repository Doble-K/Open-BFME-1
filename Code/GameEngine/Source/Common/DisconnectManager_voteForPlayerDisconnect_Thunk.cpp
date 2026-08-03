// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift MASM dump to standalone C++ thunk.

class ConnectionManager;
class DisconnectManager
{
public:
	void voteForPlayerDisconnect(int, ConnectionManager *);
};

// ?voteForPlayerDisconnect@DisconnectManager@@QAEXHPAVConnectionManager@@@Z
__declspec(naked) void DisconnectManager::voteForPlayerDisconnect(int, ConnectionManager *)
{
	__asm {
        __emit 0x53
        __emit 0x8b
        __emit 0x5c
        __emit 0x24
        __emit 0x08
        __emit 0x55
        __emit 0x56
        __emit 0x8b
        __emit 0x74
        __emit 0x24
        __emit 0x14
        __emit 0x57
        __emit 0x8b
        __emit 0xf9
        __emit 0x8b
        __emit 0xce
        __emit 0x8d
        __emit 0x2c
        __emit 0xdd
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xe8
        __emit 0x95
        __emit 0xe7
        __emit 0x9d
        __emit 0xff
        __emit 0x03
        __emit 0xc5
        __emit 0x8a
        __emit 0x4c
        __emit 0xc7
        __emit 0x30
        __emit 0x84
        __emit 0xc9
        __emit 0x75
        __emit 0x31
        __emit 0x8b
        __emit 0xce
        __emit 0xe8
        __emit 0x84
        __emit 0xe7
        __emit 0x9d
        __emit 0xff
        __emit 0x56
        __emit 0x03
        __emit 0xc5
        __emit 0x53
        __emit 0x8b
        __emit 0xcf
        __emit 0xc6
        __emit 0x44
        __emit 0xc7
        __emit 0x30
        __emit 0x01
        __emit 0xe8
        __emit 0x5c
        __emit 0x33
        __emit 0x9c
        __emit 0xff
        __emit 0xa1
        __emit 0x98
        __emit 0x08
        __emit 0x2f
        __emit 0x01
        __emit 0x8b
        __emit 0x68
        __emit 0x3c
        __emit 0x56
        __emit 0x8b
        __emit 0xce
        __emit 0xe8
        __emit 0x64
        __emit 0xe7
        __emit 0x9d
        __emit 0xff
        __emit 0x50
        __emit 0x55
        __emit 0x53
        __emit 0x8b
        __emit 0xcf
        __emit 0xe8
        __emit 0x76
        __emit 0x5a
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
