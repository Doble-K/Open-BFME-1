// The Free_Object_Memory bodies this TU used to carry now live in
// ObjectPoolFreeObjectMemory.cpp as the real mempool.h template: the four
// names that shared 0x006D1480, plus the PolyRenderTaskClass and
// MatPassTaskClass copies at 0x009452A0 and 0x009453B0. Only the allocation
// thunk is left here.

class CameraShakeSystemClass
{
public:
	class CameraShakerClass
	{
	};
};

template<class Type, int BlockSize>
class ObjectPoolClass
{
public:
	Type * Allocate_Object_Memory();
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

template __declspec(naked) CameraShakeSystemClass::CameraShakerClass * ObjectPoolClass<CameraShakeSystemClass::CameraShakerClass, 256>::Allocate_Object_Memory();
