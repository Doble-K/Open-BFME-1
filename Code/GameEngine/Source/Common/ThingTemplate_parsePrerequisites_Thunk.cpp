// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift MASM dump to standalone C++ thunk.

class INI;
class ThingTemplate
{
protected:
	static void __cdecl parsePrerequisites(INI *, void *, void *, const void *);
};

// ?parsePrerequisites@ThingTemplate@@KAXPAVINI@@PAX1PBX@Z
__declspec(naked) void __cdecl ThingTemplate::parsePrerequisites(INI *, void *, void *, const void *)
{
	__asm {
        __emit 0x56
        __emit 0x8b
        __emit 0x74
        __emit 0x24
        __emit 0x0c
        __emit 0x57
        __emit 0x8b
        __emit 0x7c
        __emit 0x24
        __emit 0x0c
        __emit 0x83
        __emit 0x7f
        __emit 0x08
        __emit 0x02
        __emit 0x75
        __emit 0x19
        __emit 0x8b
        __emit 0x86
        __emit 0xc8
        __emit 0x02
        __emit 0x00
        __emit 0x00
        __emit 0x8b
        __emit 0x96
        __emit 0xc4
        __emit 0x02
        __emit 0x00
        __emit 0x00
        __emit 0x8d
        __emit 0x8e
        __emit 0xc4
        __emit 0x02
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x52
        __emit 0xe8
        __emit 0xda
        __emit 0x85
        __emit 0xec
        __emit 0xff
        __emit 0x68
        __emit 0xf8
        __emit 0x49
        __emit 0x09
        __emit 0x01
        __emit 0x81
        __emit 0xc6
        __emit 0xc4
        __emit 0x02
        __emit 0x00
        __emit 0x00
        __emit 0x56
        __emit 0x8b
        __emit 0xcf
        __emit 0xe8
        __emit 0xb4
        __emit 0x9a
        __emit 0x70
        __emit 0x00
        __emit 0x5f
        __emit 0x5e
        __emit 0xc3
	}
}
