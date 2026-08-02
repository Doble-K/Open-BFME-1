// cl: /DNDEBUG /MD /EHsc

class Module;
class Thing;
class ModuleData;

class LargeGroupBonusUpdate
{
public:
    static Module *friend_newModuleInstance(Thing *, const ModuleData *);
};

// ?friend_newModuleInstance@LargeGroupBonusUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
__declspec(naked) Module *LargeGroupBonusUpdate::friend_newModuleInstance(Thing *, const ModuleData *)
{
    __asm {
        __emit 0x6a;
        __emit 0xff;
        __emit 0x68;
        __emit 0x6b;
        __emit 0xf1;
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
        __emit 0x6a;
        __emit 0x2c;
        __emit 0xe8;
        __emit 0xe3;
        __emit 0x93;
        __emit 0x76;
        __emit 0x00;
        __emit 0x83;
        __emit 0xc4;
        __emit 0x04;
        __emit 0x89;
        __emit 0x04;
        __emit 0x24;
        __emit 0x85;
        __emit 0xc0;
        __emit 0xc7;
        __emit 0x44;
        __emit 0x24;
        __emit 0x0c;
        __emit 0x00;
        __emit 0x00;
        __emit 0x00;
        __emit 0x00;
        __emit 0x74;
        __emit 0x20;
        __emit 0x8b;
        __emit 0x4c;
        __emit 0x24;
        __emit 0x18;
        __emit 0x8b;
        __emit 0x54;
        __emit 0x24;
        __emit 0x14;
        __emit 0x51;
        __emit 0x52;
        __emit 0x8b;
        __emit 0xc8;
        __emit 0xe8;
        __emit 0x3d;
        __emit 0x9a;
        __emit 0xef;
        __emit 0xff;
        __emit 0x8b;
        __emit 0x4c;
        __emit 0x24;
        __emit 0x04;
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
        __emit 0x8b;
        __emit 0x4c;
        __emit 0x24;
        __emit 0x04;
        __emit 0x33;
        __emit 0xc0;
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
