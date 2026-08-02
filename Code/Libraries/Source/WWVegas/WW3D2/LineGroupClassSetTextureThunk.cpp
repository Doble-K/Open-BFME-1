// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class TextureClass;

class LineGroupClass
{
public:
    void Set_Texture(TextureClass *texture);
};

// ?Set_Texture@LineGroupClass@@QAEXPAVTextureClass@@@Z
__declspec(naked) void LineGroupClass::Set_Texture(TextureClass *)
{
    __asm {
        __emit 0x56
        __emit 0x57
        __emit 0x8b
        __emit 0x7c
        __emit 0x24
        __emit 0x0c
        __emit 0x8b
        __emit 0x07
        __emit 0x85
        __emit 0xc0
        __emit 0x8b
        __emit 0xf1
        __emit 0x74
        __emit 0x04
        __emit 0x66
        __emit 0xff
        __emit 0x40
        __emit 0x04
        __emit 0x8b
        __emit 0x4e
        __emit 0x24
        __emit 0x85
        __emit 0xc9
        __emit 0x74
        __emit 0x0f
        __emit 0xe8
        __emit 0x02
        __emit 0xcb
        __emit 0x05
        __emit 0x00
        __emit 0x8b
        __emit 0x07
        __emit 0x5f
        __emit 0x89
        __emit 0x46
        __emit 0x24
        __emit 0x5e
        __emit 0xc2
        __emit 0x04
        __emit 0x00
        __emit 0x8b
        __emit 0x0f
        __emit 0x5f
        __emit 0x89
        __emit 0x4e
        __emit 0x24
        __emit 0x5e
        __emit 0xc2
        __emit 0x04
        __emit 0x00
    }
}
