// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift MASM dump to standalone C++ thunk.

enum ObjectID {};

namespace _STL {
template <class T> class allocator {};
template <class T, class A> class vector {
public:
	void resize(unsigned int, const T &);
};
}

// ?resize@?$vector@W4ObjectID@@V?$allocator@W4ObjectID@@@_STL@@@_STL@@QAEXIABW4ObjectID@@@Z
__declspec(naked) void _STL::vector<ObjectID, _STL::allocator<ObjectID> >::resize(unsigned int, const ObjectID &)
{
	__asm {
		__emit 0x8b
		__emit 0x41
		__emit 0x04
		__emit 0x56
		__emit 0x8b
		__emit 0x74
		__emit 0x24
		__emit 0x08
		__emit 0x57
		__emit 0x8b
		__emit 0x39
		__emit 0x8b
		__emit 0xd0
		__emit 0x2b
		__emit 0xd7
		__emit 0xc1
		__emit 0xfa
		__emit 0x02
		__emit 0x3b
		__emit 0xf2
		__emit 0x73
		__emit 0x23
		__emit 0x8b
		__emit 0xd0
		__emit 0x2b
		__emit 0xc2
		__emit 0xc1
		__emit 0xf8
		__emit 0x02
		__emit 0x85
		__emit 0xc0
		__emit 0x8d
		__emit 0x34
		__emit 0xb7
		__emit 0x7e
		__emit 0x0d
		__emit 0x8b
		__emit 0x3a
		__emit 0x89
		__emit 0x3e
		__emit 0x83
		__emit 0xc2
		__emit 0x04
		__emit 0x83
		__emit 0xc6
		__emit 0x04
		__emit 0x48
		__emit 0x75
		__emit 0xf3
		__emit 0x5f
		__emit 0x89
		__emit 0x71
		__emit 0x04
		__emit 0x5e
		__emit 0xc2
		__emit 0x08
		__emit 0x00
		__emit 0x8d
		__emit 0x7c
		__emit 0x24
		__emit 0x10
		__emit 0x57
		__emit 0x2b
		__emit 0xf2
		__emit 0x56
		__emit 0x50
		__emit 0xe8
		__emit 0xe1
		__emit 0x23
		__emit 0xd4
		__emit 0xff
		__emit 0x5f
		__emit 0x5e
		__emit 0xc2
		__emit 0x08
		__emit 0x00
	}
}
