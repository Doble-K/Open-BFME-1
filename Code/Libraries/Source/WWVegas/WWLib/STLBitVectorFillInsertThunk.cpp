namespace _STL
{
struct _Bit_reference
{
};

template <class Reference, class Pointer>
struct _Bit_iter
{
};

template <class T>
class allocator
{
};

template <class T, class Alloc>
class vector
{
protected:
	void _M_initialize(unsigned);
	void _M_insert_aux(_Bit_iter<_Bit_reference, _Bit_reference *>, bool);
public:
	void _M_fill_insert(_Bit_iter<_Bit_reference, _Bit_reference *>, unsigned, bool);
};

class BitVectorFillInsertShim
{
public:
	void fill_insert(_Bit_iter<_Bit_reference, _Bit_reference *> pos, unsigned n, bool x);
};

class BitVectorInitializeShim
{
public:
	void initialize(unsigned n);
};

class BitVectorInsertAuxShim
{
public:
	void insert_aux(_Bit_iter<_Bit_reference, _Bit_reference *> pos, bool x);
};

template <class T, class Alloc>
void vector<T, Alloc>::_M_fill_insert(_Bit_iter<_Bit_reference, _Bit_reference *> pos, unsigned n, bool x)
{
	((BitVectorFillInsertShim *)this)->fill_insert(pos, n, x);
}

template <class T, class Alloc>
void vector<T, Alloc>::_M_initialize(unsigned n)
{
	((BitVectorInitializeShim *)this)->initialize(n);
}

template <class T, class Alloc>
void vector<T, Alloc>::_M_insert_aux(_Bit_iter<_Bit_reference, _Bit_reference *> pos, bool x)
{
	((BitVectorInsertAuxShim *)this)->insert_aux(pos, x);
}
}

typedef _STL::vector<bool, _STL::allocator<bool> > BitVector;
template void BitVector::_M_fill_insert(_STL::_Bit_iter<_STL::_Bit_reference, _STL::_Bit_reference *>, unsigned, bool);
template void BitVector::_M_initialize(unsigned);
template void BitVector::_M_insert_aux(_STL::_Bit_iter<_STL::_Bit_reference, _STL::_Bit_reference *>, bool);
