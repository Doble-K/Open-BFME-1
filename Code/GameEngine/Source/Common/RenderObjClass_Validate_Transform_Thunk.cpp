// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift MASM dump to standalone C++ thunk.

class RenderObjClass
{
public:
	virtual void Validate_Transform() const;
};

// ?Validate_Transform@RenderObjClass@@UBEXXZ
__declspec(naked) void RenderObjClass::Validate_Transform() const
{
	__asm {
        __emit 0x56
        __emit 0x8b
        __emit 0xf1
        __emit 0x8b
        __emit 0x8e
        __emit 0x84
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x85
        __emit 0xc9
        __emit 0x74
        __emit 0x41
        __emit 0x8b
        __emit 0x51
        __emit 0x10
        __emit 0x8b
        __emit 0x81
        __emit 0x84
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xc1
        __emit 0xea
        __emit 0x15
        __emit 0x80
        __emit 0xe2
        __emit 0x01
        __emit 0x85
        __emit 0xc0
        __emit 0x74
        __emit 0x17
        __emit 0x8b
        __emit 0x49
        __emit 0x10
        __emit 0xc1
        __emit 0xe9
        __emit 0x15
        __emit 0x80
        __emit 0xe1
        __emit 0x01
        __emit 0x0a
        __emit 0xd1
        __emit 0x8b
        __emit 0xc8
        __emit 0x8b
        __emit 0x81
        __emit 0x84
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x85
        __emit 0xc0
        __emit 0x75
        __emit 0xe9
        __emit 0x84
        __emit 0xd2
        __emit 0x74
        __emit 0x13
        __emit 0x8b
        __emit 0x11
        __emit 0xff
        __emit 0x92
        __emit 0xa4
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x8d
        __emit 0x4e
        __emit 0x18
        __emit 0xe8
        __emit 0x85
        __emit 0xfc
        __emit 0xff
        __emit 0xff
        __emit 0x88
        __emit 0x46
        __emit 0x7c
        __emit 0x5e
        __emit 0xc3
	}
}
