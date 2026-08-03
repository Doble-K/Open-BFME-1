// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: ManTheWallsSpecialPower::friend_newModuleData factory

class INI;
class ModuleData;
void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);
class ManTheWallsSpecialPowerModuleData {
public:
	ManTheWallsSpecialPowerModuleData();
	virtual ~ManTheWallsSpecialPowerModuleData();
private:
	unsigned char m_pad[0x20C];
};
class INI { public: void initFromINI(void *what, const void *parseTable); };
extern "C" char ManTheWallsSpecialPowerFieldParse;
class ManTheWallsSpecialPower { public: static ModuleData *friend_newModuleData(INI *ini); };
ModuleData *ManTheWallsSpecialPower::friend_newModuleData(INI *ini) {
	ManTheWallsSpecialPowerModuleData *data = new ManTheWallsSpecialPowerModuleData;
	if (ini) ini->initFromINI(data, &ManTheWallsSpecialPowerFieldParse);
	return (ModuleData *)data;
}
