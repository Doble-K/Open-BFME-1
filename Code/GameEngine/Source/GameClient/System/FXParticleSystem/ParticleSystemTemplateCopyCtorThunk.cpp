// cl: /DNDEBUG /MD /EHsc

class AsciiString;

class AsciiStringCopyCtorShim
{
public:
	void construct(const AsciiString *other);
};

class AsciiString
{
public:
	AsciiString(const AsciiString &other)
	{
		const AsciiString *source = &other;
		((AsciiStringCopyCtorShim *)this)->construct(source);
	}
	~AsciiString();

private:
	char *m_data;
};

namespace FXParticleSystem
{

class ParticleSystemInfo
{
public:
	ParticleSystemInfo(const ParticleSystemInfo &other);
	virtual ~ParticleSystemInfo();

private:
	unsigned char m_pad[0x94];
};

class ParticleSystemTemplateTail
{
public:
	ParticleSystemTemplateTail(const ParticleSystemTemplateTail &other);
};

class ParticleSystemTemplate : public ParticleSystemInfo
{
public:
	ParticleSystemTemplate(const ParticleSystemTemplate &other);

private:
	AsciiString m_name;
	int m_slaveTemplate;
	ParticleSystemTemplateTail m_tail;
};

ParticleSystemTemplate::ParticleSystemTemplate(const ParticleSystemTemplate &other) :
	ParticleSystemInfo(other),
	m_name(other.m_name),
	m_slaveTemplate(0),
	m_tail(other.m_tail)
{
}

}
