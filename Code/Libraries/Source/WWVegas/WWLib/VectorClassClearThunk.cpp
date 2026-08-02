template<class Type>
class VectorClass
{
public:
    virtual void Clear();
};

class VectorClassClearShim
{
public:
    void run();
};

template<class Type>
void VectorClass<Type>::Clear()
{
    ((VectorClassClearShim *)this)->run();
}

template void VectorClass<float>::Clear();
