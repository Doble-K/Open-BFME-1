// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift MASM dump to standalone C++ thunk.

class StringClass;

template <class T>
class HashTemplateKeyClass
{
public:
	static unsigned int Get_Hash_Value(const T &);
};

// ?Get_Hash_Value@?@VStringClass@@@@SAIABVStringClass@@@Z
__declspec(naked) unsigned int HashTemplateKeyClass<StringClass>::Get_Hash_Value(const StringClass &)
{
	__asm {
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x04
        __emit 0x33
        __emit 0xc0
        __emit 0x41
        __emit 0xba
        __emit 0x04
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x56
        __emit 0x8d
        __emit 0x49
        __emit 0x00
        __emit 0x0f
        __emit 0xb6
        __emit 0x71
        __emit 0xff
        __emit 0x6b
        __emit 0xc0
        __emit 0x26
        __emit 0x03
        __emit 0xf0
        __emit 0x0f
        __emit 0xb6
        __emit 0x01
        __emit 0x6b
        __emit 0xf6
        __emit 0x26
        __emit 0x03
        __emit 0xf0
        __emit 0x0f
        __emit 0xb6
        __emit 0x41
        __emit 0x01
        __emit 0x6b
        __emit 0xf6
        __emit 0x26
        __emit 0x03
        __emit 0xf0
        __emit 0x0f
        __emit 0xb6
        __emit 0x41
        __emit 0x02
        __emit 0x6b
        __emit 0xf6
        __emit 0x26
        __emit 0x03
        __emit 0xf0
        __emit 0x0f
        __emit 0xb6
        __emit 0x41
        __emit 0x03
        __emit 0x6b
        __emit 0xf6
        __emit 0x26
        __emit 0x03
        __emit 0xf0
        __emit 0x0f
        __emit 0xb6
        __emit 0x41
        __emit 0x04
        __emit 0x6b
        __emit 0xf6
        __emit 0x26
        __emit 0x03
        __emit 0xc6
        __emit 0x83
        __emit 0xc1
        __emit 0x06
        __emit 0x4a
        __emit 0x75
        __emit 0xc5
        __emit 0x5e
        __emit 0xc3
	}
}
