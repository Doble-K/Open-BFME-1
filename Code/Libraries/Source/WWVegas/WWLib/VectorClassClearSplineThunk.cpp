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

class VectorClassClearSplineShim
{
public:
    void run();
};

template<class Type>
void VectorClass<Type>::Clear()
{
    ((VectorClassClearSplineShim *)this)->run();
}

template void VectorClass<VehicleCurveClass::_ArcInfoStruct>::Clear();
template void VectorClass<HermiteSpline1DClass::TangentsClass>::Clear();
template void VectorClass<HermiteSpline3DClass::TangentsClass>::Clear();
