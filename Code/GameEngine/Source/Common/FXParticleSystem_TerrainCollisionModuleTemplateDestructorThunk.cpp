// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: TerrainCollisionModuleTemplate dtor, clean C++.
//
// Template derives from CategoryModuleTemplate<8> (offset 0, size 0xc) and from
// TerrainCollisionModuleInfo (offset 0xc). MSVC inlines both base destructors:
// ~TerrainCollisionModuleInfo releases its Buffer at +4 and restores the
// TerrainCollisionModuleInfoBase vptr, then ~CategoryModuleTemplate<8> restores
// its two vptrs. The `this ? this + 4 : 0` adjustor in ~CategoryModuleTemplate<8>
// is retail's own shape (see CategoryModuleTemplate07DestructorThunk.cpp) and
// rides along into this body when the base dtor is inlined.

class Buffer
{
public:
	~Buffer();
};

namespace FXParticleSystem
{

template <int Category>
class CategoryModuleTemplate
{
};

template <>
class __declspec(novtable) CategoryModuleTemplate<8>
{
public:
	virtual ~CategoryModuleTemplate()
	{
		unsigned char *base = this ? (unsigned char *)this + 4 : 0;
		*(volatile unsigned int *)base = 0x0107375C;
		*(volatile unsigned int *)this = 0x01073758;
	}

	unsigned int m_04;
	bool m_08;
	bool m_09;
};

class TerrainCollisionModuleInfoBase
{
public:
	virtual ~TerrainCollisionModuleInfoBase() {}
};

class __declspec(novtable) TerrainCollisionModuleInfo : public TerrainCollisionModuleInfoBase
{
public:
	virtual ~TerrainCollisionModuleInfo() {}
private:
	Buffer m_buffer;
};

class __declspec(novtable) TerrainCollisionModuleTemplate
	: public CategoryModuleTemplate<8>,
	  public TerrainCollisionModuleInfo
{
public:
	virtual ~TerrainCollisionModuleTemplate();
};

// ??1TerrainCollisionModuleTemplate@FXParticleSystem@@UAE@XZ
TerrainCollisionModuleTemplate::~TerrainCollisionModuleTemplate()
{
}

} // namespace FXParticleSystem
