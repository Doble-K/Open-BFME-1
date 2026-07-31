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
#include "PreRTS.h"
#include "subsystem_interface.h"

// ??1SubsystemInterface@@UAE@XZ
SubsystemInterface::~SubsystemInterface()
{
}

// ?getName@SubsystemInterface@@QAE?AVAsciiString@@XZ
AsciiString SubsystemInterface::getName(void)
{
	return m_name;
}
