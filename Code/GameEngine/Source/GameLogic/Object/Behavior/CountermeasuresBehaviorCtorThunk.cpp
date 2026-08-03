// cl: /DNDEBUG /MD /EHsc

class Thing;
class ModuleData;

class CountermeasuresBehavior
{
public:
    CountermeasuresBehavior(Thing *, const ModuleData *);
};

// ??0CountermeasuresBehavior@@QAE@PAVThing@@PBVModuleData@@@Z
__declspec(naked) CountermeasuresBehavior::CountermeasuresBehavior(Thing *, const ModuleData *)
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
        __emit 0xa7;
        __emit 0xd6;
        __emit 0xe4;
        __emit 0xff;
        __emit 0xc7;
        __emit 0x46;
        __emit 0x50;
        __emit 0xd0;
        __emit 0x2f;
        __emit 0x0a;
        __emit 0x01;
        __emit 0xc7;
        __emit 0x06;
        __emit 0xdc;
        __emit 0x30;
        __emit 0x0a;
        __emit 0x01;
        __emit 0xc7;
        __emit 0x46;
        __emit 0x0c;
        __emit 0x18;
        __emit 0x30;
        __emit 0x0a;
        __emit 0x01;
        __emit 0xc7;
        __emit 0x46;
        __emit 0x10;
        __emit 0x08;
        __emit 0x30;
        __emit 0x0a;
        __emit 0x01;
        __emit 0xc7;
        __emit 0x46;
        __emit 0x20;
        __emit 0x04;
        __emit 0x30;
        __emit 0x0a;
        __emit 0x01;
        __emit 0xc7;
        __emit 0x46;
        __emit 0x24;
        __emit 0xf0;
        __emit 0x2f;
        __emit 0x0a;
        __emit 0x01;
        __emit 0xc7;
        __emit 0x46;
        __emit 0x50;
        __emit 0xe0;
        __emit 0x2f;
        __emit 0x0a;
        __emit 0x01;
        __emit 0x8b;
        __emit 0xc6;
        __emit 0x5e;
        __emit 0xc2;
        __emit 0x08;
        __emit 0x00;
    }
}
