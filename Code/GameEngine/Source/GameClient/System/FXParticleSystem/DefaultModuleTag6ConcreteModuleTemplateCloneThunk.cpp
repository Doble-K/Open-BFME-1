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
    virtual DefaultModuleTemplate<7> *clone() const;
};

template <class Tag>
__declspec(naked) DefaultModuleTemplate<7> *ConcreteModuleTemplate<Tag>::clone() const
{
    __asm {
        _emit 056h
        _emit 06Ah
        _emit 050h
        _emit 08Bh
        _emit 0F1h
        _emit 0E8h
        _emit 026h
        _emit 052h
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
        _emit 0C3h
        _emit 0D0h
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

template class ConcreteModuleTemplate<DefaultModuleTag<7> >;
}
