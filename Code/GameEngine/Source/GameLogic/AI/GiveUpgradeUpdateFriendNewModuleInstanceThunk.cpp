// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: GiveUpgradeUpdate::friend_newModuleInstance factory.

class Module;
class Thing;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class GiveUpgradeUpdate
{
public:
	GiveUpgradeUpdate(Thing *, const ModuleData *);
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);

private:
	unsigned char m_pad[0xf0];
};

// ?friend_newModuleInstance@GiveUpgradeUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *GiveUpgradeUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *data)
{
	return (Module *)new GiveUpgradeUpdate(thing, data);
}
