// cl: /DNDEBUG /MD /EHsc

namespace FXParticleSystem
{
template<int Category>
class CategoryModuleTemplateBase
{
};

template<>
class __declspec(novtable) CategoryModuleTemplateBase<5>
{
public:
    virtual ~CategoryModuleTemplateBase();
};

__declspec(naked) CategoryModuleTemplateBase<5>::~CategoryModuleTemplateBase()
{
    __asm {
        _emit 085h
        _emit 0C9h
        _emit 074h
        _emit 00Eh
        _emit 0C7h
        _emit 041h
        _emit 004h
        _emit 0ACh
        _emit 0F9h
        _emit 010h
        _emit 001h
        _emit 0C7h
        _emit 001h
        _emit 058h
        _emit 037h
        _emit 007h
        _emit 001h
        _emit 0C3h
        _emit 033h
        _emit 0C0h
        _emit 0C7h
        _emit 000h
        _emit 0ACh
        _emit 0F9h
        _emit 010h
        _emit 001h
        _emit 0C7h
        _emit 001h
        _emit 058h
        _emit 037h
        _emit 007h
        _emit 001h
        _emit 0C3h
    }
}
}
