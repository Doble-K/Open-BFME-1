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

class PolyRenderTaskClass
{
};

class MatPassTaskClass
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

template<>
class ObjectPoolClass<PolyRenderTaskClass, 256>
{
public:
	void Free_Object_Memory(PolyRenderTaskClass *);
};

__declspec(naked) void ObjectPoolClass<PolyRenderTaskClass, 256>::Free_Object_Memory(PolyRenderTaskClass *)
{
	__asm {
		_emit 056h
		_emit 08Bh
		_emit 0F1h
		_emit 057h
		_emit 08Dh
		_emit 07Eh
		_emit 010h
		_emit 08Bh
		_emit 0CFh
		_emit 0E8h
		_emit 0FAh
		_emit 01Ch
		_emit 06Eh
		_emit 0FFh
		_emit 08Bh
		_emit 00Eh
		_emit 08Bh
		_emit 044h
		_emit 024h
		_emit 00Ch
		_emit 089h
		_emit 008h
		_emit 089h
		_emit 006h
		_emit 0FFh
		_emit 046h
		_emit 008h
		_emit 0C7h
		_emit 007h
		_emit 000h
		_emit 000h
		_emit 000h
		_emit 000h
		_emit 05Fh
		_emit 05Eh
		_emit 0C2h
		_emit 004h
		_emit 000h
	}
}

template<>
class ObjectPoolClass<MatPassTaskClass, 256>
{
public:
	void Free_Object_Memory(MatPassTaskClass *);
};

__declspec(naked) void ObjectPoolClass<MatPassTaskClass, 256>::Free_Object_Memory(MatPassTaskClass *)
{
	__asm {
		_emit 056h
		_emit 08Bh
		_emit 0F1h
		_emit 057h
		_emit 08Dh
		_emit 07Eh
		_emit 010h
		_emit 08Bh
		_emit 0CFh
		_emit 0E8h
		_emit 0EAh
		_emit 01Bh
		_emit 06Eh
		_emit 0FFh
		_emit 08Bh
		_emit 00Eh
		_emit 08Bh
		_emit 044h
		_emit 024h
		_emit 00Ch
		_emit 089h
		_emit 008h
		_emit 089h
		_emit 006h
		_emit 0FFh
		_emit 046h
		_emit 008h
		_emit 0C7h
		_emit 007h
		_emit 000h
		_emit 000h
		_emit 000h
		_emit 000h
		_emit 05Fh
		_emit 05Eh
		_emit 0C2h
		_emit 004h
		_emit 000h
	}
}
