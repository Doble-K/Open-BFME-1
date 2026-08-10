// cl: /DNDEBUG /MD /EHsc

class Gen_dtor_00113f20
{
public:
	virtual ~Gen_dtor_00113f20();

private:
	const void *m_moduleData;
};

class ObjectModule : public Gen_dtor_00113f20
{
private:
	void *m_object;
};

class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor() = 0;
};

class UpdateModuleInterface
{
public:
	virtual void updateModuleInterfaceAnchor() = 0;
};

class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
public:
	virtual ~BehaviorModule() {}
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
	virtual ~UpdateModule() {}

private:
	unsigned int m_14;
	int m_18;
	int m_1c;
};

class AsciiString
{
public:
	~AsciiString();

private:
	char *m_data;
};

class AutoAbilityBehavior : public UpdateModule
{
public:
	virtual ~AutoAbilityBehavior();

private:
	AsciiString m_20;
};

// ??1AutoAbilityBehavior@@UAE@XZ
AutoAbilityBehavior::~AutoAbilityBehavior()
{
}
