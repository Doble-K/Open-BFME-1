// cl: /DNDEBUG /MD /EHsc

class BaseHeightMapResetShroud
{
public:
	void setBorderShroudLevel30B8(unsigned char level);
	void setBorderShroudLevel30BC(unsigned char level);
};

class BaseHeightMapRenderObjClass
{
private:
	unsigned char m_unmodelled_00[0x30b8];
	BaseHeightMapResetShroud *m_shroud;
	BaseHeightMapResetShroud *m_shroud30BC;

public:
	BaseHeightMapResetShroud *getShroud() const
	{
		return m_shroud;
	}

	BaseHeightMapResetShroud *getShroud30BC() const
	{
		return m_shroud30BC;
	}
};

extern BaseHeightMapRenderObjClass *TheTerrainRenderObject;

class W3DDisplay
{
public:
	virtual void setBorderShroudLevel(unsigned char level);
	virtual void setBorderShroudLevel30BC(unsigned char level);
};

// ?setBorderShroudLevel@W3DDisplay@@UAEXE@Z
void W3DDisplay::setBorderShroudLevel(unsigned char level)
{
	if (TheTerrainRenderObject && TheTerrainRenderObject->getShroud()) {
		TheTerrainRenderObject->getShroud()->setBorderShroudLevel30B8(level);
	}
}

// ?setBorderShroudLevel30BC@W3DDisplay@@UAEXE@Z
void W3DDisplay::setBorderShroudLevel30BC(unsigned char level)
{
	if (TheTerrainRenderObject && TheTerrainRenderObject->getShroud30BC()) {
		TheTerrainRenderObject->getShroud30BC()->setBorderShroudLevel30BC(level);
	}
}
