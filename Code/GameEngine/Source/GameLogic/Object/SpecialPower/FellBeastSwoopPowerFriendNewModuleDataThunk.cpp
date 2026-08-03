// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: FellBeastSwoopPower::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class FellBeastSwoopPowerModuleData
{
public:
	FellBeastSwoopPowerModuleData();
	virtual ~FellBeastSwoopPowerModuleData();

private:
	unsigned char m_pad[0x258];
};

class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char FellBeastSwoopPowerFieldParse;

class FellBeastSwoopPower
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@FellBeastSwoopPower@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *FellBeastSwoopPower::friend_newModuleData(INI *ini)
{
	FellBeastSwoopPowerModuleData *data = new FellBeastSwoopPowerModuleData;
	if (ini)
		ini->initFromINI(data, &FellBeastSwoopPowerFieldParse);
	return (ModuleData *)data;
}
