// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: SpecialDisguiseUpdate::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class SpecialDisguiseUpdateModuleData
{
public:
	SpecialDisguiseUpdateModuleData();
	virtual ~SpecialDisguiseUpdateModuleData();

private:
	unsigned char m_pad[0x268];
};

class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char SpecialDisguiseUpdateFieldParse;

class SpecialDisguiseUpdate
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@SpecialDisguiseUpdate@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *SpecialDisguiseUpdate::friend_newModuleData(INI *ini)
{
	SpecialDisguiseUpdateModuleData *data = new SpecialDisguiseUpdateModuleData;
	if (ini)
		ini->initFromINI(data, &SpecialDisguiseUpdateFieldParse);
	return (ModuleData *)data;
}
