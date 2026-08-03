// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: SubObjectsUpgrade::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class SubObjectsUpgradeModuleData
{
public:
	SubObjectsUpgradeModuleData();
	virtual ~SubObjectsUpgradeModuleData();

private:
	unsigned char m_pad[0xa8];
};

class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char SubObjectsUpgradeFieldParse;

class SubObjectsUpgrade
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@SubObjectsUpgrade@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *SubObjectsUpgrade::friend_newModuleData(INI *ini)
{
	SubObjectsUpgradeModuleData *data = new SubObjectsUpgradeModuleData;
	if (ini)
		ini->initFromINI(data, &SubObjectsUpgradeFieldParse);
	return (ModuleData *)data;
}
