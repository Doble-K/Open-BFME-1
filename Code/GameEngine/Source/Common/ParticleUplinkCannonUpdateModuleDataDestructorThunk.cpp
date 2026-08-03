// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: ParticleUplinkCannonUpdateModuleData dtor.
// Members @+0x08/+0xa0/+0xac/+0xb0.

class ParticleUplinkCannonUpdateModuleDataMemberA
{
public:
	~ParticleUplinkCannonUpdateModuleDataMemberA();
private:
	unsigned char m_pad[4];
};

class ParticleUplinkCannonUpdateModuleDataMemberB
{
public:
	~ParticleUplinkCannonUpdateModuleDataMemberB();
private:
	unsigned char m_pad[4];
};

class Buffer
{
public:
	~Buffer();
private:
	unsigned char m_pad[4];
};

class ParticleUplinkCannonUpdateModuleDataBase
{
public:
	virtual ~ParticleUplinkCannonUpdateModuleDataBase() {}
private:
	unsigned char m_pad[4];
};

class __declspec(novtable) ParticleUplinkCannonUpdateModuleData
	: public ParticleUplinkCannonUpdateModuleDataBase
{
public:
	virtual ~ParticleUplinkCannonUpdateModuleData();
private:
	ParticleUplinkCannonUpdateModuleDataMemberA m_a;
	unsigned char m_gap1[0x94];
	ParticleUplinkCannonUpdateModuleDataMemberB m_b;
	unsigned char m_gap2[0x8];
	Buffer m_c;
	Buffer m_d;
};

// ??1ParticleUplinkCannonUpdateModuleData@@UAE@XZ
ParticleUplinkCannonUpdateModuleData::~ParticleUplinkCannonUpdateModuleData()
{
}
