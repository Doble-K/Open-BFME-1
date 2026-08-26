// cl: /DNDEBUG /MD /EHsc

enum ObjectID
{
	INVALID_OBJECT_ID = 0
};

class Object
{
public:
	ObjectID getID() const { return m_id; }

private:
	unsigned char m_padding[0x74];
	ObjectID m_id;
};

class BaseHeightMapRenderObjClass
{
public:
	void removeTerrainBib(ObjectID id);
};

class W3DTerrainVisual
{
public:
	virtual void removeFactionBib(Object *factionBuilding);

private:
	unsigned char m_basePadding[0x0C];
	BaseHeightMapRenderObjClass *m_terrainRenderObject;
	void *m_waterRenderObject;
	void *m_logicHeightMap;
};

void W3DTerrainVisual::removeFactionBib(Object *factionBuilding)
{
	if (m_logicHeightMap) {
		m_terrainRenderObject->removeTerrainBib(factionBuilding->getID());
	}
}
