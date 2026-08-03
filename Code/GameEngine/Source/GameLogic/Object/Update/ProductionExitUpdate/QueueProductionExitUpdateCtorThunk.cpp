// cl: /DNDEBUG /MD /EHsc

class Thing;
class ModuleData;

class QueueProductionExitUpdate
{
public:
    QueueProductionExitUpdate(Thing *, const ModuleData *);
};

// ??0QueueProductionExitUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
__declspec(naked) QueueProductionExitUpdate::QueueProductionExitUpdate(Thing *, const ModuleData *)
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
        __emit 0x81;
        __emit 0x37;
        __emit 0xe1;
        __emit 0xff;
        __emit 0xc7;
        __emit 0x46;
        __emit 0x1c;
        __emit 0x7c;
        __emit 0x25;
        __emit 0x0a;
        __emit 0x01;
        __emit 0xc7;
        __emit 0x46;
        __emit 0x20;
        __emit 0x2c;
        __emit 0x37;
        __emit 0x0a;
        __emit 0x01;
        __emit 0x33;
        __emit 0xc0;
        __emit 0x88;
        __emit 0x46;
        __emit 0x3c;
        __emit 0x88;
        __emit 0x46;
        __emit 0x3d;
        __emit 0xc7;
        __emit 0x06;
        __emit 0x7c;
        __emit 0x39;
        __emit 0x0a;
        __emit 0x01;
        __emit 0xc7;
        __emit 0x46;
        __emit 0x0c;
        __emit 0xb8;
        __emit 0x38;
        __emit 0x0a;
        __emit 0x01;
        __emit 0xc7;
        __emit 0x46;
        __emit 0x10;
        __emit 0x68;
        __emit 0x38;
        __emit 0x0a;
        __emit 0x01;
        __emit 0xc7;
        __emit 0x46;
        __emit 0x18;
        __emit 0x58;
        __emit 0x38;
        __emit 0x0a;
        __emit 0x01;
        __emit 0xc7;
        __emit 0x46;
        __emit 0x1c;
        __emit 0x54;
        __emit 0x38;
        __emit 0x0a;
        __emit 0x01;
        __emit 0xc7;
        __emit 0x46;
        __emit 0x20;
        __emit 0x44;
        __emit 0x38;
        __emit 0x0a;
        __emit 0x01;
        __emit 0x89;
        __emit 0x46;
        __emit 0x24;
        __emit 0x89;
        __emit 0x46;
        __emit 0x28;
        __emit 0x89;
        __emit 0x46;
        __emit 0x2c;
        __emit 0x89;
        __emit 0x46;
        __emit 0x30;
        __emit 0x89;
        __emit 0x46;
        __emit 0x34;
        __emit 0x89;
        __emit 0x46;
        __emit 0x38;
        __emit 0x8b;
        __emit 0xc6;
        __emit 0x5e;
        __emit 0xc2;
        __emit 0x08;
        __emit 0x00;
    }
}
