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

class SphereEmissionVolumeModule
{
};

class SphereEmissionVolumeModuleTemplate
{
};

extern const char SPHERE_EMISSION_VOLUME_MODULE_KEY[1];
extern const char SPHERE_EMISSION_VOLUME_MODULE_NAME[1];

template <int Category, const char (&Key)[1], const char (&Name)[1], class Module, class ModuleTemplate, class ParticleModule, class ParticleModuleTemplate>
class ModuleTag
{
};

template <class Tag>
class ConcreteModuleTemplate;

typedef ModuleTag<5, SPHERE_EMISSION_VOLUME_MODULE_KEY, SPHERE_EMISSION_VOLUME_MODULE_NAME,
    SphereEmissionVolumeModule, SphereEmissionVolumeModuleTemplate,
    DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > SphereEmissionVolumeTag;

template <>
class ConcreteModuleTemplate<SphereEmissionVolumeTag>
{
public:
    virtual SphereEmissionVolumeModuleTemplate *clone() const;
};

__declspec(naked) SphereEmissionVolumeModuleTemplate *ConcreteModuleTemplate<SphereEmissionVolumeTag>::clone() const
{
    __asm {
        _emit 056h
        _emit 06Ah
        _emit 014h
        _emit 08Bh
        _emit 0F1h
        _emit 0E8h
        _emit 006h
        _emit 050h
        _emit 02Ah
        _emit 000h
        _emit 083h
        _emit 0C4h
        _emit 004h
        _emit 085h
        _emit 0C0h
        _emit 074h
        _emit 00Ah
        _emit 056h
        _emit 08Bh
        _emit 0C8h
        _emit 0E8h
        _emit 06Ah
        _emit 01Eh
        _emit 0A4h
        _emit 0FFh
        _emit 05Eh
        _emit 0C3h
        _emit 033h
        _emit 0C0h
        _emit 05Eh
        _emit 0C3h
    }
}
}
