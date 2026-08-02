// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/iniexception /Ireference/shims/ini /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
//
// The OptionGroup block. It is unusual among the parsers here: instead of
// handing initFromINI a static table, it builds a four-entry FieldParse array on
// the stack, one entry per value type the group can hold.
//
//   Bool  Int  String  Real
//
// So an OptionGroup body is a list of typed values rather than a fixed set of
// named settings, which is why the table has to be constructed per call. The
// four parse procs are stored as data, not called, so they are DIR32 slots the
// verifier fills in from the target; the four tokens are real string literals
// and are string-ref verified.
//
// The two globals have no recoverable names. The first is an AsciiString holding
// the group name for the duration of the parse -- set on entry, cleared to ""
// on exit -- and the second is the object the values are parsed into.
#include "PreRTS.h"
#include "Common/INI.h"

extern AsciiString TheOptionGroupName;		// 0x012ED60C
extern void *TheOptionGroupTarget;			// 0x012ED604

void parseOptionGroup( INI *ini )
{
	TheOptionGroupName = ini->getNextToken();

	const FieldParse myFieldParse[] =
	{
		{ "Bool",		INI::parseBool,			NULL, 0 },
		{ "Int",		INI::parseInt,			NULL, 0 },
		{ "String",		INI::parseAsciiString,	NULL, 0 },
		{ "Real",		INI::parseReal,			NULL, 0 },
		{ NULL,			NULL,					NULL, 0 }
	};

	ini->initFromINI( TheOptionGroupTarget, myFieldParse );

	TheOptionGroupName = "";
}
