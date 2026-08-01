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
        _emit 056h
        _emit 08Bh
        _emit 0F1h
        _emit 0E8h
        _emit 064h
        _emit 07Ch
        _emit 0A5h
        _emit 0FFh
        _emit 0C7h
        _emit 006h
        _emit 01Ch
        _emit 010h
        _emit 011h
        _emit 001h
        _emit 0C7h
        _emit 046h
        _emit 004h
        _emit 018h
        _emit 010h
        _emit 011h
        _emit 001h
        _emit 0C7h
        _emit 046h
        _emit 008h
        _emit 004h
        _emit 010h
        _emit 011h
        _emit 001h
        _emit 08Bh
        _emit 0C6h
        _emit 05Eh
        _emit 0C3h
    }
}

template class DefaultModuleTemplate<7>;
}
