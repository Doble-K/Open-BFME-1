// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: LifeEventModuleInfo dtor. SEH Buffer @+0x4 PropagandaTower pattern.

class Buffer
{
public:
	~Buffer();
};

namespace FXParticleSystem
{

class LifeEventModuleInfoBase
{
public:
	virtual ~LifeEventModuleInfoBase() {}
};

class __declspec(novtable) LifeEventModuleInfo : public LifeEventModuleInfoBase
{
public:
	virtual ~LifeEventModuleInfo();
private:
	Buffer m_buffer;
};

// ??1LifeEventModuleInfo@FXParticleSystem@@UAE@XZ
LifeEventModuleInfo::~LifeEventModuleInfo()
{
}

} // namespace FXParticleSystem
