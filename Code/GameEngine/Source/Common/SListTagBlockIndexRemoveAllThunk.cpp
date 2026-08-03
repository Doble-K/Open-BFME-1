// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift MASM dump to standalone C++ thunk.

class TagBlockIndex;

template <class T>
class SList
{
public:
	virtual void Remove_All();
};

// ?Remove_All@?@VTagBlockIndex@@@@UAEXXZ
__declspec(naked) void SList<TagBlockIndex>::Remove_All()
{
	__asm {
        __emit 0x53
        __emit 0x55
        __emit 0x56
        __emit 0x57
        __emit 0x8d
        __emit 0x59
        __emit 0x04
        __emit 0xbd
        __emit 0xcf
        __emit 0xaf
        __emit 0x00
        __emit 0x00
        __emit 0x8d
        __emit 0x64
        __emit 0x24
        __emit 0x00
        __emit 0x8b
        __emit 0x33
        __emit 0x85
        __emit 0xf6
        __emit 0x74
        __emit 0x18
        __emit 0x8b
        __emit 0x3e
        __emit 0x8b
        __emit 0xce
        __emit 0xe8
        __emit 0xa1
        __emit 0xf5
        __emit 0xff
        __emit 0xff
        __emit 0x56
        __emit 0xe8
        __emit 0x5b
        __emit 0x41
        __emit 0xe9
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x04
        __emit 0x85
        __emit 0xff
        __emit 0x8b
        __emit 0xf7
        __emit 0x75
        __emit 0xe8
        __emit 0xc7
        __emit 0x03
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x83
        __emit 0xc3
        __emit 0x04
        __emit 0x4d
        __emit 0x75
        __emit 0xd6
        __emit 0x5f
        __emit 0x5e
        __emit 0x5d
        __emit 0x5b
        __emit 0xc3
    }
}
