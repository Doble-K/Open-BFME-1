// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: StructureBody::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class StructureBodyModuleData
{
public:
	StructureBodyModuleData();
	virtual ~StructureBodyModuleData();

private:
	unsigned char m_pad[0x58];
};

class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char StructureBodyFieldParse;

class StructureBody
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@StructureBody@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *StructureBody::friend_newModuleData(INI *ini)
{
	StructureBodyModuleData *data = new StructureBodyModuleData;
	if (ini)
		ini->initFromINI(data, &StructureBodyFieldParse);
	return (ModuleData *)data;
}
