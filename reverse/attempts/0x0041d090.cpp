// ?get@BFMERopeDrawableGetPositionShim@@QBEPBUCoord3D@@XZ
// partial score=0.85 date=2026-08-25
// Retail 0x0041D090, 147 bytes: the target of the BFMERopeDrawable
// getPosition incremental-link thunk.
//
// The six-argument call is an import thunk (slot 0x012DBEC0) with no caller
// cleanup, so it is __stdcall, and its arguments are an out slot followed by
// four vectors twelve bytes apart at +0x37C, +0x388, +0x394 and +0x3A0 plus a
// float from TheGameEngine. That is a Hermite spline evaluation.
//
// The second path never sets eax: the last thing loaded into it is the z
// component of the temporary, and the epilogue follows straight on. That is a
// missing return in the original, not a computed one -- the first path does
// return a pointer, so the return type is real.

struct BfmeVector3
{
	float x;
	float y;
	float z;
};

struct Coord3D
{
	Coord3D(void) {}

	Coord3D(BfmeVector3 value)
	{
		x = value.x;
		y = value.y;
		z = value.z;
	}

	Coord3D &operator=(const Coord3D &other)
	{
		x = other.x;
		y = other.y;
		z = other.z;

		return *this;
	}

	float x;
	float y;
	float z;
};

class GameEngine
{
public:
	char m_bfmeHead[0x38];
	float m_bfmeParam;				// +0x38
};

extern GameEngine *TheGameEngine;			// 0x012ED524

BfmeVector3 *__stdcall bfmeVec3Hermite(BfmeVector3 *out, const Coord3D *v1, const Coord3D *t1,
	const Coord3D *v2, const Coord3D *t2, float s);	// import thunk 0x009FA11F

class BFMERopeDrawableGetPositionShim
{
public:
	const Coord3D *get(void) const;

private:
	void bfmeRebuild(int which);			// ILT 0x00034C3E

	char m_bfmeHeadA[0x38];
	Coord3D m_bfmeAnchor;				// +0x038
	char m_bfmeHeadB[0xFC - 0x44];
	void *m_bfmeCurve;				// +0x0FC
	char m_bfmeHeadC[0x230 - 0x100];
	Coord3D m_bfmeCached;				// +0x230
	char m_bfmeHeadD[0x37C - 0x23C];
	Coord3D m_bfmeP0;				// +0x37C
	Coord3D m_bfmeT0;				// +0x388
	Coord3D m_bfmeP1;				// +0x394
	Coord3D m_bfmeT1;				// +0x3A0
	char m_bfmeHeadE[0x3B4 - 0x3AC];
	bool m_bfmeBuilt;				// +0x3B4
};

// ?get@BFMERopeDrawableGetPositionShim@@QBEPBUCoord3D@@XZ
const Coord3D *BFMERopeDrawableGetPositionShim::get(void) const
{
	BFMERopeDrawableGetPositionShim *self = (BFMERopeDrawableGetPositionShim *)this;

	if (!m_bfmeCurve)
		return &m_bfmeAnchor;

	if (!m_bfmeBuilt)
		self->bfmeRebuild(0);

	BfmeVector3 out;
	bfmeVec3Hermite(&out, &m_bfmeP0, &m_bfmeT0, &m_bfmeP1, &m_bfmeT1, TheGameEngine->m_bfmeParam);

	self->m_bfmeCached = Coord3D(out);
}
