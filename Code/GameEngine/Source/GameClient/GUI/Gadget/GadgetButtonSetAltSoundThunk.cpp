// cl: /DNDEBUG /MD /EHsc

class GameWindow
{
};

class AsciiString
{
};

__declspec(naked) void GadgetButtonSetAltSound(GameWindow *, AsciiString)
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
        __emit 0xd8;
        __emit 0x8d;
        __emit 0x02;
        __emit 0x01;
        __emit 0x50;
        __emit 0x64;
        __emit 0x89;
        __emit 0x25;
        __emit 0x00;
        __emit 0x00;
        __emit 0x00;
        __emit 0x00;
        __emit 0x8b;
        __emit 0x4c;
        __emit 0x24;
        __emit 0x10;
        __emit 0x85;
        __emit 0xc9;
        __emit 0xc7;
        __emit 0x44;
        __emit 0x24;
        __emit 0x08;
        __emit 0x00;
        __emit 0x00;
        __emit 0x00;
        __emit 0x00;
        __emit 0x74;
        __emit 0x16;
        __emit 0xe8;
        __emit 0x9e;
        __emit 0x9d;
        __emit 0xb8;
        __emit 0xff;
        __emit 0x85;
        __emit 0xc0;
        __emit 0x74;
        __emit 0x0d;
        __emit 0x8d;
        __emit 0x48;
        __emit 0x1c;
        __emit 0x8d;
        __emit 0x44;
        __emit 0x24;
        __emit 0x14;
        __emit 0x50;
        __emit 0xe8;
        __emit 0xe5;
        __emit 0xb4;
        __emit 0x3c;
        __emit 0x00;
        __emit 0x8d;
        __emit 0x4c;
        __emit 0x24;
        __emit 0x14;
        __emit 0xc7;
        __emit 0x44;
        __emit 0x24;
        __emit 0x08;
        __emit 0xff;
        __emit 0xff;
        __emit 0xff;
        __emit 0xff;
        __emit 0xe8;
        __emit 0x84;
        __emit 0xb1;
        __emit 0x3c;
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
        __emit 0xc3;
    }
}
