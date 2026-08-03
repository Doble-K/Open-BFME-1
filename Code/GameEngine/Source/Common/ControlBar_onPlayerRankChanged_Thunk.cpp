// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift MASM dump to standalone C++ thunk.

class Player;
class ControlBar
{
public:
	void onPlayerRankChanged(const Player *);
};

// ?onPlayerRankChanged@ControlBar@@QAEXPBVPlayer@@@Z
__declspec(naked) void ControlBar::onPlayerRankChanged(const Player *)
{
	__asm {
        __emit 0x56
        __emit 0x8b
        __emit 0xf1
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x08
        __emit 0xe8
        __emit 0xdb
        __emit 0x5b
        __emit 0xb7
        __emit 0xff
        __emit 0x84
        __emit 0xc0
        __emit 0x74
        __emit 0x5b
        __emit 0xa1
        __emit 0x48
        __emit 0xd7
        __emit 0x2e
        __emit 0x01
        __emit 0x8b
        __emit 0x40
        __emit 0x0c
        __emit 0x8b
        __emit 0x80
        __emit 0x64
        __emit 0x02
        __emit 0x00
        __emit 0x00
        __emit 0x39
        __emit 0x86
        __emit 0xcc
        __emit 0x02
        __emit 0x00
        __emit 0x00
        __emit 0x7f
        __emit 0x3a
        __emit 0xa1
        __emit 0x30
        __emit 0x33
        __emit 0x2f
        __emit 0x01
        __emit 0x85
        __emit 0xc0
        __emit 0x74
        __emit 0x31
        __emit 0xa1
        __emit 0x8c
        __emit 0x14
        __emit 0x2f
        __emit 0x01
        __emit 0x8a
        __emit 0x48
        __emit 0x0d
        __emit 0x84
        __emit 0xc9
        __emit 0x74
        __emit 0x25
        __emit 0x8a
        __emit 0x48
        __emit 0x0e
        __emit 0x84
        __emit 0xc9
        __emit 0x74
        __emit 0x1e
        __emit 0x6a
        __emit 0x00
        __emit 0x51
        __emit 0x89
        __emit 0x64
        __emit 0x24
        __emit 0x10
        __emit 0x8b
        __emit 0xcc
        __emit 0x68
        __emit 0xb4
        __emit 0xb8
        __emit 0x0f
        __emit 0x01
        __emit 0xe8
        __emit 0xdb
        __emit 0xae
        __emit 0x3e
        __emit 0x00
        __emit 0x8b
        __emit 0x0d
        __emit 0x30
        __emit 0x33
        __emit 0x2f
        __emit 0x01
        __emit 0xe8
        __emit 0x38
        __emit 0x7f
        __emit 0xba
        __emit 0xff
        __emit 0xb0
        __emit 0x01
        __emit 0x88
        __emit 0x86
        __emit 0xc8
        __emit 0x02
        __emit 0x00
        __emit 0x00
        __emit 0x88
        __emit 0x46
        __emit 0x24
        __emit 0x5e
        __emit 0xc2
        __emit 0x04
        __emit 0x00
	}
}
