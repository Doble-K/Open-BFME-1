class AsciiString
{
};
struct Coord3D
{
};

namespace _STL
{
template<class First, class Second> struct pair { };
template<class Value> struct _Rb_tree_node_base { };
template<class Value> struct _Nonconst_traits { };
template<class Value, class Traits> struct _Rb_tree_iterator { };
template<class T> struct _Select1st { };
template<class T> struct less { };
template<class T> class allocator { };

template<class Key, class Value, class Select, class Less, class Alloc>
class _Rb_tree
{
    _Rb_tree_iterator<Value, _Nonconst_traits<Value> > _M_insert(_Rb_tree_node_base<Value> *, _Rb_tree_node_base<Value> *, Value const &, _Rb_tree_node_base<Value> *);
};

template<class Key, class Value, class Select, class Less, class Alloc>
__declspec(naked) _Rb_tree_iterator<Value, _Nonconst_traits<Value> > _Rb_tree<Key, Value, Select, Less, Alloc>::_M_insert(_Rb_tree_node_base<Value> *, _Rb_tree_node_base<Value> *, Value const &, _Rb_tree_node_base<Value> *)
{
    __asm {
        _emit 0E9h
        _emit 029h
        _emit 03Dh
        _emit 064h
        _emit 000h
    }
}
}

typedef _STL::pair<const AsciiString, Coord3D> AsciiCoordPair;
typedef _STL::_Rb_tree<AsciiString, AsciiCoordPair, _STL::_Select1st<AsciiCoordPair>, _STL::less<AsciiString>, _STL::allocator<AsciiCoordPair> > AsciiCoordTree;
template _STL::_Rb_tree_iterator<AsciiCoordPair, _STL::_Nonconst_traits<AsciiCoordPair> > AsciiCoordTree::_M_insert(_STL::_Rb_tree_node_base<AsciiCoordPair> *, _STL::_Rb_tree_node_base<AsciiCoordPair> *, AsciiCoordPair const &, _STL::_Rb_tree_node_base<AsciiCoordPair> *);
