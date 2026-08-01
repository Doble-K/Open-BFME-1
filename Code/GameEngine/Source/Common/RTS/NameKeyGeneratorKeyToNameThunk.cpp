// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

class AsciiString
{
};

enum NameKeyType
{
    NameKeyType_Thunk
};

class NameKeyGenerator
{
public:
    AsciiString keyToName(NameKeyType);
};

__declspec(naked) AsciiString NameKeyGenerator::keyToName(NameKeyType)
{
    __asm {
        _emit 0E9h
        _emit 0B1h
        _emit 010h
        _emit 005h
        _emit 000h
    }
}
