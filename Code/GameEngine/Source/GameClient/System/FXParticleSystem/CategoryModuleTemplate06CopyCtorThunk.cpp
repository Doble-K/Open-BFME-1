// cl: /DNDEBUG /MD /EHsc

namespace FXParticleSystem
{
template<int Category>
class CategoryModuleTemplate
{
public:
    CategoryModuleTemplate(const CategoryModuleTemplate<Category> &);
};

template<int Category>
__declspec(naked) CategoryModuleTemplate<Category>::CategoryModuleTemplate(const CategoryModuleTemplate<Category> &)
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
        _emit 0BBh
        _emit 051h
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
        _emit 0ECh
        _emit 058h
        _emit 0A8h
        _emit 0FFh
        _emit 0C7h
        _emit 007h
        _emit 094h
        _emit 0FCh
        _emit 010h
        _emit 001h
        _emit 05Fh
        _emit 0C7h
        _emit 006h
        _emit 080h
        _emit 0FCh
        _emit 010h
        _emit 001h
        _emit 0C7h
        _emit 046h
        _emit 004h
        _emit 07Ch
        _emit 0FCh
        _emit 010h
        _emit 001h
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
