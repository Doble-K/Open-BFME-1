class RenderObjClass;

template<class T>
class RefMultiListIterator;

class W3DBridgeBuffer
{
protected:
	void loadBridgesInVertexAndIndexBuffers(RefMultiListIterator<RenderObjClass> *);
};

__declspec(naked) void W3DBridgeBuffer::loadBridgesInVertexAndIndexBuffers(RefMultiListIterator<RenderObjClass> *)
{
	__asm {
		_emit 0E9h
		_emit 060h
		_emit 037h
		_emit 06Ah
		_emit 000h
	}
}
