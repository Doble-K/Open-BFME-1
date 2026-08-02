class AsciiString
{
};

class ScriptEngine
{
public:
    void createNamedMapReveal(const AsciiString &, const AsciiString &, float, const AsciiString &);
};

class ScriptEngineCreateNamedMapRevealShim
{
public:
    void create(const AsciiString &name, const AsciiString &waypoint, float radius, const AsciiString &player);
};

void ScriptEngine::createNamedMapReveal(const AsciiString &name, const AsciiString &waypoint, float radius, const AsciiString &player)
{
    ((ScriptEngineCreateNamedMapRevealShim *)this)->create(name, waypoint, radius, player);
}
