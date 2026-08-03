// cl: /DNDEBUG /MD /GX- /O2 /Ob2

// Open-BFME5: Render_Obj_Exists free-function wrapper.
// Null-check name and global AssetRegistry then thiscall impl.

class AssetRegistry
{
public:
	bool Render_Obj_Exists_Impl(const char *name);
};

extern AssetRegistry *g_theAssetRegistry;

// ?Render_Obj_Exists@@YA_NPBD@Z
bool Render_Obj_Exists(const char *name)
{
	if (name)
	{
		AssetRegistry *reg = g_theAssetRegistry;
		if (reg)
			return reg->Render_Obj_Exists_Impl(name);
	}
	return false;
}
