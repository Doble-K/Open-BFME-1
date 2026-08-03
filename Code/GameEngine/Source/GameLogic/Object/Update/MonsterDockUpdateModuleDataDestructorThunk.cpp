// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: MonsterDockUpdateModuleData dtor.
// Retail 67B SEH: destroy Buffer @+0x10, base vtbl store. Buffer pin 0x1A401.

class Buffer
{
public:
	~Buffer();
};

class MonsterDockUpdateModuleDataBase
{
public:
	virtual ~MonsterDockUpdateModuleDataBase() {}

private:
	unsigned char m_pad[0xc];
};

class __declspec(novtable) MonsterDockUpdateModuleData
	: public MonsterDockUpdateModuleDataBase
{
public:
	virtual ~MonsterDockUpdateModuleData();

private:
	Buffer m_buffer;
};

// ??1MonsterDockUpdateModuleData@@UAE@XZ
MonsterDockUpdateModuleData::~MonsterDockUpdateModuleData()
{
}
