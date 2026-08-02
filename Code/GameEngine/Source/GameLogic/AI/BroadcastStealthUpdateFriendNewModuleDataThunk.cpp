// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class INI;
class ModuleData;

class BroadcastStealthUpdate
{
public:
    static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@BroadcastStealthUpdate@@SAPAVModuleData@@PAVINI@@@Z
__declspec(naked) ModuleData *BroadcastStealthUpdate::friend_newModuleData(INI *)
{
    __asm {
        __emit 0x56
        __emit 0x68
        __emit 0x94
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xe8
        __emit 0xd5
        __emit 0x7b
        __emit 0x75
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x04
        __emit 0x85
        __emit 0xc0
        __emit 0x74
        __emit 0x0b
        __emit 0x8b
        __emit 0xc8
        __emit 0xe8
        __emit 0x9e
        __emit 0x45
        __emit 0xef
        __emit 0xff
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
        __emit 0xf3
        __emit 0x94
        __emit 0x40
        __emit 0x00
        __emit 0x56
        __emit 0xe8
        __emit 0xae
        __emit 0x7d
        __emit 0x72
        __emit 0x00
        __emit 0x8b
        __emit 0xc6
        __emit 0x5e
        __emit 0xc3
    }
}
