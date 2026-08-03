// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: ConvertToCarBombCrateCollideModuleData dtor. SEH Buffer member pin body 0x887940.

class Buffer
{
public:
	~Buffer();
};

class ConvertToCarBombCrateCollideModuleDataBase
{
public:
	virtual ~ConvertToCarBombCrateCollideModuleDataBase() {}
private:
	unsigned char m_pad[0x40];
};

class __declspec(novtable) ConvertToCarBombCrateCollideModuleData : public ConvertToCarBombCrateCollideModuleDataBase
{
public:
	virtual ~ConvertToCarBombCrateCollideModuleData();
private:
	Buffer m_buffer;
};

// ??1ConvertToCarBombCrateCollideModuleData@@UAE@XZ
ConvertToCarBombCrateCollideModuleData::~ConvertToCarBombCrateCollideModuleData()
{
}
