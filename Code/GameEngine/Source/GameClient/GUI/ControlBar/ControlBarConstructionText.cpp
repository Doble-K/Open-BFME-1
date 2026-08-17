// cl: /DNDEBUG /MD /EHsc

// FILE: ControlBarConstructionText.cpp ///////////////////////////////////////
//
// ControlBar::updateConstructionTextDisplay, retail 0x004AF520.
//
// No port of ControlBarUnderConstruction.cpp exists under Code/.  Found by the
// literal it pushes: "ControlBar.wnd:UnderConstructionDesc" appears in exactly
// one reference source and inside exactly one function there.  The body is Zero
// Hour's, minus the DEBUG_ASSERTCRASH that NDEBUG removes from both trees.
//
// Everything the stand-in asserts is read out of the bytes:
//
//   Object::getConstructionPercent() inlines to a Real at +0x220
//   ControlBar::m_displayedConstructPercent is at +0x68
//   GameWindowManager::winGetWindowFromId is virtual, at slot 0xdc
//   GameText::fetch is virtual, at slot 0x28
//   NameKeyGenerator::nameToKey takes a const char * here, not an AsciiString:
//     retail pushes the literal straight through and builds no temporary
//
// The intervening vtable slots are anonymous -- this body says where these
// three landed and nothing about what is above them.
//
///////////////////////////////////////////////////////////////////////////////

typedef float Real;
typedef unsigned int UnsignedInt;
typedef int NameKeyType;
typedef bool Bool;

template <class Type>
class StringBase
{
private:
	StringBase(const StringBase &that);
	friend class UnicodeString;
};

class UnicodeString
{
public:

	UnicodeString() { m_text = 0; }

	// Visible delegation, so the by-value temporary is scheduled retail's way.
	UnicodeString(const UnicodeString &that)
	{
		((StringBase<unsigned short> *)this)->StringBase<unsigned short>::StringBase(
			*(const StringBase<unsigned short> *)&that);
	}

	~UnicodeString();

	// Variadic member: MSVC compiles these __cdecl with this pushed first, and
	// the format string is a UnicodeString BY VALUE.
	void __cdecl format(UnicodeString fmt, ...);

private:

	void *m_text;

};

class GameWindow;

class Object
{
public:
	Real getConstructionPercent( void ) const
	{
		return *(const Real *)((const char *)this + 0x220);
	}
};

class GameWindowManager
{
public:
	virtual void slot000() = 0;
	virtual void slot004() = 0;
	virtual void slot008() = 0;
	virtual void slot00C() = 0;
	virtual void slot010() = 0;
	virtual void slot014() = 0;
	virtual void slot018() = 0;
	virtual void slot01C() = 0;
	virtual void slot020() = 0;
	virtual void slot024() = 0;
	virtual void slot028() = 0;
	virtual void slot02C() = 0;
	virtual void slot030() = 0;
	virtual void slot034() = 0;
	virtual void slot038() = 0;
	virtual void slot03C() = 0;
	virtual void slot040() = 0;
	virtual void slot044() = 0;
	virtual void slot048() = 0;
	virtual void slot04C() = 0;
	virtual void slot050() = 0;
	virtual void slot054() = 0;
	virtual void slot058() = 0;
	virtual void slot05C() = 0;
	virtual void slot060() = 0;
	virtual void slot064() = 0;
	virtual void slot068() = 0;
	virtual void slot06C() = 0;
	virtual void slot070() = 0;
	virtual void slot074() = 0;
	virtual void slot078() = 0;
	virtual void slot07C() = 0;
	virtual void slot080() = 0;
	virtual void slot084() = 0;
	virtual void slot088() = 0;
	virtual void slot08C() = 0;
	virtual void slot090() = 0;
	virtual void slot094() = 0;
	virtual void slot098() = 0;
	virtual void slot09C() = 0;
	virtual void slot0A0() = 0;
	virtual void slot0A4() = 0;
	virtual void slot0A8() = 0;
	virtual void slot0AC() = 0;
	virtual void slot0B0() = 0;
	virtual void slot0B4() = 0;
	virtual void slot0B8() = 0;
	virtual void slot0BC() = 0;
	virtual void slot0C0() = 0;
	virtual void slot0C4() = 0;
	virtual void slot0C8() = 0;
	virtual void slot0CC() = 0;
	virtual void slot0D0() = 0;
	virtual void slot0D4() = 0;
	virtual void slot0D8() = 0;
	virtual GameWindow *winGetWindowFromId( GameWindow *window, NameKeyType id ) = 0;	// @0xdc
};

class GameText
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1C() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual UnicodeString fetch( const char *label, Bool *exists = 0 ) = 0;	// @0x28
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey( const char *name );
};

extern NameKeyGenerator *TheNameKeyGenerator;
extern GameWindowManager *TheWindowManager;
extern GameText *TheGameText;

void GadgetStaticTextSetText( GameWindow *window, UnicodeString text );

class ControlBar
{
public:

	void updateConstructionTextDisplay( Object *obj );

private:

	char m_bfmeHead[0x68];
	Real m_displayedConstructPercent;						// @0x68

};

void ControlBar::updateConstructionTextDisplay( Object *obj )
{
	UnicodeString text;
	static UnsignedInt descID = TheNameKeyGenerator->nameToKey( "ControlBar.wnd:UnderConstructionDesc" );
	GameWindow *descWindow = TheWindowManager->winGetWindowFromId( 0, descID );

	// format the message
	text.format( TheGameText->fetch( "CONTROLBAR:UnderConstructionDesc" ),
							 obj->getConstructionPercent() );
	GadgetStaticTextSetText( descWindow, text );

	// record this as the last percentage displayed
	m_displayedConstructPercent = obj->getConstructionPercent();

}  // end updateConstructionTextDisplay
