// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: SpawnBehavior::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class SpawnBehaviorModuleData
{
public:
	SpawnBehaviorModuleData();
	virtual ~SpawnBehaviorModuleData();

private:
	unsigned char m_pad[0xbc];
};

class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char SpawnBehaviorFieldParse;

class SpawnBehavior
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@SpawnBehavior@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *SpawnBehavior::friend_newModuleData(INI *ini)
{
	SpawnBehaviorModuleData *data = new SpawnBehaviorModuleData;
	if (ini)
		ini->initFromINI(data, &SpawnBehaviorFieldParse);
	return (ModuleData *)data;
}
