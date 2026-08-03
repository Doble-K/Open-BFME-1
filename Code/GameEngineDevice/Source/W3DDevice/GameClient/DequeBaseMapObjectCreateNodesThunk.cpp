// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift MASM dump for no-SEH _M_create_nodes (MapObject deque).
// Clean C++ emits SEH around operator new (121B); retail is 40B no-SEH.

class MapObject
{
};

namespace _STL
{
template <class Type>
class allocator
{
};

template <class Type, class Allocator>
class _Deque_base
{
protected:
	void _M_create_nodes(Type **, Type **);
};

// ?_M_create_nodes@?$_Deque_base@PAVMapObject@@V?$allocator@PAVMapObject@@@_STL@@@_STL@@IAEXPAPAPAVMapObject@@0@Z
// Type = MapObject* => Type** = MapObject***
__declspec(naked) void _Deque_base<MapObject *, allocator<MapObject *> >::_M_create_nodes(MapObject ***, MapObject ***)
{
	__asm {
		__emit 0x56;
		__emit 0x8b;
		__emit 0x74;
		__emit 0x24;
		__emit 0x08;
		__emit 0x57;
		__emit 0x8b;
		__emit 0x7c;
		__emit 0x24;
		__emit 0x10;
		__emit 0x3b;
		__emit 0xf7;
		__emit 0x73;
		__emit 0x15;
		__emit 0x8b;
		__emit 0xff;
		__emit 0x6a;
		__emit 0x78;
		__emit 0xe8;
		__emit 0xf9;
		__emit 0x46;
		__emit 0xf3;
		__emit 0xff;
		__emit 0x89;
		__emit 0x06;
		__emit 0x83;
		__emit 0xc6;
		__emit 0x04;
		__emit 0x83;
		__emit 0xc4;
		__emit 0x04;
		__emit 0x3b;
		__emit 0xf7;
		__emit 0x72;
		__emit 0xed;
		__emit 0x5f;
		__emit 0x5e;
		__emit 0xc2;
		__emit 0x08;
		__emit 0x00;
	}
}

template void _Deque_base<MapObject *, allocator<MapObject *> >::_M_create_nodes(MapObject ***, MapObject ***);
}
