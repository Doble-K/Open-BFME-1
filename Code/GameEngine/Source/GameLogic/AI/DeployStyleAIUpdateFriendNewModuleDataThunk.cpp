// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: DeployStyleAIUpdate::friend_newModuleData factory

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class DeployStyleAIUpdateModuleDataBaseShim
{
public:
	void construct();
};

class DeployStyleAIUpdateModuleDataVtbl
{
public:
	DeployStyleAIUpdateModuleDataVtbl() {}
	virtual void dummy();

private:
	unsigned char m_pad[0x6C];
};

class __declspec(novtable) DeployStyleAIUpdateModuleData
{
public:
	DeployStyleAIUpdateModuleData();
	virtual void dummy();

private:
	unsigned char m_pad[0x6C];
};

DeployStyleAIUpdateModuleData::DeployStyleAIUpdateModuleData()
{
	((DeployStyleAIUpdateModuleDataBaseShim *)this)->construct();
	((DeployStyleAIUpdateModuleDataVtbl *)this)->DeployStyleAIUpdateModuleDataVtbl::DeployStyleAIUpdateModuleDataVtbl();
	*(unsigned int *)((char *)this + 0x64) = 0;
	*(unsigned int *)((char *)this + 0x68) = 0;
	*((unsigned char *)this + 0x6C) = 0;
	*((unsigned char *)this + 0x6D) = 0;
	*((unsigned char *)this + 0x6E) = 0;
}

class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char DeployStyleAIUpdateFieldParse;

class DeployStyleAIUpdate
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

ModuleData *DeployStyleAIUpdate::friend_newModuleData(INI *ini)
{
	DeployStyleAIUpdateModuleData *data = new DeployStyleAIUpdateModuleData;
	if (ini)
		ini->initFromINI(data, &DeployStyleAIUpdateFieldParse);
	return (ModuleData *)data;
}
