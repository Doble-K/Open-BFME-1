// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

class Dict
{
    struct DictPair;
    DictPair *ensureUnique(int, bool, DictPair *);
};

__declspec(naked) Dict::DictPair *Dict::ensureUnique(int, bool, DictPair *)
{
    __asm {
        _emit 0E9h
        _emit 0AAh
        _emit 0C4h
        _emit 003h
        _emit 000h
    }
}
