// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib
// stlport
//
// BFME's SubsystemInterface, built against the native headers. The ZH-tree port
// in SubsystemInterface.cpp keeps ZH's behaviour (its dtor unregisters from
// TheSubsystemList); BFME's is empty — 0x009A1A40 is just "restore the vptr,
// then tail-jump to destroy m_name", which only comes out of an empty body and
// an out-of-line AsciiString dtor.
//
// The base vtable is at 0x01141640 and has nine slots. SubsystemLegend overrides
// 0/1/4/5 and inherits 2/3/6/7/8, which is how those five were ruled out of
// SubsystemLegend.cpp's membership.
#define __PLACEMENT_VEC_NEW_INLINE
#include <vector>
#include "PreRTS.h"
#include "subsystem_interface.h"
#include "subsystem_legend.h"
#include "Common/INI/INI.h"

SubsystemInterfaceList *TheSubsystemList;		// 0x0134C6C8

// ??1SubsystemInterface@@UAE@XZ
SubsystemInterface::~SubsystemInterface()
{
}

// ?getName@SubsystemInterface@@QAE?AVAsciiString@@XZ
AsciiString SubsystemInterface::getName(void)
{
	return m_name;
}

// ?loadIniFilesFromLegend@SubsystemInterface@@UAE_NXZ present-unmatched
// 285 of retail's 286 bytes at 0x009A1A50; both loops, both INI entry points and
// the epilogue are in place. The residue is our compiler parking a 32-bit zero in
// ebx and reusing it (cmp eax,ebx / mov [esp+N],ebx) where retail zeroes only bl
// and uses immediates, plus the unwind-esp ordering noted below.
// Vtable slot 2, inherited by every subsystem in the game. This is the whole
// point of SubsystemLegend: a subsystem looks itself up by name and loads the
// INI files and directories its "LoadSubsystem" block lists. The Bool it returns
// tells SubsystemInterfaceList::initSubsystem whether the legend supplied
// anything — if it did, the hard-coded paths GameEngine::init passed are skipped.
Bool SubsystemInterface::loadIniFilesFromLegend()
{
	if (!TheSubsystemLegend)
		return FALSE;

	SubsystemLegendEntry *entry = TheSubsystemLegend->findEntry(getName());
	if (!entry)
		return FALSE;

	INI ini;
	Bool loadedAny = FALSE;

	for (AsciiString *f = entry->m_initFile.begin(); f != entry->m_initFile.end(); ++f)
	{
		loadedAny = TRUE;
		ini.loadFile(*f, INI_LOAD_OVERWRITE, TheSubsystemList->m_xfer);
	}

	for (AsciiString *d = entry->m_initPath.begin(); d != entry->m_initPath.end(); ++d)
	{
		loadedAny = TRUE;
		ini.loadDirectory(*d, true, INI_LOAD_OVERWRITE, TheSubsystemList->m_xfer, 0);
	}

	return loadedAny;
}

// ?initSubsystem@SubsystemInterfaceList@@QAEXPAVSubsystemInterface@@PAXPBD22PAVXfer@@VAsciiString@@@Z present-unmatched
// 251 of retail's 271 bytes at 0x009A20B0. Size-exact; the residue is register
// choice (eax/edx swapped on the two vtable loads) and the unwind-esp ordering.
// Name it, init it, then give the legend first refusal: if the subsystem's
// "LoadSubsystem" block supplied any files, the hard-coded paths GameEngine::init
// passed are skipped entirely. That precedence is the interesting part for anyone
// editing SubsystemLegend.ini.
void SubsystemInterfaceList::initSubsystem(SubsystemInterface *sys, void *slot, const char *path1,
										   const char *path2, const char *dirpath, Xfer *pXfer,
										   AsciiString name)
{
	sys->setName(name);
	sys->init();

	Bool loadedFromLegend = sys->loadIniFilesFromLegend();

	m_subsystems.push_back(std::make_pair(sys, slot));

	if (!loadedFromLegend)
	{
		INI ini;
		if (path1)
			ini.loadFile(path1, INI_LOAD_OVERWRITE, pXfer);
		if (path2)
			ini.loadFile(path2, INI_LOAD_OVERWRITE, pXfer);
		if (dirpath)
			ini.loadDirectory(dirpath, true, INI_LOAD_OVERWRITE, pXfer, 0);
	}
}

// ??$initSubsystem@VSubsystemLegend@@@@YAXAAPAVSubsystemLegend@@VAsciiString@@PAV0@PAVXfer@@PBD44@Z present-unmatched
// 148 of retail's 154 bytes at 0x00072DD0. The six that differ are one instruction
// pair: retail records the unwind esp before loading `this` (mov [esp+0x24],esp /
// mov ecx,esp), we emit the reverse. That is the same divergence Handicap.cpp and
// INI::loadSubsystemFiles are parked on — see docs/lessons.md.
//
// Force the SubsystemLegend instantiation retail carries at 0x00072DD0.
template void initSubsystem<SubsystemLegend>(SubsystemLegend *&, AsciiString, SubsystemLegend *,
											 Xfer *, const char *, const char *, const char *);
