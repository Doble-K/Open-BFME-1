// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class AsciiString;
class Anim2DTemplate;

class Anim2DCollection
{
public:
    Anim2DTemplate *newTemplate(const AsciiString &name);
};

// ?newTemplate@Anim2DCollection@@QAEPAVAnim2DTemplate@@ABVAsciiString@@@Z
__declspec(naked) Anim2DTemplate *Anim2DCollection::newTemplate(const AsciiString &name)
{
    __asm {
        __emit 0x6a
        __emit 0xff
        __emit 0x68
        __emit 0xfb
        __emit 0x93
        __emit 0x03
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
        __emit 0x83
        __emit 0xec
        __emit 0x08
        __emit 0x56
        __emit 0x57
        __emit 0x6a
        __emit 0x1c
        __emit 0x8b
        __emit 0xf9
        __emit 0xe8
        __emit 0xbd
        __emit 0x6e
        __emit 0x2c
        __emit 0x00
        __emit 0x8b
        __emit 0xf0
        __emit 0x83
        __emit 0xc4
        __emit 0x04
        __emit 0x89
        __emit 0x74
        __emit 0x24
        __emit 0x08
        __emit 0x33
        __emit 0xc0
        __emit 0x3b
        __emit 0xf0
        __emit 0x89
        __emit 0x44
        __emit 0x24
        __emit 0x18
        __emit 0x74
        __emit 0x18
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x20
        __emit 0x51
        __emit 0x89
        __emit 0x64
        __emit 0x24
        __emit 0x10
        __emit 0x8b
        __emit 0xcc
        __emit 0x50
        __emit 0xe8
        __emit 0xc9
        __emit 0xca
        __emit 0x2c
        __emit 0x00
        __emit 0x8b
        __emit 0xce
        __emit 0xe8
        __emit 0x43
        __emit 0xc2
        __emit 0xa6
        __emit 0xff
        __emit 0x8b
        __emit 0x4f
        __emit 0x08
        __emit 0x89
        __emit 0x48
        __emit 0x04
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x10
        __emit 0x89
        __emit 0x47
        __emit 0x08
        __emit 0x5f
        __emit 0x64
        __emit 0x89
        __emit 0x0d
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x5e
        __emit 0x83
        __emit 0xc4
        __emit 0x14
        __emit 0xc2
        __emit 0x04
        __emit 0x00
    }
}
