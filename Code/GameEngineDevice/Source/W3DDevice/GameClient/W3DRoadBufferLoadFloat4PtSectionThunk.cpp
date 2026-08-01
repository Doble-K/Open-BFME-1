class RoadSegment;
class Vector2
{
};

class W3DRoadBuffer
{
protected:
	void loadFloat4PtSection(RoadSegment *, Vector2, Vector2, Vector2, Vector2 *, float, float, float, float);
};

__declspec(naked) void W3DRoadBuffer::loadFloat4PtSection(RoadSegment *, Vector2, Vector2, Vector2, Vector2 *, float, float, float, float)
{
	__asm {
		_emit 0E9h
		_emit 03Ch
		_emit 03Ch
		_emit 06Dh
		_emit 000h
	}
}
