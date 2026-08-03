// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift MASM dump to standalone C++ thunk.

class GameWindow;
class FullFadeTransition
{
public:
	virtual void init(GameWindow *);
};

// ?init@FullFadeTransition@@UAEXPAVGameWindow@@@Z
__declspec(naked) void FullFadeTransition::init(GameWindow *)
{
	__asm {
        __emit 0x56
        __emit 0x8b
        __emit 0xf1
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x08
        __emit 0x85
        __emit 0xc9
        __emit 0x74
        __emit 0x20
        __emit 0x8d
        __emit 0x46
        __emit 0x24
        __emit 0x50
        __emit 0x8d
        __emit 0x56
        __emit 0x20
        __emit 0x52
        __emit 0x89
        __emit 0x4e
        __emit 0x0c
        __emit 0xe8
        __emit 0x81
        __emit 0x9a
        __emit 0xa9
        __emit 0xff
        __emit 0x8d
        __emit 0x46
        __emit 0x1c
        __emit 0x50
        __emit 0x8d
        __emit 0x4e
        __emit 0x18
        __emit 0x51
        __emit 0x8b
        __emit 0x4e
        __emit 0x0c
        __emit 0xe8
        __emit 0x00
        __emit 0x25
        __emit 0xa9
        __emit 0xff
        __emit 0x8b
        __emit 0x46
        __emit 0x10
        __emit 0x8b
        __emit 0x16
        __emit 0x50
        __emit 0x8b
        __emit 0xce
        __emit 0xc6
        __emit 0x46
        __emit 0x09
        __emit 0x00
        __emit 0xff
        __emit 0x52
        __emit 0x08
        __emit 0x8b
        __emit 0x46
        __emit 0x14
        __emit 0x99
        __emit 0x2b
        __emit 0xc2
        __emit 0xd1
        __emit 0xf8
        __emit 0x89
        __emit 0x44
        __emit 0x24
        __emit 0x08
        __emit 0xc6
        __emit 0x46
        __emit 0x08
        __emit 0x00
        __emit 0xdb
        __emit 0x44
        __emit 0x24
        __emit 0x08
        __emit 0xc6
        __emit 0x46
        __emit 0x09
        __emit 0x01
        __emit 0xd8
        __emit 0x3d
        __emit 0x34
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0xd9
        __emit 0x5e
        __emit 0x28
        __emit 0x5e
        __emit 0xc2
        __emit 0x04
        __emit 0x00
	}
}
