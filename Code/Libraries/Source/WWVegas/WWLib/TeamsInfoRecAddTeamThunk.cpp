class Dict;

class TeamsInfoRec
{
public:
    void addTeam(const Dict *);
};

class TeamsInfoRecAddTeamShim
{
public:
    void add(const Dict *dict);
};

void TeamsInfoRec::addTeam(const Dict *dict)
{
    ((TeamsInfoRecAddTeamShim *)this)->add(dict);
}
