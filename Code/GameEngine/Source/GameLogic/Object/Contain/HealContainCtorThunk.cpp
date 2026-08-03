// cl: /DNDEBUG /MD /EHsc

class Thing;
class ModuleData;

class HealContain
{
public:
    HealContain(Thing *, const ModuleData *);
};

// ??0HealContain@@QAE@PAVThing@@PBVModuleData@@@Z
__declspec(naked) HealContain::HealContain(Thing *, const ModuleData *)
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
        __emit 0xa5;
        __emit 0x6c;
        __emit 0xe1;
        __emit 0xff;
        __emit 0xc7;
        __emit 0x06;
        __emit 0x78;
        __emit 0xbc;
        __emit 0x0a;
        __emit 0x01;
        __emit 0xc7;
        __emit 0x46;
        __emit 0x0c;
        __emit 0xb0;
        __emit 0xbb;
        __emit 0x0a;
        __emit 0x01;
        __emit 0xc7;
        __emit 0x46;
        __emit 0x10;
        __emit 0xa0;
        __emit 0xbb;
        __emit 0x0a;
        __emit 0x01;
        __emit 0xc7;
        __emit 0x46;
        __emit 0x20;
        __emit 0xf8;
        __emit 0xb9;
        __emit 0x0a;
        __emit 0x01;
        __emit 0xc7;
        __emit 0x46;
        __emit 0x24;
        __emit 0xdc;
        __emit 0xb9;
        __emit 0x0a;
        __emit 0x01;
        __emit 0xc7;
        __emit 0x46;
        __emit 0x28;
        __emit 0xd8;
        __emit 0xb9;
        __emit 0x0a;
        __emit 0x01;
        __emit 0xc7;
        __emit 0x46;
        __emit 0x2c;
        __emit 0xc8;
        __emit 0xb9;
        __emit 0x0a;
        __emit 0x01;
        __emit 0xc7;
        __emit 0x46;
        __emit 0x30;
        __emit 0x8c;
        __emit 0xb9;
        __emit 0x0a;
        __emit 0x01;
        __emit 0xc7;
        __emit 0x46;
        __emit 0x34;
        __emit 0x7c;
        __emit 0xb9;
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
