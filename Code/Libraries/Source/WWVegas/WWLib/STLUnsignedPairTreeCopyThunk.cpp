namespace _STL
{
template<class First, class Second>
struct pair
{
};

template<class Value>
struct _Rb_tree_node
{
};

template<class T>
struct _Select1st
{
};

template<class T>
struct less
{
};

template<class T>
class allocator
{
};

template<class Key, class Value, class Select, class Less, class Alloc>
class _Rb_tree
{
	_Rb_tree_node<Value> *_M_copy(_Rb_tree_node<Value> *, _Rb_tree_node<Value> *);
	void _M_erase(_Rb_tree_node<Value> *);
};

template<class Key, class Value, class Select, class Less, class Alloc>
__declspec(naked) _Rb_tree_node<Value> *_Rb_tree<Key, Value, Select, Less, Alloc>::_M_copy(_Rb_tree_node<Value> *, _Rb_tree_node<Value> *)
{
	__asm {
		_emit 0E9h
		_emit 076h
		_emit 0BAh
		_emit 073h
		_emit 000h
	}
}
}

typedef _STL::pair<const unsigned short, unsigned char> UnsignedPair;
typedef _STL::_Rb_tree<unsigned short, UnsignedPair, _STL::_Select1st<UnsignedPair>, _STL::less<unsigned short>, _STL::allocator<UnsignedPair> > UnsignedTree;
template __declspec(naked) _STL::_Rb_tree_node<UnsignedPair> *UnsignedTree::_M_copy(_STL::_Rb_tree_node<UnsignedPair> *, _STL::_Rb_tree_node<UnsignedPair> *);

template<class Key, class Value, class Select, class Less, class Alloc>
__declspec(naked) void _STL::_Rb_tree<Key, Value, Select, Less, Alloc>::_M_erase(_STL::_Rb_tree_node<Value> *)
{
	__asm {
		_emit 0E9h
		_emit 0EFh
		_emit 0E2h
		_emit 071h
		_emit 000h
	}
}

template __declspec(naked) void UnsignedTree::_M_erase(_STL::_Rb_tree_node<UnsignedPair> *);
