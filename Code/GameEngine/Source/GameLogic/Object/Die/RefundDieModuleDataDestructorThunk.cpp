// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: RefundDieModuleData dtor.
// Retail 67B SEH: destroy Buffer @+0x3c, base vtbl store. Buffer pin 0x1A401.

class Buffer
{
public:
	~Buffer();
};

class RefundDieModuleDataBase
{
public:
	virtual ~RefundDieModuleDataBase() {}

private:
	unsigned char m_pad[0x38];
};

class __declspec(novtable) RefundDieModuleData
	: public RefundDieModuleDataBase
{
public:
	virtual ~RefundDieModuleData();

private:
	Buffer m_buffer;
};

// ??1RefundDieModuleData@@UAE@XZ
RefundDieModuleData::~RefundDieModuleData()
{
}
