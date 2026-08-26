// cl: /DNDEBUG /MD /EHsc

class AsciiString;

class Team
{
public:
	unsigned char m_unmodelled_000[0x31];
	unsigned char m_active;
	unsigned char m_started;
};

class TeamFactory
{
public:
	Team *createTeam(const AsciiString &owner, const AsciiString &name);

private:
	Team *bfmeCreateInactiveTeam(const AsciiString &owner, const AsciiString &name);
};

Team *TeamFactory::createTeam(const AsciiString &owner, const AsciiString &name)
{
	Team *team = bfmeCreateInactiveTeam(owner, name);
	if (!team->m_active)
	{
		team->m_started = 1;
		team->m_active = 1;
	}
	return team;
}
