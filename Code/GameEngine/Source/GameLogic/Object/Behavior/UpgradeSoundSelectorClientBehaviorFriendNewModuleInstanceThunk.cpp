// cl: /DNDEBUG /MD /EHsc

class Module;
class Thing;
class ModuleData;

class UpgradeSoundSelectorClientBehavior
{
public:
    static Module *friend_newModuleInstance(Thing *, const ModuleData *);
};

// ?friend_newModuleInstance@UpgradeSoundSelectorClientBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
__declspec(naked) Module *UpgradeSoundSelectorClientBehavior::friend_newModuleInstance(Thing *, const ModuleData *)
{
    __asm {
        __emit 0x6a;
        __emit 0xff;
        __emit 0x68;
        __emit 0x6b;
        __emit 0x16;
        __emit 0x00;
        __emit 0x01;
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
        __emit 0x6a;
        __emit 0x10;
        __emit 0xe8;
        __emit 0xe2;
        __emit 0xd3;
        __emit 0x75;
        __emit 0x00;
        __emit 0x8b;
        __emit 0xf0;
        __emit 0x83;
        __emit 0xc4;
        __emit 0x04;
        __emit 0x89;
        __emit 0x74;
        __emit 0x24;
        __emit 0x04;
        __emit 0x33;
        __emit 0xc0;
        __emit 0x3b;
        __emit 0xf0;
        __emit 0x89;
        __emit 0x44;
        __emit 0x24;
        __emit 0x10;
        __emit 0x74;
        __emit 0x27;
        __emit 0x8b;
        __emit 0x44;
        __emit 0x24;
        __emit 0x1c;
        __emit 0x8b;
        __emit 0x4c;
        __emit 0x24;
        __emit 0x18;
        __emit 0x50;
        __emit 0x51;
        __emit 0x8b;
        __emit 0xce;
        __emit 0xe8;
        __emit 0x02;
        __emit 0xdd;
        __emit 0xed;
        __emit 0xff;
        __emit 0xc7;
        __emit 0x46;
        __emit 0x0c;
        __emit 0xf8;
        __emit 0xac;
        __emit 0x08;
        __emit 0x01;
        __emit 0xc7;
        __emit 0x06;
        __emit 0x18;
        __emit 0xad;
        __emit 0x08;
        __emit 0x01;
        __emit 0xc7;
        __emit 0x46;
        __emit 0x0c;
        __emit 0x08;
        __emit 0xad;
        __emit 0x08;
        __emit 0x01;
        __emit 0x8b;
        __emit 0xc6;
        __emit 0x8b;
        __emit 0x4c;
        __emit 0x24;
        __emit 0x08;
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
