// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// SiegeDockingBehavior's destructor, lifted from its MASM dump to C++.
//
// The module-destructor shape OpenContainDestructorThunk.cpp works out: the
// UpdateModule base's vptrs at 0x00, 0x0C and 0x10, the inlined ~UpdateModule
// and ~BehaviorModule vptr restores, and the out-of-line base destructor at
// 0x00113D40. One interface base follows at 0x20.
//
// There is one tracked entity, a vector<int> at 0x24 that retail frees inline,
// and the destructor body ahead of it is a single call on this. Retail runs
// that call at unwind state 0 -- the same state as the vector -- and never
// changes the state again.
//
// That is what the `throw()` on stopDocking is for. Declared normally, the call
// can throw, so MSVC gives the body its own region and the states come out 1
// then 0; declared nothrow, the body needs no region of its own and merges into
// the vector's, which is the retail numbering. Nothing else in the function
// changes.
//
// The method itself is unclaimed at 0x00206710 and is pinned at the thunk
// address the call site encodes.

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
	unsigned int m_updateState;					///< out to sizeof() == 0x20
};

// Plain virtual rather than a virtual destructor: retail gives this subobject a
// vptr write and no unwind state.
class SiegeDockingBehaviorSecondaryBase
{
public:
	virtual void slot();
};

class SiegeDockingBehavior
	: public UpdateModule,
	  public SiegeDockingBehaviorSecondaryBase		///< vptr at 0x20
{
public:
	virtual ~SiegeDockingBehavior();

private:
	void stopDocking() throw();

	_STL::vector<int> m_vector;						///< retail this+0x24
};

// ??1SiegeDockingBehavior@@UAE@XZ
SiegeDockingBehavior::~SiegeDockingBehavior()
{
	stopDocking();
}
