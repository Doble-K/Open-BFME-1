// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift MASM dump to standalone C++ thunk.

class ConnectionManager;
class DisconnectManager
{
protected:
	void resetPlayersVotes(int, unsigned int, ConnectionManager *);
};

// ?resetPlayersVotes@DisconnectManager@@IAEXHIPAVConnectionManager@@@Z
__declspec(naked) void DisconnectManager::resetPlayersVotes(int, unsigned int, ConnectionManager *)
{
	__asm {
        __emit 0x53
        __emit 0x56
        __emit 0x8b
        __emit 0x74
        __emit 0x24
        __emit 0x0c
        __emit 0x57
        __emit 0x8b
        __emit 0x7c
        __emit 0x24
        __emit 0x14
        __emit 0x8d
        __emit 0x44
        __emit 0xf1
        __emit 0x30
        __emit 0xba
        __emit 0x08
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x39
        __emit 0x78
        __emit 0x04
        __emit 0x77
        __emit 0x03
        __emit 0xc6
        __emit 0x00
        __emit 0x00
        __emit 0x83
        __emit 0xc0
        __emit 0x40
        __emit 0x4a
        __emit 0x75
        __emit 0xf2
        __emit 0x8b
        __emit 0x7c
        __emit 0x24
        __emit 0x18
        __emit 0x57
        __emit 0x56
        __emit 0xe8
        __emit 0x74
        __emit 0x7f
        __emit 0x99
        __emit 0xff
        __emit 0x8b
        __emit 0xcf
        __emit 0x8b
        __emit 0xd8
        __emit 0xe8
        __emit 0xab
        __emit 0xea
        __emit 0x9d
        __emit 0xff
        __emit 0x3b
        __emit 0xf0
        __emit 0x7c
        __emit 0x03
        __emit 0x74
        __emit 0x17
        __emit 0x4e
        __emit 0x83
        __emit 0xfe
        __emit 0xff
        __emit 0x74
        __emit 0x11
        __emit 0x8b
        __emit 0x0d
        __emit 0x64
        __emit 0x49
        __emit 0x2f
        __emit 0x01
        __emit 0x85
        __emit 0xc9
        __emit 0x74
        __emit 0x07
        __emit 0x53
        __emit 0x56
        __emit 0xe8
        __emit 0xb5
        __emit 0x65
        __emit 0x9c
        __emit 0xff
        __emit 0x5f
        __emit 0x5e
        __emit 0x5b
        __emit 0xc2
        __emit 0x0c
        __emit 0x00
	}
}
