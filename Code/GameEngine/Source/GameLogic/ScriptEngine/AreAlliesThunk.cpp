// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class Player
{
};

__declspec(naked) bool areAllies(const Player *, const Player *)
{
    __asm {
        __emit 0x57;
        __emit 0x8b;
        __emit 0xf8;
        __emit 0x3b;
        __emit 0xfe;
        __emit 0x74;
        __emit 0x2a;
        __emit 0x8b;
        __emit 0x86;
        __emit 0x30;
        __emit 0x02;
        __emit 0x00;
        __emit 0x00;
        __emit 0x50;
        __emit 0x8b;
        __emit 0xcf;
        __emit 0xe8;
        __emit 0x15;
        __emit 0xf6;
        __emit 0xcd;
        __emit 0xff;
        __emit 0x83;
        __emit 0xf8;
        __emit 0x02;
        __emit 0x75;
        __emit 0x17;
        __emit 0x8b;
        __emit 0xbf;
        __emit 0x30;
        __emit 0x02;
        __emit 0x00;
        __emit 0x00;
        __emit 0x57;
        __emit 0x8b;
        __emit 0xce;
        __emit 0xe8;
        __emit 0x02;
        __emit 0xf6;
        __emit 0xcd;
        __emit 0xff;
        __emit 0x83;
        __emit 0xf8;
        __emit 0x02;
        __emit 0x75;
        __emit 0x04;
        __emit 0xb0;
        __emit 0x01;
        __emit 0x5f;
        __emit 0xc3;
        __emit 0x32;
        __emit 0xc0;
        __emit 0x5f;
        __emit 0xc3;
    }
}
