// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: ShareExperienceBehaviorModuleData dtor.
// Retail 67B SEH: destroy Buffer @+0x14, base vtbl store. Buffer pin 0x1A401.

class Buffer
{
public:
	~Buffer();
};

class ShareExperienceBehaviorModuleDataBase
{
public:
	virtual ~ShareExperienceBehaviorModuleDataBase() {}

private:
	unsigned char m_pad[0x10];
};

class __declspec(novtable) ShareExperienceBehaviorModuleData
	: public ShareExperienceBehaviorModuleDataBase
{
public:
	virtual ~ShareExperienceBehaviorModuleData();

private:
	Buffer m_buffer;
};

// ??1ShareExperienceBehaviorModuleData@@UAE@XZ
ShareExperienceBehaviorModuleData::~ShareExperienceBehaviorModuleData()
{
}
