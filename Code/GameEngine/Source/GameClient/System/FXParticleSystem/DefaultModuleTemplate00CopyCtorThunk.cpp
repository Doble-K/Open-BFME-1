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
        _emit 056h
        _emit 057h
        _emit 08Bh
        _emit 07Ch
        _emit 024h
        _emit 00Ch
        _emit 057h
        _emit 08Bh
        _emit 0F1h
        _emit 0E8h
        _emit 0F9h
        _emit 0D6h
        _emit 0A6h
        _emit 0FFh
        _emit 085h
        _emit 0FFh
        _emit 074h
        _emit 005h
        _emit 08Dh
        _emit 047h
        _emit 008h
        _emit 0EBh
        _emit 002h
        _emit 033h
        _emit 0C0h
        _emit 08Dh
        _emit 07Eh
        _emit 008h
        _emit 050h
        _emit 08Bh
        _emit 0CFh
        _emit 0E8h
        _emit 088h
        _emit 08Eh
        _emit 0A4h
        _emit 0FFh
        _emit 0C7h
        _emit 007h
        _emit 0CCh
        _emit 008h
        _emit 011h
        _emit 001h
        _emit 05Fh
        _emit 0C7h
        _emit 006h
        _emit 0B8h
        _emit 008h
        _emit 011h
        _emit 001h
        _emit 0C7h
        _emit 046h
        _emit 004h
        _emit 0B4h
        _emit 008h
        _emit 011h
        _emit 001h
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
