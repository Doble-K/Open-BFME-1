// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift MASM dump to standalone C++ thunk.

class Thing;
class ModuleData;

enum DamageType
{
	DAMAGE_NORMAL = 0
};

enum DeathType
{
	DEATH_SLAVE_WATCHER_RELEASE = 13
};

class Object
{
public:
	void kill(DamageType, DeathType);
};

class GameLogic
{
public:
	Object *findObjectByID(int);
};

extern GameLogic *TheGameLogic;

class PB_DeepBase
{
public:
	virtual ~PB_DeepBase();

protected:
	void *m_p4;
	Object *m_object;
};

class SlaveWatcherBehaviorIface1
{
public:
	virtual void slot() = 0;
};

class SlaveWatcherBehaviorIface2
{
public:
	virtual void slot() = 0;
};

class UpdateModule : public PB_DeepBase, public SlaveWatcherBehaviorIface1
{
public:
	virtual ~UpdateModule() {}
};

class SlaveWatcherUpdateModule : public UpdateModule, public SlaveWatcherBehaviorIface2
{
public:
	virtual ~SlaveWatcherUpdateModule() {}
};

class SlaveWatcherBehavior : public SlaveWatcherUpdateModule
{
public:
	virtual ~SlaveWatcherBehavior();

private:
	unsigned int m_f14;
	int m_f18;
	int m_f1c;
	int m_slaveID;
};

SlaveWatcherBehavior::~SlaveWatcherBehavior()
{
	if (m_slaveID)
	{
		Object *slave = TheGameLogic->findObjectByID(m_slaveID);
		if (slave)
			slave->kill(DAMAGE_NORMAL, DEATH_SLAVE_WATCHER_RELEASE);
	}
}
