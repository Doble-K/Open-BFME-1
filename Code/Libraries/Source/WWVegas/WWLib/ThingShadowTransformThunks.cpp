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

__declspec(naked) void Thing::setOrientation(float)
{
	__asm {
		_emit 0E9h
		_emit 096h
		_emit 094h
		_emit 00Fh
		_emit 000h
	}
}

__declspec(naked) void Thing::setTransformMatrix(Matrix3D const *)
{
	__asm {
		_emit 0E9h
		_emit 052h
		_emit 0D9h
		_emit 019h
		_emit 000h
	}
}

__declspec(naked) void Shadow::setSize(float, float)
{
	__asm {
		_emit 0E9h
		_emit 00Fh
		_emit 02Fh
		_emit 01Ch
		_emit 000h
	}
}
