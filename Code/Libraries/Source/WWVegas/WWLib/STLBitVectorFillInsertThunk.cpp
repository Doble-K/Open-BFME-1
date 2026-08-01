namespace _STL
{
struct _Bit_reference
{
};

template<class Reference, class Pointer>
struct _Bit_iter
{
};

template<class T>
class allocator
{
};

template<class T, class Alloc>
class vector
{
protected:
	void _M_initialize(unsigned);
	void _M_insert_aux(_Bit_iter<_Bit_reference, _Bit_reference *> , bool);

public:
	void _M_fill_insert(_Bit_iter<_Bit_reference, _Bit_reference *> , unsigned, bool);
};

template<class T, class Alloc>
__declspec(naked) void vector<T, Alloc>::_M_fill_insert(_Bit_iter<_Bit_reference, _Bit_reference *> , unsigned, bool)
{
	__asm {
		_emit 0E9h
		_emit 01Dh
		_emit 03Ah
		_emit 02Ch
		_emit 000h
	}
}
}

typedef _STL::vector<bool, _STL::allocator<bool> > BitVector;
template __declspec(naked) void BitVector::_M_fill_insert(_STL::_Bit_iter<_STL::_Bit_reference, _STL::_Bit_reference *> , unsigned, bool);

namespace _STL
{
template<class T, class Alloc>
__declspec(naked) void vector<T, Alloc>::_M_initialize(unsigned)
{
	__asm {
		_emit 0E9h
		_emit 01Ah
		_emit 0BAh
		_emit 04Eh
		_emit 000h
	}
}
}

template __declspec(naked) void BitVector::_M_initialize(unsigned);

namespace _STL
{
template<class T, class Alloc>
__declspec(naked) void vector<T, Alloc>::_M_insert_aux(_Bit_iter<_Bit_reference, _Bit_reference *> , bool)
{
	__asm {
		_emit 0E9h
		_emit 0D0h
		_emit 0F3h
		_emit 029h
		_emit 000h
	}
}
}

template __declspec(naked) void BitVector::_M_insert_aux(_STL::_Bit_iter<_STL::_Bit_reference, _STL::_Bit_reference *> , bool);
