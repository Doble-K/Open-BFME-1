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

class ButterflyDrawModule
{
};

class ButterflyDrawModuleTemplate
{
};

extern const char BUTTERFLY_DRAW_MODULE_KEY[1];
extern const char BUTTERFLY_DRAW_MODULE_NAME[1];

template <int Category, const char (&Key)[1], const char (&Name)[1], class Module, class ModuleTemplate, class ParticleModule, class ParticleModuleTemplate>
class ModuleTag
{
};

template <class Tag>
class ConcreteModuleTemplate;

typedef ModuleTag<6, BUTTERFLY_DRAW_MODULE_KEY, BUTTERFLY_DRAW_MODULE_NAME,
    ButterflyDrawModule, ButterflyDrawModuleTemplate,
    DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > ButterflyDrawTag;

template <>
class ConcreteModuleTemplate<ButterflyDrawTag>
{
public:
    virtual ButterflyDrawModuleTemplate *clone() const;
};

__declspec(naked) ButterflyDrawModuleTemplate *ConcreteModuleTemplate<ButterflyDrawTag>::clone() const
{
    __asm {
        _emit 056h
        _emit 06Ah
        _emit 00Ch
        _emit 08Bh
        _emit 0F1h
        _emit 0E8h
        _emit 0A6h
        _emit 071h
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
        _emit 006h
        _emit 015h
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
