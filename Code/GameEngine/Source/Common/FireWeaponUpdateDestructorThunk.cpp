// cl: /DNDEBUG /MD /EHsc

class Gen_dtor_00113f20
{
public:
	virtual ~Gen_dtor_00113f20();

private:
	const void *m_moduleData;
};

class BehaviorModuleInterface
{
public:
	virtual void getBehaviorModuleInterface() = 0;
};

class UpdateModuleInterface
{
public:
	virtual void updateModuleInterface() = 0;
};

class ObjectModule : public Gen_dtor_00113f20
{
private:
	void *m_object;
};

class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
public:
	virtual ~BehaviorModule() {}
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
private:
	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_indexInUpdate;

public:
	virtual ~UpdateModule() {}
};

class Weapon
{
public:
	virtual ~Weapon();
};

class FireWeaponUpdate : public UpdateModule
{
public:
	virtual ~FireWeaponUpdate();

private:
	Weapon *m_weapon;
};

// ??1FireWeaponUpdate@@UAE@XZ
FireWeaponUpdate::~FireWeaponUpdate()
{
	delete m_weapon;
}
