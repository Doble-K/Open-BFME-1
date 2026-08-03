// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: UpgradeDieModuleData dtor. PropagandaTower SEH pattern.

class Buffer
{
public:
	~Buffer();
};

class UpgradeDieModuleDataBase
{
public:
	virtual ~UpgradeDieModuleDataBase() {}
private:
	unsigned char m_pad[0x30];
};

class __declspec(novtable) UpgradeDieModuleData : public UpgradeDieModuleDataBase
{
public:
	virtual ~UpgradeDieModuleData();
private:
	Buffer m_member;
};

// ??1UpgradeDieModuleData@@UAE@XZ
UpgradeDieModuleData::~UpgradeDieModuleData()
{
}
