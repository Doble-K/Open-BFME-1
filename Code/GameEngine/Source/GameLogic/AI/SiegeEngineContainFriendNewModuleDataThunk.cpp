// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: SiegeEngineContain::friend_newModuleData factory

class INI;
class ModuleData;
void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);
class SiegeEngineContainModuleData {
public:
SiegeEngineContainModuleData();
virtual ~SiegeEngineContainModuleData();
private:
unsigned char m_pad[0x220];
};
class INI { public: void initFromINI(void *what, const void *parseTable); };
extern "C" char SiegeEngineContainFieldParse;
class SiegeEngineContain { public: static ModuleData *friend_newModuleData(INI *ini); };
// ?friend_newModuleData@SiegeEngineContain@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *SiegeEngineContain::friend_newModuleData(INI *ini) {
SiegeEngineContainModuleData *data = new SiegeEngineContainModuleData;
if (ini) ini->initFromINI(data, &SiegeEngineContainFieldParse);
return (ModuleData *)data;
}
