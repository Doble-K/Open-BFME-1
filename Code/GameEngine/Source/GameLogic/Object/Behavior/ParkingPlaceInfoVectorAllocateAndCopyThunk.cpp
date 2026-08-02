// cl: /DNDEBUG /MD /EHsc

class ParkingPlaceBehavior
{
public:
    struct ParkingPlaceInfo
    {
    };
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
        __emit 0x53;
        __emit 0x55;
        __emit 0x56;
        __emit 0x74;
        __emit 0x23;
        __emit 0x6b;
        __emit 0xc0;
        __emit 0x3c;
        __emit 0x3d;
        __emit 0x80;
        __emit 0x00;
        __emit 0x00;
        __emit 0x00;
        __emit 0x50;
        __emit 0x76;
        __emit 0x0c;
        __emit 0xe8;
        __emit 0x15;
        __emit 0x45;
        __emit 0x4b;
        __emit 0x00;
        __emit 0x83;
        __emit 0xc4;
        __emit 0x04;
        __emit 0x8b;
        __emit 0xe8;
        __emit 0xeb;
        __emit 0x0e;
        __emit 0xe8;
        __emit 0x19;
        __emit 0x0b;
        __emit 0x46;
        __emit 0x00;
        __emit 0x83;
        __emit 0xc4;
        __emit 0x04;
        __emit 0x8b;
        __emit 0xe8;
        __emit 0xeb;
        __emit 0x02;
        __emit 0x33;
        __emit 0xed;
        __emit 0x8b;
        __emit 0x74;
        __emit 0x24;
        __emit 0x14;
        __emit 0x8b;
        __emit 0x5c;
        __emit 0x24;
        __emit 0x18;
        __emit 0x3b;
        __emit 0xf3;
        __emit 0x74;
        __emit 0x1a;
        __emit 0x57;
        __emit 0x8b;
        __emit 0xfd;
        __emit 0x2b;
        __emit 0xfe;
        __emit 0x8d;
        __emit 0x04;
        __emit 0x37;
        __emit 0x56;
        __emit 0x50;
        __emit 0xe8;
        __emit 0x73;
        __emit 0x0a;
        __emit 0xc7;
        __emit 0xff;
        __emit 0x83;
        __emit 0xc6;
        __emit 0x3c;
        __emit 0x83;
        __emit 0xc4;
        __emit 0x08;
        __emit 0x3b;
        __emit 0xf3;
        __emit 0x75;
        __emit 0xec;
        __emit 0x5f;
        __emit 0x5e;
        __emit 0x8b;
        __emit 0xc5;
        __emit 0x5d;
        __emit 0x5b;
        __emit 0xc2;
        __emit 0x0c;
        __emit 0x00;
    }
}

template ParkingPlaceBehavior::ParkingPlaceInfo *vector<
    ParkingPlaceBehavior::ParkingPlaceInfo,
    allocator<ParkingPlaceBehavior::ParkingPlaceInfo>
>::_M_allocate_and_copy<ParkingPlaceBehavior::ParkingPlaceInfo *>(
    unsigned int, ParkingPlaceBehavior::ParkingPlaceInfo *, ParkingPlaceBehavior::ParkingPlaceInfo *);
}
