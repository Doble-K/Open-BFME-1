// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift MASM dump to standalone C++ thunk.

class ObjectDefectionHelper
{
public:
	void startDefectionTimer(unsigned int, bool);
};

// ?startDefectionTimer@ObjectDefectionHelper@@QAEXI_N@Z
__declspec(naked) void ObjectDefectionHelper::startDefectionTimer(unsigned int, bool)
{
	__asm {
        __emit 0x8b
        __emit 0x51
        __emit 0x08
        __emit 0xf6
        __emit 0x82
        __emit 0x44
        __emit 0x03
        __emit 0x00
        __emit 0x00
        __emit 0x02
        __emit 0x75
        __emit 0x11
        __emit 0xc7
        __emit 0x44
        __emit 0x24
        __emit 0x08
        __emit 0xff
        __emit 0xff
        __emit 0xff
        __emit 0x3f
        __emit 0x89
        __emit 0x54
        __emit 0x24
        __emit 0x04
        __emit 0xe9
        __emit 0xcd
        __emit 0xf4
        __emit 0xdb
        __emit 0xff
        __emit 0xa1
        __emit 0x98
        __emit 0x08
        __emit 0x2f
        __emit 0x01
        __emit 0x8b
        __emit 0x40
        __emit 0x3c
        __emit 0x56
        __emit 0x8b
        __emit 0x74
        __emit 0x24
        __emit 0x08
        __emit 0x89
        __emit 0x41
        __emit 0x20
        __emit 0x03
        __emit 0xc6
        __emit 0x89
        __emit 0x41
        __emit 0x24
        __emit 0x8a
        __emit 0x44
        __emit 0x24
        __emit 0x0c
        __emit 0xc7
        __emit 0x41
        __emit 0x28
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x88
        __emit 0x41
        __emit 0x2c
        __emit 0x5e
        __emit 0xc7
        __emit 0x44
        __emit 0x24
        __emit 0x08
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x89
        __emit 0x54
        __emit 0x24
        __emit 0x04
        __emit 0xe9
        __emit 0x98
        __emit 0xf4
        __emit 0xdb
        __emit 0xff
	}
}
