// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class HeaderTemplateManager
{
    void populateGameFonts();
};

// ?populateGameFonts@HeaderTemplateManager@@AAEXXZ
__declspec(naked) void HeaderTemplateManager::populateGameFonts()
{
    __asm {
        __emit 0x51
        __emit 0x53
        __emit 0x8b
        __emit 0xd9
        __emit 0x8b
        __emit 0x03
        __emit 0x57
        __emit 0x8b
        __emit 0x38
        __emit 0x3b
        __emit 0xf8
        __emit 0x74
        __emit 0x44
        __emit 0x56
        __emit 0x8b
        __emit 0xff
        __emit 0x8b
        __emit 0x77
        __emit 0x08
        __emit 0x8b
        __emit 0x46
        __emit 0x0c
        __emit 0x8b
        __emit 0x0d
        __emit 0x84
        __emit 0x14
        __emit 0x2f
        __emit 0x01
        __emit 0x50
        __emit 0xe8
        __emit 0xc5
        __emit 0x89
        __emit 0xb7
        __emit 0xff
        __emit 0x33
        __emit 0xc9
        __emit 0x8a
        __emit 0x4e
        __emit 0x10
        __emit 0x89
        __emit 0x44
        __emit 0x24
        __emit 0x0c
        __emit 0xdb
        __emit 0x44
        __emit 0x24
        __emit 0x0c
        __emit 0x8d
        __emit 0x46
        __emit 0x08
        __emit 0xd9
        __emit 0x5c
        __emit 0x24
        __emit 0x0c
        __emit 0x8b
        __emit 0x54
        __emit 0x24
        __emit 0x0c
        __emit 0x51
        __emit 0x8b
        __emit 0x0d
        __emit 0x38
        __emit 0x1b
        __emit 0x2f
        __emit 0x01
        __emit 0x52
        __emit 0x50
        __emit 0xe8
        __emit 0xfb
        __emit 0xe6
        __emit 0xb7
        __emit 0xff
        __emit 0x89
        __emit 0x06
        __emit 0x8b
        __emit 0x3f
        __emit 0x3b
        __emit 0x3b
        __emit 0x75
        __emit 0xc0
        __emit 0x5e
        __emit 0x5f
        __emit 0x5b
        __emit 0x59
        __emit 0xc3
    }
}
