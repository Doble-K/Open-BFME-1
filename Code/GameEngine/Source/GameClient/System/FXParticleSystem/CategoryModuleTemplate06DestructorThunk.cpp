// cl: /DNDEBUG /MD /EHsc

namespace FXParticleSystem
{
template<int Category>
class CategoryModuleTemplate
{
};

template<>
class __declspec(novtable) CategoryModuleTemplate<6>
{
public:
    virtual ~CategoryModuleTemplate();
};

__declspec(naked) CategoryModuleTemplate<6>::~CategoryModuleTemplate()
{
    __asm {
        _emit 085h
        _emit 0C9h
        _emit 074h
        _emit 00Eh
        _emit 0C7h
        _emit 041h
        _emit 004h
        _emit 07Ch
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
        _emit 07Ch
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
