// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: TerrainCollisionModuleInfo dtor. SEH Buffer @+0x4 PropagandaTower pattern.

class Buffer
{
public:
	~Buffer();
};

namespace FXParticleSystem
{

class TerrainCollisionModuleInfoBase
{
public:
	virtual ~TerrainCollisionModuleInfoBase() {}
};

class __declspec(novtable) TerrainCollisionModuleInfo : public TerrainCollisionModuleInfoBase
{
public:
	virtual ~TerrainCollisionModuleInfo();
private:
	Buffer m_buffer;
};

// ??1TerrainCollisionModuleInfo@FXParticleSystem@@UAE@XZ
TerrainCollisionModuleInfo::~TerrainCollisionModuleInfo()
{
}

} // namespace FXParticleSystem
