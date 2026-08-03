// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift MASM dump to standalone C++ thunk.

class AsciiString;
class ScriptActions
{
protected:
	void doPlayerGrantScience(const AsciiString &, const AsciiString &);
};

// ?doPlayerGrantScience@ScriptActions@@IAEXABVAsciiString@@0@Z
__declspec(naked) void ScriptActions::doPlayerGrantScience(const AsciiString &, const AsciiString &)
{
	__asm {
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x08
        __emit 0x8b
        __emit 0x0d
        __emit 0xac
        __emit 0xd7
        __emit 0x2e
        __emit 0x01
        __emit 0x56
        __emit 0x50
        __emit 0xe8
        __emit 0x9b
        __emit 0xb2
        __emit 0xd5
        __emit 0xff
        __emit 0x8b
        __emit 0xf0
        __emit 0x83
        __emit 0xfe
        __emit 0xff
        __emit 0x74
        __emit 0x3f
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x08
        __emit 0x6a
        __emit 0x00
        __emit 0x51
        __emit 0x8b
        __emit 0x0d
        __emit 0x6c
        __emit 0x07
        __emit 0x2f
        __emit 0x01
        __emit 0xe8
        __emit 0xa6
        __emit 0xb1
        __emit 0xd5
        __emit 0xff
        __emit 0x66
        __emit 0x85
        __emit 0xc0
        __emit 0x89
        __emit 0x44
        __emit 0x24
        __emit 0x0c
        __emit 0x74
        __emit 0x24
        __emit 0x8b
        __emit 0x0d
        __emit 0x48
        __emit 0xd7
        __emit 0x2e
        __emit 0x01
        __emit 0x8d
        __emit 0x54
        __emit 0x24
        __emit 0x0c
        __emit 0x52
        __emit 0xe8
        __emit 0x5d
        __emit 0xed
        __emit 0xd3
        __emit 0xff
        __emit 0x85
        __emit 0xc0
        __emit 0x74
        __emit 0x08
        __emit 0x56
        __emit 0x8b
        __emit 0xc8
        __emit 0xe8
        __emit 0x2e
        __emit 0xc2
        __emit 0xd1
        __emit 0xff
        __emit 0x66
        __emit 0x83
        __emit 0x7c
        __emit 0x24
        __emit 0x0c
        __emit 0x00
        __emit 0x75
        __emit 0xdc
        __emit 0x5e
        __emit 0xc2
        __emit 0x08
        __emit 0x00
	}
}
