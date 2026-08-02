// cl: /DNDEBUG /MD /EHsc

class W3DQuadrupedDrawModuleData
{
public:
    W3DQuadrupedDrawModuleData();
};

__declspec(naked) W3DQuadrupedDrawModuleData::W3DQuadrupedDrawModuleData()
{
    __asm {
        __emit 0x6a;
        __emit 0xff;
        __emit 0x68;
        __emit 0x38;
        __emit 0x9b;
        __emit 0x04;
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
        __emit 0x8b;
        __emit 0xf1;
        __emit 0x89;
        __emit 0x74;
        __emit 0x24;
        __emit 0x04;
        __emit 0xe8;
        __emit 0x7a;
        __emit 0x2a;
        __emit 0x94;
        __emit 0xff;
        __emit 0x68;
        __emit 0x28;
        __emit 0xd8;
        __emit 0x40;
        __emit 0x00;
        __emit 0x68;
        __emit 0xd9;
        __emit 0x7b;
        __emit 0x41;
        __emit 0x00;
        __emit 0x6a;
        __emit 0x04;
        __emit 0x6a;
        __emit 0x04;
        __emit 0x8d;
        __emit 0x86;
        __emit 0x5c;
        __emit 0x01;
        __emit 0x00;
        __emit 0x00;
        __emit 0x50;
        __emit 0xc7;
        __emit 0x44;
        __emit 0x24;
        __emit 0x24;
        __emit 0x00;
        __emit 0x00;
        __emit 0x00;
        __emit 0x00;
        __emit 0xc7;
        __emit 0x06;
        __emit 0x90;
        __emit 0xd1;
        __emit 0x11;
        __emit 0x01;
        __emit 0xe8;
        __emit 0x9a;
        __emit 0x70;
        __emit 0x33;
        __emit 0x00;
        __emit 0x8b;
        __emit 0x4c;
        __emit 0x24;
        __emit 0x08;
        __emit 0x8b;
        __emit 0xc6;
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
