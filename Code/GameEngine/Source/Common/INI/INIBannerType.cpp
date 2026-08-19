// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/campaignmanagerascii /ICode/Libraries/Source/WWVegas/WWLib

// FILE: INIBannerType.cpp ////////////////////////////////////////////////////
//
// The BannerType block, retail 0x00584550. BFME-only; the INI block table in
// .data names it, and the parser is spelled parse<Block> like the rest of them.
//
// The store is not a global of its own: retail loads 0x012F4B70 and adds 8,
// so the lookup runs on a member at +8 of the subsystem there. That subsystem
// is TheBannerUI - its constructor at 0x005849E0 hands "TheBannerUI" to the
// name setter, and the field table this block parses with (0x0110B898) sits in
// the same literal run as that string.
//
// The name is a temporary, not a local: retail releases the AsciiString before
// it calls initFromINI, which is end-of-full-expression for an argument passed
// by const reference, not the end of the block.
//
///////////////////////////////////////////////////////////////////////////////

#include <stddef.h>

#include "Common/AsciiString.h"

struct FieldParse;

class INI
{
public:
	const char *getNextToken( const char *seps = 0 );
	void initFromINI( void *what, const FieldParse *parseTable );
};

class BannerType
{
public:
	static const FieldParse m_fieldParseTable[];		// 0x0110B898
};

// The lookup at 0x00583CD0: find by name, insert a default-constructed entry
// when it misses. Only its address is claimed here, not its shape.
class BannerTypeStore
{
public:
	BannerType *findOrCreate( const AsciiString &name );
};

class BannerUI
{
public:
	unsigned char m_unmodelled_00[ 8 ];
	BannerTypeStore m_bannerTypes;						// +0x08
};

extern BannerUI *TheBannerUI;							// 0x012F4B70

// ?parseBannerType@@YAXPAVINI@@@Z
void parseBannerType( INI *ini )
{
	BannerType *type = TheBannerUI->m_bannerTypes.findOrCreate( AsciiString( ini->getNextToken() ) );

	ini->initFromINI( type, BannerType::m_fieldParseTable );
}
