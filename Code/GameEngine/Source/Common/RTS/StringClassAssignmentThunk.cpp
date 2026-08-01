// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

class StringClass
{
public:
    const StringClass &operator=(const StringClass &);
};

__declspec(naked) const StringClass &StringClass::operator=(const StringClass &)
{
    __asm {
        _emit 0E9h
        _emit 01Ch
        _emit 056h
        _emit 010h
        _emit 000h
    }
}
