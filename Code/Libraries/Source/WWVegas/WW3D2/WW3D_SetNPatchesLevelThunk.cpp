// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: WW3D::Set_NPatches_Level, spelled against the retail BFME shape.
//
// The clamp and the two invalidation tests are the reference body unchanged.
// Two things differ in BFME: TheDX8MeshRenderer is a pointer rather than a
// global object, so the call loads it with 'mov ecx, dword ptr [0x0134B0E8]',
// and Invalidate takes a bool that retail passes as false.  Spelled in its own
// translation unit so the change stays off the rest of ww3d.cpp (AGENTS.md,
// "Placement and integrity").
//
// Identity: the two calls resolve to the matched
// DX8MeshRendererClass::Invalidate at 0x00947BD0, and the clamped value lands
// in the same 0x012D6D8C global both invalidation tests read.

class DX8MeshRendererClass
{
public:
	void Invalidate( bool shutdown );
};

// A pointer in BFME where Zero Hour has a global object; 0x0134B0E8.
extern DX8MeshRendererClass *TheDX8MeshRenderer;

// 0x012D6D8C.  Declared external rather than file-static so the optimizer
// cannot reason about the only writer, which is what keeps the two reloads
// retail performs around the first Invalidate call.
extern unsigned NPatchesLevel;

class WW3D
{
public:
	static void Set_NPatches_Level( unsigned level );
};

void WW3D::Set_NPatches_Level( unsigned level )
{
	if( level > 8 ) level = 8;
	if( level < 1 ) level = 1;
	if( NPatchesLevel == 1 && level > 1 ) TheDX8MeshRenderer->Invalidate( false );
	if( NPatchesLevel > 1 && level == 1 ) TheDX8MeshRenderer->Invalidate( false );
	NPatchesLevel = level;
}
