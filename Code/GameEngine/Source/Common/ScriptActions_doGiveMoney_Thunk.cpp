// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift MASM dump to standalone C++ thunk.

class AsciiString;
class ScriptActions
{
protected:
	void doGiveMoney(const AsciiString &, int);
};

// ?doGiveMoney@ScriptActions@@IAEXABVAsciiString@@H@Z
__declspec(naked) void ScriptActions::doGiveMoney(const AsciiString &, int)
{
	__asm {
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x04
        __emit 0x8b
        __emit 0x0d
        __emit 0x6c
        __emit 0x07
        __emit 0x2f
        __emit 0x01
        __emit 0x6a
        __emit 0x00
        __emit 0x50
        __emit 0xe8
        __emit 0x4e
        __emit 0xb9
        __emit 0xd5
        __emit 0xff
        __emit 0x66
        __emit 0x85
        __emit 0xc0
        __emit 0x89
        __emit 0x44
        __emit 0x24
        __emit 0x04
        __emit 0x74
        __emit 0x41
        __emit 0x56
        __emit 0x8b
        __emit 0x74
        __emit 0x24
        __emit 0x0c
        __emit 0x8d
        __emit 0x4c
        __emit 0x24
        __emit 0x08
        __emit 0x51
        __emit 0x8b
        __emit 0x0d
        __emit 0x48
        __emit 0xd7
        __emit 0x2e
        __emit 0x01
        __emit 0xe8
        __emit 0x00
        __emit 0xf5
        __emit 0xd3
        __emit 0xff
        __emit 0x85
        __emit 0xc0
        __emit 0x74
        __emit 0x1f
        __emit 0x8d
        __emit 0x48
        __emit 0x48
        __emit 0x85
        __emit 0xc9
        __emit 0x74
        __emit 0x18
        __emit 0x85
        __emit 0xf6
        __emit 0x6a
        __emit 0x01
        __emit 0x7d
        __emit 0x0c
        __emit 0x8b
        __emit 0xd6
        __emit 0xf7
        __emit 0xda
        __emit 0x52
        __emit 0xe8
        __emit 0x19
        __emit 0x1f
        __emit 0xd5
        __emit 0xff
        __emit 0xeb
        __emit 0x06
        __emit 0x56
        __emit 0xe8
        __emit 0xea
        __emit 0x83
        __emit 0xd3
        __emit 0xff
        __emit 0x66
        __emit 0x83
        __emit 0x7c
        __emit 0x24
        __emit 0x08
        __emit 0x00
        __emit 0x75
        __emit 0xc5
        __emit 0x5e
        __emit 0xc2
        __emit 0x08
        __emit 0x00
	}
}
