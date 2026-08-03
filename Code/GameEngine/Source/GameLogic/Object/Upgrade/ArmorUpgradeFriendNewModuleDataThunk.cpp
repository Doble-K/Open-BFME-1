// cl: /DNDEBUG /MD /GX- /O2 /Ob2

// Open-BFME5: ArmorUpgrade::friend_newModuleData
// Retail: new(0x78); sub-ctor at +8; outer vtbl;
// byte +0x70/+0x71 = 0; dword +0x74 = 3.

class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class UpgradeModuleDataSub
{
public:
	UpgradeModuleDataSub();

private:
	char opaque[0x68];
};

class ArmorUpgradeModuleData
{
public:
	ArmorUpgradeModuleData()
	{
		m_b70 = 0;
		m_b71 = 0;
		m_val74 = 3;
	}
	virtual void dummy();

private:
	int m_pad;
	char m_sub_space[0x68];
	unsigned char m_b70;
	unsigned char m_b71;
	unsigned char m_pad72[2];
	unsigned int m_val74;
};

class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char ArmorUpgradeFieldParse;

class ArmorUpgrade
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@ArmorUpgrade@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *ArmorUpgrade::friend_newModuleData(INI *ini)
{
	ArmorUpgradeModuleData *data =
		(ArmorUpgradeModuleData *)operator new(0x78);
	if (data)
	{
		UpgradeModuleDataSub *sub =
			(UpgradeModuleDataSub *)((char *)data + 8);
		sub->UpgradeModuleDataSub::UpgradeModuleDataSub();
		data->ArmorUpgradeModuleData::ArmorUpgradeModuleData();
	}
	else
		data = 0;
	if (ini)
		ini->initFromINI(data, &ArmorUpgradeFieldParse);
	return (ModuleData *)data;
}
