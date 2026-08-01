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
class ConcreteModuleClass
{
public:
    virtual DefaultModuleTemplate<6> *createTemplate() const;
};

template<class Tag>
__declspec(naked) DefaultModuleTemplate<6> *ConcreteModuleClass<Tag>::createTemplate() const
{
    __asm {
        _emit 06Ah
        _emit 0FFh
        _emit 068h
        _emit 03Bh
        _emit 0B6h
        _emit 003h
        _emit 001h
        _emit 064h
        _emit 0A1h
        _emit 000h
        _emit 000h
        _emit 000h
        _emit 000h
        _emit 050h
        _emit 064h
        _emit 089h
        _emit 025h
        _emit 000h
        _emit 000h
        _emit 000h
        _emit 000h
        _emit 051h
        _emit 056h
        _emit 06Ah
        _emit 00Ch
        _emit 0E8h
        _emit 0E2h
        _emit 0E0h
        _emit 029h
        _emit 000h
        _emit 08Bh
        _emit 0F0h
        _emit 083h
        _emit 0C4h
        _emit 004h
        _emit 089h
        _emit 074h
        _emit 024h
        _emit 004h
        _emit 033h
        _emit 0C0h
        _emit 03Bh
        _emit 0F0h
        _emit 089h
        _emit 044h
        _emit 024h
        _emit 010h
        _emit 074h
        _emit 01Dh
        _emit 08Bh
        _emit 0CEh
        _emit 0E8h
        _emit 0C2h
        _emit 0BDh
        _emit 0A4h
        _emit 0FFh
        _emit 0C7h
        _emit 006h
        _emit 00Ch
        _emit 00Eh
        _emit 011h
        _emit 001h
        _emit 0C7h
        _emit 046h
        _emit 004h
        _emit 008h
        _emit 00Eh
        _emit 011h
        _emit 001h
        _emit 0C7h
        _emit 046h
        _emit 008h
        _emit 0F4h
        _emit 00Dh
        _emit 011h
        _emit 001h
        _emit 08Bh
        _emit 0C6h
        _emit 08Bh
        _emit 04Ch
        _emit 024h
        _emit 008h
        _emit 05Eh
        _emit 064h
        _emit 089h
        _emit 00Dh
        _emit 000h
        _emit 000h
        _emit 000h
        _emit 000h
        _emit 083h
        _emit 0C4h
        _emit 010h
        _emit 0C3h
    }
}

template class ConcreteModuleClass<DefaultModuleTag<6> >;
}
