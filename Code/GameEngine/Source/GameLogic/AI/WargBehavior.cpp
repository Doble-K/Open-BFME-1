// cl: /DNDEBUG /MD /EHsc

class Thing;
class ModuleData;

class ObjectModule
{
public:
	virtual void objectModuleAnchor();
	ObjectModule( Thing *thing, const ModuleData *moduleData );

private:
	unsigned char m_data[8];
};

class ModuleInterface
{
public:
	virtual void moduleInterfaceAnchor();
};

class WargBehavior : public ObjectModule, public ModuleInterface
{
public:
	WargBehavior( Thing *thing, const ModuleData *moduleData );
};

WargBehavior::WargBehavior( Thing *thing, const ModuleData *moduleData )
	: ObjectModule( thing, moduleData )
{
}
