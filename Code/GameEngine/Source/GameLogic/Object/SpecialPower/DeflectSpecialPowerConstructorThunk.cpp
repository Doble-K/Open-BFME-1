// cl: /DNDEBUG /MD /EHsc

class Thing;
class ModuleData;

class DeflectSpecialPower
{
public:
    DeflectSpecialPower(Thing *, const ModuleData *);
};

// ??0DeflectSpecialPower@@QAE@PAVThing@@PBVModuleData@@@Z
__declspec(naked) DeflectSpecialPower::DeflectSpecialPower(Thing *, const ModuleData *)
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
        __emit 0x7c;
        __emit 0x3b;
        __emit 0xdc;
        __emit 0xff;
        __emit 0xc7;
        __emit 0x46;
        __emit 0x38;
        __emit 0xe4;
        __emit 0x1d;
        __emit 0x0a;
        __emit 0x01;
        __emit 0x32;
        __emit 0xc0;
        __emit 0x88;
        __emit 0x46;
        __emit 0x3c;
        __emit 0x88;
        __emit 0x46;
        __emit 0x3d;
        __emit 0xc7;
        __emit 0x06;
        __emit 0xec;
        __emit 0x44;
        __emit 0x0b;
        __emit 0x01;
        __emit 0xc7;
        __emit 0x46;
        __emit 0x0c;
        __emit 0x28;
        __emit 0x44;
        __emit 0x0b;
        __emit 0x01;
        __emit 0xc7;
        __emit 0x46;
        __emit 0x10;
        __emit 0x1c;
        __emit 0x44;
        __emit 0x0b;
        __emit 0x01;
        __emit 0xc7;
        __emit 0x46;
        __emit 0x20;
        __emit 0xf0;
        __emit 0x43;
        __emit 0x0b;
        __emit 0x01;
        __emit 0xc7;
        __emit 0x46;
        __emit 0x24;
        __emit 0x78;
        __emit 0x43;
        __emit 0x0b;
        __emit 0x01;
        __emit 0xc7;
        __emit 0x46;
        __emit 0x38;
        __emit 0x58;
        __emit 0x43;
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
