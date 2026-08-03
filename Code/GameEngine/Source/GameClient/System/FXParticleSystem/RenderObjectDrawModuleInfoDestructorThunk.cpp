// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: RenderObjectDrawModuleInfo dtor. Buffers @+0x10/+0x20/+0x30.

class Buffer
{
public:
	~Buffer();

private:
	unsigned char m_pad[4];
};

namespace FXParticleSystem
{

class RenderObjectDrawModuleInfoBase
{
public:
	virtual ~RenderObjectDrawModuleInfoBase() {}

private:
	unsigned char m_pad[0xc];
};

class __declspec(novtable) RenderObjectDrawModuleInfo
	: public RenderObjectDrawModuleInfoBase
{
public:
	virtual ~RenderObjectDrawModuleInfo();

private:
	Buffer m_a;
	unsigned char m_gap1[0xc];
	Buffer m_b;
	unsigned char m_gap2[0xc];
	Buffer m_c;
};

// ??1RenderObjectDrawModuleInfo@FXParticleSystem@@UAE@XZ
RenderObjectDrawModuleInfo::~RenderObjectDrawModuleInfo()
{
}

}
