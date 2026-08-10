// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// Open-BFME5: convert the retail W3DRopeDraw destructor to clean C++.

#include <vector>

// The drawable module's root base occupies twelve bytes before W3DRopeDraw's
// secondary interface subobject.  The middle base destructor resets the
// primary vtable, then calls this root destructor through 0x0002B8C8.
class W3DRopeDrawRootBase
{
public:
	virtual ~W3DRopeDrawRootBase();

private:
	unsigned char m_pad[8];
};

class W3DRopeDrawDrawModule : public W3DRopeDrawRootBase
{
public:
	virtual ~W3DRopeDrawDrawModule() {}
};

class W3DRopeDrawInterface
{
public:
	virtual void initRopeParms() = 0;
};

struct W3DRopeDrawSegInfo
{
	void *line;
	void *softLine;
	float wobbleAxisX;
	float wobbleAxisY;
};

class W3DRopeDraw : public W3DRopeDrawDrawModule, public W3DRopeDrawInterface
{
public:
	virtual ~W3DRopeDraw();

private:
	std::vector<W3DRopeDrawSegInfo> m_segments;

	void tossSegments();
};

// ??1W3DRopeDraw@@UAE@XZ
W3DRopeDraw::~W3DRopeDraw()
{
	tossSegments();
}
