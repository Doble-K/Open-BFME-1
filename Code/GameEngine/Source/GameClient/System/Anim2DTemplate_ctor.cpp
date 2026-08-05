// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/asciistring_outofline /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it

// Anim2DTemplate's constructor, lifted from Anim2DTemplate_ctor_dtor.asm to real
// C++. It lives in its own translation unit rather than in Anim2D.cpp on purpose:
// adding a definition to that file renumbers its compiler-generated labels and
// breaks the object-symbol=$L row uw_00c39340, which relabel.py cannot re-key
// (see docs/lessons.md). A standalone TU leaves the neighbour untouched.
//
// The one thing it needs beyond the reference source is
// reference/shims/asciistring_outofline: retail calls
// AsciiString::operator=(const AsciiString&) out of line at 0x00887C90, and an
// inlined assignment costs a self-assignment guard, the buffer walk and a
// register -- 168 bytes against retail's 124.

#define ANIM2D_INLINE_SNAPSHOT_DTOR
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine
#include "Common/RandomValue.h"
#include "Common/Xfer.h"
#include "GameClient/Anim2D.h"
#include "GameClient/Image.h"

// ??0Anim2DTemplate@@QAE@VAsciiString@@@Z
Anim2DTemplate::Anim2DTemplate( AsciiString name )
{

	m_name = name;
	m_images = NULL;
	m_numFrames = NUM_FRAMES_INVALID;
	m_framesBetweenUpdates = 0;
	m_animMode = ANIM_2D_LOOP;
	m_randomizeStartFrame = FALSE;
	m_nextTemplate = NULL;

}  // end Anim2DTemplate
