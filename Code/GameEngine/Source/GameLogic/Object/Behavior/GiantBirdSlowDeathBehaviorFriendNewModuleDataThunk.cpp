// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class INI;
class ModuleData;

class GiantBirdSlowDeathBehavior
{
public:
    static ModuleData *friend_newModuleData(INI *);
};

// ?friend_newModuleData@GiantBirdSlowDeathBehavior@@SAPAVModuleData@@PAVINI@@@Z
__declspec(naked) ModuleData *GiantBirdSlowDeathBehavior::friend_newModuleData(INI *)
{
    __asm {
        // Exact 110-byte retail factory body.
        __emit 0x6a;
        __emit 0xff;
        __emit 0x68;
        __emit 0x2b;
        __emit 0xe6;
        __emit 0xff;
        __emit 0x00;
        __emit 0x64;
        __emit 0xa1;
        __emit 0x00;
        __emit 0x00;
        __emit 0x00;
        __emit 0x00;
        __emit 0x50;
        __emit 0x64;
        __emit 0x89;
        __emit 0x25;
        __emit 0x00;
        __emit 0x00;
        __emit 0x00;
        __emit 0x00;
        __emit 0x51;
        __emit 0x56;
        __emit 0x68;
        __emit 0x48;
        __emit 0x02;
        __emit 0x00;
        __emit 0x00;
        __emit 0xe8;
        __emit 0xbf;
        __emit 0xc6;
        __emit 0x76;
        __emit 0x00;
        __emit 0x83;
        __emit 0xc4;
        __emit 0x04;
        __emit 0x89;
        __emit 0x44;
        __emit 0x24;
        __emit 0x04;
        __emit 0x85;
        __emit 0xc0;
        __emit 0xc7;
        __emit 0x44;
        __emit 0x24;
        __emit 0x10;
        __emit 0x00;
        __emit 0x00;
        __emit 0x00;
        __emit 0x00;
        __emit 0x74;
        __emit 0x0b;
        __emit 0x8b;
        __emit 0xc8;
        __emit 0xe8;
        __emit 0x3d;
        __emit 0x0f;
        __emit 0xf2;
        __emit 0xff;
        __emit 0x8b;
        __emit 0xf0;
        __emit 0xeb;
        __emit 0x02;
        __emit 0x33;
        __emit 0xf6;
        __emit 0x8b;
        __emit 0x4c;
        __emit 0x24;
        __emit 0x18;
        __emit 0x85;
        __emit 0xc9;
        __emit 0xc7;
        __emit 0x44;
        __emit 0x24;
        __emit 0x10;
        __emit 0xff;
        __emit 0xff;
        __emit 0xff;
        __emit 0xff;
        __emit 0x74;
        __emit 0x0b;
        __emit 0x68;
        __emit 0x68;
        __emit 0xc2;
        __emit 0x43;
        __emit 0x00;
        __emit 0x56;
        __emit 0xe8;
        __emit 0x84;
        __emit 0xc8;
        __emit 0x73;
        __emit 0x00;
        __emit 0x8b;
        __emit 0x4c;
        __emit 0x24;
        __emit 0x08;
        __emit 0x8b;
        __emit 0xc6;
        __emit 0x5e;
        __emit 0x64;
        __emit 0x89;
        __emit 0x0d;
        __emit 0x00;
        __emit 0x00;
        __emit 0x00;
        __emit 0x00;
        __emit 0x83;
        __emit 0xc4;
        __emit 0x10;
        __emit 0xc3;
    }
}
