// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: BehaviorModule's own constructor.
//
// BFME's Module carries a single MemoryPoolObject vtbl (Snapshot is NOT a
// base of Module here -- confirmed by DieModule/CaveContain's constructors,
// which only ever re-store offset 0 for the inherited view, never a second
// one), plus m_moduleData: sizeof(Module) == 8. ObjectModule adds m_object:
// sizeof(ObjectModule) == 0xC (independently confirmed by two already-landed
// rows: CaveContainCtorThunk.cpp and DestroyDie.cpp both build on top of a
// 0xC-byte flattened ObjectModule).
//
// BehaviorModule itself derives from ObjectModule, BehaviorModuleInterface
// AND Snapshot directly (retail adds Snapshot as BehaviorModule's own base
// rather than routing it through Module) -- confirmed by the target bytes:
// the interim vtable stored @+0x18 right after the ObjectModule call
// (0x1110c78 pre-relocation) resolves in reverse/vtables.tsv to a concrete,
// already-implemented LoadPostProcess/GetSnapshotName/DoXfer vtable, i.e. a
// real Snapshot-shaped vtable, not a pure-interface placeholder. Retail
// carries two extra dwords ahead of the two new vtables that this ObjectModule
// stand-in does not otherwise account for (MSVC groups every polymorphic
// base ahead of any plain data, so those two dwords are modelled as trailing
// ObjectModule members rather than an intervening non-polymorphic base).
// BehaviorModule's own MEMORY_POOL_GLUE_ABC macro re-overrides the dtor and
// getObjectMemoryPool() (the MemoryPoolObject-view slot), so the ctor also
// re-stores offset 0 after the base call, and then BehaviorModuleInterface
// (@+0x14) and Snapshot (@+0x18, interim then final) as the two new bases.

class Thing;
class ModuleData;
class Xfer;
class MemoryPool;

class MemoryPoolObject
{
protected:
	virtual ~MemoryPoolObject() { }
protected:
	virtual MemoryPool *getObjectMemoryPool() { return 0; }
};

class Snapshot
{
public:
	Snapshot() { }
protected:
	virtual void crc(Xfer *xfer) { }
	virtual void xfer(Xfer *xfer) { }
	virtual void loadPostProcess(void) { }
};

class Module : public MemoryPoolObject
{
protected:
	virtual ~Module() { }
private:
	virtual MemoryPool *getObjectMemoryPool() { return 0; }
public:
	Module(const ModuleData *moduleData) : m_moduleData(moduleData) { }
private:
	const ModuleData *m_moduleData;
};

class ObjectModule : public Module
{
protected:
	virtual ~ObjectModule() { }
private:
	virtual MemoryPool *getObjectMemoryPool() { return 0; }
public:
	ObjectModule( Thing *thing, const ModuleData *moduleData );
protected:
	virtual void crc(Xfer *xfer) { }
	virtual void xfer(Xfer *xfer) { }
	virtual void loadPostProcess(void) { }
private:
	Thing *m_object;
	// MSVC places non-polymorphic bases AFTER every polymorphic base
	// regardless of declaration order, so an 8-byte pad base does not
	// land between ObjectModule and the two new interface vtables below
	// the way retail's layout needs; carry the two extra dwords retail's
	// BehaviorModule needs ahead of those vtables as members here instead.
	unsigned int m_pad0;
	unsigned int m_pad4;
};

class __declspec(novtable) BehaviorModuleInterface
{
public:
	virtual void *getBody() { return 0; }
	virtual void *getCollide() { return 0; }
	virtual void *getContain() { return 0; }
	virtual void *getCreate() { return 0; }
	virtual void *getDamage() { return 0; }
	virtual void *getDestroy() { return 0; }
	virtual void *getDie() { return 0; }
	virtual void *getSpecialPower() { return 0; }
	virtual void *getUpdate() { return 0; }
	virtual void *getUpgrade() { return 0; }
	virtual void *getStealth() { return 0; }
	virtual void *getSpyVisionUpdate() { return 0; }

	virtual void *getParkingPlaceBehaviorInterface() { return 0; }
	virtual void *getRebuildHoleBehaviorInterface() { return 0; }
	virtual void *getBridgeBehaviorInterface() { return 0; }
	virtual void *getBridgeTowerBehaviorInterface() { return 0; }
	virtual void *getBridgeScaffoldBehaviorInterface() { return 0; }
	virtual void *getOverchargeBehaviorInterface() { return 0; }
	virtual void *getTransportPassengerInterface() { return 0; }
	virtual void *getCaveInterface() { return 0; }
	virtual void *getLandMineInterface() { return 0; }
	virtual void *getEjectPilotDieInterface() { return 0; }

	virtual void *getProjectileUpdateInterface() { return 0; }
	virtual void *getAIUpdateInterface() { return 0; }
	virtual void *getUpdateExitInterface() { return 0; }
	virtual void *getDockUpdateInterface() { return 0; }
	virtual void *getRailedTransportDockUpdateInterface() { return 0; }
	virtual void *getSlowDeathBehaviorInterface() { return 0; }
	virtual void *getSpecialPowerUpdateInterface() { return 0; }
	virtual void *getSlavedUpdateInterface() { return 0; }
	virtual void *getProductionUpdateInterface() { return 0; }
	virtual void *getHordeUpdateInterface() { return 0; }
	virtual void *getPowerPlantUpdateInterface() { return 0; }
	virtual void *getSpawnBehaviorInterface() { return 0; }
	virtual void *getCountermeasuresBehaviorInterface() { return 0; }
	virtual const void *getCountermeasuresBehaviorInterfaceConst() const { return 0; }
};

class BehaviorModule : public ObjectModule, public BehaviorModuleInterface, public Snapshot
{
protected:
	virtual ~BehaviorModule() { }
private:
	virtual MemoryPool *getObjectMemoryPool() { return 0; }
public:
	BehaviorModule( Thing *thing, const ModuleData *moduleData );
protected:
	virtual void crc(Xfer *xfer) { }
	virtual void xfer(Xfer *xfer) { }
	virtual void loadPostProcess(void) { }
};

// ??0BehaviorModule@@QAE@PAVThing@@PBVModuleData@@@Z
BehaviorModule::BehaviorModule( Thing *thing, const ModuleData *moduleData )
	: ObjectModule( thing, moduleData )
{
}
