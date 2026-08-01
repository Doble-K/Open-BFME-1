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

class BoxEmissionVolumeModule
{
};

class BoxEmissionVolumeModuleTemplate
{
};

extern const char BOX_EMISSION_VOLUME_MODULE_KEY[1];
extern const char BOX_EMISSION_VOLUME_MODULE_NAME[1];

template <int Category, const char (&Key)[1], const char (&Name)[1], class Module, class ModuleTemplate, class ParticleModule, class ParticleModuleTemplate>
class ModuleTag
{
};

template <class Tag>
class ConcreteModuleTemplate;

typedef ModuleTag<5, BOX_EMISSION_VOLUME_MODULE_KEY, BOX_EMISSION_VOLUME_MODULE_NAME,
    BoxEmissionVolumeModule, BoxEmissionVolumeModuleTemplate,
    DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > BoxEmissionVolumeTag;

template <>
class ConcreteModuleTemplate<BoxEmissionVolumeTag>
{
public:
    virtual BoxEmissionVolumeModuleTemplate *clone() const;
};

__declspec(naked) BoxEmissionVolumeModuleTemplate *ConcreteModuleTemplate<BoxEmissionVolumeTag>::clone() const
{
    __asm {
        _emit 056h
        _emit 057h
        _emit 06Ah
        _emit 01Ch
        _emit 08Bh
        _emit 0F9h
        _emit 0E8h
        _emit 055h
        _emit 050h
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
        _emit 016h
        _emit 005h
        _emit 0A5h
        _emit 0FFh
        _emit 05Fh
        _emit 0C7h
        _emit 006h
        _emit 0D4h
        _emit 011h
        _emit 011h
        _emit 001h
        _emit 0C7h
        _emit 046h
        _emit 004h
        _emit 0D0h
        _emit 011h
        _emit 011h
        _emit 001h
        _emit 0C7h
        _emit 046h
        _emit 008h
        _emit 0BCh
        _emit 011h
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
