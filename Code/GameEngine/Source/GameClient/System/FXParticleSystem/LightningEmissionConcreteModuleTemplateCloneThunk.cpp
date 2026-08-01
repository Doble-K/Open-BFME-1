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

class LightningEmissionModule
{
};

class LightningEmissionModuleTemplate
{
};

extern const char LIGHTNING_EMISSION_MODULE_KEY[1];
extern const char LIGHTNING_EMISSION_MODULE_NAME[1];

template <int Category, const char (&Key)[1], const char (&Name)[1], class Module, class ModuleTemplate, class ParticleModule, class ParticleModuleTemplate>
class ModuleTag
{
};

template <class Tag>
class ConcreteModuleTemplate;

typedef ModuleTag<5, LIGHTNING_EMISSION_MODULE_KEY, LIGHTNING_EMISSION_MODULE_NAME,
    LightningEmissionModule, LightningEmissionModuleTemplate,
    DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > LightningEmissionTag;

template <>
class ConcreteModuleTemplate<LightningEmissionTag>
{
public:
    virtual LightningEmissionModuleTemplate *clone() const;
};

__declspec(naked) LightningEmissionModuleTemplate *ConcreteModuleTemplate<LightningEmissionTag>::clone() const
{
    __asm {
        _emit 056h
        _emit 068h
        _emit 094h
        _emit 000h
        _emit 000h
        _emit 000h
        _emit 08Bh
        _emit 0F1h
        _emit 0E8h
        _emit 083h
        _emit 04Fh
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
        _emit 0CCh
        _emit 0CFh
        _emit 0A3h
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
