// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift MASM dump to standalone C++ thunk.

class INI;
class ThingTemplate
{
protected:
	static void __cdecl parseAddModule(INI *, void *, void *, const void *);
};

// ?parseAddModule@ThingTemplate@@KAXPAVINI@@PAX1PBX@Z
__declspec(naked) void __cdecl ThingTemplate::parseAddModule(INI *, void *, void *, const void *)
{
	__asm {
        __emit 0x83
        __emit 0xec
        __emit 0x08
        __emit 0x56
        __emit 0x8b
        __emit 0x74
        __emit 0x24
        __emit 0x14
        __emit 0x0f
        __emit 0xbe
        __emit 0x86
        __emit 0x98
        __emit 0x04
        __emit 0x00
        __emit 0x00
        __emit 0x85
        __emit 0xc0
        __emit 0x74
        __emit 0x23
        __emit 0x68
        __emit 0xb0
        __emit 0x40
        __emit 0x09
        __emit 0x01
        __emit 0x8d
        __emit 0x44
        __emit 0x24
        __emit 0x08
        __emit 0x6a
        __emit 0x03
        __emit 0x50
        __emit 0xe8
        __emit 0xcc
        __emit 0x23
        __emit 0x71
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x0c
        __emit 0x68
        __emit 0x30
        __emit 0xfc
        __emit 0x1d
        __emit 0x01
        __emit 0x8d
        __emit 0x4c
        __emit 0x24
        __emit 0x08
        __emit 0x51
        __emit 0xe8
        __emit 0xba
        __emit 0x8a
        __emit 0x8b
        __emit 0x00
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x10
        __emit 0x68
        __emit 0xa0
        __emit 0x10
        __emit 0x09
        __emit 0x01
        __emit 0x56
        __emit 0xc6
        __emit 0x86
        __emit 0x98
        __emit 0x04
        __emit 0x00
        __emit 0x00
        __emit 0x01
        __emit 0xe8
        __emit 0x44
        __emit 0x3e
        __emit 0x71
        __emit 0x00
        __emit 0xc6
        __emit 0x86
        __emit 0x98
        __emit 0x04
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x5e
        __emit 0x83
        __emit 0xc4
        __emit 0x08
        __emit 0xc3
	}
}
