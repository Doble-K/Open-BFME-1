// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift MASM dump to standalone C++ thunk.

class Object;
class ApplyRandomForceNugget
{
public:
    virtual Object *create(const Object *, const Object *, unsigned int) const;
};

// ?create@ApplyRandomForceNugget@@UBEPAVObject@@PBV2@0I@Z
__declspec(naked) Object *ApplyRandomForceNugget::create(const Object *, const Object *, unsigned int) const
{
    __asm {
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x04
        __emit 0x83
        __emit 0xec
        __emit 0x0c
        __emit 0x85
        __emit 0xc0
        __emit 0x74
        __emit 0x35
        __emit 0x56
        __emit 0x8b
        __emit 0xb0
        __emit 0x08
        __emit 0x02
        __emit 0x00
        __emit 0x00
        __emit 0x85
        __emit 0xf6
        __emit 0x74
        __emit 0x29
        __emit 0x8b
        __emit 0x51
        __emit 0x10
        __emit 0x8d
        __emit 0x44
        __emit 0x24
        __emit 0x04
        __emit 0x50
        __emit 0x8b
        __emit 0x41
        __emit 0x0c
        __emit 0x52
        __emit 0x8b
        __emit 0x51
        __emit 0x08
        __emit 0x50
        __emit 0x8b
        __emit 0x41
        __emit 0x04
        __emit 0x52
        __emit 0x50
        __emit 0xe8
        __emit 0x30
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x14
        __emit 0x8d
        __emit 0x4c
        __emit 0x24
        __emit 0x04
        __emit 0x51
        __emit 0x8b
        __emit 0xce
        __emit 0xe8
        __emit 0x95
        __emit 0x3d
        __emit 0xe5
        __emit 0xff
        __emit 0x5e
        __emit 0x83
        __emit 0xc4
        __emit 0x0c
        __emit 0xc2
        __emit 0x0c
        __emit 0x00
    }
}

