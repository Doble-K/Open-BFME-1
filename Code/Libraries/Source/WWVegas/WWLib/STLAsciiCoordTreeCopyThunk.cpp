class AsciiString
{
};
struct Coord3D
{
};

namespace _STL
{
template<class First, class Second> struct pair { };
template<class Value> struct _Rb_tree_node { };
template<class T> struct _Select1st { };
template<class T> struct less { };
template<class T> class allocator { };

template<class Key, class Value, class Select, class Less, class Alloc>
class _Rb_tree
{
	_Rb_tree_node<Value> *_M_copy(_Rb_tree_node<Value> *, _Rb_tree_node<Value> *);
};

template<class Key, class Value, class Select, class Less, class Alloc>
__declspec(naked) _Rb_tree_node<Value> *_Rb_tree<Key, Value, Select, Less, Alloc>::_M_copy(_Rb_tree_node<Value> *, _Rb_tree_node<Value> *)
{
	__asm {
		_emit 0E9h
		_emit 0EDh
		_emit 01Dh
		_emit 009h
		_emit 000h
	}
}
}

typedef _STL::pair<const AsciiString, Coord3D> AsciiCoordPair;
typedef _STL::_Rb_tree<AsciiString, AsciiCoordPair, _STL::_Select1st<AsciiCoordPair>, _STL::less<AsciiString>, _STL::allocator<AsciiCoordPair> > AsciiCoordTree;
template __declspec(naked) _STL::_Rb_tree_node<AsciiCoordPair> *AsciiCoordTree::_M_copy(_STL::_Rb_tree_node<AsciiCoordPair> *, _STL::_Rb_tree_node<AsciiCoordPair> *);
