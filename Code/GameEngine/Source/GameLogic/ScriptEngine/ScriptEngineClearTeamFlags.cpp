// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: retail ScriptEngine::clearTeamFlags.

class AsciiString
{
public:
	AsciiString(const char *);
	~AsciiString();

private:
	char *m_data;
};

class ScriptEngine
{
public:
	void clearTeamFlags(void);
	void clearFlag(const AsciiString &name);
};

void ScriptEngine::clearTeamFlags(void)
{
	clearFlag("USA Team is Building");
	clearFlag("USA Air Team Is Building");
	clearFlag("USA Inf Team Is Building");
	clearFlag("China Team is Building");
	clearFlag("China Air Team Is Building");
	clearFlag("China Inf Team Is Building");
	clearFlag("GLA Team is Building");
	clearFlag("GLA Inf Team is Building");
}
