// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift MASM dump to standalone C++ thunk.

class QuickMatchPreferences
{
public:
	unsigned short getLastLadderPort();
};

// ?getLastLadderPort@QuickMatchPreferences@@QAEGXZ
__declspec(naked) unsigned short QuickMatchPreferences::getLastLadderPort()
{
	__asm {
        __emit 0x51
        __emit 0x56
        __emit 0x57
        __emit 0x8b
        __emit 0xf1
        __emit 0x68
        __emit 0x84
        __emit 0x11
        __emit 0x08
        __emit 0x01
        __emit 0x8d
        __emit 0x4c
        __emit 0x24
        __emit 0x0c
        __emit 0xe8
        __emit 0x9d
        __emit 0xcc
        __emit 0x7d
        __emit 0x00
        __emit 0x8d
        __emit 0x44
        __emit 0x24
        __emit 0x08
        __emit 0x83
        __emit 0xc6
        __emit 0x04
        __emit 0x50
        __emit 0x8b
        __emit 0xce
        __emit 0xe8
        __emit 0x7a
        __emit 0xef
        __emit 0xf5
        __emit 0xff
        __emit 0x8d
        __emit 0x4c
        __emit 0x24
        __emit 0x08
        __emit 0x8b
        __emit 0xf8
        __emit 0xe8
        __emit 0x03
        __emit 0xba
        __emit 0x7d
        __emit 0x00
        __emit 0x3b
        __emit 0x3e
        __emit 0x75
        __emit 0x06
        __emit 0x5f
        __emit 0x33
        __emit 0xc0
        __emit 0x5e
        __emit 0x59
        __emit 0xc3
        __emit 0x8b
        __emit 0x7f
        __emit 0x14
        __emit 0x85
        __emit 0xff
        __emit 0x8d
        __emit 0x47
        __emit 0x08
        __emit 0x75
        __emit 0x05
        __emit 0xb8
        __emit 0x8b
        __emit 0x38
        __emit 0x07
        __emit 0x01
        __emit 0x50
        __emit 0xff
        __emit 0x15
        __emit 0x84
        __emit 0x93
        __emit 0x35
        __emit 0x01
        __emit 0x83
        __emit 0xc4
        __emit 0x04
        __emit 0x5f
        __emit 0x5e
        __emit 0x59
        __emit 0xc3
	}
}
