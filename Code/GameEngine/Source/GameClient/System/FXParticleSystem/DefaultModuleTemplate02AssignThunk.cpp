// cl: /DNDEBUG /MD /EHsc

namespace FXParticleSystem
{
template<int Category>
class DefaultModuleTemplate
{
public:
    DefaultModuleTemplate<Category> &operator=(const DefaultModuleTemplate<Category> &);
};

template<int Category>
__declspec(naked) DefaultModuleTemplate<Category> &DefaultModuleTemplate<Category>::operator=(const DefaultModuleTemplate<Category> &)
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
        _emit 074h
        _emit 005h
        _emit 08Dh
        _emit 051h
        _emit 008h
        _emit 0EBh
        _emit 002h
        _emit 033h
        _emit 0D2h
        _emit 056h
        _emit 08Dh
        _emit 04Ah
        _emit 004h
        _emit 057h
        _emit 08Bh
        _emit 039h
        _emit 08Dh
        _emit 070h
        _emit 00Ch
        _emit 089h
        _emit 03Eh
        _emit 08Bh
        _emit 079h
        _emit 004h
        _emit 089h
        _emit 07Eh
        _emit 004h
        _emit 08Bh
        _emit 049h
        _emit 008h
        _emit 089h
        _emit 04Eh
        _emit 008h
        _emit 08Bh
        _emit 04Ah
        _emit 010h
        _emit 089h
        _emit 048h
        _emit 018h
        _emit 083h
        _emit 0C2h
        _emit 014h
        _emit 08Bh
        _emit 032h
        _emit 08Dh
        _emit 048h
        _emit 01Ch
        _emit 089h
        _emit 031h
        _emit 08Bh
        _emit 072h
        _emit 004h
        _emit 089h
        _emit 071h
        _emit 004h
        _emit 08Bh
        _emit 052h
        _emit 008h
        _emit 05Fh
        _emit 089h
        _emit 051h
        _emit 008h
        _emit 05Eh
        _emit 0C2h
        _emit 004h
        _emit 000h
    }
}

template class DefaultModuleTemplate<3>;
}
