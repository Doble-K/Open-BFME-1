// cl: /DNDEBUG /MD /EHsc

class SiegeDeploySpecialPowerModuleData
{
public:
    SiegeDeploySpecialPowerModuleData();
};

__declspec(naked) SiegeDeploySpecialPowerModuleData::SiegeDeploySpecialPowerModuleData()
{
    __asm {
        __emit 0x56;
        __emit 0x8b;
        __emit 0xf1;
        __emit 0xe8;
        __emit 0x8f;
        __emit 0xdb;
        __emit 0xdb;
        __emit 0xff;
        __emit 0x33;
        __emit 0xc0;
        __emit 0x89;
        __emit 0x86;
        __emit 0xd0;
        __emit 0x01;
        __emit 0x00;
        __emit 0x00;
        __emit 0x89;
        __emit 0x86;
        __emit 0xd4;
        __emit 0x01;
        __emit 0x00;
        __emit 0x00;
        __emit 0x88;
        __emit 0x86;
        __emit 0xd9;
        __emit 0x01;
        __emit 0x00;
        __emit 0x00;
        __emit 0x88;
        __emit 0x86;
        __emit 0xda;
        __emit 0x01;
        __emit 0x00;
        __emit 0x00;
        __emit 0xc7;
        __emit 0x06;
        __emit 0x98;
        __emit 0x75;
        __emit 0x0b;
        __emit 0x01;
        __emit 0xc6;
        __emit 0x86;
        __emit 0xd8;
        __emit 0x01;
        __emit 0x00;
        __emit 0x00;
        __emit 0x01;
        __emit 0xc7;
        __emit 0x86;
        __emit 0xdc;
        __emit 0x01;
        __emit 0x00;
        __emit 0x00;
        __emit 0x00;
        __emit 0x00;
        __emit 0xfa;
        __emit 0x43;
        __emit 0xc7;
        __emit 0x86;
        __emit 0xe0;
        __emit 0x01;
        __emit 0x00;
        __emit 0x00;
        __emit 0x00;
        __emit 0x00;
        __emit 0x48;
        __emit 0x43;
        __emit 0x8b;
        __emit 0xc6;
        __emit 0x5e;
        __emit 0xc3;
    }
}
