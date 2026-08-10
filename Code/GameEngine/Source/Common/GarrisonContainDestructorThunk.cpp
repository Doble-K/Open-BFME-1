// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// The retail GarrisonContain object has OpenContain's nine polymorphic
// subobjects followed by its 3x40 Coord3D array at offset 0x3fc.  Keeping
// those subobjects and the non-trivial coordinate destructor here lets the
// compiler emit the complete destructor, including its SEH cleanup and
// base-destructor call.

class OpenContainPrimaryBase
{
public:
	virtual ~OpenContainPrimaryBase() {}

private:
	unsigned char m_pad[8];
};

template <int Number>
class OpenContainSecondaryBase
{
public:
	virtual ~OpenContainSecondaryBase() {}
};

class OpenContainWideSecondaryBase
{
public:
	virtual ~OpenContainWideSecondaryBase() {}

private:
	unsigned char m_pad[12];
};

class __declspec(novtable) OpenContain
	: public OpenContainPrimaryBase,
	  public OpenContainSecondaryBase<1>,
	  public OpenContainWideSecondaryBase,
	  public OpenContainSecondaryBase<2>,
	  public OpenContainSecondaryBase<3>,
	  public OpenContainSecondaryBase<4>,
	  public OpenContainSecondaryBase<5>,
	  public OpenContainSecondaryBase<6>,
	  public OpenContainSecondaryBase<7>
{
public:
	virtual ~OpenContain();

private:
	unsigned char m_pad[0x3c4];
};

class Coord3D
{
	public:
	~Coord3D() {}

	private:
	float m_value[3];
};

class GarrisonContain : public OpenContain
{
public:
	virtual ~GarrisonContain();

private:
	Coord3D m_garrisonPoint[3][40];
};

// ??1GarrisonContain@@UAE@XZ
GarrisonContain::~GarrisonContain()
{
}
