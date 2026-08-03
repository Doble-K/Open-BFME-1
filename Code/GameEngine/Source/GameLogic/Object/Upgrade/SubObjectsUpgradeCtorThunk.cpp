// cl: /DNDEBUG /MD /EHsc

class Thing;
class ModuleData;

class SubObjectsUpgrade
{
public:
    SubObjectsUpgrade(Thing *, const ModuleData *);
};

// ??0SubObjectsUpgrade@@QAE@PAVThing@@PBVModuleData@@@Z
__declspec(naked) SubObjectsUpgrade::SubObjectsUpgrade(Thing *, const ModuleData *)
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
        __emit 0x61;
        __emit 0x3f;
        __emit 0xd3;
        __emit 0xff;
        __emit 0xc7;
        __emit 0x06;
        __emit 0xc4;
        __emit 0xdf;
        __emit 0x0c;
        __emit 0x01;
        __emit 0xc7;
        __emit 0x46;
        __emit 0x0c;
        __emit 0x00;
        __emit 0xdf;
        __emit 0x0c;
        __emit 0x01;
        __emit 0xc7;
        __emit 0x46;
        __emit 0x10;
        __emit 0xb0;
        __emit 0xde;
        __emit 0x0c;
        __emit 0x01;
        __emit 0xc7;
        __emit 0x46;
        __emit 0x18;
        __emit 0x9c;
        __emit 0xde;
        __emit 0x0c;
        __emit 0x01;
        __emit 0x8b;
        __emit 0x15;
        __emit 0x98;
        __emit 0x08;
        __emit 0x2f;
        __emit 0x01;
        __emit 0x8b;
        __emit 0x42;
        __emit 0x3c;
        __emit 0x89;
        __emit 0x46;
        __emit 0x1c;
        __emit 0xc6;
        __emit 0x46;
        __emit 0x20;
        __emit 0x00;
        __emit 0x8b;
        __emit 0xc6;
        __emit 0x5e;
        __emit 0xc2;
        __emit 0x08;
        __emit 0x00;
    }
}
