class GameSpyStagingRoom
{
};
struct GameSortStruct
{
};

namespace _STL
{
struct _Rb_tree_node_base { };
template<class Value> struct _Nonconst_traits { };
template<class Value, class Traits> struct _Rb_tree_iterator { };
template<class T> struct _Identity { };
template<class T> class allocator { };

template<class Key, class Value, class Identity, class Compare, class Alloc>
class _Rb_tree
{
    _Rb_tree_iterator<Value, _Nonconst_traits<Value> > _M_insert(_Rb_tree_node_base *, _Rb_tree_node_base *, Value const &, Value);
};

template<class Key, class Value, class Identity, class Compare, class Alloc>
__declspec(naked) _Rb_tree_iterator<Value, _Nonconst_traits<Value> > _Rb_tree<Key, Value, Identity, Compare, Alloc>::_M_insert(_Rb_tree_node_base *, _Rb_tree_node_base *, Value const &, Value)
{
    __asm {
        _emit 0E9h
        _emit 094h
        _emit 0F8h
        _emit 052h
        _emit 000h
    }
}
}

typedef _STL::_Rb_tree<GameSpyStagingRoom *, GameSpyStagingRoom *, _STL::_Identity<GameSpyStagingRoom *>, GameSortStruct, _STL::allocator<GameSpyStagingRoom *> > GameSpyStagingRoomTree;
template _STL::_Rb_tree_iterator<GameSpyStagingRoom *, _STL::_Nonconst_traits<GameSpyStagingRoom *> > GameSpyStagingRoomTree::_M_insert(_STL::_Rb_tree_node_base *, _STL::_Rb_tree_node_base *, GameSpyStagingRoom *const &, GameSpyStagingRoom *);
