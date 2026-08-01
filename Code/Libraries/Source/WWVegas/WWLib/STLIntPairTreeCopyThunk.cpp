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
		_emit 0B8h
		_emit 080h
		_emit 006h
		_emit 000h
	}
}
}

typedef _STL::pair<const int, unsigned int> IntPair;
typedef _STL::_Rb_tree<int, IntPair, _STL::_Select1st<IntPair>, _STL::less<int>, _STL::allocator<IntPair> > IntTree;
template __declspec(naked) _STL::_Rb_tree_node<IntPair> *IntTree::_M_copy(_STL::_Rb_tree_node<IntPair> *, _STL::_Rb_tree_node<IntPair> *);

template<class Key, class Value, class Select, class Less, class Alloc>
__declspec(naked) void _STL::_Rb_tree<Key, Value, Select, Less, Alloc>::_M_erase(_STL::_Rb_tree_node<Value> *)
{
	__asm {
		_emit 0E9h
		_emit 02Dh
		_emit 01Fh
		_emit 006h
		_emit 000h
	}
}

template __declspec(naked) void IntTree::_M_erase(_STL::_Rb_tree_node<IntPair> *);
