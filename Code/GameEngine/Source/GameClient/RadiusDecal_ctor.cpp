// cl: /DNDEBUG /MD /EHsc

// RadiusDecal's constructor, retail 0x004582F0. Four fields and no base call:
// three zeroed and the flag at +0x08 set true, which is the state clear() and
// the destructor both leave it in.

class RadiusDecalShadow;

class RadiusDecal
{
public:
	RadiusDecal();

private:
	int m_unmodelled_00;					// +0x00
	RadiusDecalShadow *m_shadow;			// +0x04
	bool m_unmodelled_08;					// +0x08
	int m_unmodelled_0C;					// +0x0C
};

// ??0RadiusDecal@@QAE@XZ
RadiusDecal::RadiusDecal()
	: m_unmodelled_00( 0 ),
	  m_shadow( 0 ),
	  m_unmodelled_08( true ),
	  m_unmodelled_0C( 0 )
{
}
