// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: RepairSpecialPower::friend_newModuleData factory

class INI;
class ModuleData;
void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);
class RepairSpecialPowerModuleData {
public:
	RepairSpecialPowerModuleData();
	virtual ~RepairSpecialPowerModuleData();
private:
	unsigned char m_pad[0x20C];
};
class INI { public: void initFromINI(void *what, const void *parseTable); };
extern "C" char RepairSpecialPowerFieldParse;
class RepairSpecialPower { public: static ModuleData *friend_newModuleData(INI *ini); };
ModuleData *RepairSpecialPower::friend_newModuleData(INI *ini) {
	RepairSpecialPowerModuleData *data = new RepairSpecialPowerModuleData;
	if (ini) ini->initFromINI(data, &RepairSpecialPowerFieldParse);
	return (ModuleData *)data;
}
