// cl: /DNDEBUG /MD /EHsc

namespace FXParticleSystem
{
template <int N>
class DefaultModuleTemplate
{
public:
    DefaultModuleTemplate();
};

template <int N>
__declspec(naked) DefaultModuleTemplate<N>::DefaultModuleTemplate()
{
    __asm {
        _emit 06Ah
        _emit 0FFh
        _emit 068h
        _emit 078h
        _emit 0ADh
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
        _emit 08Bh
        _emit 0F1h
        _emit 0C7h
        _emit 046h
        _emit 004h
        _emit 0E8h
        _emit 0F9h
        _emit 010h
        _emit 001h
        _emit 057h
        _emit 089h
        _emit 074h
        _emit 024h
        _emit 008h
        _emit 0C7h
        _emit 006h
        _emit 090h
        _emit 0FBh
        _emit 010h
        _emit 001h
        _emit 0C7h
        _emit 046h
        _emit 004h
        _emit 08Ch
        _emit 0FBh
        _emit 010h
        _emit 001h
        _emit 08Dh
        _emit 07Eh
        _emit 008h
        _emit 08Bh
        _emit 0CFh
        _emit 0C7h
        _emit 044h
        _emit 024h
        _emit 014h
        _emit 000h
        _emit 000h
        _emit 000h
        _emit 000h
        _emit 0E8h
        _emit 0B7h
        _emit 073h
        _emit 0A6h
        _emit 0FFh
        _emit 08Bh
        _emit 04Ch
        _emit 024h
        _emit 00Ch
        _emit 0C7h
        _emit 007h
        _emit 064h
        _emit 00Ch
        _emit 011h
        _emit 001h
        _emit 0C7h
        _emit 006h
        _emit 050h
        _emit 00Ch
        _emit 011h
        _emit 001h
        _emit 0C7h
        _emit 046h
        _emit 004h
        _emit 04Ch
        _emit 00Ch
        _emit 011h
        _emit 001h
        _emit 05Fh
        _emit 08Bh
        _emit 0C6h
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

template class DefaultModuleTemplate<2>;
}
