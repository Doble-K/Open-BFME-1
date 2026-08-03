// cl: /DNDEBUG /MD /GX- /O2 /Ob2

// Open-BFME5: GiveUpgradeUpdateModuleData ctor
// Base call, vtbl, zeros +0x254..+0x268, float +0x26c=0.025, byte +0x270=0.

class GiveUpgradeUpdateModuleDataBase
{
public:
	GiveUpgradeUpdateModuleDataBase();
	virtual void giveUpgradeModuleDataBaseAnchor();

private:
	unsigned char m_pad[0x250];
};

extern "C" char GiveUpgradeUpdateModuleData_vtbl;

class __declspec(novtable) GiveUpgradeUpdateModuleData
	: public GiveUpgradeUpdateModuleDataBase
{
public:
	GiveUpgradeUpdateModuleData();

private:
	unsigned int m_254;
	unsigned int m_258;
	unsigned int m_25c;
	unsigned int m_260;
	unsigned int m_264;
	unsigned int m_268;
	unsigned int m_26c;
	unsigned char m_270;
};

// ??0GiveUpgradeUpdateModuleData@@QAE@XZ
GiveUpgradeUpdateModuleData::GiveUpgradeUpdateModuleData()
{
	*reinterpret_cast<char *volatile *>(this) =
		&GiveUpgradeUpdateModuleData_vtbl;
	*reinterpret_cast<unsigned int volatile *>(&m_254) = 0;
	*reinterpret_cast<unsigned int volatile *>(&m_258) = 0;
	*reinterpret_cast<unsigned int volatile *>(&m_25c) = 0;
	*reinterpret_cast<unsigned int volatile *>(&m_260) = 0;
	*reinterpret_cast<unsigned int volatile *>(&m_264) = 0;
	*reinterpret_cast<unsigned int volatile *>(&m_268) = 0;
	*reinterpret_cast<unsigned char volatile *>(&m_270) = 0;
	*reinterpret_cast<unsigned int volatile *>(&m_26c) = 0x3CCCCCCDu; // ~0.025f
}
