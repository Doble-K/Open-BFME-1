// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: LevelGrantSpecialPower::friend_newModuleInstance factory.

class Module;
class Thing;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class LevelGrantSpecialPower
{
public:
	LevelGrantSpecialPower(Thing *, const ModuleData *);
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);

private:
	unsigned char m_pad[0xe8];
};

// ?friend_newModuleInstance@LevelGrantSpecialPower@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *LevelGrantSpecialPower::friend_newModuleInstance(Thing *thing, const ModuleData *data)
{
	return (Module *)new LevelGrantSpecialPower(thing, data);
}
