// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: KeepObjectDie::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class KeepObjectDieModuleData
{
public:
	KeepObjectDieModuleData();
	virtual ~KeepObjectDieModuleData();

private:
	unsigned char m_pad[0x30];
};

class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char KeepObjectDieFieldParse;

class KeepObjectDie
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@KeepObjectDie@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *KeepObjectDie::friend_newModuleData(INI *ini)
{
	KeepObjectDieModuleData *data = new KeepObjectDieModuleData;
	if (ini)
		ini->initFromINI(data, &KeepObjectDieFieldParse);
	return (ModuleData *)data;
}
