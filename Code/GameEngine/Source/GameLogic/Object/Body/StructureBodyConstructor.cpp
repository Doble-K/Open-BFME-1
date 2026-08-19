// cl: /DNDEBUG /MD /EHsc

class Thing;
class ModuleData;

class BehaviorModule
{
public:
	virtual void behaviorModuleAnchor();

private:
	unsigned char m_data[8];
};

class BodyModuleInterface
{
public:
	virtual void bodyModuleInterfaceAnchor();
};

class ModuleInterface
{
public:
	virtual void moduleInterfaceAnchor();
};

class BodyModule : public BehaviorModule,
	public BodyModuleInterface,
	public ModuleInterface
{
public:
	BodyModule( Thing *thing, const ModuleData *moduleData );

private:
	// The three module bases reach +0x14; StructureBody's own first member is
	// at +0xE0, so this is what sits between. Only its size is claimed.
	unsigned char m_unmodelled_14[ 0xE0 - 0x14 ];
};

class StructureBody : public BodyModule
{
public:
	StructureBody( Thing *thing, const ModuleData *moduleData );

private:
	int m_unmodelled_E0;			// +0xE0, zeroed by the constructor
};

StructureBody::StructureBody( Thing *thing, const ModuleData *moduleData )
	: BodyModule( thing, moduleData ), m_unmodelled_E0( 0 )
{
}
