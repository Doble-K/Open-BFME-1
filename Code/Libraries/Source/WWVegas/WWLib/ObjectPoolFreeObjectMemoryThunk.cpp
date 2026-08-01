class AABTreeLinkClass
{
};

class AABTreeNodeClass
{
};

class CameraShakeSystemClass
{
public:
	class CameraShakerClass
	{
	};
};

class GenericSLNode
{
};

template<class Type, int BlockSize>
class ObjectPoolClass
{
public:
	Type * Allocate_Object_Memory();
	void Free_Object_Memory(Type *);
};

template<class Type, int BlockSize>
__declspec(naked) Type * ObjectPoolClass<Type, BlockSize>::Allocate_Object_Memory()
{
	__asm {
		_emit 0E9h
		_emit 068h
		_emit 0EDh
		_emit 06Ch
		_emit 000h
	}
}

template<class Type, int BlockSize>
__declspec(naked) void ObjectPoolClass<Type, BlockSize>::Free_Object_Memory(Type *)
{
	__asm {
		_emit 0E9h
		_emit 078h
		_emit 003h
		_emit 06Ch
		_emit 000h
	}
}

template __declspec(naked) void ObjectPoolClass<AABTreeLinkClass, 256>::Free_Object_Memory(AABTreeLinkClass *);
template __declspec(naked) void ObjectPoolClass<AABTreeNodeClass, 256>::Free_Object_Memory(AABTreeNodeClass *);
template __declspec(naked) void ObjectPoolClass<CameraShakeSystemClass::CameraShakerClass, 256>::Free_Object_Memory(CameraShakeSystemClass::CameraShakerClass *);
template __declspec(naked) void ObjectPoolClass<GenericSLNode, 256>::Free_Object_Memory(GenericSLNode *);
template __declspec(naked) CameraShakeSystemClass::CameraShakerClass * ObjectPoolClass<CameraShakeSystemClass::CameraShakerClass, 256>::Allocate_Object_Memory();
