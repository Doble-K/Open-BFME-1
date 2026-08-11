// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// EmotionTrackerUpdate's destructor, lifted from its MASM dump to C++.
//
// The module-destructor shape OpenContainDestructorThunk.cpp works out: the
// UpdateModule base's vptrs at 0x00, 0x0C and 0x10, the inlined ~UpdateModule
// and ~BehaviorModule vptr restores, and the out-of-line base destructor at
// 0x00113D40. One interface base follows at 0x20, then 0x5C bytes of the
// class's own data.
//
// Two members, unwind states 1 and 0:
//
//   0x80  _STL::vector<int>            inlined (sar 2 / shl 2)
//   0x94  _STL::set<4-byte class>      thunk 0x0001FE2E -> 0x000EF440
//
// The set's payload is spelled the way Code/gen_small/tgrid_124.cpp spells that
// instantiation, so the emitted _Rb_tree destructor mangles to the name the
// ledger already carries at 0x000EF440.

#include <set>
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

// payload spelling from Code/gen_small/tgrid_124.cpp
struct Gen_t_000ef440_k4 { int a[1]; Gen_t_000ef440_k4(); Gen_t_000ef440_k4(const Gen_t_000ef440_k4&); ~Gen_t_000ef440_k4(); Gen_t_000ef440_k4& operator=(const Gen_t_000ef440_k4&); };
bool operator==(const Gen_t_000ef440_k4&, const Gen_t_000ef440_k4&);
bool operator<(const Gen_t_000ef440_k4&, const Gen_t_000ef440_k4&);

// Plain virtual rather than a virtual destructor: retail gives this subobject a
// vptr write and no unwind state.
class EmotionTrackerUpdateSecondaryBase
{
public:
	virtual void slot();
};

class EmotionTrackerUpdate
	: public UpdateModule,
	  public EmotionTrackerUpdateSecondaryBase		///< vptr at 0x20
{
public:
	virtual ~EmotionTrackerUpdate();

private:
	unsigned char m_unreconstructed_24[0x5c];
	_STL::vector<int> m_vector;						///< retail this+0x80
	unsigned char m_unreconstructed_8c[8];
	_STL::set<Gen_t_000ef440_k4> m_set;				///< retail this+0x94
};

// ??1EmotionTrackerUpdate@@UAE@XZ
EmotionTrackerUpdate::~EmotionTrackerUpdate()
{
}
