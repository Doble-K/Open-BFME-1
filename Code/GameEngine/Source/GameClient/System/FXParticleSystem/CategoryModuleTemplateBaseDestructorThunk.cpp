// cl: /DNDEBUG /MD /EHsc

namespace FXParticleSystem
{
template<int Category>
class CategoryModuleTemplate
{
};

template<>
class __declspec(novtable) CategoryModuleTemplate<0>
{
public:
    virtual ~CategoryModuleTemplate();
};

__declspec(naked) CategoryModuleTemplate<0>::~CategoryModuleTemplate()
{
    __asm {
        _emit 085h
        _emit 0C9h
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

template<int Category>
class CategoryModuleTemplateBase
{
};

template<>
class __declspec(novtable) CategoryModuleTemplateBase<1>
{
public:
    virtual ~CategoryModuleTemplateBase();
};

__declspec(naked) CategoryModuleTemplateBase<1>::~CategoryModuleTemplateBase()
{
    __asm {
        _emit 085h
        _emit 0C9h
        _emit 074h
        _emit 00Eh
        _emit 0C7h
        _emit 041h
        _emit 004h
        _emit 078h
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
        _emit 078h
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

template<>
class __declspec(novtable) CategoryModuleTemplateBase<3>
{
public:
    virtual ~CategoryModuleTemplateBase();
};

__declspec(naked) CategoryModuleTemplateBase<3>::~CategoryModuleTemplateBase()
{
    __asm {
        _emit 085h
        _emit 0C9h
        _emit 074h
        _emit 00Eh
        _emit 0C7h
        _emit 041h
        _emit 004h
        _emit 0E4h
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
        _emit 0E4h
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

template<>
class __declspec(novtable) CategoryModuleTemplateBase<7>
{
public:
    virtual ~CategoryModuleTemplateBase();
};

__declspec(naked) CategoryModuleTemplateBase<7>::~CategoryModuleTemplateBase()
{
    __asm {
        _emit 085h
        _emit 0C9h
        _emit 074h
        _emit 00Eh
        _emit 0C7h
        _emit 041h
        _emit 004h
        _emit 014h
        _emit 0FAh
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
        _emit 014h
        _emit 0FAh
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

template<>
class __declspec(novtable) CategoryModuleTemplateBase<2>
{
public:
    virtual ~CategoryModuleTemplateBase();
};

__declspec(naked) CategoryModuleTemplateBase<2>::~CategoryModuleTemplateBase()
{
    __asm {
        _emit 085h
        _emit 0C9h
        _emit 074h
        _emit 00Eh
        _emit 0C7h
        _emit 041h
        _emit 004h
        _emit 0E8h
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
        _emit 0E8h
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

template<>
class __declspec(novtable) CategoryModuleTemplateBase<0>
{
public:
    virtual ~CategoryModuleTemplateBase();
};

__declspec(naked) CategoryModuleTemplateBase<0>::~CategoryModuleTemplateBase()
{
    __asm {
        _emit 085h
        _emit 0C9h
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
