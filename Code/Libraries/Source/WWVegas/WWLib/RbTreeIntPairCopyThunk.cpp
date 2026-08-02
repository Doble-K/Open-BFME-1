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

template <class Value>
struct _Select1st
{
};

template <class Type>
struct less
{
};

template <class Type>
class allocator
{
};

template <class Key, class Value, class KeyOfValue, class Compare, class Allocator>
class _Rb_tree
{
	_Rb_tree_node<Value> *_M_copy(_Rb_tree_node<Value> *, _Rb_tree_node<Value> *);
	void _M_erase(_Rb_tree_node<Value> *);
};

class IntPairTreeCopyShim
{
public:
	_Rb_tree_node<pair<int const, unsigned int> > *copy(
		_Rb_tree_node<pair<int const, unsigned int> > *x,
		_Rb_tree_node<pair<int const, unsigned int> > *p);
};

class IntPairTreeEraseShim
{
public:
	void erase(_Rb_tree_node<pair<int const, unsigned int> > *x);
};

template <class Key, class Value, class KeyOfValue, class Compare, class Allocator>
_Rb_tree_node<Value> *_Rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::_M_copy(
	_Rb_tree_node<Value> *x, _Rb_tree_node<Value> *p)
{
	return (_Rb_tree_node<Value> *)((IntPairTreeCopyShim *)this)->copy(
		(_Rb_tree_node<pair<int const, unsigned int> > *)x,
		(_Rb_tree_node<pair<int const, unsigned int> > *)p);
}

template <class Key, class Value, class KeyOfValue, class Compare, class Allocator>
void _Rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::_M_erase(_Rb_tree_node<Value> *x)
{
	((IntPairTreeEraseShim *)this)->erase((_Rb_tree_node<pair<int const, unsigned int> > *)x);
}

typedef pair<int const, unsigned int> IntPair;
template _Rb_tree_node<IntPair> *_Rb_tree<int, IntPair, _Select1st<IntPair>, less<int>, allocator<IntPair> >::_M_copy(_Rb_tree_node<IntPair> *, _Rb_tree_node<IntPair> *);
template void _Rb_tree<int, IntPair, _Select1st<IntPair>, less<int>, allocator<IntPair> >::_M_erase(_Rb_tree_node<IntPair> *);
}
