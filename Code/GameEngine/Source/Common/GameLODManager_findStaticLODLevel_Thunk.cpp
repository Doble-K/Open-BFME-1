// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift MASM dump to standalone C++ thunk.

enum StaticGameLODLevel { STATIC_GAME_LOD_LOW = 0 };
class GameLODManager
{
public:
	StaticGameLODLevel findStaticLODLevel();
};

// ?findStaticLODLevel@GameLODManager@@QAE?AW4StaticGameLODLevel@@XZ
__declspec(naked) StaticGameLODLevel GameLODManager::findStaticLODLevel()
{
	__asm {
        __emit 0x51
        __emit 0x56
        __emit 0x57
        __emit 0x8b
        __emit 0xf1
        __emit 0x68
        __emit 0xc0
        __emit 0x6c
        __emit 0x07
        __emit 0x01
        __emit 0x8d
        __emit 0x4c
        __emit 0x24
        __emit 0x0c
        __emit 0xe8
        __emit 0x3d
        __emit 0x82
        __emit 0x7f
        __emit 0x00
        __emit 0x8d
        __emit 0x44
        __emit 0x24
        __emit 0x08
        __emit 0x83
        __emit 0xc6
        __emit 0x04
        __emit 0x50
        __emit 0x8b
        __emit 0xce
        __emit 0xe8
        __emit 0x1a
        __emit 0xa5
        __emit 0xf7
        __emit 0xff
        __emit 0x8d
        __emit 0x4c
        __emit 0x24
        __emit 0x08
        __emit 0x8b
        __emit 0xf8
        __emit 0xe8
        __emit 0xa3
        __emit 0x6f
        __emit 0x7f
        __emit 0x00
        __emit 0x3b
        __emit 0x3e
        __emit 0x75
        __emit 0x1a
        __emit 0xa1
        __emit 0xac
        __emit 0xd5
        __emit 0x2e
        __emit 0x01
        __emit 0x85
        __emit 0xc0
        __emit 0x74
        __emit 0x0a
        __emit 0x8b
        __emit 0x80
        __emit 0xc0
        __emit 0x16
        __emit 0x00
        __emit 0x00
        __emit 0x5f
        __emit 0x5e
        __emit 0x59
        __emit 0xc3
        __emit 0x83
        __emit 0xc8
        __emit 0xff
        __emit 0x5f
        __emit 0x5e
        __emit 0x59
        __emit 0xc3
        __emit 0x51
        __emit 0x89
        __emit 0x64
        __emit 0x24
        __emit 0x0c
        __emit 0x8b
        __emit 0xcc
        __emit 0x83
        __emit 0xc7
        __emit 0x14
        __emit 0x57
        __emit 0xe8
        __emit 0x95
        __emit 0x71
        __emit 0x7f
        __emit 0x00
        __emit 0x8b
        __emit 0x0d
        __emit 0xac
        __emit 0xd5
        __emit 0x2e
        __emit 0x01
        __emit 0xe8
        __emit 0xca
        __emit 0x3b
        __emit 0xf9
        __emit 0xff
        __emit 0x5f
        __emit 0x5e
        __emit 0x59
        __emit 0xc3
	}
}
