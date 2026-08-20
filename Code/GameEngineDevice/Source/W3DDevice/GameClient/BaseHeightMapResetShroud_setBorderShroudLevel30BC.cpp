// cl: /DNDEBUG /MD /EHsc

// BaseHeightMapResetShroud::setBorderShroudLevel30BC, retail 0x00727010.
// The BFME shroud wrapper stores the border level at +0x36 and marks the
// value dirty at +0x35.

class BaseHeightMapResetShroud
{
private:
	unsigned char m_unmodelled_00[ 0x35 ];
	unsigned char m_dirty;
	unsigned char m_borderLevel;

public:
	void setBorderShroudLevel30BC( unsigned char level );
};

// ?setBorderShroudLevel30BC@BaseHeightMapResetShroud@@QAEXE@Z
void BaseHeightMapResetShroud::setBorderShroudLevel30BC( unsigned char level )
{
	m_borderLevel = level;
	m_dirty = 1;
}
