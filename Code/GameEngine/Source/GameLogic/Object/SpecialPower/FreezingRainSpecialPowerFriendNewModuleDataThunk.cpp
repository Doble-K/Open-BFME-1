// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: FreezingRainSpecialPower::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class FreezingRainSpecialPowerModuleData
{
public:
	FreezingRainSpecialPowerModuleData();
	virtual ~FreezingRainSpecialPowerModuleData();

private:
	unsigned char m_pad[0x214];
};

class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char FreezingRainSpecialPowerFieldParse;

class FreezingRainSpecialPower
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@FreezingRainSpecialPower@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *FreezingRainSpecialPower::friend_newModuleData(INI *ini)
{
	FreezingRainSpecialPowerModuleData *data = new FreezingRainSpecialPowerModuleData;
	if (ini)
		ini->initFromINI(data, &FreezingRainSpecialPowerFieldParse);
	return (ModuleData *)data;
}
