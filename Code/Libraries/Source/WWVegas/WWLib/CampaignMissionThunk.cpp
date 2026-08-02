class Mission
{
};

class Campaign
{
public:
    Mission *getNextMission(Mission *);
};

class CampaignGetNextMissionShim
{
public:
    Mission *next(Mission *current);
};

Mission *Campaign::getNextMission(Mission *current)
{
    return ((CampaignGetNextMissionShim *)this)->next(current);
}
