class SpawnPointProductionExitUpdate
{
    void initializeBonePositions();
};

class SpawnPointInitializeBonePositionsShim
{
public:
    void init();
};

void SpawnPointProductionExitUpdate::initializeBonePositions()
{
    ((SpawnPointInitializeBonePositionsShim *)this)->init();
}
