// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: ObjectCreationUpgradeModuleData dtor.
// Member @+0x10, triple Buffer @+0x78/+0x7c/+0x80.

class ObjectCreationUpgradeModuleDataMemberA
{
public:
	~ObjectCreationUpgradeModuleDataMemberA();
private:
	unsigned char m_pad[0x68];
};

class Buffer
{
public:
	~Buffer();
private:
	unsigned char m_pad[4];
};

class ObjectCreationUpgradeModuleDataBase
{
public:
	virtual ~ObjectCreationUpgradeModuleDataBase() {}
private:
	unsigned char m_pad[0xc];
};

class __declspec(novtable) ObjectCreationUpgradeModuleData
	: public ObjectCreationUpgradeModuleDataBase
{
public:
	virtual ~ObjectCreationUpgradeModuleData();
private:
	ObjectCreationUpgradeModuleDataMemberA m_a;
	Buffer m_b;
	Buffer m_c;
	Buffer m_d;
};

// ??1ObjectCreationUpgradeModuleData@@UAE@XZ
ObjectCreationUpgradeModuleData::~ObjectCreationUpgradeModuleData()
{
}
