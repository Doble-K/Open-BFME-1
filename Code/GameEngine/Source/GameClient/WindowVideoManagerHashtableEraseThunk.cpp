class GameWindow
{
};

class WindowVideo
{
};

namespace WindowVideoManager
{
struct hashConstGameWindowPtr
{
};
}

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
struct _Const_traits
{
};

template<class Value, class Traits>
struct _Ht_iterator
{
};

template<class T>
struct equal_to
{
};

template<class T>
class allocator
{
};

template<class Value, class Key, class Hash, class Extract, class Equal, class Alloc>
class hashtable
{
public:
    void erase(const _Ht_iterator<Value, _Const_traits<Value> > &);
};

template<class Value, class Key, class Hash, class Extract, class Equal, class Alloc>
__declspec(naked) void hashtable<Value, Key, Hash, Extract, Equal, Alloc>::erase(const _Ht_iterator<Value, _Const_traits<Value> > &)
{
    __asm {
        _emit 0E9h
        _emit 0F3h
        _emit 08Eh
        _emit 045h
        _emit 000h
    }
}
}

typedef const GameWindow * GameWindowKey;
typedef _STL::pair<const GameWindowKey, WindowVideo *> GameWindowVideoPair;
typedef _STL::hashtable<GameWindowVideoPair, GameWindowKey, WindowVideoManager::hashConstGameWindowPtr, _STL::_Select1st<GameWindowVideoPair>, _STL::equal_to<GameWindowKey>, _STL::allocator<GameWindowVideoPair> > GameWindowVideoHashtable;
template void GameWindowVideoHashtable::erase(const _STL::_Ht_iterator<GameWindowVideoPair, _STL::_Const_traits<GameWindowVideoPair> > &);
