// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: DefectorSpecialPower::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class DefectorSpecialPowerModuleData
{
public:
	DefectorSpecialPowerModuleData();
	virtual ~DefectorSpecialPowerModuleData();

private:
	unsigned char m_pad[0x210];
};

class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char DefectorSpecialPowerFieldParse;

class DefectorSpecialPower
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@DefectorSpecialPower@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *DefectorSpecialPower::friend_newModuleData(INI *ini)
{
	DefectorSpecialPowerModuleData *data = new DefectorSpecialPowerModuleData;
	if (ini)
		ini->initFromINI(data, &DefectorSpecialPowerFieldParse);
	return (ModuleData *)data;
}
