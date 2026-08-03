// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift MASM dump to standalone C++ thunk.

class Object;
class PartitionFilterPlayerAffiliation
{
protected:
	virtual bool allow(Object *);
};

// ?allow@PartitionFilterPlayerAffiliation@@MAE_NPAVObject@@@Z
__declspec(naked) bool PartitionFilterPlayerAffiliation::allow(Object *)
{
	__asm {
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x04
        __emit 0x8b
        __emit 0x80
        __emit 0x3c
        __emit 0x02
        __emit 0x00
        __emit 0x00
        __emit 0x56
        __emit 0x8b
        __emit 0xf1
        __emit 0x8b
        __emit 0x4e
        __emit 0x08
        __emit 0x50
        __emit 0xe8
        __emit 0x24
        __emit 0x16
        __emit 0xe6
        __emit 0xff
        __emit 0x83
        __emit 0xe8
        __emit 0x00
        __emit 0x74
        __emit 0x20
        __emit 0x48
        __emit 0x74
        __emit 0x10
        __emit 0x48
        __emit 0x75
        __emit 0x27
        __emit 0xf6
        __emit 0x46
        __emit 0x10
        __emit 0x02
        __emit 0x74
        __emit 0x21
        __emit 0x8a
        __emit 0x46
        __emit 0x0c
        __emit 0x5e
        __emit 0xc2
        __emit 0x04
        __emit 0x00
        __emit 0xf6
        __emit 0x46
        __emit 0x10
        __emit 0x08
        __emit 0x74
        __emit 0x14
        __emit 0x8a
        __emit 0x46
        __emit 0x0c
        __emit 0x5e
        __emit 0xc2
        __emit 0x04
        __emit 0x00
        __emit 0xf6
        __emit 0x46
        __emit 0x10
        __emit 0x04
        __emit 0x74
        __emit 0x07
        __emit 0x8a
        __emit 0x46
        __emit 0x0c
        __emit 0x5e
        __emit 0xc2
        __emit 0x04
        __emit 0x00
        __emit 0x8a
        __emit 0x4e
        __emit 0x0c
        __emit 0x33
        __emit 0xc0
        __emit 0x84
        __emit 0xc9
        __emit 0x0f
        __emit 0x94
        __emit 0xc0
        __emit 0x5e
        __emit 0xc2
        __emit 0x04
        __emit 0x00
	}
}
