class WeaponTemplateSet
{
};

template<int Bits>
class BitFlags
{
};

template<class Set, class Flags>
class SparseMatchFinder
{
public:
    struct MapHelper
    {
    };
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
    template<class SearchKey>
    _Rb_tree_node<Value> *_M_find(const SearchKey &) const;
};

template<class Key, class Value, class KeyOfValue, class Compare, class Alloc>
template<class SearchKey>
__declspec(naked) _Rb_tree_node<Value> *_Rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::_M_find(const SearchKey &) const
{
    __asm {
        _emit 0E9h
        _emit 000h
        _emit 0E5h
        _emit 00Fh
        _emit 000h
    }
}
}

typedef BitFlags<17> WeaponSetFlags;
typedef _STL::pair<const WeaponSetFlags, const WeaponTemplateSet *> WeaponTemplateSetPair;
typedef SparseMatchFinder<WeaponTemplateSet, WeaponSetFlags>::MapHelper WeaponTemplateSetMapHelper;
typedef _STL::_Rb_tree<const WeaponSetFlags, WeaponTemplateSetPair, _STL::_Select1st<WeaponTemplateSetPair>, WeaponTemplateSetMapHelper, _STL::allocator<WeaponTemplateSetPair> > WeaponTemplateSetTree;
template _STL::_Rb_tree_node<WeaponTemplateSetPair> *WeaponTemplateSetTree::_M_find<WeaponSetFlags>(const WeaponSetFlags &) const;
