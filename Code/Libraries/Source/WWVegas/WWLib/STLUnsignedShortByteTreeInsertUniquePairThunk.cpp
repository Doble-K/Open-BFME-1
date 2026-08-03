namespace _STL
{
template<class First, class Second> struct pair { };
template<class T> struct _Select1st { };
template<class T> struct less { };
template<class T> class allocator { };
template<class T> struct _Nonconst_traits { };
template<class T, class Traits> struct _Rb_tree_iterator { };

template<class Key, class Value, class Select, class Compare, class Allocator>
class _Rb_tree
{
public:
    typedef _Rb_tree_iterator<Value, _Nonconst_traits<Value> > iterator;
    pair<iterator, bool> insert_unique(Value const &);
};

template<class Key, class Value, class Select, class Compare, class Allocator>
__declspec(naked) pair<typename _Rb_tree<Key, Value, Select, Compare, Allocator>::iterator, bool> _Rb_tree<Key, Value, Select, Compare, Allocator>::insert_unique(Value const &)
{
    __asm {
        _emit 08Bh
        _emit 0E9h
        _emit 08Bh
        _emit 055h
        _emit 000h
        _emit 056h
        _emit 08Bh
        _emit 072h
        _emit 004h
        _emit 085h
        _emit 0F6h
        _emit 057h
        _emit 08Bh
        _emit 0FAh
        _emit 0B1h
        _emit 001h
        _emit 074h
        _emit 021h
        _emit 066h
        _emit 08Bh
        _emit 003h
        _emit 0EBh
        _emit 003h
        _emit 08Dh
        _emit 049h
        _emit 000h
        _emit 066h
        _emit 03Bh
        _emit 046h
        _emit 010h
        _emit 08Bh
        _emit 0FEh
        _emit 00Fh
        _emit 092h
        _emit 0C1h
        _emit 084h
        _emit 0C9h
        _emit 074h
        _emit 005h
        _emit 08Bh
        _emit 076h
        _emit 008h
        _emit 0EBh
        _emit 003h
        _emit 08Bh
        _emit 076h
        _emit 00Ch
        _emit 085h
        _emit 0F6h
        _emit 075h
        _emit 0E7h
        _emit 084h
        _emit 0C9h
        _emit 08Bh
        _emit 0C7h
        _emit 074h
        _emit 015h
        _emit 03Bh
        _emit 07Ah
        _emit 008h
        _emit 075h
        _emit 007h
        _emit 06Ah
        _emit 000h
        _emit 053h
        _emit 057h
        _emit 057h
        _emit 0EBh
        _emit 017h
        _emit 057h
        _emit 0E8h
        _emit 04Fh
        _emit 0BAh
        _emit 0EEh
        _emit 0FFh
        _emit 083h
        _emit 0C4h
        _emit 004h
        _emit 066h
        _emit 08Bh
        _emit 050h
        _emit 010h
        _emit 066h
        _emit 03Bh
        _emit 013h
        _emit 073h
        _emit 024h
        _emit 06Ah
        _emit 000h
        _emit 053h
        _emit 057h
        _emit 056h
        _emit 08Dh
        _emit 044h
        _emit 024h
        _emit 028h
        _emit 050h
        _emit 08Bh
        _emit 0CDh
        _emit 0E8h
        _emit 0D2h
        _emit 0FEh
        _emit 0FFh
        _emit 0FFh
        _emit 08Bh
        _emit 008h
        _emit 08Bh
        _emit 044h
        _emit 024h
        _emit 014h
        _emit 05Fh
        _emit 05Eh
        _emit 05Dh
        _emit 089h
        _emit 008h
        _emit 0C6h
        _emit 040h
        _emit 004h
        _emit 001h
        _emit 05Bh
        _emit 0C2h
        _emit 008h
        _emit 000h
        _emit 08Bh
        _emit 04Ch
        _emit 024h
        _emit 014h
        _emit 05Fh
        _emit 05Eh
        _emit 05Dh
        _emit 089h
        _emit 001h
        _emit 0C6h
        _emit 041h
        _emit 004h
        _emit 000h
        _emit 08Bh
        _emit 0C1h
        _emit 05Bh
        _emit 0C2h
        _emit 008h
        _emit 000h
    }
}
}

typedef _STL::pair<const unsigned short, unsigned char> UnsignedShortBytePair;
typedef _STL::_Rb_tree<unsigned short, UnsignedShortBytePair, _STL::_Select1st<UnsignedShortBytePair>, _STL::less<unsigned short>, _STL::allocator<UnsignedShortBytePair> > UnsignedShortByteTree;
template __declspec(naked) _STL::pair<_STL::_Rb_tree_iterator<UnsignedShortBytePair, _STL::_Nonconst_traits<UnsignedShortBytePair> >, bool> UnsignedShortByteTree::insert_unique(UnsignedShortBytePair const &);
