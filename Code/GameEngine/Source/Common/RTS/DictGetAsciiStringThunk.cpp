// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /Code/GameEngine/Include/Precompiled /Code/Libraries/Source/WWVegas/WWLib

class AsciiString
{
};

enum NameKeyType
{
    NameKeyType_Thunk
};

class Dict
{
public:
    AsciiString getAsciiString(NameKeyType, bool *) const;
};

__declspec(naked) AsciiString Dict::getAsciiString(NameKeyType, bool *) const
{
    __asm {
        _emit 0E9h
        _emit 00Eh
        _emit 086h
        _emit 003h
        _emit 000h
    }
}
