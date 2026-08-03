// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: SpawnUnitBehavior::friend_newModuleInstance factory.

class Module;
class Thing;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class SpawnUnitBehavior
{
public:
	SpawnUnitBehavior(Thing *, const ModuleData *);
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);

private:
	unsigned char m_pad[0x28];
};

// ?friend_newModuleInstance@SpawnUnitBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *SpawnUnitBehavior::friend_newModuleInstance(Thing *thing, const ModuleData *data)
{
	return (Module *)new SpawnUnitBehavior(thing, data);
}
