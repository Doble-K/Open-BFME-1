// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: HealContain::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class HealContainModuleData
{
public:
	HealContainModuleData();
	virtual ~HealContainModuleData();

private:
	unsigned char m_pad[0x20];
};

class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char HealContainFieldParse;

class HealContain
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@HealContain@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *HealContain::friend_newModuleData(INI *ini)
{
	HealContainModuleData *data = new HealContainModuleData;
	if (ini)
		ini->initFromINI(data, &HealContainFieldParse);
	return (ModuleData *)data;
}
