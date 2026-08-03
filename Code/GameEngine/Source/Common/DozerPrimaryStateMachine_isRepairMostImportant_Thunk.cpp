// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift MASM dump to standalone C++ thunk.

class State;
class DozerPrimaryStateMachine
{
public:
	static bool __cdecl isRepairMostImportant(State *, void *);
};

// ?isRepairMostImportant@DozerPrimaryStateMachine@@SA_NPAVState@@PAX@Z
__declspec(naked) bool __cdecl DozerPrimaryStateMachine::isRepairMostImportant(State *, void *)
{
	__asm {
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x04
        __emit 0x8b
        __emit 0x48
        __emit 0x1c
        __emit 0x8b
        __emit 0x51
        __emit 0x10
        __emit 0x56
        __emit 0x8b
        __emit 0xb2
        __emit 0x04
        __emit 0x02
        __emit 0x00
        __emit 0x00
        __emit 0x85
        __emit 0xf6
        __emit 0x75
        __emit 0x04
        __emit 0x32
        __emit 0xc0
        __emit 0x5e
        __emit 0xc3
        __emit 0x8b
        __emit 0x06
        __emit 0x57
        __emit 0x8b
        __emit 0xce
        __emit 0xff
        __emit 0x90
        __emit 0x3c
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x8b
        __emit 0xf8
        __emit 0x85
        __emit 0xff
        __emit 0x75
        __emit 0x05
        __emit 0x5f
        __emit 0x32
        __emit 0xc0
        __emit 0x5e
        __emit 0xc3
        __emit 0x8b
        __emit 0x16
        __emit 0x8b
        __emit 0xce
        __emit 0xff
        __emit 0x92
        __emit 0x80
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x84
        __emit 0xc0
        __emit 0x74
        __emit 0xed
        __emit 0x8b
        __emit 0x07
        __emit 0x8b
        __emit 0xcf
        __emit 0xff
        __emit 0x50
        __emit 0x14
        __emit 0x48
        __emit 0xf7
        __emit 0xd8
        __emit 0x1b
        __emit 0xc0
        __emit 0x5f
        __emit 0x40
        __emit 0x5e
        __emit 0xc3
	}
}
