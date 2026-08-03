// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: SpecialEnemySenseUpdateModuleData dtor.
// Retail 67B SEH: destroy Buffer @+0x8, base vtbl store. Buffer pin 0x1A401.

class Buffer
{
public:
	~Buffer();
};

class SpecialEnemySenseUpdateModuleDataBase
{
public:
	virtual ~SpecialEnemySenseUpdateModuleDataBase() {}

private:
	unsigned char m_pad[0x4];
};

class __declspec(novtable) SpecialEnemySenseUpdateModuleData
	: public SpecialEnemySenseUpdateModuleDataBase
{
public:
	virtual ~SpecialEnemySenseUpdateModuleData();

private:
	Buffer m_buffer;
};

// ??1SpecialEnemySenseUpdateModuleData@@UAE@XZ
SpecialEnemySenseUpdateModuleData::~SpecialEnemySenseUpdateModuleData()
{
}
