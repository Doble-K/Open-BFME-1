// cl: /DNDEBUG /MD /EHsc

// BaseHeightMapResetShroud::setBorderShroudLevel30B8, retail 0x0071A0D0.
// The BFME shroud wrapper stores the border level at +0x36 and marks the
// value dirty at +0x35.

class BaseHeightMapResetShroud
{
private:
	unsigned char m_unmodelled_00[ 0x35 ];
	unsigned char m_dirty;
	unsigned char m_borderLevel;

public:
	void setBorderShroudLevel30B8( unsigned char level );
};

// ?setBorderShroudLevel30B8@BaseHeightMapResetShroud@@QAEXE@Z
void BaseHeightMapResetShroud::setBorderShroudLevel30B8( unsigned char level )
{
	m_borderLevel = level;
	m_dirty = 1;
}
