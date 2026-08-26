// cl: /DNDEBUG /MD /EHsc

typedef bool Bool;

class WaterRenderObjClass
{
public:
	Bool worldToGridSpace(float worldX, float worldY, float &gridX, float &gridY);
	void getGridVertexHeight(int x, int y, float *height);
};

class W3DTerrainVisual
{
public:
	virtual Bool getWaterGridHeight(float worldX, float worldY, float *height);

private:
	unsigned char m_basePadding[0x0C];
	void *m_terrainRenderObject;
	WaterRenderObjClass *m_waterRenderObject;
	void *m_logicHeightMap;
	Bool m_isWaterGridRenderingEnabled;
};

Bool W3DTerrainVisual::getWaterGridHeight(float worldX, float worldY, float *height)
{
	float gridX;
	float gridY;
	if (m_isWaterGridRenderingEnabled) {
		WaterRenderObjClass *water = m_waterRenderObject;
		if (water && water->worldToGridSpace(worldX, worldY, gridX, gridY)) {
			water->getGridVertexHeight(static_cast<int>(gridX),
				static_cast<int>(gridY), height);
			return 1;
		}
	}
	return 0;
}
