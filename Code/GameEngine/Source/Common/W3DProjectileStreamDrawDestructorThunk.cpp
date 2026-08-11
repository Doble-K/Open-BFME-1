// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift MASM dump to standalone C++ thunk.

class PB_DeepBase
{
public:
	virtual ~PB_DeepBase();

private:
	void *m_p4;
	void *m_p8;
};

class DrawModuleInterface1
{
public:
	virtual void slot() = 0;
};

class DrawModuleInterface2
{
public:
	virtual void slot() = 0;
};

class DrawModule : public PB_DeepBase, public DrawModuleInterface1
{
public:
	virtual ~DrawModule() {}
};

class ProjectileStreamDrawBase : public DrawModule, public DrawModuleInterface2
{
public:
	virtual ~ProjectileStreamDrawBase() {}
};

class W3DProjectileStreamResources
{
public:
	~W3DProjectileStreamResources();
};

class W3DProjectileStreamDraw : public ProjectileStreamDrawBase
{
public:
	virtual ~W3DProjectileStreamDraw();

private:
	unsigned char m_pad14[0x0c];
	W3DProjectileStreamResources m_resources;
};

W3DProjectileStreamDraw::~W3DProjectileStreamDraw()
{
}
