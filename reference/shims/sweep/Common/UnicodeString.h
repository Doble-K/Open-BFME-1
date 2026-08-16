#pragma once
// Open-BFME5: retail's UnicodeStringData is EIGHT bytes, not four.
//
// str() inlines to a fixed idiom -- test the data pointer, add the header size,
// or fall back to the shared empty string. Counted across retail .text that
// idiom appears 808 times and every one of them adds 8; retail never emits
// `add eax,4`. The vendored header makes the struct four bytes by compiling out
// its m_debugptr field, which is gated on _DEBUG || _INTERNAL, and eight with it
// in. So the shipped build had that field.
//
// _INTERNAL is defined across the include and taken away again. The includes the
// header itself pulls are hoisted ABOVE that, deliberately: Common/Debug.h reads
// _INTERNAL too, and letting it see the define turns DEBUG_ASSERTCRASH back on,
// which grew LANAPI::removePlayer past its matched extent when this shim first
// went in.
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include "Lib/BaseType.h"
#include "Common/Debug.h"
#include "Common/Errors.h"

#ifdef _INTERNAL
#include "../../../CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h"
#else
#define _INTERNAL
#include "../../../CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h"
#undef _INTERNAL
#endif
