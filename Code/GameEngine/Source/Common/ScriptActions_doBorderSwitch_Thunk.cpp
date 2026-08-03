// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift MASM dump to standalone C++ thunk.

class ScriptActions
{
protected:
	void doBorderSwitch(int);
};

// ?doBorderSwitch@ScriptActions@@IAEXH@Z
__declspec(naked) void ScriptActions::doBorderSwitch(int)
{
	__asm {
        __emit 0xa1
        __emit 0x48
        __emit 0xd7
        __emit 0x2e
        __emit 0x01
        __emit 0x56
        __emit 0x83
        __emit 0xce
        __emit 0xff
        __emit 0x85
        __emit 0xc0
        __emit 0x74
        __emit 0x34
        __emit 0x8b
        __emit 0x0d
        __emit 0x00
        __emit 0xd6
        __emit 0x2e
        __emit 0x01
        __emit 0x68
        __emit 0xb8
        __emit 0x40
        __emit 0x08
        __emit 0x01
        __emit 0xe8
        __emit 0x6a
        __emit 0xb1
        __emit 0xd4
        __emit 0xff
        __emit 0x8b
        __emit 0x0d
        __emit 0x48
        __emit 0xd7
        __emit 0x2e
        __emit 0x01
        __emit 0x50
        __emit 0xe8
        __emit 0x0d
        __emit 0xf9
        __emit 0xd3
        __emit 0xff
        __emit 0x85
        __emit 0xc0
        __emit 0x74
        __emit 0x14
        __emit 0x8b
        __emit 0x70
        __emit 0x24
        __emit 0x83
        __emit 0xfe
        __emit 0xff
        __emit 0x74
        __emit 0x0c
        __emit 0x8b
        __emit 0x0d
        __emit 0xbc
        __emit 0xd5
        __emit 0x2e
        __emit 0x01
        __emit 0x56
        __emit 0xe8
        __emit 0x6f
        __emit 0x77
        __emit 0x60
        __emit 0x00
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x08
        __emit 0x8b
        __emit 0x0d
        __emit 0xcc
        __emit 0xf4
        __emit 0x2e
        __emit 0x01
        __emit 0x50
        __emit 0xe8
        __emit 0xf9
        __emit 0xe5
        __emit 0xd2
        __emit 0xff
        __emit 0x83
        __emit 0xfe
        __emit 0xff
        __emit 0x74
        __emit 0x0c
        __emit 0x8b
        __emit 0x0d
        __emit 0xbc
        __emit 0xd5
        __emit 0x2e
        __emit 0x01
        __emit 0x56
        __emit 0xe8
        __emit 0x2e
        __emit 0x77
        __emit 0x60
        __emit 0x00
        __emit 0x5e
        __emit 0xc2
        __emit 0x04
        __emit 0x00
	}
}
