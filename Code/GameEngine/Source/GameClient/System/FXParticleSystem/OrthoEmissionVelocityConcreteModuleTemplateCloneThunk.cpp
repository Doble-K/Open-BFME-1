// cl: /DNDEBUG /MD /EHsc

namespace FXParticleSystem
{
struct OrthoEmissionVelocityModuleTag
{
};

class OrthoEmissionVelocityModuleTemplate
{
};

template <class Tag>
class ConcreteModuleTemplate
{
public:
    virtual OrthoEmissionVelocityModuleTemplate *clone() const;
};

template <>
class ConcreteModuleTemplate<OrthoEmissionVelocityModuleTag>
{
public:
    virtual OrthoEmissionVelocityModuleTemplate *clone() const;
};

__declspec(naked) OrthoEmissionVelocityModuleTemplate *ConcreteModuleTemplate<OrthoEmissionVelocityModuleTag>::clone() const
{
    __asm {
        _emit 056h
        _emit 06Ah
        _emit 030h
        _emit 08Bh
        _emit 0F1h
        _emit 0E8h
        _emit 0C6h
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
        _emit 037h
        _emit 04Fh
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
