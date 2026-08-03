// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: TransportContainModuleData dtor. SEH Buffer @+0x174 then base.

class Buffer
{
public:
	~Buffer();
private:
	unsigned char m_pad[4];
};

class TransportContainModuleDataBase
{
public:
	virtual ~TransportContainModuleDataBase();
private:
	unsigned char m_pad[0x170];
};

class __declspec(novtable) TransportContainModuleData : public TransportContainModuleDataBase
{
public:
	virtual ~TransportContainModuleData();
private:
	Buffer m_buffer;
};

// ??1TransportContainModuleData@@UAE@XZ
TransportContainModuleData::~TransportContainModuleData()
{
}
