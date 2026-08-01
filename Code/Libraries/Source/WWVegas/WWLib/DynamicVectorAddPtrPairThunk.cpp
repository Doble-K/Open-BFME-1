class PointerRemapClass
{
public:
	struct PtrPairStruct
	{
	};
};

template<class Type>
class DynamicVectorClass
{
public:
	bool Add(Type const &);
};

template<class Type>
__declspec(naked) bool DynamicVectorClass<Type>::Add(Type const &)
{
	__asm {
		_emit 0E9h
		_emit 0A5h
		_emit 0E0h
		_emit 00Ch
		_emit 000h
	}
}

template __declspec(naked) bool DynamicVectorClass<PointerRemapClass::PtrPairStruct>::Add(const PointerRemapClass::PtrPairStruct &);
