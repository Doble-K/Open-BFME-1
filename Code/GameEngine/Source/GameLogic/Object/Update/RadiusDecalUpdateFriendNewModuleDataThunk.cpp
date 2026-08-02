// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class INI;
class ModuleData;

class RadiusDecalUpdate
{
public:
    static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@RadiusDecalUpdate@@SAPAVModuleData@@PAVINI@@@Z
__declspec(naked) ModuleData *RadiusDecalUpdate::friend_newModuleData(INI *)
{
    __asm {
        __emit 0x56
        __emit 0x6a
        __emit 0x08
        __emit 0xe8
        __emit 0xd8
        __emit 0xe0
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
        __emit 0x10
        __emit 0xce
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
        __emit 0xf0
        __emit 0x20
        __emit 0x44
        __emit 0x00
        __emit 0x56
        __emit 0xe8
        __emit 0xb2
        __emit 0xe2
        __emit 0x72
        __emit 0x00
        __emit 0x8b
        __emit 0xc6
        __emit 0x5e
        __emit 0xc3
    }
}
