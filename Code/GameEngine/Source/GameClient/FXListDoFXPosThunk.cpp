struct Coord3D;
class Matrix3D;

class FXList
{
protected:
	void doFXPos(const Coord3D *, const Matrix3D *, float, const Coord3D *, float) const;
};

__declspec(naked) void FXList::doFXPos(const Coord3D *, const Matrix3D *, float, const Coord3D *, float) const
{
	__asm {
		_emit 0E9h
		_emit 00Bh
		_emit 084h
		_emit 019h
		_emit 000h
	}
}
