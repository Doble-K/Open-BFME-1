template<class Type>
class VectorClass
{
public:
	virtual void Clear();
};

template<class Type>
__declspec(naked) void VectorClass<Type>::Clear()
{
	__asm {
		_emit 0E9h
		_emit 0C4h
		_emit 02Dh
		_emit 040h
		_emit 000h
	}
}

template __declspec(naked) void VectorClass<float>::Clear();
