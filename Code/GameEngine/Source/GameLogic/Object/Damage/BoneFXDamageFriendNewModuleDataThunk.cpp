// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class INI;
class ModuleData;

class BoneFXDamage
{
public:
    static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@BoneFXDamage@@SAPAVModuleData@@PAVINI@@@Z
__declspec(naked) ModuleData *BoneFXDamage::friend_newModuleData(INI *)
{
    __asm {
        __emit 0x56
        __emit 0x6a
        __emit 0x08
        __emit 0xe8
        __emit 0xa8
        __emit 0xf1
        __emit 0x75
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x04
        __emit 0x85
        __emit 0xc0
        __emit 0x74
        __emit 0x0a
        __emit 0xc7
        __emit 0x00
        __emit 0x38
        __emit 0xae
        __emit 0x08
        __emit 0x01
        __emit 0x8b
        __emit 0xf0
        __emit 0xeb
        __emit 0x02
        __emit 0x33
        __emit 0xf6
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x08
        __emit 0x85
        __emit 0xc9
        __emit 0x74
        __emit 0x0b
        __emit 0x68
        __emit 0x8a
        __emit 0x8d
        __emit 0x42
        __emit 0x00
        __emit 0x56
        __emit 0xe8
        __emit 0x82
        __emit 0xf3
        __emit 0x72
        __emit 0x00
        __emit 0x8b
        __emit 0xc6
        __emit 0x5e
        __emit 0xc3
    }
}
