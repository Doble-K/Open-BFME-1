// cl: /DNDEBUG /MD /EHsc

namespace FXParticleSystem
{
template <int Category>
class CategoryModuleTemplate
{
public:
    CategoryModuleTemplate();
};

template <int Category>
__declspec(naked) CategoryModuleTemplate<Category>::CategoryModuleTemplate()
{
    __asm {
        _emit 08Bh
        _emit 0C1h
        _emit 0C7h
        _emit 040h
        _emit 004h
        _emit 05Ch
        _emit 037h
        _emit 007h
        _emit 001h
        _emit 0B1h
        _emit 001h
        _emit 088h
        _emit 048h
        _emit 008h
        _emit 088h
        _emit 048h
        _emit 009h
        _emit 0C7h
        _emit 000h
        _emit 048h
        _emit 038h
        _emit 007h
        _emit 001h
        _emit 0C7h
        _emit 040h
        _emit 004h
        _emit 044h
        _emit 038h
        _emit 007h
        _emit 001h
        _emit 0C3h
    }
}

template class CategoryModuleTemplate<8>;
}
