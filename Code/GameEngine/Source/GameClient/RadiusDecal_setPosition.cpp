// cl: /DNDEBUG /MD /EHsc

// RadiusDecal::setPosition, retail 0x004583A0. The decal itself is behind the
// pointer at +0x04 and does nothing when that is null; the position it carries
// is three floats at +0x08 of whatever it points at.

struct Coord3D
{
	float x;
	float y;
	float z;
};

class RadiusDecalShadow
{
public:
	unsigned char m_unmodelled_00[ 8 ];
	Coord3D m_position;						// +0x08
};

class RadiusDecal
{
public:
	void setPosition( const Coord3D &pos );

private:
	unsigned char m_unmodelled_00[ 4 ];
	RadiusDecalShadow *m_shadow;			// +0x04
};

// ?setPosition@RadiusDecal@@QAEXABUCoord3D@@@Z
void RadiusDecal::setPosition( const Coord3D &pos )
{
	if( m_shadow )
		m_shadow->m_position = pos;
}
