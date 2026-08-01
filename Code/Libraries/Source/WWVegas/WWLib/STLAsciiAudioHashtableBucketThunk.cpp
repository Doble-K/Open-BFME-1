class AsciiString
{
};
struct AudioEventInfo
{
};

namespace _STL
{
template<class First, class Second> struct pair { };
template<class T> struct _Select1st { };
template<class T> class allocator { };
template<class Value, class Key, class Hash, class Select, class Equal, class Alloc>
class hashtable
{
    unsigned int _M_bkt_num_key(Key const &, unsigned int) const;
};
template<class Value, class Key, class Hash, class Select, class Equal, class Alloc>
__declspec(naked) unsigned int hashtable<Value, Key, Hash, Select, Equal, Alloc>::_M_bkt_num_key(Key const &, unsigned int) const
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
namespace rts
{
template<class T> struct hash { };
template<class T> struct equal_to { };
}
typedef _STL::pair<const AsciiString, AudioEventInfo *> AudioEventPair;
typedef _STL::hashtable<AudioEventPair, AsciiString, rts::hash<AsciiString>, _STL::_Select1st<AudioEventPair>, rts::equal_to<AsciiString>, _STL::allocator<AudioEventPair> > AudioEventHashtable;
template unsigned int AudioEventHashtable::_M_bkt_num_key(AsciiString const &, unsigned int) const;
