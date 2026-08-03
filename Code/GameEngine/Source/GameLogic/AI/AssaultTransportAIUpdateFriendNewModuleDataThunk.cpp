// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: AssaultTransportAIUpdate::friend_newModuleData factory
// Retail: new; base construct; outer vtbl; trailing field inits; optional initFromINI.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class AssaultTransportAIUpdateModuleDataBaseShim
{
public:
	void construct();
};

class AssaultTransportAIUpdateModuleDataVtbl
{
public:
	AssaultTransportAIUpdateModuleDataVtbl() {}
	virtual void dummy();

private:
	unsigned char m_pad[0x68];
};

class __declspec(novtable) AssaultTransportAIUpdateModuleData
{
public:
	AssaultTransportAIUpdateModuleData();
	virtual void dummy();

private:
	unsigned char m_pad[0x68];
};

AssaultTransportAIUpdateModuleData::AssaultTransportAIUpdateModuleData()
{
	((AssaultTransportAIUpdateModuleDataBaseShim *)this)->construct();
	((AssaultTransportAIUpdateModuleDataVtbl *)this)->AssaultTransportAIUpdateModuleDataVtbl::AssaultTransportAIUpdateModuleDataVtbl();
	*(unsigned int *)((char *)this + 0x64) = 0;
	*(unsigned int *)((char *)this + 0x68) = 0x42480000;
}

class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char AssaultTransportAIUpdateFieldParse;

class AssaultTransportAIUpdate
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

ModuleData *AssaultTransportAIUpdate::friend_newModuleData(INI *ini)
{
	AssaultTransportAIUpdateModuleData *data = new AssaultTransportAIUpdateModuleData;
	if (ini)
		ini->initFromINI(data, &AssaultTransportAIUpdateFieldParse);
	return (ModuleData *)data;
}
