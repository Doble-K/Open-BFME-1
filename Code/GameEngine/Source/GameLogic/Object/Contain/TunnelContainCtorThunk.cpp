// cl: /DNDEBUG /MD /EHsc

class Thing;
class ModuleData;

class TunnelContain
{
public:
    TunnelContain(Thing *, const ModuleData *);
};

// ??0TunnelContain@@QAE@PAVThing@@PBVModuleData@@@Z
__declspec(naked) TunnelContain::TunnelContain(Thing *, const ModuleData *)
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
        __emit 0xc5;
        __emit 0x7f;
        __emit 0xe0;
        __emit 0xff;
        __emit 0xc7;
        __emit 0x06;
        __emit 0xb8;
        __emit 0xdd;
        __emit 0x0a;
        __emit 0x01;
        __emit 0xc7;
        __emit 0x46;
        __emit 0x0c;
        __emit 0xf0;
        __emit 0xdc;
        __emit 0x0a;
        __emit 0x01;
        __emit 0xc7;
        __emit 0x46;
        __emit 0x10;
        __emit 0xe0;
        __emit 0xdc;
        __emit 0x0a;
        __emit 0x01;
        __emit 0xc7;
        __emit 0x46;
        __emit 0x20;
        __emit 0x38;
        __emit 0xdb;
        __emit 0x0a;
        __emit 0x01;
        __emit 0xc7;
        __emit 0x46;
        __emit 0x24;
        __emit 0x18;
        __emit 0xdb;
        __emit 0x0a;
        __emit 0x01;
        __emit 0xc7;
        __emit 0x46;
        __emit 0x28;
        __emit 0x14;
        __emit 0xdb;
        __emit 0x0a;
        __emit 0x01;
        __emit 0xc7;
        __emit 0x46;
        __emit 0x2c;
        __emit 0x04;
        __emit 0xdb;
        __emit 0x0a;
        __emit 0x01;
        __emit 0xc7;
        __emit 0x46;
        __emit 0x30;
        __emit 0xc8;
        __emit 0xda;
        __emit 0x0a;
        __emit 0x01;
        __emit 0xc7;
        __emit 0x46;
        __emit 0x34;
        __emit 0xb8;
        __emit 0xda;
        __emit 0x0a;
        __emit 0x01;
        __emit 0xc6;
        __emit 0x86;
        __emit 0xd4;
        __emit 0x00;
        __emit 0x00;
        __emit 0x00;
        __emit 0x01;
        __emit 0xc6;
        __emit 0x86;
        __emit 0xd5;
        __emit 0x00;
        __emit 0x00;
        __emit 0x00;
        __emit 0x00;
        __emit 0x8b;
        __emit 0xc6;
        __emit 0x5e;
        __emit 0xc2;
        __emit 0x08;
        __emit 0x00;
    }
}
