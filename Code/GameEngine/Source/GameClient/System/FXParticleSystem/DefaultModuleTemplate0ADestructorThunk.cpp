// cl: /DNDEBUG /MD /EHsc

namespace FXParticleSystem
{
template<int Category>
class DefaultModuleTemplate
{
};

template<>
class __declspec(novtable) DefaultModuleTemplate<0>
{
public:
    virtual ~DefaultModuleTemplate();
};

__declspec(naked) DefaultModuleTemplate<0>::~DefaultModuleTemplate()
{
    __asm {
        _emit 085h
        _emit 0C9h
        _emit 074h
        _emit 005h
        _emit 08Dh
        _emit 041h
        _emit 008h
        _emit 0EBh
        _emit 002h
        _emit 033h
        _emit 0C0h
        _emit 085h
        _emit 0C9h
        _emit 0C7h
        _emit 000h
        _emit 044h
        _emit 037h
        _emit 007h
        _emit 001h
        _emit 074h
        _emit 00Eh
        _emit 0C7h
        _emit 041h
        _emit 004h
        _emit 060h
        _emit 037h
        _emit 007h
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
        _emit 060h
        _emit 037h
        _emit 007h
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
