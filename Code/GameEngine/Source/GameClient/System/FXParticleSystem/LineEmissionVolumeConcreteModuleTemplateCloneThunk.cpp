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

class LineEmissionVolumeModule
{
};

class LineEmissionVolumeModuleTemplate
{
};

extern const char LINE_EMISSION_VOLUME_MODULE_KEY[1];
extern const char LINE_EMISSION_VOLUME_MODULE_NAME[1];

template <int Category, const char (&Key)[1], const char (&Name)[1], class Module, class ModuleTemplate, class ParticleModule, class ParticleModuleTemplate>
class ModuleTag
{
};

template <class Tag>
class ConcreteModuleTemplate;

typedef ModuleTag<5, LINE_EMISSION_VOLUME_MODULE_KEY, LINE_EMISSION_VOLUME_MODULE_NAME,
    LineEmissionVolumeModule, LineEmissionVolumeModuleTemplate,
    DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > LineEmissionVolumeTag;

template <>
class ConcreteModuleTemplate<LineEmissionVolumeTag>
{
public:
    virtual LineEmissionVolumeModuleTemplate *clone() const;
};

__declspec(naked) LineEmissionVolumeModuleTemplate *ConcreteModuleTemplate<LineEmissionVolumeTag>::clone() const
{
    __asm {
        _emit 056h
        _emit 057h
        _emit 06Ah
        _emit 028h
        _emit 08Bh
        _emit 0F9h
        _emit 0E8h
        _emit 0A5h
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
        _emit 0CDh
        _emit 073h
        _emit 0A2h
        _emit 0FFh
        _emit 05Fh
        _emit 0C7h
        _emit 006h
        _emit 0A8h
        _emit 011h
        _emit 011h
        _emit 001h
        _emit 0C7h
        _emit 046h
        _emit 004h
        _emit 0A4h
        _emit 011h
        _emit 011h
        _emit 001h
        _emit 0C7h
        _emit 046h
        _emit 008h
        _emit 090h
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
