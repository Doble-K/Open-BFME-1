// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /Code/GameEngine/Include /Code/GameEngine/Include/Precompiled /Code/Libraries/Source/WWVegas/WWLib

class INI;

class BoneFXUpdateModuleData
{
public:
    __declspec(dllexport) static void parseObjectCreationList(INI *, void *, void *, const void *);
};

__declspec(naked) void BoneFXUpdateModuleData::parseObjectCreationList(INI *, void *, void *, const void *)
{
    __asm {
        _emit 0E9h
        _emit 0D6h
        _emit 046h
        _emit 028h
        _emit 000h
    }
}
