// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift MASM dump to standalone C++ thunk.

class ControlBar
{
protected:
	void updateRadarAttackGlow();
};

// ?updateRadarAttackGlow@ControlBar@@IAEXXZ
__declspec(naked) void ControlBar::updateRadarAttackGlow()
{
	__asm {
        __emit 0x56
        __emit 0x8b
        __emit 0xf1
        __emit 0x8a
        __emit 0x86
        __emit 0xe0
        __emit 0x02
        __emit 0x00
        __emit 0x00
        __emit 0x84
        __emit 0xc0
        __emit 0x74
        __emit 0x57
        __emit 0x8b
        __emit 0x8e
        __emit 0xe8
        __emit 0x02
        __emit 0x00
        __emit 0x00
        __emit 0x85
        __emit 0xc9
        __emit 0x74
        __emit 0x4d
        __emit 0x57
        __emit 0x8b
        __emit 0xbe
        __emit 0xe4
        __emit 0x02
        __emit 0x00
        __emit 0x00
        __emit 0x4f
        __emit 0x8b
        __emit 0xc7
        __emit 0x85
        __emit 0xc0
        __emit 0x89
        __emit 0xbe
        __emit 0xe4
        __emit 0x02
        __emit 0x00
        __emit 0x00
        __emit 0x7f
        __emit 0x11
        __emit 0x6a
        __emit 0x01
        __emit 0xc6
        __emit 0x86
        __emit 0xe0
        __emit 0x02
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xe8
        __emit 0x52
        __emit 0xce
        __emit 0xba
        __emit 0xff
        __emit 0x5f
        __emit 0x5e
        __emit 0xc3
        __emit 0x99
        __emit 0xbf
        __emit 0x0f
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xf7
        __emit 0xff
        __emit 0x85
        __emit 0xd2
        __emit 0x75
        __emit 0x1b
        __emit 0xe8
        __emit 0x1d
        __emit 0x6a
        __emit 0xb8
        __emit 0xff
        __emit 0x8b
        __emit 0x8e
        __emit 0xe8
        __emit 0x02
        __emit 0x00
        __emit 0x00
        __emit 0xc1
        __emit 0xe8
        __emit 0x03
        __emit 0xf6
        __emit 0xd0
        __emit 0x25
        __emit 0x01
        __emit 0xff
        __emit 0xff
        __emit 0xff
        __emit 0x50
        __emit 0xe8
        __emit 0x28
        __emit 0xce
        __emit 0xba
        __emit 0xff
        __emit 0x5f
        __emit 0x5e
        __emit 0xc3
	}
}
