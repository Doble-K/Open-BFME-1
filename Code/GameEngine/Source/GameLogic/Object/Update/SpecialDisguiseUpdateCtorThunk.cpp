// cl: /DNDEBUG /MD /EHsc

class Thing;
class ModuleData;

class SpecialDisguiseUpdate
{
public:
    SpecialDisguiseUpdate(Thing *, const ModuleData *);
};

__declspec(naked) SpecialDisguiseUpdate::SpecialDisguiseUpdate(Thing *, const ModuleData *)
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
        __emit 0x2e;
        __emit 0xbc;
        __emit 0xda;
        __emit 0xff;
        __emit 0xc7;
        __emit 0x86;
        __emit 0xe8;
        __emit 0x00;
        __emit 0x00;
        __emit 0x00;
        __emit 0x2c;
        __emit 0x37;
        __emit 0x0a;
        __emit 0x01;
        __emit 0x33;
        __emit 0xc0;
        __emit 0x89;
        __emit 0x86;
        __emit 0xec;
        __emit 0x00;
        __emit 0x00;
        __emit 0x00;
        __emit 0x88;
        __emit 0x86;
        __emit 0xf0;
        __emit 0x00;
        __emit 0x00;
        __emit 0x00;
        __emit 0xc7;
        __emit 0x06;
        __emit 0x08;
        __emit 0x77;
        __emit 0x0b;
        __emit 0x01;
        __emit 0xc7;
        __emit 0x46;
        __emit 0x0c;
        __emit 0x40;
        __emit 0x76;
        __emit 0x0b;
        __emit 0x01;
        __emit 0xc7;
        __emit 0x46;
        __emit 0x10;
        __emit 0x30;
        __emit 0x76;
        __emit 0x0b;
        __emit 0x01;
        __emit 0xc7;
        __emit 0x46;
        __emit 0x20;
        __emit 0x04;
        __emit 0x76;
        __emit 0x0b;
        __emit 0x01;
        __emit 0xc7;
        __emit 0x86;
        __emit 0xe8;
        __emit 0x00;
        __emit 0x00;
        __emit 0x00;
        __emit 0xf4;
        __emit 0x75;
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
