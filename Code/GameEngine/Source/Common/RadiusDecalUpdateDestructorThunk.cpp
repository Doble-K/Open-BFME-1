// cl: /DNDEBUG /MD /EHsc

// The retail object is an UpdateModule-shaped multiple-inheritance object with
// one RadiusDecal member.  These declarations are TU-local so the destructor
// can be emitted without changing the shared engine headers.

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

public:
	virtual ~UpdateModule() {}
};

class RadiusDecal
{
public:
	void clear();
	~RadiusDecal();

private:
	const void *m_template;
	void *m_decal;
	unsigned char m_empty;
};

class RadiusDecalUpdate : public UpdateModule
{
public:
	virtual ~RadiusDecalUpdate();

private:
	RadiusDecal m_deliveryDecal;
};

// ??1RadiusDecalUpdate@@UAE@XZ
RadiusDecalUpdate::~RadiusDecalUpdate()
{
	m_deliveryDecal.clear();
}
