// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Lift the GameTextManager::deinit naked dump to clean C++.
//
// Zero Hour's GameText.cpp body; the DEBUG_LOGs around the missing-string walk
// compile out and leave the loop.
//
// The two array deletes are not the same shape and that is the layout evidence.
// m_stringInfo goes through the vector destructor iterator -- retail reads the
// element count from the word ahead of the array, pushes a per-element
// destructor and an element size of 8, then frees the block -- so its element
// type has a destructor and is eight bytes, where ZH's StringInfo is twelve.
// m_stringLUT is freed with a bare operator delete[], so its elements are
// trivially destructible.
//
// Retail pins the layout: the text count is at this+0x08, the two arrays at
// +0x780C and +0x7810, the initialised flag at +0x7814 and the missing-string
// list head at +0x7818, with each node's next pointer at its own +0x00.

typedef int Int;
typedef bool Bool;

class AsciiString
{
	void *m_data;
};

class UnicodeString
{
	void *m_data;
};

// Eight bytes with a destructor, which is what the vector destructor iterator
// call proves; the member names follow ZH for the two that fit.
class StringInfo
{
public:
	~StringInfo();

	AsciiString label;
	UnicodeString text;
};

class NoString
{
public:
	~NoString();

	NoString *next;										///< retail this+0x00
	UnicodeString text;
};

class GameTextManager
{
public:
	virtual void deinit(void);

private:
	unsigned char m_unreconstructed_04[8 - 4];
	Int m_textCount;									///< retail this+0x08
	unsigned char m_unreconstructed_0C[0x780C - 0x0C];
	StringInfo *m_stringInfo;							///< retail this+0x780C
	StringInfo **m_stringLUT;							///< retail this+0x7810
	Bool m_initialized;									///< retail this+0x7814
	unsigned char m_unreconstructed_7815[3];
	NoString *m_noStringList;							///< retail this+0x7818
};

// ?deinit@GameTextManager@@UAEXXZ
void GameTextManager::deinit( void )
{

	if( m_stringInfo != 0 )
	{
		delete [] m_stringInfo;
		m_stringInfo = 0;
	}

	if( m_stringLUT != 0 )
	{
		delete [] m_stringLUT;
		m_stringLUT = 0;
	}

	m_textCount = 0;

	NoString *noString = m_noStringList;

	while ( noString )
	{
		NoString *next = noString->next;
		delete noString;
		noString = next;
	}

	m_noStringList = 0;

	m_initialized = false;
}
