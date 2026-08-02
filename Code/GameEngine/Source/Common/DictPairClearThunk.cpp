// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class Dict
{
public:
    class DictPair
    {
    public:
        void clear();
    };
};

// ?clear@DictPair@Dict@@QAEXXZ
__declspec(naked) void Dict::DictPair::clear()
{
    __asm {
        __emit 0x8b
        __emit 0x01
        __emit 0x25
        __emit 0xff
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x83
        __emit 0xf8
        __emit 0x04
        __emit 0x77
        __emit 0x0e
        __emit 0xff
        __emit 0x24
        __emit 0x85
        __emit 0xfc
        __emit 0x80
        __emit 0x46
        __emit 0x00
        __emit 0xc7
        __emit 0x41
        __emit 0x04
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xc3
        __emit 0x83
        __emit 0xc1
        __emit 0x04
        __emit 0xe9
        __emit 0x4d
        __emit 0xf8
        __emit 0x81
        __emit 0x00
        __emit 0x83
        __emit 0xc1
        __emit 0x04
        __emit 0xe9
        __emit 0xd5
        __emit 0x00
        __emit 0x82
        __emit 0x00
        __emit 0x90
        __emit 0xe3
        __emit 0x80
        __emit 0x46
        __emit 0x00
        __emit 0xe3
        __emit 0x80
        __emit 0x46
        __emit 0x00
        __emit 0xe3
        __emit 0x80
        __emit 0x46
        __emit 0x00
        __emit 0xeb
        __emit 0x80
        __emit 0x46
        __emit 0x00
        __emit 0xf3
        __emit 0x80
        __emit 0x46
        __emit 0x00
    }
}
