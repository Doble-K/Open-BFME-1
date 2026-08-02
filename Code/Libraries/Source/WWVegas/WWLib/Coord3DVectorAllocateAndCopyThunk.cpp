// cl: /DNDEBUG /MD /EHsc

struct Coord3D
{
    float x;
    float y;
    float z;
};

namespace _STL
{
template <class Type>
class allocator
{
};

template <class Type, class Allocator>
class vector
{
protected:
    template <class Iterator>
    Type *_M_allocate_and_copy(unsigned int, Iterator, Iterator);
};

template <class Type, class Allocator>
template <class Iterator>
__declspec(naked) Type *vector<Type, Allocator>::_M_allocate_and_copy(
    unsigned int, Iterator, Iterator)
{
    __asm {
        __emit 0x8b;
        __emit 0x44;
        __emit 0x24;
        __emit 0x04;
        __emit 0x85;
        __emit 0xc0;
        __emit 0x56;
        __emit 0x74;
        __emit 0x26;
        __emit 0x8d;
        __emit 0x04;
        __emit 0x40;
        __emit 0xc1;
        __emit 0xe0;
        __emit 0x02;
        __emit 0x3d;
        __emit 0x80;
        __emit 0x00;
        __emit 0x00;
        __emit 0x00;
        __emit 0x50;
        __emit 0x76;
        __emit 0x0c;
        __emit 0xe8;
        __emit 0x24;
        __emit 0x92;
        __emit 0x81;
        __emit 0x00;
        __emit 0x83;
        __emit 0xc4;
        __emit 0x04;
        __emit 0x8b;
        __emit 0xf0;
        __emit 0xeb;
        __emit 0x0e;
        __emit 0xe8;
        __emit 0x28;
        __emit 0x58;
        __emit 0x7c;
        __emit 0x00;
        __emit 0x83;
        __emit 0xc4;
        __emit 0x04;
        __emit 0x8b;
        __emit 0xf0;
        __emit 0xeb;
        __emit 0x02;
        __emit 0x33;
        __emit 0xf6;
        __emit 0x8b;
        __emit 0x4c;
        __emit 0x24;
        __emit 0x10;
        __emit 0x8b;
        __emit 0x54;
        __emit 0x24;
        __emit 0x0c;
        __emit 0x8d;
        __emit 0x44;
        __emit 0x24;
        __emit 0x08;
        __emit 0x50;
        __emit 0x56;
        __emit 0x51;
        __emit 0x52;
        __emit 0xe8;
        __emit 0xe6;
        __emit 0x38;
        __emit 0xfa;
        __emit 0xff;
        __emit 0x83;
        __emit 0xc4;
        __emit 0x10;
        __emit 0x8b;
        __emit 0xc6;
        __emit 0x5e;
        __emit 0xc2;
        __emit 0x0c;
        __emit 0x00;
    }
}

template Coord3D *vector<Coord3D, allocator<Coord3D> >::_M_allocate_and_copy<const Coord3D *>(
    unsigned int, const Coord3D *, const Coord3D *);
}
