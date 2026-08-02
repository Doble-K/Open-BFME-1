// cl: /DNDEBUG /MD /EHsc

class ScienceInfo
{
public:
    ScienceInfo &operator=(const ScienceInfo &);
};

__declspec(naked) ScienceInfo &ScienceInfo::operator=(const ScienceInfo &)
{
    __asm {
        __emit 0x56;
        __emit 0x57;
        __emit 0x8b;
        __emit 0x7c;
        __emit 0x24;
        __emit 0x0c;
        __emit 0x57;
        __emit 0x8b;
        __emit 0xf1;
        __emit 0xe8;
        __emit 0x57;
        __emit 0x01;
        __emit 0xf6;
        __emit 0xff;
        __emit 0x8b;
        __emit 0x47;
        __emit 0x0c;
        __emit 0x8d;
        __emit 0x4f;
        __emit 0x10;
        __emit 0x51;
        __emit 0x8d;
        __emit 0x4e;
        __emit 0x10;
        __emit 0x89;
        __emit 0x46;
        __emit 0x0c;
        __emit 0xe8;
        __emit 0x50;
        __emit 0xff;
        __emit 0x79;
        __emit 0x00;
        __emit 0x8d;
        __emit 0x57;
        __emit 0x14;
        __emit 0x52;
        __emit 0x8d;
        __emit 0x4e;
        __emit 0x14;
        __emit 0xe8;
        __emit 0x44;
        __emit 0xff;
        __emit 0x79;
        __emit 0x00;
        __emit 0x8d;
        __emit 0x47;
        __emit 0x18;
        __emit 0x50;
        __emit 0x8d;
        __emit 0x4e;
        __emit 0x18;
        __emit 0xe8;
        __emit 0x8d;
        __emit 0x1b;
        __emit 0xf4;
        __emit 0xff;
        __emit 0x8b;
        __emit 0x4f;
        __emit 0x24;
        __emit 0x89;
        __emit 0x4e;
        __emit 0x24;
        __emit 0x8b;
        __emit 0x57;
        __emit 0x28;
        __emit 0x89;
        __emit 0x56;
        __emit 0x28;
        __emit 0x8a;
        __emit 0x47;
        __emit 0x2c;
        __emit 0x88;
        __emit 0x46;
        __emit 0x2c;
        __emit 0x5f;
        __emit 0x8b;
        __emit 0xc6;
        __emit 0x5e;
        __emit 0xc2;
        __emit 0x04;
        __emit 0x00;
    }
}
