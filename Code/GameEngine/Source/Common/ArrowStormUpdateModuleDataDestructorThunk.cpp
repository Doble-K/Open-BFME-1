// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: ArrowStormUpdateModuleData dtor. SEH Buffer @+0x254 then base.

class Buffer
{
public:
	~Buffer();
private:
	unsigned char m_pad[4];
};

class ArrowStormUpdateModuleDataBase
{
public:
	virtual ~ArrowStormUpdateModuleDataBase();
private:
	unsigned char m_pad[0x250];
};

class __declspec(novtable) ArrowStormUpdateModuleData : public ArrowStormUpdateModuleDataBase
{
public:
	virtual ~ArrowStormUpdateModuleData();
private:
	Buffer m_buffer;
};

// ??1ArrowStormUpdateModuleData@@UAE@XZ
ArrowStormUpdateModuleData::~ArrowStormUpdateModuleData()
{
}
