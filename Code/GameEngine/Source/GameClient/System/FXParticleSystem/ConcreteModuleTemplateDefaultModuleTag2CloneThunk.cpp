// cl: /DNDEBUG /MD /EHsc

namespace FXParticleSystem
{
template<int Category>
class DefaultModuleTag
{
};

template<int Category>
class DefaultModuleTemplate
{
};

template<class Tag>
class ConcreteModuleTemplate
{
public:
    virtual DefaultModuleTemplate<3> *clone() const;
};

template<class Tag>
__declspec(naked) DefaultModuleTemplate<3> *ConcreteModuleTemplate<Tag>::clone() const
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
        _emit 052h
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
        _emit 0AAh
        _emit 07Eh
        _emit 0A3h
        _emit 0FFh
        _emit 05Fh
        _emit 0C7h
        _emit 006h
        _emit 0C4h
        _emit 00Fh
        _emit 011h
        _emit 001h
        _emit 0C7h
        _emit 046h
        _emit 004h
        _emit 0C0h
        _emit 00Fh
        _emit 011h
        _emit 001h
        _emit 0C7h
        _emit 046h
        _emit 008h
        _emit 0ACh
        _emit 00Fh
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

template class ConcreteModuleTemplate<DefaultModuleTag<3> >;
}
