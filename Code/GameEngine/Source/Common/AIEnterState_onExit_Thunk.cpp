// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift MASM dump to standalone C++ thunk.

enum StateExitType { EXIT_NORMAL = 0 };
class AIEnterState
{
public:
	virtual void onExit(StateExitType);
};

// ?onExit@AIEnterState@@UAEXW4StateExitType@@@Z
__declspec(naked) void AIEnterState::onExit(StateExitType)
{
	__asm {
        __emit 0x53
        __emit 0x56
        __emit 0x57
        __emit 0x8b
        __emit 0xf9
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x10
        __emit 0x8b
        __emit 0x47
        __emit 0x1c
        __emit 0x8b
        __emit 0x58
        __emit 0x10
        __emit 0x51
        __emit 0x8b
        __emit 0xcf
        __emit 0xe8
        __emit 0xfa
        __emit 0xb8
        __emit 0xea
        __emit 0xff
        __emit 0x8b
        __emit 0xb3
        __emit 0x04
        __emit 0x02
        __emit 0x00
        __emit 0x00
        __emit 0x85
        __emit 0xf6
        __emit 0x74
        __emit 0x17
        __emit 0x6a
        __emit 0x00
        __emit 0x8b
        __emit 0xce
        __emit 0xe8
        __emit 0x32
        __emit 0x57
        __emit 0xe8
        __emit 0xff
        __emit 0x8b
        __emit 0xb6
        __emit 0xcc
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x85
        __emit 0xf6
        __emit 0x74
        __emit 0x04
        __emit 0x83
        __emit 0x66
        __emit 0x40
        __emit 0xfd
        __emit 0x8b
        __emit 0x7f
        __emit 0x50
        __emit 0x85
        __emit 0xff
        __emit 0x74
        __emit 0x22
        __emit 0x8b
        __emit 0x0d
        __emit 0x98
        __emit 0x08
        __emit 0x2f
        __emit 0x01
        __emit 0x57
        __emit 0xe8
        __emit 0x08
        __emit 0x18
        __emit 0xea
        __emit 0xff
        __emit 0x85
        __emit 0xc0
        __emit 0x74
        __emit 0x12
        __emit 0x8b
        __emit 0x88
        __emit 0xfc
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x85
        __emit 0xc9
        __emit 0x74
        __emit 0x08
        __emit 0x8b
        __emit 0x11
        __emit 0x6a
        __emit 0x02
        __emit 0x53
        __emit 0xff
        __emit 0x52
        __emit 0x34
        __emit 0x5f
        __emit 0x5e
        __emit 0x5b
        __emit 0xc2
        __emit 0x04
        __emit 0x00
	}
}
