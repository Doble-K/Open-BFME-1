// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: W3DDisplayStringManager::update, retail 0x006F56A0, converted out
// of Code/gen_asm/d_006e7d70.asm. The reference body ports unchanged.
//
// Offsets it fixes, all read off this one body:
//
//   manager +0x08  m_stringList, +0x0C  m_currentCheckpoint
//   string  +0x0C  the list link next() returns
//           +0x14  m_textRenderer, +0xE0  m_textRendererHotKey -- each reset
//                  through slot 0 of its own vtable
//           +0x1AC m_textChanged, +0x208  m_lastResourceFrame
//   TheGameClient's getFrame is vtable slot 26, `call [eax+0x68]`
//
// The base DisplayStringManager::update the reference calls first emits nothing
// here, which is what an empty base does: retail's first instruction after the
// prologue already reads m_currentCheckpoint. The call is kept for the same
// reason the reference keeps it.

typedef int Int;
typedef unsigned int UnsignedInt;

#define TRUE 1

class GameClient
{
public:
	virtual void slot000() = 0;
	virtual void slot004() = 0;
	virtual void slot008() = 0;
	virtual void slot00c() = 0;
	virtual void slot010() = 0;
	virtual void slot014() = 0;
	virtual void slot018() = 0;
	virtual void slot01c() = 0;
	virtual void slot020() = 0;
	virtual void slot024() = 0;
	virtual void slot028() = 0;
	virtual void slot02c() = 0;
	virtual void slot030() = 0;
	virtual void slot034() = 0;
	virtual void slot038() = 0;
	virtual void slot03c() = 0;
	virtual void slot040() = 0;
	virtual void slot044() = 0;
	virtual void slot048() = 0;
	virtual void slot04c() = 0;
	virtual void slot050() = 0;
	virtual void slot054() = 0;
	virtual void slot058() = 0;
	virtual void slot05c() = 0;
	virtual void slot060() = 0;
	virtual void slot064() = 0;
	virtual UnsignedInt getFrame( void ) const = 0;			///< +0x68
};

extern GameClient *TheGameClient;

// Only Reset matters, and retail reaches it through slot 0.
class Render2DSentenceClass
{
public:
	virtual void Reset( void );
};

class DisplayString
{
public:
	DisplayString *next( void ) { return m_next; }

protected:
	unsigned char m_unreconstructed_00[0x0C];
	DisplayString *m_next;									///< +0x0C
};

class W3DDisplayString : public DisplayString
{
public:
	unsigned char m_unreconstructed_10[0x14 - 0x10];
	Render2DSentenceClass m_textRenderer;					///< +0x14
	unsigned char m_unreconstructed_18[0xE0 - 0x18];
	Render2DSentenceClass m_textRendererHotKey;				///< +0xE0
	unsigned char m_unreconstructed_e4[0x1AC - 0xE4];
	unsigned char m_textChanged;							///< +0x1AC
	unsigned char m_unreconstructed_1ad[0x208 - 0x1AD];
	UnsignedInt m_lastResourceFrame;						///< +0x208
};

class DisplayStringManager
{
public:
	virtual void update( void ) { }

protected:
	unsigned char m_unreconstructed_04[0x08 - 0x04];
	DisplayString *m_stringList;							///< +0x08
	DisplayString *m_currentCheckpoint;						///< +0x0C
};

class W3DDisplayStringManager : public DisplayStringManager
{
public:
	virtual void update( void );
};

// ?update@W3DDisplayStringManager@@UAEXXZ
void W3DDisplayStringManager::update( void )
{
	// call base in case we add something later
	DisplayStringManager::update();

	W3DDisplayString *string = static_cast<W3DDisplayString *>(m_stringList);

	// if the m_currentCheckpoint is valid, use it for the starting point for the search
	if (m_currentCheckpoint) {
		string = static_cast<W3DDisplayString *>(m_currentCheckpoint);
	}

	UnsignedInt currFrame = TheGameClient->getFrame();
	const UnsignedInt w3dCleanupTime = 60;

	int numStrings = 10;
	while ( numStrings-- && string )
	{
		if( string->m_lastResourceFrame != 0 &&
				currFrame - string->m_lastResourceFrame > w3dCleanupTime )
		{
			string->m_textRenderer.Reset();
			string->m_textRendererHotKey.Reset();
			string->m_textChanged = TRUE;
			string->m_lastResourceFrame = 0;
		}

		string = static_cast<W3DDisplayString *>(string->next());
	}

	m_currentCheckpoint = string;
}
