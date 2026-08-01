class VehicleCurveClass
{
public:
	struct _ArcInfoStruct
	{
	};
};

class HermiteSpline1DClass
{
public:
	struct TangentsClass
	{
	};
};

class HermiteSpline3DClass
{
public:
	struct TangentsClass
	{
	};
};

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
		_emit 0CDh
		_emit 077h
		_emit 066h
		_emit 000h
	}
}

template __declspec(naked) void VectorClass<VehicleCurveClass::_ArcInfoStruct>::Clear();
template __declspec(naked) void VectorClass<HermiteSpline1DClass::TangentsClass>::Clear();
template __declspec(naked) void VectorClass<HermiteSpline3DClass::TangentsClass>::Clear();
