// cl: /DNDEBUG /MD /EHsc

namespace FXParticleSystem
{
struct PointEmissionVolumeModuleTag
{
};

class PointEmissionVolumeModuleTemplate
{
};

template <class Tag>
class ConcreteModuleTemplate;

template <>
class ConcreteModuleTemplate<PointEmissionVolumeModuleTag>
{
public:
    virtual PointEmissionVolumeModuleTemplate *clone() const;
};

__declspec(naked) PointEmissionVolumeModuleTemplate *ConcreteModuleTemplate<PointEmissionVolumeModuleTag>::clone() const
{
    __asm {
        _emit 056h
        _emit 06Ah
        _emit 010h
        _emit 08Bh
        _emit 0F1h
        _emit 0E8h
        _emit 0D6h
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
        _emit 03Ah
        _emit 0C3h
        _emit 0A5h
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
