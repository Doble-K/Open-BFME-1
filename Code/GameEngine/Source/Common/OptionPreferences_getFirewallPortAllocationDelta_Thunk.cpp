// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift MASM dump to standalone C++ thunk.

class OptionPreferences
{
public:
	short getFirewallPortAllocationDelta();
};

// ?getFirewallPortAllocationDelta@OptionPreferences@@QAEFXZ
__declspec(naked) short OptionPreferences::getFirewallPortAllocationDelta()
{
	__asm {
        __emit 0x51
        __emit 0x56
        __emit 0x57
        __emit 0x8b
        __emit 0xf1
        __emit 0x68
        __emit 0x3c
        __emit 0xa1
        __emit 0x07
        __emit 0x01
        __emit 0x8d
        __emit 0x4c
        __emit 0x24
        __emit 0x0c
        __emit 0xe8
        __emit 0xad
        __emit 0x7f
        __emit 0x7f
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
        __emit 0x8a
        __emit 0xa2
        __emit 0xf7
        __emit 0xff
        __emit 0x8d
        __emit 0x4c
        __emit 0x24
        __emit 0x08
        __emit 0x8b
        __emit 0xf8
        __emit 0xe8
        __emit 0x13
        __emit 0x6d
        __emit 0x7f
        __emit 0x00
        __emit 0x3b
        __emit 0x3e
        __emit 0x75
        __emit 0x11
        __emit 0x8b
        __emit 0x0d
        __emit 0xc8
        __emit 0xd5
        __emit 0x2e
        __emit 0x01
        __emit 0x66
        __emit 0x8b
        __emit 0x81
        __emit 0x20
        __emit 0x0b
        __emit 0x00
        __emit 0x00
        __emit 0x5f
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
