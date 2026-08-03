// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: AutoDepositUpdateModuleData dtor.
// Retail 67B SEH: destroy Buffer @+0x1c, base vtbl store. Buffer pin 0x1A401.

class Buffer
{
public:
	~Buffer();
};

class AutoDepositUpdateModuleDataBase
{
public:
	virtual ~AutoDepositUpdateModuleDataBase() {}

private:
	unsigned char m_pad[0x18];
};

class __declspec(novtable) AutoDepositUpdateModuleData
	: public AutoDepositUpdateModuleDataBase
{
public:
	virtual ~AutoDepositUpdateModuleData();

private:
	Buffer m_buffer;
};

// ??1AutoDepositUpdateModuleData@@UAE@XZ
AutoDepositUpdateModuleData::~AutoDepositUpdateModuleData()
{
}
