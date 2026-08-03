// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift MASM dump to standalone C++ thunk.

enum StateExitType
{
	EXIT_NORMAL = 0
};

class AIPanicState
{
public:
	virtual void onExit(StateExitType);
};

// ?onExit@AIPanicState@@UAEXW4StateExitType@@@Z
__declspec(naked) void AIPanicState::onExit(StateExitType)
{
	__asm {
        __emit 0x56
        __emit 0x57
        __emit 0x8b
        __emit 0xf9
        __emit 0x8b
        __emit 0x47
        __emit 0x1c
        __emit 0x8b
        __emit 0x70
        __emit 0x10
        __emit 0x85
        __emit 0xf6
        __emit 0x74
        __emit 0x35
        __emit 0x8b
        __emit 0x86
        __emit 0x98
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xf6
        __emit 0xc4
        __emit 0x20
        __emit 0x74
        __emit 0x2a
        __emit 0x6a
        __emit 0x4d
        __emit 0x8b
        __emit 0xce
        __emit 0xe8
        __emit 0x78
        __emit 0x2d
        __emit 0xeb
        __emit 0xff
        __emit 0x6a
        __emit 0x03
        __emit 0x8b
        __emit 0xce
        __emit 0xe8
        __emit 0x6f
        __emit 0x2d
        __emit 0xeb
        __emit 0xff
        __emit 0x6a
        __emit 0x6c
        __emit 0x8b
        __emit 0xce
        __emit 0xe8
        __emit 0x0b
        __emit 0x33
        __emit 0xeb
        __emit 0xff
        __emit 0x84
        __emit 0xc0
        __emit 0x74
        __emit 0x0b
        __emit 0x6a
        __emit 0x00
        __emit 0x6a
        __emit 0x03
        __emit 0x8b
        __emit 0xce
        __emit 0xe8
        __emit 0x31
        __emit 0xaa
        __emit 0xe9
        __emit 0xff
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x0c
        __emit 0x51
        __emit 0x8b
        __emit 0xcf
        __emit 0xe8
        __emit 0xe2
        __emit 0xa0
        __emit 0xea
        __emit 0xff
        __emit 0x5f
        __emit 0x5e
        __emit 0xc2
        __emit 0x04
        __emit 0x00
	}
}
