// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

class Dict
{
    struct DictPair;
    DictPair *ensureUnique(int, bool, DictPair *);
};

class DictEnsureUniqueShim
{
public:
    struct DictPair;
    DictPair *run(int count, bool flag, DictPair *pair);
};

Dict::DictPair *Dict::ensureUnique(int count, bool flag, DictPair *pair)
{
    return (Dict::DictPair *)((DictEnsureUniqueShim *)this)->run(count, flag, (DictEnsureUniqueShim::DictPair *)pair);
}
