// cl: /DNDEBUG /MD /EHsc

class Thing;
class ModuleData;

class SpawnUnitBehavior
{
public:
    SpawnUnitBehavior(Thing *, const ModuleData *);
};

// ??0SpawnUnitBehavior@@QAE@PAVThing@@PBVModuleData@@@Z
__declspec(naked) SpawnUnitBehavior::SpawnUnitBehavior(Thing *, const ModuleData *)
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
        __emit 0xe0;
        __emit 0x9f;
        __emit 0xe0;
        __emit 0xff;
        __emit 0xc7;
        __emit 0x46;
        __emit 0x0c;
        __emit 0xd0;
        __emit 0xc9;
        __emit 0x09;
        __emit 0x01;
        __emit 0xc7;
        __emit 0x46;
        __emit 0x10;
        __emit 0xa0;
        __emit 0xcb;
        __emit 0x09;
        __emit 0x01;
        __emit 0x83;
        __emit 0xc8;
        __emit 0xff;
        __emit 0x89;
        __emit 0x46;
        __emit 0x18;
        __emit 0x89;
        __emit 0x46;
        __emit 0x1c;
        __emit 0xc7;
        __emit 0x46;
        __emit 0x14;
        __emit 0x00;
        __emit 0x00;
        __emit 0x00;
        __emit 0x00;
        __emit 0xc7;
        __emit 0x46;
        __emit 0x20;
        __emit 0xbc;
        __emit 0x6e;
        __emit 0x0a;
        __emit 0x01;
        __emit 0x8b;
        __emit 0x56;
        __emit 0x04;
        __emit 0xc7;
        __emit 0x06;
        __emit 0x94;
        __emit 0x6f;
        __emit 0x0a;
        __emit 0x01;
        __emit 0xc7;
        __emit 0x46;
        __emit 0x0c;
        __emit 0xd0;
        __emit 0x6e;
        __emit 0x0a;
        __emit 0x01;
        __emit 0xc7;
        __emit 0x46;
        __emit 0x10;
        __emit 0xc4;
        __emit 0x6e;
        __emit 0x0a;
        __emit 0x01;
        __emit 0xc7;
        __emit 0x46;
        __emit 0x20;
        __emit 0xc0;
        __emit 0x6e;
        __emit 0x0a;
        __emit 0x01;
        __emit 0x8a;
        __emit 0x42;
        __emit 0x1c;
        __emit 0x88;
        __emit 0x46;
        __emit 0x24;
        __emit 0x8b;
        __emit 0xc6;
        __emit 0x5e;
        __emit 0xc2;
        __emit 0x08;
        __emit 0x00;
    }
}
