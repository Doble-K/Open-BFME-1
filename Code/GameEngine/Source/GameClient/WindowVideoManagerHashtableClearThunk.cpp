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
    void clear();
};

template<class Value, class Key, class Hash, class Extract, class Equal, class Alloc>
__declspec(naked) void hashtable<Value, Key, Hash, Extract, Equal, Alloc>::clear()
{
    __asm {
        _emit 0E9h
        _emit 02Eh
        _emit 02Ch
        _emit 045h
        _emit 000h
    }
}
}

typedef const GameWindow * GameWindowKey;
typedef _STL::pair<const GameWindowKey, WindowVideo *> GameWindowVideoPair;
typedef _STL::hashtable<GameWindowVideoPair, GameWindowKey, WindowVideoManager::hashConstGameWindowPtr, _STL::_Select1st<GameWindowVideoPair>, _STL::equal_to<GameWindowKey>, _STL::allocator<GameWindowVideoPair> > GameWindowVideoHashtable;
template void GameWindowVideoHashtable::clear();
