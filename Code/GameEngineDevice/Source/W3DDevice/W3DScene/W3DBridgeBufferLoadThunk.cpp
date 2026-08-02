class RenderObjClass
{
};

template <class T>
class RefMultiListIterator
{
};

class W3DBridgeBuffer
{
protected:
	void loadBridgesInVertexAndIndexBuffers(RefMultiListIterator<RenderObjClass> *);
};

class W3DBridgeBufferLoadBridgesShim
{
public:
	void loadBridgesInVertexAndIndexBuffers(RefMultiListIterator<RenderObjClass> *);
};

void W3DBridgeBuffer::loadBridgesInVertexAndIndexBuffers(RefMultiListIterator<RenderObjClass> *iterator)
{
	((W3DBridgeBufferLoadBridgesShim *)this)->loadBridgesInVertexAndIndexBuffers(iterator);
}
