class AsciiString
{
};
struct Coord3D
{
};

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

class AsciiCoordTreeCopyShim
{
public:
	_Rb_tree_node<pair<const AsciiString, Coord3D> > *copy(
		_Rb_tree_node<pair<const AsciiString, Coord3D> > *x,
		_Rb_tree_node<pair<const AsciiString, Coord3D> > *p);
};

template <class Key, class Value, class Select, class Less, class Alloc>
_Rb_tree_node<Value> *_Rb_tree<Key, Value, Select, Less, Alloc>::_M_copy(
	_Rb_tree_node<Value> *x, _Rb_tree_node<Value> *p)
{
	return (_Rb_tree_node<Value> *)((AsciiCoordTreeCopyShim *)this)->copy(
		(_Rb_tree_node<pair<const AsciiString, Coord3D> > *)x,
		(_Rb_tree_node<pair<const AsciiString, Coord3D> > *)p);
}
}

typedef _STL::pair<const AsciiString, Coord3D> AsciiCoordPair;
typedef _STL::_Rb_tree<AsciiString, AsciiCoordPair, _STL::_Select1st<AsciiCoordPair>, _STL::less<AsciiString>, _STL::allocator<AsciiCoordPair> > AsciiCoordTree;
template _STL::_Rb_tree_node<AsciiCoordPair> *AsciiCoordTree::_M_copy(_STL::_Rb_tree_node<AsciiCoordPair> *, _STL::_Rb_tree_node<AsciiCoordPair> *);
