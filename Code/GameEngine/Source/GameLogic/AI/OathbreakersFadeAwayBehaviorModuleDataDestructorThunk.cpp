// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: OathbreakersFadeAwayBehaviorModuleData dtor.
// Retail 80B SEH: destroy Buffer @+0xc then @+0x8, base vtbl store. Buffer pin 0x887940.

class Buffer
{
public:
	~Buffer();

private:
	unsigned char m_pad[4];
};

class OathbreakersFadeAwayBehaviorModuleDataBase
{
public:
	virtual ~OathbreakersFadeAwayBehaviorModuleDataBase() {}

private:
	unsigned char m_pad[0x4];
};

class __declspec(novtable) OathbreakersFadeAwayBehaviorModuleData
	: public OathbreakersFadeAwayBehaviorModuleDataBase
{
public:
	virtual ~OathbreakersFadeAwayBehaviorModuleData();

private:
	Buffer m_a;
	Buffer m_b;
};

// ??1OathbreakersFadeAwayBehaviorModuleData@@UAE@XZ
OathbreakersFadeAwayBehaviorModuleData::~OathbreakersFadeAwayBehaviorModuleData()
{
}
