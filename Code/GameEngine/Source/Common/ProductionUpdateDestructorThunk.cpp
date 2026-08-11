// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// ProductionUpdate's destructor, lifted from its MASM dump to C++.
//
// Same module-destructor shape as PassiveAreaEffectBehavior next door -- the
// UpdateModule base's three vptrs at 0x00, 0x0C and 0x10, the inlined
// ~UpdateModule and ~BehaviorModule vptr restores, and the out-of-line base
// destructor at 0x00113D40 -- with two secondary interface bases at 0x20 and
// 0x24 on top, an _STL::list<int> member at 0xDC, and a real body.
//
// That body is the production queue teardown. It drains the linked list whose
// head is at 0x28, handing each entry to a method of this object and then
// deleting it through its own vtable slot 0, and then, if the global at
// 0x012ED668 is live, calls that object's vtable slot 0x4C with this+0xE4.

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

// Plain virtuals rather than virtual destructors: retail gives these two
// subobjects a vptr write and no unwind state.
template <int Number>
class ProductionUpdateSecondaryBase
{
public:
	virtual void slot();
};

// Deleted through vtable slot 0 with the flag argument: the scalar deleting
// destructor, called as `delete entry` would call it.
class ProductionEntry
{
public:
	virtual void *scalarDeletingDestructor(unsigned int flags);
};

// Only slot 0x4C is used; the slots ahead of it are placeholders that put it
// at the offset the call site encodes.
class ProductionUpdateOwner
{
public:
	virtual void slot00();	virtual void slot04();	virtual void slot08();
	virtual void slot0c();	virtual void slot10();	virtual void slot14();
	virtual void slot18();	virtual void slot1c();	virtual void slot20();
	virtual void slot24();	virtual void slot28();	virtual void slot2c();
	virtual void slot30();	virtual void slot34();	virtual void slot38();
	virtual void slot3c();	virtual void slot40();	virtual void slot44();
	virtual void slot48();
	virtual void slot4c(void *arg);
};

extern ProductionUpdateOwner *TheProductionUpdateOwner;

class ProductionUpdate
	: public UpdateModule,
	  public ProductionUpdateSecondaryBase<1>,		///< vptr at 0x20
	  public ProductionUpdateSecondaryBase<2>		///< vptr at 0x24
{
public:
	virtual ~ProductionUpdate();

private:
	void removeEntry(ProductionEntry *entry);

	ProductionEntry *m_productionQueue;				///< retail this+0x028
	unsigned char m_unreconstructed_2c[0xb0];
	_STL::list<int> m_list;							///< retail this+0x0DC
	unsigned char m_unreconstructed_e0[4];
	void *m_unreconstructed_e4;						///< retail this+0x0E4
};

// ??1ProductionUpdate@@UAE@XZ
ProductionUpdate::~ProductionUpdate()
{
	while (m_productionQueue)
	{
		ProductionEntry *entry = m_productionQueue;
		removeEntry(entry);
		if (entry)
		{
			entry->scalarDeletingDestructor(1);
		}
	}

	if (TheProductionUpdateOwner)
	{
		TheProductionUpdateOwner->slot4c(m_unreconstructed_e4);
	}
}
