struct Coord3D;

class BezierSegment
{
public:
	void evaluateBezSegmentAtT(float, Coord3D *) const;
};

__declspec(naked) void BezierSegment::evaluateBezSegmentAtT(float, Coord3D *) const
{
	__asm {
		_emit 0E9h
		_emit 0AEh
		_emit 00Fh
		_emit 00Bh
		_emit 000h
	}
}
