// cl: /DNDEBUG /MD /EHsc

class Team;

class TeamFactory
{
public:
	void teamAboutToBeDeleted(Team *team);
};

extern TeamFactory *TheTeamFactory;

class Team
{
public:
	virtual ~Team();
};

void deleteTeamCallback(Team *team)
{
	if (team)
	{
		TheTeamFactory->teamAboutToBeDeleted(team);
		delete team;
	}
}
