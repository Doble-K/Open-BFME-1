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
        _emit 0C1h
        _emit 08Bh
        _emit 04Ch
        _emit 024h
        _emit 004h
        _emit 085h
        _emit 0C9h
        _emit 074h
        _emit 00Dh
        _emit 08Dh
        _emit 051h
        _emit 008h
        _emit 066h
        _emit 08Bh
        _emit 00Ah
        _emit 066h
        _emit 089h
        _emit 048h
        _emit 008h
        _emit 0C2h
        _emit 004h
        _emit 000h
        _emit 033h
        _emit 0D2h
        _emit 066h
        _emit 08Bh
        _emit 00Ah
        _emit 066h
        _emit 089h
        _emit 048h
        _emit 008h
        _emit 0C2h
        _emit 004h
        _emit 000h
    }
}

template class CategoryModuleTemplate<8>;
}
