// cl: /O2 /Ob0

class DX8MeshRendererClass
{
public:
	void Invalidate(bool);
};

DX8MeshRendererClass *g_rva008fd2a0;

void rva008fd2a0()
{
	g_rva008fd2a0->Invalidate(false);
}
