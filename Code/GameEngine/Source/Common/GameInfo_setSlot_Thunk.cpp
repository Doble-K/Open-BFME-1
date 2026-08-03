// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift MASM dump to standalone C++ thunk.

class GameSlot
{
public:
	unsigned char pad[64];
};

class GameInfo
{
public:
	void setSlot(int, GameSlot);
};

// ?setSlot@GameInfo@@QAEXHVGameSlot@@@Z
__declspec(naked) void GameInfo::setSlot(int, GameSlot)
{
	__asm {
        __emit 0x64
        __emit 0xa1
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x6a
        __emit 0xff
        __emit 0x68
        __emit 0x68
        __emit 0xf2
        __emit 0x03
        __emit 0x01
        __emit 0x50
        __emit 0x64
        __emit 0x89
        __emit 0x25
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x10
        __emit 0x85
        __emit 0xc0
        __emit 0xc7
        __emit 0x44
        __emit 0x24
        __emit 0x08
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x7c
        __emit 0x2c
        __emit 0x83
        __emit 0xf8
        __emit 0x08
        __emit 0x7d
        __emit 0x27
        __emit 0x8b
        __emit 0x4c
        __emit 0x81
        __emit 0x14
        __emit 0x85
        __emit 0xc9
        __emit 0x74
        __emit 0x1f
        __emit 0x85
        __emit 0xc0
        __emit 0x75
        __emit 0x11
        __emit 0x83
        __emit 0x7c
        __emit 0x24
        __emit 0x18
        __emit 0x05
        __emit 0xb0
        __emit 0x01
        __emit 0x88
        __emit 0x44
        __emit 0x24
        __emit 0x1c
        __emit 0x75
        __emit 0x04
        __emit 0x88
        __emit 0x44
        __emit 0x24
        __emit 0x1d
        __emit 0x8d
        __emit 0x44
        __emit 0x24
        __emit 0x14
        __emit 0x50
        __emit 0xe8
        __emit 0x67
        __emit 0x30
        __emit 0x9f
        __emit 0xff
        __emit 0x8d
        __emit 0x4c
        __emit 0x24
        __emit 0x14
        __emit 0xc7
        __emit 0x44
        __emit 0x24
        __emit 0x08
        __emit 0xff
        __emit 0xff
        __emit 0xff
        __emit 0xff
        __emit 0xe8
        __emit 0xf6
        __emit 0xc2
        __emit 0x9e
        __emit 0xff
        __emit 0x8b
        __emit 0x0c
        __emit 0x24
        __emit 0x64
        __emit 0x89
        __emit 0x0d
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x0c
        __emit 0xc2
        __emit 0x48
        __emit 0x00
	}
}
