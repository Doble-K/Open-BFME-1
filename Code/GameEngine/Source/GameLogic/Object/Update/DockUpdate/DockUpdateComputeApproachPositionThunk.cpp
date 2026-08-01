struct Coord3D
{
};

class Object
{
};

class DockUpdate
{
protected:
	Coord3D computeApproachPosition(int, Object *);
};

__declspec(naked) Coord3D DockUpdate::computeApproachPosition(int, Object *)
{
	__asm {
		_emit 0E9h
		_emit 073h
		_emit 0DFh
		_emit 02Ah
		_emit 000h
	}
}
