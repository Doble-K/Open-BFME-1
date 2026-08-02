// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class INI;
class ModuleData;

class AttributeModifierUpgrade
{
public:
    static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@AttributeModifierUpgrade@@SAPAVModuleData@@PAVINI@@@Z
__declspec(naked) ModuleData *AttributeModifierUpgrade::friend_newModuleData(INI *)
{
    __asm {
        __emit 0x56
        __emit 0x6a
        __emit 0x74
        __emit 0xe8
        __emit 0xd8
        __emit 0x65
        __emit 0x75
        __emit 0x00
        __emit 0x8b
        __emit 0xf0
        __emit 0x83
        __emit 0xc4
        __emit 0x04
        __emit 0x85
        __emit 0xf6
        __emit 0x74
        __emit 0x17
        __emit 0x8d
        __emit 0x4e
        __emit 0x08
        __emit 0xe8
        __emit 0x3d
        __emit 0x37
        __emit 0xee
        __emit 0xff
        __emit 0xc7
        __emit 0x06
        __emit 0xa0
        __emit 0xf5
        __emit 0x08
        __emit 0x01
        __emit 0xc7
        __emit 0x46
        __emit 0x70
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
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
        __emit 0xb6
        __emit 0x25
        __emit 0x42
        __emit 0x00
        __emit 0x56
        __emit 0xe8
        __emit 0xa3
        __emit 0x67
        __emit 0x72
        __emit 0x00
        __emit 0x8b
        __emit 0xc6
        __emit 0x5e
        __emit 0xc3
    }
}
