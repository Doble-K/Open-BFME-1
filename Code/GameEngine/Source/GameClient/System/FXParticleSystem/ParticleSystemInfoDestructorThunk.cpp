// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: FXParticleSystem::ParticleSystemInfo dtor. Buffers @+0x10/+0x68/+0x78.

class Buffer
{
public:
	~Buffer();
private:
	unsigned char m_pad[4];
};

namespace FXParticleSystem
{

class ParticleSystemInfoBase
{
public:
	virtual ~ParticleSystemInfoBase() {}
private:
	unsigned char m_pad[0xc];
};

class __declspec(novtable) ParticleSystemInfo : public ParticleSystemInfoBase
{
public:
	virtual ~ParticleSystemInfo();
private:
	Buffer m_a;
	unsigned char m_gap[0x54];
	Buffer m_b;
	unsigned char m_gap2[0xc];
	Buffer m_c;
};

// ??1ParticleSystemInfo@FXParticleSystem@@UAE@XZ
ParticleSystemInfo::~ParticleSystemInfo()
{
}

}
