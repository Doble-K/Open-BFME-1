// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: SplitHordeSpecialPower::friend_newModuleData factory

class INI;
class ModuleData;
void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);
class SplitHordeSpecialPowerModuleData {
public:
	SplitHordeSpecialPowerModuleData();
	virtual ~SplitHordeSpecialPowerModuleData();
private:
	unsigned char m_pad[0x20C];
};
class INI { public: void initFromINI(void *what, const void *parseTable); };
extern "C" char SplitHordeSpecialPowerFieldParse;
class SplitHordeSpecialPower { public: static ModuleData *friend_newModuleData(INI *ini); };
ModuleData *SplitHordeSpecialPower::friend_newModuleData(INI *ini) {
	SplitHordeSpecialPowerModuleData *data = new SplitHordeSpecialPowerModuleData;
	if (ini) ini->initFromINI(data, &SplitHordeSpecialPowerFieldParse);
	return (ModuleData *)data;
}
