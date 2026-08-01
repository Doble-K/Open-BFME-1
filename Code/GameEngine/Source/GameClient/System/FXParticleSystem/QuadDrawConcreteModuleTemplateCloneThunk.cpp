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

class QuadDrawModule
{
};

class QuadDrawModuleTemplate
{
};

extern const char QUAD_DRAW_MODULE_KEY[1];
extern const char QUAD_DRAW_MODULE_NAME[1];

template <int Category, const char (&Key)[1], const char (&Name)[1], class Module, class ModuleTemplate, class ParticleModule, class ParticleModuleTemplate>
class ModuleTag
{
};

template <class Tag>
class ConcreteModuleTemplate;

typedef ModuleTag<6, QUAD_DRAW_MODULE_KEY, QUAD_DRAW_MODULE_NAME,
    QuadDrawModule, QuadDrawModuleTemplate,
    DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > QuadDrawTag;

template <>
class ConcreteModuleTemplate<QuadDrawTag>
{
public:
    virtual QuadDrawModuleTemplate *clone() const;
};

__declspec(naked) QuadDrawModuleTemplate *ConcreteModuleTemplate<QuadDrawTag>::clone() const
{
    __asm {
        _emit 056h
        _emit 06Ah
        _emit 00Ch
        _emit 08Bh
        _emit 0F1h
        _emit 0E8h
        _emit 0D6h
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
        _emit 024h
        _emit 074h
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
