// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/campaignmanagerascii /ICode/Libraries/Source/WWVegas/WWLib
// stlport

// FILE: INILivingWorldAnimObject.cpp /////////////////////////////////////////
//
// The LivingWorldAnimObject block, retail 0x0060A3A0. BFME-only; the INI block
// table in .data names it, and the "LivingWorldAnimObject" literal sits in the
// same run as the field table this body pushes (0x01115B60).
//
// Same shape as ParseArmyIconBlock in INIArmyIcon.cpp - guard the token, look
// the record up on TheLivingWorldManager by name, hand it to initFromINI - with
// two differences: this one does not throw on a null INI, and it does not test
// the lookup's result before parsing into it.
//
// The manager keeps the stand-in class name INIArmyIcon.cpp gave it. That is
// not a claim about what BFME calls it; it is so the one global at 0x012F706C
// keeps one decorated name across both translation units.
//
///////////////////////////////////////////////////////////////////////////////

#include <stddef.h>
#include <vector>

#include "Common/AsciiString.h"

struct FieldParse;

class INI
{
public:
	const char *getNextToken( const char *seps = 0 );
	void initFromINI( void *what, const FieldParse *parseTable );
};

class BfmeLivingWorldAnimObjectBase
{
public:
	BfmeLivingWorldAnimObjectBase() {}
	virtual ~BfmeLivingWorldAnimObjectBase();
};

class BfmeLivingWorldAnimObjectMember0C
{
public:
	BfmeLivingWorldAnimObjectMember0C() : m_value( 0 ) {}
	~BfmeLivingWorldAnimObjectMember0C();

private:
	void *m_value;
};

class BfmeLivingWorldAnimObject : public BfmeLivingWorldAnimObjectBase
{
public:
	BfmeLivingWorldAnimObject( const AsciiString &name );
	virtual ~BfmeLivingWorldAnimObject();
	static const FieldParse m_fieldParseTable[];		// 0x01115B60

private:
	int m_zero04;
	int m_zero08;
	BfmeLivingWorldAnimObjectMember0C m_member0C;
	bool m_zero10;
	bool m_zero11;
	unsigned char m_pad12[ 2 ];
	int m_zero14;
	AsciiString m_name;
	unsigned char m_unmodelled1C[ 0x0C ];
};

class BfmeLivingWorldManagerIcons
{
public:
	BfmeLivingWorldAnimObject *findAnimObject( const AsciiString &name );

private:
	char m_unmodelled[ 0x258 ];
	std::vector<BfmeLivingWorldAnimObject *> m_animObjects;
};

extern BfmeLivingWorldManagerIcons *TheLivingWorldManager;		// 0x012F706C

BfmeLivingWorldAnimObject::BfmeLivingWorldAnimObject( const AsciiString &name ) :
	m_zero10( false ),
	m_zero11( false ),
	m_zero14( 0 ),
	m_name( name )
{
	m_zero04 = 0;
	m_zero08 = 0;
}

BfmeLivingWorldAnimObject *BfmeLivingWorldManagerIcons::findAnimObject(
	const AsciiString &name )
{
	BfmeLivingWorldAnimObject *object = new BfmeLivingWorldAnimObject( name );
	m_animObjects.push_back( object );
	return object;
}

// ?parseLivingWorldAnimObject@@YAXPAVINI@@@Z
void parseLivingWorldAnimObject( INI *ini )
{
	const char *token = ini->getNextToken();
	if( !token )
		return;

	BfmeLivingWorldAnimObject *object = TheLivingWorldManager->findAnimObject( AsciiString( token ) );

	ini->initFromINI( object, BfmeLivingWorldAnimObject::m_fieldParseTable );
}
