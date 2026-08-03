// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: ContestableContain::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class ContestableContainModuleData
{
public:
	ContestableContainModuleData();
	virtual ~ContestableContainModuleData();

private:
	unsigned char m_pad[0x1a4];
};

class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char ContestableContainFieldParse;

class ContestableContain
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@ContestableContain@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *ContestableContain::friend_newModuleData(INI *ini)
{
	ContestableContainModuleData *data = new ContestableContainModuleData;
	if (ini)
		ini->initFromINI(data, &ContestableContainFieldParse);
	return (ModuleData *)data;
}
