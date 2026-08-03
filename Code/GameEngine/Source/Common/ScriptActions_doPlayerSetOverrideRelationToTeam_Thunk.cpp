// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift MASM dump to standalone C++ thunk.

class AsciiString;
class ScriptActions
{
protected:
	void doPlayerSetOverrideRelationToTeam(const AsciiString &, const AsciiString &, int);
};

// ?doPlayerSetOverrideRelationToTeam@ScriptActions@@IAEXABVAsciiString@@0H@Z
__declspec(naked) void ScriptActions::doPlayerSetOverrideRelationToTeam(const AsciiString &, const AsciiString &, int)
{
	__asm {
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x04
        __emit 0x8b
        __emit 0x00
        __emit 0x85
        __emit 0xc0
        __emit 0x56
        __emit 0x74
        __emit 0x05
        __emit 0x83
        __emit 0xc0
        __emit 0x08
        __emit 0xeb
        __emit 0x05
        __emit 0xb8
        __emit 0x8b
        __emit 0x38
        __emit 0x07
        __emit 0x01
        __emit 0x8b
        __emit 0x0d
        __emit 0x00
        __emit 0xd6
        __emit 0x2e
        __emit 0x01
        __emit 0x50
        __emit 0xe8
        __emit 0xf6
        __emit 0x28
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
        __emit 0x99
        __emit 0x70
        __emit 0xd3
        __emit 0xff
        __emit 0x8b
        __emit 0x54
        __emit 0x24
        __emit 0x0c
        __emit 0x6a
        __emit 0x00
        __emit 0x51
        __emit 0x89
        __emit 0x64
        __emit 0x24
        __emit 0x10
        __emit 0x8b
        __emit 0xcc
        __emit 0x52
        __emit 0x8b
        __emit 0xf0
        __emit 0xe8
        __emit 0x5e
        __emit 0xf6
        __emit 0x58
        __emit 0x00
        __emit 0x8b
        __emit 0x0d
        __emit 0x6c
        __emit 0x07
        __emit 0x2f
        __emit 0x01
        __emit 0x8b
        __emit 0x01
        __emit 0xff
        __emit 0x50
        __emit 0x44
        __emit 0x85
        __emit 0xf6
        __emit 0x74
        __emit 0x11
        __emit 0x85
        __emit 0xc0
        __emit 0x74
        __emit 0x0d
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x10
        __emit 0x51
        __emit 0x50
        __emit 0x8b
        __emit 0xce
        __emit 0xe8
        __emit 0xb4
        __emit 0xc2
        __emit 0xd1
        __emit 0xff
        __emit 0x5e
        __emit 0xc2
        __emit 0x0c
        __emit 0x00
	}
}
