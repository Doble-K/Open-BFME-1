// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: SlaveWatcherBehaviorModuleData dtor.
// Retail 80B SEH: destroy Buffer @+0xc then @+0x8, base vtbl store. Buffer pin 0x887940.

class Buffer
{
public:
	~Buffer();

private:
	unsigned char m_pad[4];
};

class SlaveWatcherBehaviorModuleDataBase
{
public:
	virtual ~SlaveWatcherBehaviorModuleDataBase() {}

private:
	unsigned char m_pad[0x4];
};

class __declspec(novtable) SlaveWatcherBehaviorModuleData
	: public SlaveWatcherBehaviorModuleDataBase
{
public:
	virtual ~SlaveWatcherBehaviorModuleData();

private:
	Buffer m_a;
	Buffer m_b;
};

// ??1SlaveWatcherBehaviorModuleData@@UAE@XZ
SlaveWatcherBehaviorModuleData::~SlaveWatcherBehaviorModuleData()
{
}
