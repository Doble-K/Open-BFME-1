// cl: /DNDEBUG /MD /EHsc

class UnicodeString
{
};

class LANGameInfo
{
public:
    void setName(UnicodeString);
};

__declspec(naked) void LANGameInfo::setName(UnicodeString)
{
    __asm {
        __emit 0x64;
        __emit 0xa1;
        __emit 0x00;
        __emit 0x00;
        __emit 0x00;
        __emit 0x00;
        __emit 0x6a;
        __emit 0xff;
        __emit 0x68;
        __emit 0x58;
        __emit 0x62;
        __emit 0x04;
        __emit 0x01;
        __emit 0x50;
        __emit 0x64;
        __emit 0x89;
        __emit 0x25;
        __emit 0x00;
        __emit 0x00;
        __emit 0x00;
        __emit 0x00;
        __emit 0x8d;
        __emit 0x44;
        __emit 0x24;
        __emit 0x10;
        __emit 0x81;
        __emit 0xc1;
        __emit 0xa0;
        __emit 0x03;
        __emit 0x00;
        __emit 0x00;
        __emit 0x50;
        __emit 0xc7;
        __emit 0x44;
        __emit 0x24;
        __emit 0x0c;
        __emit 0x00;
        __emit 0x00;
        __emit 0x00;
        __emit 0x00;
        __emit 0xe8;
        __emit 0x83;
        __emit 0x30;
        __emit 0x20;
        __emit 0x00;
        __emit 0x8d;
        __emit 0x4c;
        __emit 0x24;
        __emit 0x10;
        __emit 0xc7;
        __emit 0x44;
        __emit 0x24;
        __emit 0x08;
        __emit 0xff;
        __emit 0xff;
        __emit 0xff;
        __emit 0xff;
        __emit 0xe8;
        __emit 0x12;
        __emit 0x2d;
        __emit 0x20;
        __emit 0x00;
        __emit 0x8b;
        __emit 0x0c;
        __emit 0x24;
        __emit 0x64;
        __emit 0x89;
        __emit 0x0d;
        __emit 0x00;
        __emit 0x00;
        __emit 0x00;
        __emit 0x00;
        __emit 0x83;
        __emit 0xc4;
        __emit 0x0c;
        __emit 0xc2;
        __emit 0x04;
        __emit 0x00;
    }
}
