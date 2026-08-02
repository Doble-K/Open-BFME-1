// cl: /DNDEBUG /MD /EHsc

class TexBufferClass
{
public:
    TexBufferClass(int, const char *);
};

__declspec(naked) TexBufferClass::TexBufferClass(int, const char *)
{
    __asm {
        __emit 0x8b;
        __emit 0x44;
        __emit 0x24;
        __emit 0x08;
        __emit 0x56;
        __emit 0x57;
        __emit 0x6a;
        __emit 0x00;
        __emit 0x8b;
        __emit 0xf1;
        __emit 0x8b;
        __emit 0x4c;
        __emit 0x24;
        __emit 0x10;
        __emit 0x50;
        __emit 0x51;
        __emit 0x8b;
        __emit 0xce;
        __emit 0xe8;
        __emit 0x49;
        __emit 0xe5;
        __emit 0xff;
        __emit 0xff;
        __emit 0x8b;
        __emit 0x4e;
        __emit 0x10;
        __emit 0x8b;
        __emit 0x7e;
        __emit 0x0c;
        __emit 0xc1;
        __emit 0xe1;
        __emit 0x02;
        __emit 0x8b;
        __emit 0xd1;
        __emit 0xc1;
        __emit 0xe9;
        __emit 0x02;
        __emit 0xc7;
        __emit 0x06;
        __emit 0x40;
        __emit 0xc3;
        __emit 0x13;
        __emit 0x01;
        __emit 0x33;
        __emit 0xc0;
        __emit 0xf3;
        __emit 0xab;
        __emit 0x8b;
        __emit 0xca;
        __emit 0x83;
        __emit 0xe1;
        __emit 0x03;
        __emit 0xf3;
        __emit 0xaa;
        __emit 0x5f;
        __emit 0x8b;
        __emit 0xc6;
        __emit 0x5e;
        __emit 0xc2;
        __emit 0x08;
        __emit 0x00;
    }
}
