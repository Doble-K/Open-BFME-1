// cl: /DNDEBUG /MD /EHsc

namespace FXParticleSystem
{
template <int N>
class DefaultModuleTag
{
};

template <int N>
class DefaultModuleTemplate
{
};

template <class Tag>
class ConcreteModuleTemplate
{
public:
    virtual DefaultModuleTemplate<1> *clone() const;
};

template <class Tag>
__declspec(naked) DefaultModuleTemplate<1> *ConcreteModuleTemplate<Tag>::clone() const
{
    __asm {
        _emit 056h
        _emit 068h
        _emit 08Ch
        _emit 000h
        _emit 000h
        _emit 000h
        _emit 08Bh
        _emit 0F1h
        _emit 0E8h
        _emit 003h
        _emit 053h
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
        _emit 01Eh
        _emit 0A7h
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

template class ConcreteModuleTemplate<DefaultModuleTag<1> >;
}
