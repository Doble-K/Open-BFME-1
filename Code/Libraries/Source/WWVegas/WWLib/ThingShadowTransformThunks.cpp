class Matrix3D
{
};

class Thing
{
public:
	void setOrientation(float);
	void setTransformMatrix(Matrix3D const *);
};

class Shadow
{
public:
	void setSize(float, float);
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

class ShadowSetSizeShim
{
public:
	void setSize(float a0, float a1);
};

void Thing::setOrientation(float a0)
{
	((ThingSetOrientationShim *)this)->setOrientation(a0);
}

void Thing::setTransformMatrix(Matrix3D const *a0)
{
	((ThingSetTransformMatrixShim *)this)->setTransformMatrix(a0);
}

void Shadow::setSize(float a0, float a1)
{
	((ShadowSetSizeShim *)this)->setSize(a0, a1);
}
