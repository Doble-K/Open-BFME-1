// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift MASM dump to standalone C++ thunk.

class INI
{
public:
	static void __cdecl parseDynamicGameLODLevel(INI *, void *, void *, const void *);
};

// ?parseDynamicGameLODLevel@INI@@SAXPAV1@PAX1PBX@Z
__declspec(naked) void __cdecl INI::parseDynamicGameLODLevel(INI *, void *, void *, const void *)
{
	__asm {
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x04
        __emit 0x83
        __emit 0xec
        __emit 0x08
        __emit 0x53
        __emit 0x56
        __emit 0x57
        __emit 0x6a
        __emit 0x00
        __emit 0xe8
        __emit 0xcf
        __emit 0x45
        __emit 0x7d
        __emit 0x00
        __emit 0x8b
        __emit 0x1d
        __emit 0x3c
        __emit 0x93
        __emit 0x35
        __emit 0x01
        __emit 0x8b
        __emit 0xf8
        __emit 0x33
        __emit 0xf6
        __emit 0xeb
        __emit 0x03
        __emit 0x8d
        __emit 0x49
        __emit 0x00
        __emit 0x8b
        __emit 0x04
        __emit 0xb5
        __emit 0xfc
        __emit 0x73
        __emit 0x2a
        __emit 0x01
        __emit 0x50
        __emit 0x57
        __emit 0xff
        __emit 0xd3
        __emit 0x83
        __emit 0xc4
        __emit 0x08
        __emit 0x85
        __emit 0xc0
        __emit 0x74
        __emit 0x2a
        __emit 0x46
        __emit 0x83
        __emit 0xfe
        __emit 0x05
        __emit 0x7c
        __emit 0xe8
        __emit 0x57
        __emit 0x68
        __emit 0xcc
        __emit 0x6b
        __emit 0x07
        __emit 0x01
        __emit 0x8d
        __emit 0x54
        __emit 0x24
        __emit 0x14
        __emit 0x6a
        __emit 0x03
        __emit 0x52
        __emit 0xe8
        __emit 0x26
        __emit 0x42
        __emit 0x7d
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0x68
        __emit 0x30
        __emit 0xfc
        __emit 0x1d
        __emit 0x01
        __emit 0x8d
        __emit 0x44
        __emit 0x24
        __emit 0x10
        __emit 0x50
        __emit 0xe8
        __emit 0x14
        __emit 0xa9
        __emit 0x97
        __emit 0x00
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x20
        __emit 0x5f
        __emit 0x89
        __emit 0x31
        __emit 0x5e
        __emit 0x5b
        __emit 0x83
        __emit 0xc4
        __emit 0x08
        __emit 0xc3
	}
}
