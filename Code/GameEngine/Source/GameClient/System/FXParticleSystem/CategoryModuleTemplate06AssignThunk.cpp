// cl: /DNDEBUG /MD /EHsc

namespace FXParticleSystem
{
template<int Category>
class CategoryModuleTemplate
{
public:
    CategoryModuleTemplate<Category> &operator=(const CategoryModuleTemplate<Category> &);
};

template<int Category>
__declspec(naked) CategoryModuleTemplate<Category> &CategoryModuleTemplate<Category>::operator=(const CategoryModuleTemplate<Category> &)
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
        _emit 0BCh
        _emit 0A3h
        _emit 0A5h
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
        _emit 0ABh
        _emit 0A3h
        _emit 0A5h
        _emit 0FFh
        _emit 08Bh
        _emit 0C6h
        _emit 05Eh
        _emit 0C2h
        _emit 004h
        _emit 000h
    }
}

template class CategoryModuleTemplate<7>;
}
