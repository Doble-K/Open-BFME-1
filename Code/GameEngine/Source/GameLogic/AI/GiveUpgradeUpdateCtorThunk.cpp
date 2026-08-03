// cl: /DNDEBUG /MD /EHsc

class Thing;
class ModuleData;

class GiveUpgradeUpdate
{
public:
    GiveUpgradeUpdate(Thing *, const ModuleData *);
};

// ??0GiveUpgradeUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
__declspec(naked) GiveUpgradeUpdate::GiveUpgradeUpdate(Thing *, const ModuleData *)
{
    __asm {
        __emit 0x8b;
        __emit 0x44;
        __emit 0x24;
        __emit 0x08;
        __emit 0x56;
        __emit 0x8b;
        __emit 0xf1;
        __emit 0x8b;
        __emit 0x4c;
        __emit 0x24;
        __emit 0x08;
        __emit 0x50;
        __emit 0x51;
        __emit 0x8b;
        __emit 0xce;
        __emit 0xe8;
        __emit 0xae;
        __emit 0x5a;
        __emit 0xdb;
        __emit 0xff;
        __emit 0x33;
        __emit 0xc0;
        __emit 0x88;
        __emit 0x86;
        __emit 0xe8;
        __emit 0x00;
        __emit 0x00;
        __emit 0x00;
        __emit 0x88;
        __emit 0x86;
        __emit 0xe9;
        __emit 0x00;
        __emit 0x00;
        __emit 0x00;
        __emit 0x89;
        __emit 0x86;
        __emit 0xec;
        __emit 0x00;
        __emit 0x00;
        __emit 0x00;
        __emit 0xc7;
        __emit 0x06;
        __emit 0x68;
        __emit 0x53;
        __emit 0x0b;
        __emit 0x01;
        __emit 0xc7;
        __emit 0x46;
        __emit 0x0c;
        __emit 0xa0;
        __emit 0x52;
        __emit 0x0b;
        __emit 0x01;
        __emit 0xc7;
        __emit 0x46;
        __emit 0x10;
        __emit 0x90;
        __emit 0x52;
        __emit 0x0b;
        __emit 0x01;
        __emit 0xc7;
        __emit 0x46;
        __emit 0x20;
        __emit 0x64;
        __emit 0x52;
        __emit 0x0b;
        __emit 0x01;
        __emit 0x8b;
        __emit 0xc6;
        __emit 0x5e;
        __emit 0xc2;
        __emit 0x08;
        __emit 0x00;
    }
}
