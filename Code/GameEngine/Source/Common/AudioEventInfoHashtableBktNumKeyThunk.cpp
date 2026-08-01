class AsciiString
{
};

struct AudioEventInfo
{
};

namespace rts
{
template<class T>
struct hash
{
};

template<class T>
struct equal_to
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
class allocator
{
};

template<class Value, class Key, class Hash, class Extract, class Equal, class Alloc>
class hashtable
{
    unsigned int _M_bkt_num_key(const Key &, unsigned int) const;
};

template<class Value, class Key, class Hash, class Extract, class Equal, class Alloc>
__declspec(naked) unsigned int hashtable<Value, Key, Hash, Extract, Equal, Alloc>::_M_bkt_num_key(const Key &, unsigned int) const
{
    __asm {
        _emit 0E9h
        _emit 074h
        _emit 082h
        _emit 00Ah
        _emit 000h
    }
}
}

typedef _STL::pair<const AsciiString, AudioEventInfo *> AudioEventInfoPair;
typedef _STL::hashtable<AudioEventInfoPair, AsciiString, rts::hash<AsciiString>, _STL::_Select1st<AudioEventInfoPair>, rts::equal_to<AsciiString>, _STL::allocator<AudioEventInfoPair> > AudioEventInfoHashtable;
template unsigned int AudioEventInfoHashtable::_M_bkt_num_key(const AsciiString &, unsigned int) const;
