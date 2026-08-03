// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift MASM dump to standalone C++ thunk.

class INI;
class AttackNugget
{
public:
	static void __cdecl parse(INI *, void *, void *, const void *);
};

// ?parse@AttackNugget@@SAXPAVINI@@PAX1PBX@Z
__declspec(naked) void __cdecl AttackNugget::parse(INI *, void *, void *, const void *)
{
	__asm {
        __emit 0x6a
        __emit 0xff
        __emit 0x68
        __emit 0x4b
        __emit 0x9c
        __emit 0x00
        __emit 0x01
        __emit 0x64
        __emit 0xa1
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x64
        __emit 0x89
        __emit 0x25
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x56
        __emit 0x6a
        __emit 0x40
        __emit 0xe8
        __emit 0xa2
        __emit 0x97
        __emit 0x6a
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x04
        __emit 0x89
        __emit 0x44
        __emit 0x24
        __emit 0x04
        __emit 0x33
        __emit 0xf6
        __emit 0x3b
        __emit 0xc6
        __emit 0x89
        __emit 0x74
        __emit 0x24
        __emit 0x10
        __emit 0x74
        __emit 0x09
        __emit 0x8b
        __emit 0xc8
        __emit 0xe8
        __emit 0x9c
        __emit 0xa3
        __emit 0xe4
        __emit 0xff
        __emit 0x8b
        __emit 0xf0
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x18
        __emit 0x68
        __emit 0x78
        __emit 0xf6
        __emit 0x09
        __emit 0x01
        __emit 0x56
        __emit 0xc7
        __emit 0x44
        __emit 0x24
        __emit 0x18
        __emit 0xff
        __emit 0xff
        __emit 0xff
        __emit 0xff
        __emit 0xe8
        __emit 0xe1
        __emit 0x98
        __emit 0x67
        __emit 0x00
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x1c
        __emit 0x56
        __emit 0xe8
        __emit 0x87
        __emit 0x84
        __emit 0xe6
        __emit 0xff
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x08
        __emit 0x5e
        __emit 0x64
        __emit 0x89
        __emit 0x0d
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xc3
	}
}
