struct Coord3D;
class Matrix3D;

class FXList
{
protected:
	void doFXPos(const Coord3D *, const Matrix3D *, float, const Coord3D *, float) const;
};

class FXListDoFXPosShim
{
public:
	void run(const Coord3D *, const Matrix3D *, float, const Coord3D *, float) const;
};

void FXList::doFXPos(const Coord3D *pos, const Matrix3D *mtx, float scale, const Coord3D *dir, float speed) const
{
	((const FXListDoFXPosShim *)this)->run(pos, mtx, scale, dir, speed);
}
