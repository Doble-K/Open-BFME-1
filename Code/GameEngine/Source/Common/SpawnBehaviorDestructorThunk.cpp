// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// SpawnBehavior's destructor, lifted from its MASM dump to C++.
//
// The module-destructor shape from OpenContain: the UpdateModule base's vptrs
// at 0x00, 0x0C and 0x10, the inlined ~UpdateModule and ~BehaviorModule vptr
// restores, and the out-of-line base destructor at 0x00113D40. Four interface
// bases follow at 0x20, 0x24, 0x28 and 0x2C.
//
// Two _STL::list<int> members at 0x44 and 0x48, unwind states 0 and 1, and a
// body at state 2: an inlined clear() of the 0x44 list, walking its nodes and
// freeing each at 12 bytes -- next, prev and the int -- before resetting the
// header. The body gets a state of its own because those operator delete calls
// can throw.
//
// The two members reach _List_base<int>::~_List_base through two different
// COMDAT copies, 0x000E5E70 for 0x48 and 0x0020ACD0 for 0x44, both already
// pinned.

#include <list>

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

// Plain virtuals rather than virtual destructors: retail gives these subobjects
// a vptr write and no unwind state.
template <int Number>
class SpawnBehaviorSecondaryBase
{
public:
	virtual void slot();
};

class SpawnBehavior
	: public UpdateModule,
	  public SpawnBehaviorSecondaryBase<1>,			///< vptr at 0x20
	  public SpawnBehaviorSecondaryBase<2>,			///< vptr at 0x24
	  public SpawnBehaviorSecondaryBase<3>,			///< vptr at 0x28
	  public SpawnBehaviorSecondaryBase<4>			///< vptr at 0x2C
{
public:
	virtual ~SpawnBehavior();

private:
	unsigned char m_unreconstructed_30[0x14];
	_STL::list<int> m_spawnList;					///< retail this+0x44
	_STL::list<int> m_list48;						///< retail this+0x48
};

// ??1SpawnBehavior@@UAE@XZ
SpawnBehavior::~SpawnBehavior()
{
	m_spawnList.clear();
}
