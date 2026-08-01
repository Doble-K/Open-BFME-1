class GameWindow
{
};
class WindowVideo
{
};
class WindowVideoManager
{
public:
    struct hashConstGameWindowPtr
    {
    };
};

namespace _STL
{
template<class First, class Second> struct pair { };
template<class T> struct _Select1st { };
template<class T> struct equal_to { };
template<class T> class allocator { };

template<class Value, class Key, class Hash, class Select, class Equal, class Alloc>
class hashtable
{
    void clear();
};

template<class Value, class Key, class Hash, class Select, class Equal, class Alloc>
__declspec(naked) void hashtable<Value, Key, Hash, Select, Equal, Alloc>::clear()
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

typedef _STL::pair<const GameWindow *, WindowVideo *> GameWindowVideoPair;
typedef _STL::hashtable<GameWindowVideoPair, const GameWindow *, WindowVideoManager::hashConstGameWindowPtr, _STL::_Select1st<GameWindowVideoPair>, _STL::equal_to<const GameWindow *>, _STL::allocator<GameWindowVideoPair> > GameWindowVideoHashtable;
template __declspec(naked) void GameWindowVideoHashtable::clear();
