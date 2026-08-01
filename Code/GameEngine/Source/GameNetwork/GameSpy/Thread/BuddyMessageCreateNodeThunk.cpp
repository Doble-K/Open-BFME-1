// cl: /DNDEBUG /MD /EHsc

class BuddyMessage
{
};

namespace _STL
{
template <class Type>
class allocator
{
};

template <class Type>
struct _List_node
{
};

template <class Type, class Allocator>
class list
{
protected:
    _List_node<Type> *_M_create_node(Type const &);
};

template <class Type, class Allocator>
__declspec(naked) _List_node<Type> *list<Type, Allocator>::_M_create_node(Type const &)
{
    __asm {
        _emit 056h
        _emit 06Ah
        _emit 020h
        _emit 0E8h
        _emit 008h
        _emit 030h
        _emit 034h
        _emit 000h
        _emit 08Bh
        _emit 0F0h
        _emit 08Bh
        _emit 044h
        _emit 024h
        _emit 00Ch
        _emit 050h
        _emit 08Dh
        _emit 04Eh
        _emit 008h
        _emit 051h
        _emit 0E8h
        _emit 021h
        _emit 059h
        _emit 0B3h
        _emit 0FFh
        _emit 083h
        _emit 0C4h
        _emit 00Ch
        _emit 08Bh
        _emit 0C6h
        _emit 05Eh
        _emit 0C2h
        _emit 004h
        _emit 000h
    }
}

template __declspec(naked) _List_node<BuddyMessage> *list<BuddyMessage, allocator<BuddyMessage> >::_M_create_node(BuddyMessage const &);
}
