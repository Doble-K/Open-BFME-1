struct VertexFormatXYZNDUV1;
class Vector3;
class Matrix3D;
class MeshClass;
class RenderObjClass;

template<class T>
class RefMultiListIterator;

class W3DBridge
{
protected:
	int getModelVertices(VertexFormatXYZNDUV1 *, int, float, Vector3 &, Vector3 &, Vector3 &, Vector3 &, const Matrix3D &, MeshClass *, RefMultiListIterator<RenderObjClass> *);
};

__declspec(naked) int W3DBridge::getModelVertices(VertexFormatXYZNDUV1 *, int, float, Vector3 &, Vector3 &, Vector3 &, Vector3 &, const Matrix3D &, MeshClass *, RefMultiListIterator<RenderObjClass> *)
{
	__asm {
		_emit 0E9h
		_emit 04Dh
		_emit 0CDh
		_emit 06Bh
		_emit 000h
	}
}
