// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: StealthDetectorUpdateModuleData dtor.
// Buffer @+0x104, members @+0x84/+0x14.

class Buffer
{
public:
	~Buffer();
private:
	unsigned char m_pad[4];
};

class StealthDetectorUpdateModuleDataMemberA
{
public:
	~StealthDetectorUpdateModuleDataMemberA();
private:
	unsigned char m_pad[4];
};

class StealthDetectorUpdateModuleDataBase
{
public:
	virtual ~StealthDetectorUpdateModuleDataBase() {}
private:
	unsigned char m_pad[0x10];
};

class __declspec(novtable) StealthDetectorUpdateModuleData
	: public StealthDetectorUpdateModuleDataBase
{
public:
	virtual ~StealthDetectorUpdateModuleData();
private:
	StealthDetectorUpdateModuleDataMemberA m_a;
	unsigned char m_gap1[0x6c];
	StealthDetectorUpdateModuleDataMemberA m_b;
	unsigned char m_gap2[0x7c];
	Buffer m_c;
};

// ??1StealthDetectorUpdateModuleData@@UAE@XZ
StealthDetectorUpdateModuleData::~StealthDetectorUpdateModuleData()
{
}
