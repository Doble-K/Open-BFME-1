// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift MASM dump to standalone C++ thunk.

class INI;
class GarrisonContainModuleData
{
public:
	static void __cdecl parseInitialRoster(INI *, void *, void *, const void *);
};

// ?parseInitialRoster@GarrisonContainModuleData@@SAXPAVINI@@PAX1PBX@Z
__declspec(naked) void __cdecl GarrisonContainModuleData::parseInitialRoster(INI *, void *, void *, const void *)
{
	__asm {
        __emit 0x53
        __emit 0x56
        __emit 0x8b
        __emit 0x74
        __emit 0x24
        __emit 0x0c
        __emit 0x57
        __emit 0x6a
        __emit 0x00
        __emit 0x8b
        __emit 0xce
        __emit 0xe8
        __emit 0xb0
        __emit 0xd8
        __emit 0x72
        __emit 0x00
        __emit 0x6a
        __emit 0x00
        __emit 0x8b
        __emit 0xce
        __emit 0x8b
        __emit 0xf8
        __emit 0xe8
        __emit 0xf5
        __emit 0xd8
        __emit 0x72
        __emit 0x00
        __emit 0x85
        __emit 0xc0
        __emit 0x74
        __emit 0x0d
        __emit 0x50
        __emit 0xe8
        __emit 0x4b
        __emit 0xf5
        __emit 0x72
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x04
        __emit 0x8b
        __emit 0xd8
        __emit 0xeb
        __emit 0x05
        __emit 0xbb
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x85
        __emit 0xff
        __emit 0x74
        __emit 0x16
        __emit 0x8b
        __emit 0xc7
        __emit 0x8d
        __emit 0x50
        __emit 0x01
        __emit 0x8d
        __emit 0x9b
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x8a
        __emit 0x08
        __emit 0x40
        __emit 0x84
        __emit 0xc9
        __emit 0x75
        __emit 0xf9
        __emit 0x2b
        __emit 0xc2
        __emit 0xeb
        __emit 0x02
        __emit 0x33
        __emit 0xc0
        __emit 0x8b
        __emit 0x74
        __emit 0x24
        __emit 0x14
        __emit 0x50
        __emit 0x57
        __emit 0x8d
        __emit 0x8e
        __emit 0x74
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0xe8
        __emit 0x12
        __emit 0x4c
        __emit 0x76
        __emit 0x00
        __emit 0x5f
        __emit 0x89
        __emit 0x9e
        __emit 0x78
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x5e
        __emit 0x5b
        __emit 0xc3
	}
}
