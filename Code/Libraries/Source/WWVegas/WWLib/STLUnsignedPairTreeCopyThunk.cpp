namespace _STL
{
template <class First, class Second>
struct pair
{
};

template <class Value>
struct _Rb_tree_node
{
};

template <class T>
struct _Select1st
{
};

template <class T>
struct less
{
};

template <class T>
class allocator
{
};

template <class Key, class Value, class Select, class Less, class Alloc>
class _Rb_tree
{
	_Rb_tree_node<Value> *_M_copy(_Rb_tree_node<Value> *, _Rb_tree_node<Value> *);
};

class UnsignedPairTreeCopyShim
{
public:
	_Rb_tree_node<pair<const unsigned short, unsigned char> > *copy(
		_Rb_tree_node<pair<const unsigned short, unsigned char> > *x,
		_Rb_tree_node<pair<const unsigned short, unsigned char> > *p);
};

template <class Key, class Value, class Select, class Less, class Alloc>
_Rb_tree_node<Value> *_Rb_tree<Key, Value, Select, Less, Alloc>::_M_copy(
	_Rb_tree_node<Value> *x, _Rb_tree_node<Value> *p)
{
	return (_Rb_tree_node<Value> *)((UnsignedPairTreeCopyShim *)this)->copy(
		(_Rb_tree_node<pair<const unsigned short, unsigned char> > *)x,
		(_Rb_tree_node<pair<const unsigned short, unsigned char> > *)p);
}
}

typedef _STL::pair<const unsigned short, unsigned char> UnsignedPair;
typedef _STL::_Rb_tree<unsigned short, UnsignedPair, _STL::_Select1st<UnsignedPair>, _STL::less<unsigned short>, _STL::allocator<UnsignedPair> > UnsignedTree;
template _STL::_Rb_tree_node<UnsignedPair> *UnsignedTree::_M_copy(_STL::_Rb_tree_node<UnsignedPair> *, _STL::_Rb_tree_node<UnsignedPair> *);
