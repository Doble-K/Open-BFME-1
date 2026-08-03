// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: PlayerHealSpecialPower::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class PlayerHealSpecialPowerModuleData
{
public:
	PlayerHealSpecialPowerModuleData();
	virtual ~PlayerHealSpecialPowerModuleData();

private:
	unsigned char m_pad[0x234];
};

class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char PlayerHealSpecialPowerFieldParse;

class PlayerHealSpecialPower
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@PlayerHealSpecialPower@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *PlayerHealSpecialPower::friend_newModuleData(INI *ini)
{
	PlayerHealSpecialPowerModuleData *data = new PlayerHealSpecialPowerModuleData;
	if (ini)
		ini->initFromINI(data, &PlayerHealSpecialPowerFieldParse);
	return (ModuleData *)data;
}
