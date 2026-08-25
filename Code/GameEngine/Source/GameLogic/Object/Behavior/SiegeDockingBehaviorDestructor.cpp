// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// SiegeDockingBehavior's retail destructor uses the BFME UpdateModule layout,
// with a vector at +0x24 and a nothrow stopDocking call.  Keep this recovered
// view in the proper behavior source family instead of changing shared headers.

#include <vector>

class Gen_dtor_00113d40
{
public:
	virtual ~Gen_dtor_00113d40();

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

class ObjectModule : public Gen_dtor_00113d40
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
public:
	virtual ~UpdateModule() {}

private:
	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	unsigned int m_updateState;
};

class SiegeDockingBehaviorSecondaryBase
{
public:
	virtual void slot();
};

class SiegeDockingBehavior
	: public UpdateModule,
	  public SiegeDockingBehaviorSecondaryBase
{
public:
	virtual ~SiegeDockingBehavior();

private:
	void stopDocking() throw();

	_STL::vector<int> m_vector;
};

// ??1SiegeDockingBehavior@@UAE@XZ
SiegeDockingBehavior::~SiegeDockingBehavior()
{
	stopDocking();
}
