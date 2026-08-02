// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /Code/GameEngine/Include/Precompiled /Code/Libraries/Source/WWVegas/WWLib

class MultiIniFieldParse;

class ActiveBodyModuleData
{
public:
    static void buildFieldParse(MultiIniFieldParse &parse);
};

class ActiveBodyModuleDataBuildFieldParseShim
{
public:
    static void build(MultiIniFieldParse &parse);
};

void ActiveBodyModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
    ActiveBodyModuleDataBuildFieldParseShim::build(parse);
}
