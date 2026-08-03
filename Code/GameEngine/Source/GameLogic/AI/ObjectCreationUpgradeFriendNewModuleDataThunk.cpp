// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: ObjectCreationUpgrade::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class ObjectCreationUpgradeModuleData
{
public:
	ObjectCreationUpgradeModuleData();
	virtual ~ObjectCreationUpgradeModuleData();

private:
	unsigned char m_pad[0xa0];
};

class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char ObjectCreationUpgradeFieldParse;

class ObjectCreationUpgrade
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@ObjectCreationUpgrade@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *ObjectCreationUpgrade::friend_newModuleData(INI *ini)
{
	ObjectCreationUpgradeModuleData *data = new ObjectCreationUpgradeModuleData;
	if (ini)
		ini->initFromINI(data, &ObjectCreationUpgradeFieldParse);
	return (ModuleData *)data;
}
