class AsciiString
{
};

namespace _STL
{
template <class T>
struct _Identity
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

template <class Value>
struct _Rb_tree_node
{
};

template <class Key, class Value, class Select, class Less, class Alloc>
class _Rb_tree
{
	_Rb_tree_node<Value> *_M_lower_bound(const Key &) const;
	_Rb_tree_node<Value> *_M_upper_bound(const Key &) const;
};

class AsciiStringTreeLowerBoundShim
{
public:
	_Rb_tree_node<AsciiString> *lower_bound(const AsciiString &k) const;
};

class AsciiStringTreeUpperBoundShim
{
public:
	_Rb_tree_node<AsciiString> *upper_bound(const AsciiString &k) const;
};

template <class Key, class Value, class Select, class Less, class Alloc>
_Rb_tree_node<Value> *_Rb_tree<Key, Value, Select, Less, Alloc>::_M_lower_bound(const Key &k) const
{
	return (_Rb_tree_node<Value> *)((AsciiStringTreeLowerBoundShim const *)this)->lower_bound((const AsciiString &)k);
}

template <class Key, class Value, class Select, class Less, class Alloc>
_Rb_tree_node<Value> *_Rb_tree<Key, Value, Select, Less, Alloc>::_M_upper_bound(const Key &k) const
{
	return (_Rb_tree_node<Value> *)((AsciiStringTreeUpperBoundShim const *)this)->upper_bound((const AsciiString &)k);
}
}

typedef _STL::_Rb_tree<AsciiString, AsciiString, _STL::_Identity<AsciiString>, _STL::less<AsciiString>, _STL::allocator<AsciiString> > AsciiTree;
template _STL::_Rb_tree_node<AsciiString> *AsciiTree::_M_lower_bound(const AsciiString &) const;
template _STL::_Rb_tree_node<AsciiString> *AsciiTree::_M_upper_bound(const AsciiString &) const;
