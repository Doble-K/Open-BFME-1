// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
// Open-BFME5: BFME stores the side-icon name at +0xe0; the Zero Hour class
// layout used by the reference header places the corresponding member earlier.

#include "PreRTS.h"

#include "Common/GameCommon.h"
#define getSideIconImage _bfme_getSideIconImage
#include "Common/PlayerTemplate.h"
#undef getSideIconImage
#include "GameClient/Image.h"

// @?_bfme_getSideIconImage@PlayerTemplate@@QBEPBVImage@@XZ 0x000E0B80
const Image *PlayerTemplate::_bfme_getSideIconImage(void) const
{
	const AsciiString &name = *reinterpret_cast<const AsciiString *>(
		reinterpret_cast<const char *>(this) + 0xe0);
	return TheMappedImageCollection->findImageByName(name);
}
