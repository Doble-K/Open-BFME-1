// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: ElvenWoodSpecialPower::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class ElvenWoodSpecialPowerModuleData
{
public:
	ElvenWoodSpecialPowerModuleData();
	virtual ~ElvenWoodSpecialPowerModuleData();

private:
	unsigned char m_pad[0x22c];
};

class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char ElvenWoodSpecialPowerFieldParse;

class ElvenWoodSpecialPower
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@ElvenWoodSpecialPower@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *ElvenWoodSpecialPower::friend_newModuleData(INI *ini)
{
	ElvenWoodSpecialPowerModuleData *data = new ElvenWoodSpecialPowerModuleData;
	if (ini)
		ini->initFromINI(data, &ElvenWoodSpecialPowerFieldParse);
	return (ModuleData *)data;
}
