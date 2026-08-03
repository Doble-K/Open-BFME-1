// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: UpgradeSoundSelectorClientBehavior::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class UpgradeSoundSelectorClientBehaviorModuleData
{
public:
	UpgradeSoundSelectorClientBehaviorModuleData();
	virtual ~UpgradeSoundSelectorClientBehaviorModuleData();

private:
	unsigned char m_pad[0x10];
};

class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char UpgradeSoundSelectorClientBehaviorFieldParse;

class UpgradeSoundSelectorClientBehavior
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@UpgradeSoundSelectorClientBehavior@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *UpgradeSoundSelectorClientBehavior::friend_newModuleData(INI *ini)
{
	UpgradeSoundSelectorClientBehaviorModuleData *data = new UpgradeSoundSelectorClientBehaviorModuleData;
	if (ini)
		ini->initFromINI(data, &UpgradeSoundSelectorClientBehaviorFieldParse);
	return (ModuleData *)data;
}
