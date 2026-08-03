// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class MultiIniFieldParse;

class BroadcastStealthUpdateModuleData
{
public:
    static void buildFieldParse(MultiIniFieldParse &parse);
};

class BroadcastStealthUpdateModuleDataBuildFieldParseShim
{
public:
    static void build(MultiIniFieldParse &parse);
};

void BroadcastStealthUpdateModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
    BroadcastStealthUpdateModuleDataBuildFieldParseShim::build(parse);
}
