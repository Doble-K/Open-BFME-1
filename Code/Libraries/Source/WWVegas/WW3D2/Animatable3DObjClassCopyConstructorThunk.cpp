// cl: /DNDEBUG /MD /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/Wwutil /ICode/Libraries/Source/WWVegas/WWDownload /ICode/Libraries/Source/Compression /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
#define Matrix4x4 Matrix4
#include "winbase_shim.h"

#include "animobj.h"
#include "htree.h"
#include "assetmgr.h"
#include "hanim.h"
#include "hcanim.h"
#include "ww3d.h"
#include "wwmemlog.h"
#include "animatedsoundmgr.h"

// ??0Animatable3DObjClass@@QAE@ABV0@@Z
Animatable3DObjClass::Animatable3DObjClass(const Animatable3DObjClass & src) :
	CompositeRenderObjClass(src),
	IsTreeValid(0),
	CurMotionMode(BASE_POSE),
	HTree(NULL),
	_bfme_a3o_v0(NULL)
{
   // Inline struct members can't be initialized in init list for some reason...
	ModeAnim.Motion=NULL;
	ModeAnim.Frame=0.0f;
	ModeAnim.PrevFrame=0.0f;
	ModeAnim.LastSyncTime=WW3D::Get_Sync_Time();
	ModeAnim.frameRateMultiplier=1.0;	// 020607 srj -- added
	ModeAnim.animDirection=1.0;	// 020607 srj -- added
	ModeInterp.Motion0=NULL;
	ModeInterp.Motion1=NULL;
	ModeInterp.Frame0=0.0f;
	ModeInterp.Frame1=0.0f;
	ModeInterp.Percentage=0.0f;
	ModeCombo.AnimCombo=NULL;

	*this = src;
}
