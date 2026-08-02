// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

class INI
{
public:
    __declspec(dllexport) static void parseScienceVector(INI *, void *, void *, const void *);
};

class INIParseScienceVectorShim
{
public:
    static void parse(INI *ini, void *store, void *userData, const void *desc);
};

void INI::parseScienceVector(INI *ini, void *store, void *userData, const void *desc)
{
    INIParseScienceVectorShim::parse(ini, store, userData, desc);
}
