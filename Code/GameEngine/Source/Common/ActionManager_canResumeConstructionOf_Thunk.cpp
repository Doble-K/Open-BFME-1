// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift MASM dump to standalone C++ thunk.

class Object;
enum CommandSourceType { CMD_SRC_PLACEHOLDER = 0 };
class ActionManager
{
public:
	bool canResumeConstructionOf(const Object *, const Object *, CommandSourceType);
};

// ?canResumeConstructionOf@ActionManager@@QAE_NPBVObject@@0W4CommandSourceType@@@Z
__declspec(naked) bool ActionManager::canResumeConstructionOf(const Object *, const Object *, CommandSourceType)
{
	__asm {
        __emit 0x56
        __emit 0x57
        __emit 0x8b
        __emit 0x7c
        __emit 0x24
        __emit 0x0c
        __emit 0x85
        __emit 0xff
        __emit 0x74
        __emit 0x4b
        __emit 0x8b
        __emit 0x74
        __emit 0x24
        __emit 0x10
        __emit 0x85
        __emit 0xf6
        __emit 0x74
        __emit 0x43
        __emit 0x6a
        __emit 0x0e
        __emit 0x8b
        __emit 0xcf
        __emit 0xe8
        __emit 0x44
        __emit 0xd1
        __emit 0xf6
        __emit 0xff
        __emit 0x84
        __emit 0xc0
        __emit 0x74
        __emit 0x36
        __emit 0x56
        __emit 0x8b
        __emit 0xcf
        __emit 0xe8
        __emit 0x32
        __emit 0x53
        __emit 0xf8
        __emit 0xff
        __emit 0x83
        __emit 0xf8
        __emit 0x02
        __emit 0x75
        __emit 0x29
        __emit 0xf6
        __emit 0x86
        __emit 0x90
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x04
        __emit 0x74
        __emit 0x20
        __emit 0xf6
        __emit 0x87
        __emit 0x44
        __emit 0x03
        __emit 0x00
        __emit 0x00
        __emit 0x01
        __emit 0x75
        __emit 0x17
        __emit 0x8b
        __emit 0xce
        __emit 0xe8
        __emit 0xd2
        __emit 0xd5
        __emit 0xf3
        __emit 0xff
        __emit 0x85
        __emit 0xc0
        __emit 0x74
        __emit 0x05
        __emit 0x3b
        __emit 0x47
        __emit 0x74
        __emit 0x75
        __emit 0x07
        __emit 0x5f
        __emit 0xb0
        __emit 0x01
        __emit 0x5e
        __emit 0xc2
        __emit 0x0c
        __emit 0x00
        __emit 0x5f
        __emit 0x32
        __emit 0xc0
        __emit 0x5e
        __emit 0xc2
        __emit 0x0c
        __emit 0x00
	}
}
