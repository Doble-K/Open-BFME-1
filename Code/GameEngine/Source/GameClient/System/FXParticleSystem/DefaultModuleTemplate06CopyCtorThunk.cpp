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
        _emit 044h
        _emit 024h
        _emit 004h
        _emit 056h
        _emit 050h
        _emit 08Bh
        _emit 0F1h
        _emit 0E8h
        _emit 000h
        _emit 019h
        _emit 0A3h
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
        _emit 0C2h
        _emit 004h
        _emit 000h
    }
}
}

template class FXParticleSystem::DefaultModuleTemplate<7>;
