struct Coord3D;

class BezierSegment
{
public:
    void evaluateBezSegmentAtT(float, Coord3D *) const;
};

class BezierSegmentEvaluateShim
{
public:
    void evaluate(float t, Coord3D *out) const;
};

void BezierSegment::evaluateBezSegmentAtT(float t, Coord3D *out) const
{
    ((const BezierSegmentEvaluateShim *)this)->evaluate(t, out);
}
