// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: HordeGarrisonContain::friend_newModuleData factory

class INI;
class ModuleData;
void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);
class HordeGarrisonContainModuleData {
public:
	HordeGarrisonContainModuleData();
	virtual ~HordeGarrisonContainModuleData();
private:
	unsigned char m_pad[0x220];
};
class INI { public: void initFromINI(void *what, const void *parseTable); };
extern "C" char HordeGarrisonContainFieldParse;
class HordeGarrisonContain { public: static ModuleData *friend_newModuleData(INI *ini); };
ModuleData *HordeGarrisonContain::friend_newModuleData(INI *ini) {
	HordeGarrisonContainModuleData *data = new HordeGarrisonContainModuleData;
	if (ini) ini->initFromINI(data, &HordeGarrisonContainFieldParse);
	return (ModuleData *)data;
}
