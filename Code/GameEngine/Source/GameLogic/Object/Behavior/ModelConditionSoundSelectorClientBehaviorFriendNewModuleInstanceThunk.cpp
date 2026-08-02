// cl: /DNDEBUG /MD /EHsc

class Module;
class Thing;
class ModuleData;

class ModelConditionSoundSelectorClientBehavior
{
public:
    static Module *friend_newModuleInstance(Thing *, const ModuleData *);
};

// ?friend_newModuleInstance@ModelConditionSoundSelectorClientBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
__declspec(naked) Module *ModelConditionSoundSelectorClientBehavior::friend_newModuleInstance(Thing *, const ModuleData *)
{
    __asm {
        __emit 0x6a;
        __emit 0xff;
        __emit 0x68;
        __emit 0xeb;
        __emit 0x18;
        __emit 0x00;
        __emit 0x01;
        __emit 0x64;
        __emit 0xa1;
        __emit 0x00;
        __emit 0x00;
        __emit 0x00;
        __emit 0x00;
        __emit 0x50;
        __emit 0x64;
        __emit 0x89;
        __emit 0x25;
        __emit 0x00;
        __emit 0x00;
        __emit 0x00;
        __emit 0x00;
        __emit 0x51;
        __emit 0x56;
        __emit 0x6a;
        __emit 0x10;
        __emit 0xe8;
        __emit 0x82;
        __emit 0xbd;
        __emit 0x75;
        __emit 0x00;
        __emit 0x8b;
        __emit 0xf0;
        __emit 0x83;
        __emit 0xc4;
        __emit 0x04;
        __emit 0x89;
        __emit 0x74;
        __emit 0x24;
        __emit 0x04;
        __emit 0x33;
        __emit 0xc0;
        __emit 0x3b;
        __emit 0xf0;
        __emit 0x89;
        __emit 0x44;
        __emit 0x24;
        __emit 0x10;
        __emit 0x74;
        __emit 0x27;
        __emit 0x8b;
        __emit 0x44;
        __emit 0x24;
        __emit 0x1c;
        __emit 0x8b;
        __emit 0x4c;
        __emit 0x24;
        __emit 0x18;
        __emit 0x50;
        __emit 0x51;
        __emit 0x8b;
        __emit 0xce;
        __emit 0xe8;
        __emit 0xa2;
        __emit 0xc6;
        __emit 0xed;
        __emit 0xff;
        __emit 0xc7;
        __emit 0x46;
        __emit 0x0c;
        __emit 0xf8;
        __emit 0xac;
        __emit 0x08;
        __emit 0x01;
        __emit 0xc7;
        __emit 0x06;
        __emit 0x3c;
        __emit 0xe5;
        __emit 0x08;
        __emit 0x01;
        __emit 0xc7;
        __emit 0x46;
        __emit 0x0c;
        __emit 0x2c;
        __emit 0xe5;
        __emit 0x08;
        __emit 0x01;
        __emit 0x8b;
        __emit 0xc6;
        __emit 0x8b;
        __emit 0x4c;
        __emit 0x24;
        __emit 0x08;
        __emit 0x5e;
        __emit 0x64;
        __emit 0x89;
        __emit 0x0d;
        __emit 0x00;
        __emit 0x00;
        __emit 0x00;
        __emit 0x00;
        __emit 0x83;
        __emit 0xc4;
        __emit 0x10;
        __emit 0xc3;
    }
}
