// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: ToppleUpdateModuleData dtor. SEH Buffer member pin body 0x887940.

class Buffer
{
public:
	~Buffer();
};

class ToppleUpdateModuleDataBase
{
public:
	virtual ~ToppleUpdateModuleDataBase() {}
private:
	unsigned char m_pad[0xc];
};

class __declspec(novtable) ToppleUpdateModuleData : public ToppleUpdateModuleDataBase
{
public:
	virtual ~ToppleUpdateModuleData();
private:
	Buffer m_buffer;
};

// ??1ToppleUpdateModuleData@@UAE@XZ
ToppleUpdateModuleData::~ToppleUpdateModuleData()
{
}
