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
        _emit 044h
        _emit 024h
        _emit 004h
        _emit 085h
        _emit 0C0h
        _emit 056h
        _emit 08Bh
        _emit 0F1h
        _emit 074h
        _emit 012h
        _emit 083h
        _emit 0C0h
        _emit 008h
        _emit 050h
        _emit 08Dh
        _emit 04Eh
        _emit 008h
        _emit 0E8h
        _emit 02Fh
        _emit 09Ah
        _emit 0A4h
        _emit 0FFh
        _emit 08Bh
        _emit 0C6h
        _emit 05Eh
        _emit 0C2h
        _emit 004h
        _emit 000h
        _emit 033h
        _emit 0C0h
        _emit 050h
        _emit 08Dh
        _emit 04Eh
        _emit 008h
        _emit 0E8h
        _emit 01Eh
        _emit 09Ah
        _emit 0A4h
        _emit 0FFh
        _emit 08Bh
        _emit 0C6h
        _emit 05Eh
        _emit 0C2h
        _emit 004h
        _emit 000h
    }
}

template class DefaultModuleTemplate<1>;
}
