// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/stringbaseascii /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /ICode/Libraries/Source/WWVegas/WWLib
// stlport
//
// The ExperienceScalarTable block, retail 0x00380400. BFME-only; the INI block
// table in .data names it.
//
// The store is TheExperienceLevelSystem at 0x012F0888 - GameEngine::init builds
// the literal "TheExperienceLevelSystem" into the AsciiString it hands the
// registrar in the instruction before that address is pushed - and the tables
// go into a vector at +0x20 of it. Retail inlines the whole push_back fast path
// (compare finish against end_of_storage, copy-construct, bump finish) and only
// calls out to _M_insert_overflow, which is what says it is a vector and not a
// list.
//
// The table record is 0x10 bytes and this block reads none of it: it is built
// from the name, filled by the field table, and appended.
//
///////////////////////////////////////////////////////////////////////////////
#include "PreRTS.h"
#include "Common/INI.h"
#include "Common/STLTypedefs.h"

class ExperienceScalarTable
{
public:
	ExperienceScalarTable( const AsciiString &name );

	static const FieldParse m_fieldParseTable[];		// 0x010EA91C

private:
	char m_unmodelled[ 0x10 ];
};

class BfmeExperienceLevelSystem
{
public:
	// By value and inline: retail materialises the pointer into its stack slot
	// AFTER initFromINI returns, at the push_back itself, which is what a
	// by-value parameter whose address the inlined push_back then takes does. A
	// bare `m_scalarTables.push_back( table )' at the call site spills the
	// variable before the call instead.
	void addScalarTable( ExperienceScalarTable *table )
	{
		m_scalarTables.push_back( table );
	}

	unsigned char m_unmodelled_00[ 0x20 ];
	std::vector<ExperienceScalarTable *> m_scalarTables;	// +0x20
};

extern BfmeExperienceLevelSystem *TheExperienceLevelSystem;	// 0x012F0888

// ?parseExperienceScalarTable@@YAXPAVINI@@@Z
void parseExperienceScalarTable( INI *ini )
{
	if( !TheExperienceLevelSystem )
		return;

	AsciiString name( ini->getNextToken() );

	ExperienceScalarTable *table = new ExperienceScalarTable( name );

	ini->initFromINI( table, ExperienceScalarTable::m_fieldParseTable );

	TheExperienceLevelSystem->addScalarTable( table );
}
