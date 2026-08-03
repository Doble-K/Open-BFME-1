// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift MASM dump to standalone C++ thunk.

class ControlBar
{
protected:
	void setSquishedControlBarConfig();
};

// ?setSquishedControlBarConfig@ControlBar@@IAEXXZ
__declspec(naked) void ControlBar::setSquishedControlBarConfig()
{
	__asm {
        __emit 0x56
        __emit 0x8b
        __emit 0xf1
        __emit 0x83
        __emit 0x7e
        __emit 0x20
        __emit 0x01
        __emit 0x74
        __emit 0x54
        __emit 0x8b
        __emit 0x46
        __emit 0x1c
        __emit 0x8b
        __emit 0x4e
        __emit 0x18
        __emit 0x53
        __emit 0x50
        __emit 0x51
        __emit 0x8b
        __emit 0x4e
        __emit 0x34
        __emit 0xc7
        __emit 0x46
        __emit 0x20
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xe8
        __emit 0xcc
        __emit 0xc3
        __emit 0xb7
        __emit 0xff
        __emit 0x8b
        __emit 0xce
        __emit 0xe8
        __emit 0x73
        __emit 0xbe
        __emit 0xb9
        __emit 0xff
        __emit 0x8b
        __emit 0x0d
        __emit 0x70
        __emit 0x12
        __emit 0x2f
        __emit 0x01
        __emit 0x8b
        __emit 0x15
        __emit 0x00
        __emit 0x16
        __emit 0x2f
        __emit 0x01
        __emit 0x8b
        __emit 0x01
        __emit 0x8b
        __emit 0x1a
        __emit 0xff
        __emit 0x50
        __emit 0x30
        __emit 0x8b
        __emit 0x0d
        __emit 0x00
        __emit 0x16
        __emit 0x2f
        __emit 0x01
        __emit 0x50
        __emit 0xff
        __emit 0x53
        __emit 0x40
        __emit 0x8b
        __emit 0x0d
        __emit 0x48
        __emit 0xd7
        __emit 0x2e
        __emit 0x01
        __emit 0x8b
        __emit 0x51
        __emit 0x0c
        __emit 0x8b
        __emit 0x42
        __emit 0x04
        __emit 0x8b
        __emit 0x4e
        __emit 0x30
        __emit 0x6a
        __emit 0x01
        __emit 0x50
        __emit 0xe8
        __emit 0xe2
        __emit 0xa7
        __emit 0xb9
        __emit 0xff
        __emit 0x5b
        __emit 0x5e
        __emit 0xc3
	}
}
