// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Oy- /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib
// stlport
//
// The subsystem loader: look a subsystem up in the legend by name and load every
// INI file its "LoadSubsystem" block lists. This is the function that makes
// SubsystemLegend mean something — the legend is a manifest, and this is what
// reads it.
//
// Retail's home for it is ini.cpp: 0x000BB310 sits in that TU's arena, directly
// after INI::parseThingTemplate / parseParticleSystemTemplate / parseUpgradeTemplate
// (0x000BAD6A..0x000BB040), and shares their EH funcinfo run. It lives here
// instead because ini.cpp is still a ZH-tree port, and ZH's AsciiString inlines
// its release path while this function needs the out-of-line StringBase<char>
// calls retail makes. Fold it into ini.cpp when that file goes native.
#define __PLACEMENT_VEC_NEW_INLINE
#include <vector>
#include "PreRTS.h"
#include "subsystem_legend.h"
#include "Common/INI/INI.h"

// ?loadSubsystemFiles@INI@@SA_NPBDPAX@Z present-unmatched
// 181 of retail's 214 bytes at 0x000BB310; the size, the frame, the call
// sequence, the catch funclet and both epilogues are right. What is left is the
// same MSVC ordering divergence Handicap.cpp is parked on: retail records the
// unwind esp BEFORE loading `this` for the by-value AsciiString temp
//     push ecx / mov [ebp-0x14],esp / mov ecx,esp
// where we emit
//     push ecx / mov ecx,esp / mov [ebp-0x14],esp
// and retail keeps the EH-state stores inside the loop where we hoist them out.
// Neither moved under ~20 source shapes (try/catch placement and scope, six loop
// forms, explicit vs implicit temp, named local vs temporary) or any flag
// (/Ob0../Ob2 /EHa /GX /Ox /Ot /Os /Oa /Ow /Op /Oy- /G5../G7 /Zi /Gy-), with or
// without _STLP_NO_EXCEPTIONS.
bool INI::loadSubsystemFiles(const char *subsystem, void *xfer)
{
	SubsystemLegendEntry *entry = TheSubsystemLegend->findEntry(AsciiString(subsystem));
	if (entry)
	{
		INI ini;
		try
		{
			for (std::vector<AsciiString>::iterator f = entry->m_initFile.begin();
				 f != entry->m_initFile.end(); ++f)
			{
				ini.load(*f, 1, 0, xfer);
			}
		}
		catch (...)
		{
			return false;
		}
		return true;
	}
	return false;
}
