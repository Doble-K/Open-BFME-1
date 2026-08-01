// cl: /DNDEBUG /MD /EHsc

namespace FXParticleSystem
{
template <int N>
class DefaultParticleModule
{
};

template <int N>
class DefaultParticleModuleTemplate
{
};

class CylinderEmissionVolumeModule
{
};

class CylinderEmissionVolumeModuleTemplate
{
};

extern const char CYLINDER_EMISSION_VOLUME_MODULE_KEY[1];
extern const char CYLINDER_EMISSION_VOLUME_MODULE_NAME[1];

template <int Category, const char (&Key)[1], const char (&Name)[1], class Module, class ModuleTemplate, class ParticleModule, class ParticleModuleTemplate>
class ModuleTag
{
};

template <class Tag>
class ConcreteModuleTemplate;

typedef ModuleTag<5, CYLINDER_EMISSION_VOLUME_MODULE_KEY, CYLINDER_EMISSION_VOLUME_MODULE_NAME,
    CylinderEmissionVolumeModule, CylinderEmissionVolumeModuleTemplate,
    DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > CylinderEmissionVolumeTag;

template <>
class ConcreteModuleTemplate<CylinderEmissionVolumeTag>
{
public:
    virtual CylinderEmissionVolumeModuleTemplate *clone() const;
};

__declspec(naked) CylinderEmissionVolumeModuleTemplate *ConcreteModuleTemplate<CylinderEmissionVolumeTag>::clone() const
{
    __asm {
        _emit 056h
        _emit 057h
        _emit 06Ah
        _emit 024h
        _emit 08Bh
        _emit 0F9h
        _emit 0E8h
        _emit 0D5h
        _emit 04Fh
        _emit 02Ah
        _emit 000h
        _emit 08Bh
        _emit 0F0h
        _emit 083h
        _emit 0C4h
        _emit 004h
        _emit 085h
        _emit 0F6h
        _emit 074h
        _emit 021h
        _emit 057h
        _emit 08Bh
        _emit 0CEh
        _emit 0E8h
        _emit 083h
        _emit 068h
        _emit 0A4h
        _emit 0FFh
        _emit 05Fh
        _emit 0C7h
        _emit 006h
        _emit 02Ch
        _emit 012h
        _emit 011h
        _emit 001h
        _emit 0C7h
        _emit 046h
        _emit 004h
        _emit 028h
        _emit 012h
        _emit 011h
        _emit 001h
        _emit 0C7h
        _emit 046h
        _emit 008h
        _emit 014h
        _emit 012h
        _emit 011h
        _emit 001h
        _emit 08Bh
        _emit 0C6h
        _emit 05Eh
        _emit 0C3h
        _emit 05Fh
        _emit 033h
        _emit 0C0h
        _emit 05Eh
        _emit 0C3h
    }
}
}
