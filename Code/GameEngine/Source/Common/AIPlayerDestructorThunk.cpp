// cl: /DNDEBUG /MD /EHsc

class PlayerController
{
protected:
	virtual ~PlayerController() {}
};

class TeamInQueue;
static void deleteQueue(TeamInQueue *) {}

class AIPlayer : public PlayerController
{
protected:
	virtual ~AIPlayer();
	void removeAll_TeamBuildQueue(void (*)(TeamInQueue *));
	void removeAll_TeamReadyQueue(void (*)(TeamInQueue *));
};

// ??1AIPlayer@@MAE@XZ
AIPlayer::~AIPlayer()
{
	removeAll_TeamBuildQueue(deleteQueue);
	removeAll_TeamReadyQueue(deleteQueue);
}
