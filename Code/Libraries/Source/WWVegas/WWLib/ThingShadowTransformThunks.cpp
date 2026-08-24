class Matrix3D
{
};

class Thing
{
public:
	void setOrientation(float);
	void setTransformMatrix(Matrix3D const *);
};

class ThingSetOrientationShim
{
public:
	void setOrientation(float a0);
};

class ThingSetTransformMatrixShim
{
public:
	void setTransformMatrix(Matrix3D const *a0);
};

void Thing::setOrientation(float a0)
{
	((ThingSetOrientationShim *)this)->setOrientation(a0);
}

void Thing::setTransformMatrix(Matrix3D const *a0)
{
	((ThingSetTransformMatrixShim *)this)->setTransformMatrix(a0);
}
