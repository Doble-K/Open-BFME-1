// cl: /DNDEBUG /MD /EHsc

namespace FXParticleSystem
{
template<int Category>
class DefaultModuleTemplate
{
public:
    DefaultModuleTemplate(const DefaultModuleTemplate<Category> &);
};

template<int Category>
__declspec(naked) DefaultModuleTemplate<Category>::DefaultModuleTemplate(const DefaultModuleTemplate<Category> &)
{
    __asm {
        _emit 08Bh
        _emit 0C1h
        _emit 08Bh
        _emit 04Ch
        _emit 024h
        _emit 004h
        _emit 085h
        _emit 0C9h
        _emit 0C7h
        _emit 040h
        _emit 004h
        _emit 0E4h
        _emit 0F9h
        _emit 010h
        _emit 001h
        _emit 0C7h
        _emit 000h
        _emit 0C0h
        _emit 0FBh
        _emit 010h
        _emit 001h
        _emit 0C7h
        _emit 040h
        _emit 004h
        _emit 0BCh
        _emit 0FBh
        _emit 010h
        _emit 001h
        _emit 074h
        _emit 005h
        _emit 083h
        _emit 0C1h
        _emit 008h
        _emit 0EBh
        _emit 002h
        _emit 033h
        _emit 0C9h
        _emit 0C7h
        _emit 040h
        _emit 008h
        _emit 0F8h
        _emit 00Bh
        _emit 011h
        _emit 001h
        _emit 08Bh
        _emit 051h
        _emit 004h
        _emit 089h
        _emit 050h
        _emit 00Ch
        _emit 08Bh
        _emit 051h
        _emit 008h
        _emit 089h
        _emit 050h
        _emit 010h
        _emit 08Bh
        _emit 051h
        _emit 00Ch
        _emit 089h
        _emit 050h
        _emit 014h
        _emit 08Bh
        _emit 051h
        _emit 010h
        _emit 089h
        _emit 050h
        _emit 018h
        _emit 083h
        _emit 0C1h
        _emit 014h
        _emit 056h
        _emit 08Bh
        _emit 031h
        _emit 08Dh
        _emit 050h
        _emit 01Ch
        _emit 089h
        _emit 032h
        _emit 08Bh
        _emit 071h
        _emit 004h
        _emit 089h
        _emit 072h
        _emit 004h
        _emit 08Bh
        _emit 049h
        _emit 008h
        _emit 089h
        _emit 04Ah
        _emit 008h
        _emit 0C7h
        _emit 000h
        _emit 024h
        _emit 00Ch
        _emit 011h
        _emit 001h
        _emit 0C7h
        _emit 040h
        _emit 004h
        _emit 020h
        _emit 00Ch
        _emit 011h
        _emit 001h
        _emit 0C7h
        _emit 040h
        _emit 008h
        _emit 00Ch
        _emit 00Ch
        _emit 011h
        _emit 001h
        _emit 05Eh
        _emit 0C2h
        _emit 004h
        _emit 000h
    }
}

template class DefaultModuleTemplate<3>;
}
