// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift MASM dump to standalone C++ thunk.

class SuperweaponInfo;
class AsciiString;
class SpecialPowerTemplate;
enum ObjectID { OBJECT_ID_INVALID = 0 };

class InGameUI
{
protected:
    SuperweaponInfo *findSWInfo(int, const AsciiString &, ObjectID, const SpecialPowerTemplate *);
};

// ?findSWInfo@InGameUI@@IAEPAVSuperweaponInfo@@HABVAsciiString@@W4ObjectID@@PBVSpecialPowerTemplate@@@Z
__declspec(naked) SuperweaponInfo *InGameUI::findSWInfo(int, const AsciiString &, ObjectID, const SpecialPowerTemplate *)
{
    __asm {
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x04
        __emit 0x56
        __emit 0x8d
        __emit 0x04
        __emit 0x40
        __emit 0x8d
        __emit 0xb4
        __emit 0x81
        __emit 0xcc
        __emit 0x05
        __emit 0x00
        __emit 0x00
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x0c
        __emit 0x51
        __emit 0x8b
        __emit 0xce
        __emit 0xe8
        __emit 0x70
        __emit 0x3e
        __emit 0xbc
        __emit 0xff
        __emit 0x3b
        __emit 0x06
        __emit 0x74
        __emit 0x1f
        __emit 0x8b
        __emit 0x48
        __emit 0x14
        __emit 0x8b
        __emit 0x01
        __emit 0x3b
        __emit 0xc1
        __emit 0x74
        __emit 0x16
        __emit 0x8b
        __emit 0x54
        __emit 0x24
        __emit 0x10
        __emit 0x8d
        __emit 0x64
        __emit 0x24
        __emit 0x00
        __emit 0x8b
        __emit 0x70
        __emit 0x08
        __emit 0x39
        __emit 0x56
        __emit 0x18
        __emit 0x74
        __emit 0x0c
        __emit 0x8b
        __emit 0x00
        __emit 0x3b
        __emit 0xc1
        __emit 0x75
        __emit 0xf2
        __emit 0x33
        __emit 0xc0
        __emit 0x5e
        __emit 0xc2
        __emit 0x10
        __emit 0x00
        __emit 0x8b
        __emit 0x40
        __emit 0x08
        __emit 0x5e
        __emit 0xc2
        __emit 0x10
        __emit 0x00
    }
}
