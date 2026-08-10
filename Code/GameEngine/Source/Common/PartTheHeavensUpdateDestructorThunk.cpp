// cl: /DNDEBUG /MD /EHsc

// The retail object is an UpdateModule-shaped multiple-inheritance object.  The
// declarations are deliberately TU-local: only the ABI-relevant base layout and
// the one explicitly destroyed pointee are needed here.

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
	unsigned int m_updateState;
	unsigned int m_nextUpdateFrame;

public:
	virtual ~UpdateModule() {}
};

class PartTheHeavensUpdatePointee
{
public:
	virtual void pointeeSlot0();
	virtual void pointeeSlot1();
	virtual void releasePointee();
};

class PartTheHeavensUpdate : public UpdateModule
{
public:
	virtual ~PartTheHeavensUpdate();

private:
	PartTheHeavensUpdatePointee *m_pointee;
};

// ??1PartTheHeavensUpdate@@UAE@XZ
PartTheHeavensUpdate::~PartTheHeavensUpdate()
{
	if (m_pointee)
		m_pointee->releasePointee();
}
