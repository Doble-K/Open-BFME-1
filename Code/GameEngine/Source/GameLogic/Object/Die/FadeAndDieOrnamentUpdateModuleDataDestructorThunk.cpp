// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: FadeAndDieOrnamentUpdateModuleData dtor. SEH Buffer member pin body 0x887940.

class Buffer
{
public:
	~Buffer();
};

class FadeAndDieOrnamentUpdateModuleDataBase
{
public:
	virtual ~FadeAndDieOrnamentUpdateModuleDataBase() {}
private:
	unsigned char m_pad[0x4];
};

class __declspec(novtable) FadeAndDieOrnamentUpdateModuleData : public FadeAndDieOrnamentUpdateModuleDataBase
{
public:
	virtual ~FadeAndDieOrnamentUpdateModuleData();
private:
	Buffer m_buffer;
};

// ??1FadeAndDieOrnamentUpdateModuleData@@UAE@XZ
FadeAndDieOrnamentUpdateModuleData::~FadeAndDieOrnamentUpdateModuleData()
{
}
