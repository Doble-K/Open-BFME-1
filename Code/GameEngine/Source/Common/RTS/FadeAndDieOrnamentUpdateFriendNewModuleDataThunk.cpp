// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: FadeAndDieOrnamentUpdate::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class FadeAndDieOrnamentUpdateModuleData
{
public:
	FadeAndDieOrnamentUpdateModuleData();
	virtual ~FadeAndDieOrnamentUpdateModuleData();

private:
	unsigned char m_pad[0x34];
};

class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char FadeAndDieOrnamentUpdateFieldParse;

class FadeAndDieOrnamentUpdate
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@FadeAndDieOrnamentUpdate@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *FadeAndDieOrnamentUpdate::friend_newModuleData(INI *ini)
{
	FadeAndDieOrnamentUpdateModuleData *data = new FadeAndDieOrnamentUpdateModuleData;
	if (ini)
		ini->initFromINI(data, &FadeAndDieOrnamentUpdateFieldParse);
	return (ModuleData *)data;
}
