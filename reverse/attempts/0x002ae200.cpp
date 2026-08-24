// ??0StructureCollapseUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
// partial score=0.95 date=2026-08-25
// cl: /DNDEBUG /MD /EHsc

// Retail 0x002AE200, 174 bytes. Same base stack as the raw BannerCarrierUpdate
// at 0x00283330 -- a twelve-byte module base taking thing and moduleData
// through ILT 0x000170E4, two bare interface bases at +0x0C and +0x10, and a
// vftable-less base holding +0x14, +0x18 and +0x1C -- with two things added.
//
// First, a fifth base at +0x20 carrying a vftable of its own, stored before
// the derived overwrites it. That base has a destructor: this constructor has
// an SEH frame and parks this in it, which is what MSVC does when a
// half-constructed object needs unwinding.
//
// Second, a call in the body. The arguments are the module base's own member
// at +0x08 and 0x3FFFFFFF, which is UpdateModule::setWakeFrame with
// UPDATE_SLEEP_FOREVER -- so setWakeFrame has to sit at offset zero of the
// chain, above the class whose constructor the ILT reaches.
//
// The five words +0x24 through +0x34 come out in the order 0x24, 0x2C, 0x30,
// 0x28, 0x34: that is the scheduler permuting equal stores, and it falls out
// of declaring them in offset order. The three after the call keep source
// order because the call separates them.

typedef int Int;

class Thing;
class ModuleData;
class Object;

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 0,
	UPDATE_SLEEP_FOREVER = 0x3FFFFFFF
};

class UpdateModule
{
public:
	virtual void bfmeModuleSlot(void) = 0;

protected:
	void setWakeFrame(Object *object, UpdateSleepTime when);	// ILT 0x000157DA

	char m_bfmePad[0x08 - 0x04];
	Object *m_bfmeObject;						// +0x08
};

class ObjectModule : public UpdateModule
{
public:
	ObjectModule(Thing *thing, const ModuleData *moduleData);	// ILT 0x000170E4
};

class BfmeCollapseInterfaceA
{
public:
	virtual void bfmeInterfaceSlotA(void) = 0;
};

class BfmeCollapseInterfaceB
{
public:
	BfmeCollapseInterfaceB()
	{
		m_bfme0014 = 0;
		m_bfme0018 = -1;
		m_bfme001C = -1;
	}

	virtual void bfmeInterfaceSlotB(void) = 0;

	Int m_bfme0014;							// +0x14
	Int m_bfme0018;							// +0x18
	Int m_bfme001C;							// +0x1C
};

class BfmeCollapseHelperBase
{
public:
	BfmeCollapseHelperBase() { }
	~BfmeCollapseHelperBase();

	virtual void bfmeHelperSlot(void) = 0;
};

class StructureCollapseUpdate : public ObjectModule,
				public BfmeCollapseInterfaceA,
				public BfmeCollapseInterfaceB,
				public BfmeCollapseHelperBase
{
public:
	StructureCollapseUpdate(Thing *thing, const ModuleData *moduleData);

	virtual void bfmeModuleSlot(void) { }
	virtual void bfmeInterfaceSlotA(void) { }
	virtual void bfmeInterfaceSlotB(void) { }
	virtual void bfmeHelperSlot(void) { }

private:
	Int m_bfme0024;							// +0x24
	Int m_bfme0028;							// +0x28
	Int m_bfme002C;							// +0x2C
	Int m_bfme0030;							// +0x30
	Int m_bfme0034;							// +0x34
	Int m_bfme0038;							// +0x38
	Int m_bfme003C;							// +0x3C
	Int m_bfme0040;							// +0x40
};

// ??0StructureCollapseUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
StructureCollapseUpdate::StructureCollapseUpdate(Thing *thing, const ModuleData *moduleData)
	: ObjectModule(thing, moduleData),
	  m_bfme0024(0),
	  m_bfme0028(0),
	  m_bfme002C(0),
	  m_bfme0030(0),
	  m_bfme0034(0)
{
	setWakeFrame(m_bfmeObject, UPDATE_SLEEP_FOREVER);

	m_bfme0038 = 0;
	m_bfme003C = 0;
	m_bfme0040 = 0;
}
