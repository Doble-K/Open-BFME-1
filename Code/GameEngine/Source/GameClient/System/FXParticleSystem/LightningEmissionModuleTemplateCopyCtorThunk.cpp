// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

namespace FXParticleSystem {

class LightningEmissionModuleTemplate
{
public:
    __declspec(nothrow) LightningEmissionModuleTemplate(const LightningEmissionModuleTemplate &that);
};

// ??0LightningEmissionModuleTemplate@FXParticleSystem@@QAE@ABV01@@Z
__declspec(naked) LightningEmissionModuleTemplate::LightningEmissionModuleTemplate(const LightningEmissionModuleTemplate &that)
{
    __asm {
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x04
        __emit 0x85
        __emit 0xc0
        __emit 0x56
        __emit 0x8b
        __emit 0xf1
        __emit 0xc7
        __emit 0x46
        __emit 0x04
        __emit 0xac
        __emit 0xf9
        __emit 0x10
        __emit 0x01
        __emit 0x57
        __emit 0xc7
        __emit 0x06
        __emit 0x20
        __emit 0xfc
        __emit 0x10
        __emit 0x01
        __emit 0xc7
        __emit 0x46
        __emit 0x04
        __emit 0x1c
        __emit 0xfc
        __emit 0x10
        __emit 0x01
        __emit 0x74
        __emit 0x05
        __emit 0x83
        __emit 0xc0
        __emit 0x08
        __emit 0xeb
        __emit 0x02
        __emit 0x33
        __emit 0xc0
        __emit 0x8d
        __emit 0x7e
        __emit 0x08
        __emit 0x50
        __emit 0x8b
        __emit 0xcf
        __emit 0xe8
        __emit 0x5c
        __emit 0x77
        __emit 0xa6
        __emit 0xff
        __emit 0xc7
        __emit 0x07
        __emit 0xb8
        __emit 0x0a
        __emit 0x11
        __emit 0x01
        __emit 0x5f
        __emit 0xc7
        __emit 0x06
        __emit 0xa4
        __emit 0x0a
        __emit 0x11
        __emit 0x01
        __emit 0xc7
        __emit 0x46
        __emit 0x04
        __emit 0xa0
        __emit 0x0a
        __emit 0x11
        __emit 0x01
        __emit 0x8b
        __emit 0xc6
        __emit 0x5e
        __emit 0xc2
        __emit 0x04
        __emit 0x00
    }
}

}
