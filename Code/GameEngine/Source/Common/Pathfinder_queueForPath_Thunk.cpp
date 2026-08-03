// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift MASM dump to standalone C++ thunk.

enum ObjectID { OBJECT_ID_INVALID = 0 };
class Pathfinder
{
public:
	bool queueForPath(ObjectID);
};

// ?queueForPath@Pathfinder@@QAE_NW4ObjectID@@@Z
__declspec(naked) bool Pathfinder::queueForPath(ObjectID)
{
	__asm {
        __emit 0x8b
        __emit 0x91
        __emit 0x1c
        __emit 0x4f
        __emit 0x02
        __emit 0x00
        __emit 0x56
        __emit 0x8b
        __emit 0xb1
        __emit 0x18
        __emit 0x4f
        __emit 0x02
        __emit 0x00
        __emit 0x8b
        __emit 0xc6
        __emit 0x3b
        __emit 0xc2
        __emit 0x57
        __emit 0x8b
        __emit 0x7c
        __emit 0x24
        __emit 0x0c
        __emit 0x74
        __emit 0x23
        __emit 0xeb
        __emit 0x06
        __emit 0x8d
        __emit 0x9b
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x39
        __emit 0xbc
        __emit 0x81
        __emit 0x18
        __emit 0x47
        __emit 0x02
        __emit 0x00
        __emit 0x74
        __emit 0x36
        __emit 0x40
        __emit 0x3d
        __emit 0x00
        __emit 0x02
        __emit 0x00
        __emit 0x00
        __emit 0x7c
        __emit 0x02
        __emit 0x33
        __emit 0xc0
        __emit 0x3b
        __emit 0x81
        __emit 0x1c
        __emit 0x4f
        __emit 0x02
        __emit 0x00
        __emit 0x75
        __emit 0xe5
        __emit 0x8d
        __emit 0x42
        __emit 0x01
        __emit 0x3d
        __emit 0x00
        __emit 0x02
        __emit 0x00
        __emit 0x00
        __emit 0x7c
        __emit 0x02
        __emit 0x33
        __emit 0xc0
        __emit 0x3b
        __emit 0xc6
        __emit 0x75
        __emit 0x07
        __emit 0x5f
        __emit 0x5e
        __emit 0x32
        __emit 0xc0
        __emit 0xc2
        __emit 0x04
        __emit 0x00
        __emit 0x89
        __emit 0xbc
        __emit 0x91
        __emit 0x18
        __emit 0x47
        __emit 0x02
        __emit 0x00
        __emit 0x89
        __emit 0x81
        __emit 0x1c
        __emit 0x4f
        __emit 0x02
        __emit 0x00
        __emit 0x5f
	}
}
