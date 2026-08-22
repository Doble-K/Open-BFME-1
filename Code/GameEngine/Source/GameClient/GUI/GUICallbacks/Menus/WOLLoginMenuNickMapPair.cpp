// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/ini /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport

#define __PLACEMENT_VEC_NEW_INLINE
#include <map>

#include "PreRTS.h"
#include "Common/STLTypedefs.h"

// WOLLoginMenu's NickMap stores a list of nicknames for each email address.
// This translation unit preserves the retail StringBase-backed AsciiString
// copy context without changing the other matched WOLLoginMenu instantiations.
template class _STL::pair<const AsciiString, AsciiStringList>;
