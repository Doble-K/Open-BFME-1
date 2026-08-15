// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: W3DDebugDisplay::~W3DDebugDisplay, retail 0x006E6C50,
// zh_sweep packet 006e6c50.
//
// The Zero Hour body unchanged:
//
//   if ( m_displayString )
//     TheDisplayStringManager->freeDisplayString( m_displayString );
//
// The reference tree's W3DDebugDisplay.cpp is not ported, so the two classes
// are spelled TU-locally at the offsets retail proves:
//
//  - m_displayString is [this+0x2C], which is exactly where the vendored
//    headers put it: DebugDisplay is a vptr plus m_textColor/m_xPos/m_yPos/
//    m_width/m_height/m_rightMargin/m_leftMargin (0x20 bytes), then
//    W3DDebugDisplay adds m_font/m_fontWidth/m_fontHeight before it. So the
//    layout did not drift; only the class hierarchy did.
//  - Retail's destructor stores exactly two vtables, the derived one and one
//    base. Zero Hour's chain is three deep -- W3DDebugDisplay : DebugDisplay :
//    DebugDisplayInterface -- and each level's inline destructor stamps its
//    own vptr, which would be three stores. BFME collapses that to two, so the
//    hierarchy here is two levels.
//  - freeDisplayString is [vtbl+0x28] on TheDisplayStringManager, slot 10.

class DisplayString;
class GameFont;

class DisplayStringManager
{
public:
	// Only the one slot is named; the rest exist to place it.
	virtual void slot0( void ) = 0;
	virtual void slot1( void ) = 0;
	virtual void slot2( void ) = 0;
	virtual void slot3( void ) = 0;
	virtual void slot4( void ) = 0;
	virtual void slot5( void ) = 0;
	virtual void slot6( void ) = 0;
	virtual void slot7( void ) = 0;
	virtual void slot8( void ) = 0;
	virtual void slot9( void ) = 0;
	virtual void freeDisplayString( DisplayString *string ) = 0;	///< slot 10, [vtbl+0x28]
};

extern DisplayStringManager *TheDisplayStringManager;				///< retail 0x012F12CC

class DebugDisplay
{
public:
	virtual ~DebugDisplay() {}

protected:
	int m_textColor;					///< +0x04
	int m_xPos;							///< +0x08
	int m_yPos;							///< +0x0C
	int m_width;						///< +0x10
	int m_height;						///< +0x14
	int m_rightMargin;					///< +0x18
	int m_leftMargin;					///< +0x1C
};

class W3DDebugDisplay : public DebugDisplay
{
public:
	virtual ~W3DDebugDisplay();

protected:
	GameFont *m_font;					///< +0x20
	int m_fontWidth;					///< +0x24
	int m_fontHeight;					///< +0x28
	DisplayString *m_displayString;		///< +0x2C
};

//============================================================================
// W3DDebugDisplay::~W3DDebugDisplay
//============================================================================
// ??1W3DDebugDisplay@@UAE@XZ
W3DDebugDisplay::~W3DDebugDisplay()
{
	if ( m_displayString )
	{
		TheDisplayStringManager->freeDisplayString( m_displayString );
	}
}
