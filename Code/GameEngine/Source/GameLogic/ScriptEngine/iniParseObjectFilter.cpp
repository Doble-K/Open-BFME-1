// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

class INI;

void iniParseObjectFilter(INI *, void *, void *, const void *);

class IniParseObjectFilterShim
{
public:
    static void run(INI *ini, void *store, void *userData, const void *desc);
};

void iniParseObjectFilter(INI *ini, void *store, void *userData, const void *desc)
{
    IniParseObjectFilterShim::run(ini, store, userData, desc);
}
