// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class INI;
class ModuleData;

class AssistedTargetingUpdate
{
public:
    static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@AssistedTargetingUpdate@@SAPAVModuleData@@PAVINI@@@Z
__declspec(naked) ModuleData *AssistedTargetingUpdate::friend_newModuleData(INI *)
{
    __asm {
        __emit 0x56
        __emit 0x6a
        __emit 0x18
        __emit 0xe8
        __emit 0x78
        __emit 0xe7
        __emit 0x75
        __emit 0x00
        __emit 0x33
        __emit 0xd2
        __emit 0x83
        __emit 0xc4
        __emit 0x04
        __emit 0x3b
        __emit 0xc2
        __emit 0x74
        __emit 0x1a
        __emit 0xc7
        __emit 0x00
        __emit 0xe0
        __emit 0xb8
        __emit 0x08
        __emit 0x01
        __emit 0xc7
        __emit 0x40
        __emit 0x08
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x89
        __emit 0x50
        __emit 0x0c
        __emit 0x89
        __emit 0x50
        __emit 0x10
        __emit 0x89
        __emit 0x50
        __emit 0x14
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
        __emit 0x3b
        __emit 0xca
        __emit 0x74
        __emit 0x0b
        __emit 0x68
        __emit 0xc2
        __emit 0x4c
        __emit 0x41
        __emit 0x00
        __emit 0x56
        __emit 0xe8
        __emit 0x40
        __emit 0xe9
        __emit 0x72
        __emit 0x00
        __emit 0x8b
        __emit 0xc6
        __emit 0x5e
        __emit 0xc3
    }
}
