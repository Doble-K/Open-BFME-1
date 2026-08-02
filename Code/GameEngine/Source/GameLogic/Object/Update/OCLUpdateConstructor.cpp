// cl: /DNDEBUG /MD /EHsc

class Thing;
class ModuleData;

class ObjectModule
{
public:
	virtual void objectModuleAnchor();
	ObjectModule( Thing *, const ModuleData * );

private:
	unsigned char m_data[8];
};

class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor();
};

class UpdateModuleInterface
{
public:
	virtual void updateModuleInterfaceAnchor();
};

class UpdateModule : public ObjectModule,
	public BehaviorModuleInterface,
	public UpdateModuleInterface
{
public:
	UpdateModule( Thing *thing, const ModuleData *moduleData )
		: ObjectModule( thing, moduleData ),
		  m_nextCallFrameAndPhase( 0 ),
		  m_indexInLogic( -1 ),
		  m_oclIndex( -1 ),
		  m_delay( 0 ),
		  m_count( 0 )
	{
	}

private:
	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_oclIndex;
	unsigned int m_delay;
	unsigned int m_count;
};

class OCLUpdate : public UpdateModule
{
public:
	OCLUpdate( Thing *, const ModuleData * );
};

OCLUpdate::OCLUpdate( Thing *thing, const ModuleData *moduleData )
	: UpdateModule( thing, moduleData )
{
}
