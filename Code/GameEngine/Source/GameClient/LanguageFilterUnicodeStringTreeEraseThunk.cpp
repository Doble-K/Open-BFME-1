class UnicodeString
{
};

struct UnicodeStringLessThan
{
};

namespace _STL
{
template<class First, class Second>
struct pair
{
};

template<class T>
struct _Select1st
{
};

template<class T>
class allocator
{
};

template<class T>
struct _Rb_tree_node
{
};

template<class Key, class Value, class KeyOfValue, class Compare, class Alloc>
class _Rb_tree
{
    void _M_erase(_Rb_tree_node<Value> *);
};

template<class Key, class Value, class KeyOfValue, class Compare, class Alloc>
__declspec(naked) void _Rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::_M_erase(_Rb_tree_node<Value> *)
{
    __asm {
        _emit 0E9h
        _emit 0B7h
        _emit 04Bh
        _emit 044h
        _emit 000h
    }
}
}

typedef _STL::pair<const UnicodeString, bool> UnicodeStringBoolPair;
typedef _STL::_Rb_tree<UnicodeString, UnicodeStringBoolPair, _STL::_Select1st<UnicodeStringBoolPair>, UnicodeStringLessThan, _STL::allocator<UnicodeStringBoolPair> > UnicodeStringTree;
template void UnicodeStringTree::_M_erase(_STL::_Rb_tree_node<UnicodeStringBoolPair> *);
