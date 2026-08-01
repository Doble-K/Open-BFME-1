enum NameKeyType
{
};

namespace _STL
{
template<class First, class Second> struct pair { };
struct _Rb_tree_node_base { };
template<class Value> struct _Nonconst_traits { };
template<class Value, class Traits> struct _Rb_tree_iterator { };
template<class T> struct _Select1st { };
template<class T> struct less { };
template<class T> class allocator { };

template<class Key, class Value, class Select, class Less, class Alloc>
class _Rb_tree
{
    _Rb_tree_iterator<Value, _Nonconst_traits<Value> > insert_unique(_Rb_tree_node_base *, Value const &);
};

template<class Key, class Value, class Select, class Less, class Alloc>
__declspec(naked) _Rb_tree_iterator<Value, _Nonconst_traits<Value> > _Rb_tree<Key, Value, Select, Less, Alloc>::insert_unique(_Rb_tree_node_base *, Value const &)
{
    __asm {
        _emit 0E9h
        _emit 099h
        _emit 01Eh
        _emit 011h
        _emit 000h
    }
}
}

typedef _STL::pair<const NameKeyType, float> NameKeyFloatPair;
typedef _STL::_Rb_tree<NameKeyType, NameKeyFloatPair, _STL::_Select1st<NameKeyFloatPair>, _STL::less<NameKeyType>, _STL::allocator<NameKeyFloatPair> > NameKeyFloatTree;
template _STL::_Rb_tree_iterator<NameKeyFloatPair, _STL::_Nonconst_traits<NameKeyFloatPair> > NameKeyFloatTree::insert_unique(_STL::_Rb_tree_node_base *, NameKeyFloatPair const &);
