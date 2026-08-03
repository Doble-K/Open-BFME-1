// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: ToggleHiddenSpecialAbilityUpdate::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class ToggleHiddenSpecialAbilityUpdateModuleData
{
public:
	ToggleHiddenSpecialAbilityUpdateModuleData();
	virtual ~ToggleHiddenSpecialAbilityUpdateModuleData();

private:
	unsigned char m_pad[0x250];
};

class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char ToggleHiddenSpecialAbilityUpdateFieldParse;

class ToggleHiddenSpecialAbilityUpdate
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@ToggleHiddenSpecialAbilityUpdate@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *ToggleHiddenSpecialAbilityUpdate::friend_newModuleData(INI *ini)
{
	ToggleHiddenSpecialAbilityUpdateModuleData *data = new ToggleHiddenSpecialAbilityUpdateModuleData;
	if (ini)
		ini->initFromINI(data, &ToggleHiddenSpecialAbilityUpdateFieldParse);
	return (ModuleData *)data;
}
