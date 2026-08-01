class CameraClass
{
};

class BaseHeightMapRenderObjClass
{
public:
	void renderTrees(CameraClass *);
};

__declspec(naked) void BaseHeightMapRenderObjClass::renderTrees(CameraClass *)
{
	__asm {
		_emit 0E9h
		_emit 055h
		_emit 0DBh
		_emit 068h
		_emit 000h
	}
}
