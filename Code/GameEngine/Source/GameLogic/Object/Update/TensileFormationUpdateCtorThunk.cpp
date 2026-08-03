// cl: /DNDEBUG /MD /EHsc

class Thing;
class ModuleData;

class TensileFormationUpdate
{
public:
    TensileFormationUpdate(Thing *, const ModuleData *);
};

// ??0TensileFormationUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
__declspec(naked) TensileFormationUpdate::TensileFormationUpdate(Thing *, const ModuleData *)
{
    __asm {
        __emit 0x8b;
        __emit 0x44;
        __emit 0x24;
        __emit 0x08;
        __emit 0x56;
        __emit 0x57;
        __emit 0x8b;
        __emit 0xf1;
        __emit 0x8b;
        __emit 0x4c;
        __emit 0x24;
        __emit 0x0c;
        __emit 0x50;
        __emit 0x51;
        __emit 0x8b;
        __emit 0xce;
        __emit 0xe8;
        __emit 0x7f;
        __emit 0x41;
        __emit 0xdc;
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
        __emit 0xfc;
        __emit 0x1b;
        __emit 0x0a;
        __emit 0x01;
        __emit 0x33;
        __emit 0xc0;
        __emit 0xc7;
        __emit 0x06;
        __emit 0x5c;
        __emit 0x26;
        __emit 0x0b;
        __emit 0x01;
        __emit 0xc7;
        __emit 0x46;
        __emit 0x0c;
        __emit 0x98;
        __emit 0x25;
        __emit 0x0b;
        __emit 0x01;
        __emit 0xc7;
        __emit 0x46;
        __emit 0x10;
        __emit 0x88;
        __emit 0x25;
        __emit 0x0b;
        __emit 0x01;
        __emit 0x89;
        __emit 0x86;
        __emit 0xd4;
        __emit 0x00;
        __emit 0x00;
        __emit 0x00;
        __emit 0x89;
        __emit 0x86;
        __emit 0xd8;
        __emit 0x00;
        __emit 0x00;
        __emit 0x00;
        __emit 0x89;
        __emit 0x86;
        __emit 0xdc;
        __emit 0x00;
        __emit 0x00;
        __emit 0x00;
        __emit 0x8d;
        __emit 0x7e;
        __emit 0x14;
        __emit 0xb9;
        __emit 0x30;
        __emit 0x00;
        __emit 0x00;
        __emit 0x00;
        __emit 0xf3;
        __emit 0xab;
        __emit 0x5f;
        __emit 0x8b;
        __emit 0xc6;
        __emit 0x5e;
        __emit 0xc2;
        __emit 0x08;
        __emit 0x00;
    }
}
