// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: TunnelContainModuleData dtor.

class TunnelContainModuleDataMemberA
{
public:
	~TunnelContainModuleDataMemberA();
private:
	unsigned char m_pad[0x8];
};

class TunnelContainModuleDataMemberB
{
public:
	~TunnelContainModuleDataMemberB();
private:
	unsigned char m_pad[4];
};

class TunnelContainModuleDataBase
{
public:
	virtual ~TunnelContainModuleDataBase();
private:
	unsigned char m_pad[0x220];
};

class __declspec(novtable) TunnelContainModuleData : public TunnelContainModuleDataBase
{
public:
	virtual ~TunnelContainModuleData();
private:
	TunnelContainModuleDataMemberA m_a;
	TunnelContainModuleDataMemberB m_b;
};

// ??1TunnelContainModuleData@@UAE@XZ
TunnelContainModuleData::~TunnelContainModuleData()
{
}
