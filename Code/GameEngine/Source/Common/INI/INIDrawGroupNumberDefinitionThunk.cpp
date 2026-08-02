// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class INI
{
public:
    static void parseDrawGroupNumberDefinition(INI *ini);
};

// ?parseDrawGroupNumberDefinition@INI@@SAXPAV1@@Z
__declspec(naked) void INI::parseDrawGroupNumberDefinition(INI *ini)
{
    __asm {
        __emit 0xa1
        __emit 0xf8
        __emit 0x13
        __emit 0x2f
        __emit 0x01
        __emit 0x83
        __emit 0xec
        __emit 0x08
        __emit 0x85
        __emit 0xc0
        __emit 0x75
        __emit 0x23
        __emit 0x68
        __emit 0x54
        __emit 0x2b
        __emit 0x08
        __emit 0x01
        __emit 0x8d
        __emit 0x44
        __emit 0x24
        __emit 0x04
        __emit 0x6a
        __emit 0x09
        __emit 0x50
        __emit 0xe8
        __emit 0xe3
        __emit 0x83
        __emit 0x79
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
        __emit 0x04
        __emit 0x51
        __emit 0xe8
        __emit 0xd1
        __emit 0xea
        __emit 0x93
        __emit 0x00
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x0c
        __emit 0x68
        __emit 0x58
        __emit 0x29
        __emit 0x08
        __emit 0x01
        __emit 0x50
        __emit 0xe8
        __emit 0x62
        __emit 0x9e
        __emit 0x79
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x08
        __emit 0xc3
    }
}
