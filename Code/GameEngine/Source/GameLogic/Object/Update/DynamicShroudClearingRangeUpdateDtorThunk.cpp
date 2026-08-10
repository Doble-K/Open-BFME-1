// cl: /DNDEBUG /MD /EHsc

// The retail object is an UpdateModule-shaped multiple-inheritance object with
// a 30-element RadiusDecal member array.  These declarations are TU-local so
// the destructor can be emitted without changing the shared engine headers.

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
	unsigned char m_pad[4];
};

class DynamicShroudClearingRangeUpdate : public UpdateModule
{
public:
	virtual ~DynamicShroudClearingRangeUpdate();

private:
	unsigned char m_data[0x30];
	RadiusDecal m_gridDecal[30];
};

// ??1DynamicShroudClearingRangeUpdate@@UAE@XZ
DynamicShroudClearingRangeUpdate::~DynamicShroudClearingRangeUpdate()
{
	for (int d = 0; d < 30; ++d)
	{
		m_gridDecal[d].clear();
	}
}
