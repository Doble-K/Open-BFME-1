// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: SpecialDisguiseUpdateModuleData dtor. 2x Buffer then base.

class Buffer
{
public:
	~Buffer();
private:
	unsigned char m_pad[4];
};

class SpecialDisguiseUpdateModuleDataBase
{
public:
	virtual ~SpecialDisguiseUpdateModuleDataBase();
private:
	unsigned char m_pad[0x258];
};

class __declspec(novtable) SpecialDisguiseUpdateModuleData : public SpecialDisguiseUpdateModuleDataBase
{
public:
	virtual ~SpecialDisguiseUpdateModuleData();
private:
	Buffer m_0;
	Buffer m_1;
};

// ??1SpecialDisguiseUpdateModuleData@@UAE@XZ
SpecialDisguiseUpdateModuleData::~SpecialDisguiseUpdateModuleData()
{
}
