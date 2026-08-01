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

class HemisphericalEmissionVelocityModule
{
};

class HemisphericalEmissionVelocityModuleTemplate
{
};

extern const char HEMISPHERICAL_EMISSION_VELOCITY_MODULE_KEY[1];
extern const char HEMISPHERICAL_EMISSION_VELOCITY_MODULE_NAME[1];

template <int Category, const char (&Key)[1], const char (&Name)[1], class Module, class ModuleTemplate, class ParticleModule, class ParticleModuleTemplate>
class ModuleTag
{
};

template <class Tag>
class ConcreteModuleTemplate;

typedef ModuleTag<4, HEMISPHERICAL_EMISSION_VELOCITY_MODULE_KEY, HEMISPHERICAL_EMISSION_VELOCITY_MODULE_NAME,
    HemisphericalEmissionVelocityModule, HemisphericalEmissionVelocityModuleTemplate,
    DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > HemisphericalEmissionVelocityTag;

template <>
class ConcreteModuleTemplate<HemisphericalEmissionVelocityTag>
{
public:
    virtual HemisphericalEmissionVelocityModuleTemplate *clone() const;
};

__declspec(naked) HemisphericalEmissionVelocityModuleTemplate *ConcreteModuleTemplate<HemisphericalEmissionVelocityTag>::clone() const
{
    __asm {
        _emit 056h
        _emit 06Ah
        _emit 018h
        _emit 08Bh
        _emit 0F1h
        _emit 0E8h
        _emit 066h
        _emit 051h
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
        _emit 0CAh
        _emit 031h
        _emit 0A6h
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
