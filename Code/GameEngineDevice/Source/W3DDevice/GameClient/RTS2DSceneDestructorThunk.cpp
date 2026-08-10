// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: convert the retail RTS2DScene destructor to clean C++.

class RefCountClass
{
public:
	void Release_Ref(void)
	{
		NumRefs--;
		if (NumRefs == 0)
		{
			Delete_This();
		}
	}

protected:
	virtual void Delete_This(void);
	int NumRefs;
};

class RenderObjClass : public RefCountClass
{
};

class SimpleSceneClass
{
public:
	virtual ~SimpleSceneClass();
	virtual void Remove_Render_Object(RenderObjClass *obj);

private:
	unsigned char m_pad[0x104];
};

class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();

private:
	unsigned char m_pad[4];
};

class RTS2DScene : public SimpleSceneClass, public SubsystemInterface
{
public:
	virtual ~RTS2DScene();

private:
	RenderObjClass *m_status;
	void *m_camera;
};

// ??1RTS2DScene@@UAE@XZ
RTS2DScene::~RTS2DScene()
{
	Remove_Render_Object(m_status);
	if (m_status)
	{
		m_status->Release_Ref();
		m_status = 0;
	}
}
