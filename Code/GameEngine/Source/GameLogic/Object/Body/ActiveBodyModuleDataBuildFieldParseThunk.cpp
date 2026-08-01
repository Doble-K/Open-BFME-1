// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /Code/GameEngine/Include/Precompiled /Code/Libraries/Source/WWVegas/WWLib

class MultiIniFieldParse;

class ActiveBodyModuleData
{
public:
    static void buildFieldParse(MultiIniFieldParse &parse);
};

__declspec(naked) void ActiveBodyModuleData::buildFieldParse(MultiIniFieldParse &)
{
    __asm {
        _emit 0E9h
        _emit 029h
        _emit 0EDh
        _emit 020h
        _emit 000h
    }
}
