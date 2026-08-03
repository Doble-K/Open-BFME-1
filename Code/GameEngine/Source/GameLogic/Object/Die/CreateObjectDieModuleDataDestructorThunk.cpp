// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: CreateObjectDieModuleData dtor. PropagandaTower SEH pattern.

class Buffer
{
public:
	~Buffer();
};

class CreateObjectDieModuleDataBase
{
public:
	virtual ~CreateObjectDieModuleDataBase() {}
private:
	unsigned char m_pad[0x34];
};

class __declspec(novtable) CreateObjectDieModuleData : public CreateObjectDieModuleDataBase
{
public:
	virtual ~CreateObjectDieModuleData();
private:
	Buffer m_member;
};

// ??1CreateObjectDieModuleData@@UAE@XZ
CreateObjectDieModuleData::~CreateObjectDieModuleData()
{
}
