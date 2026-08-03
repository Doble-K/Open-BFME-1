// cl: /DNDEBUG /MD /EHsc

class StringClass
{
    void Store_Length(int);
};

// ?Store_Length@StringClass@@AAEXH@Z
__declspec(naked) void StringClass::Store_Length(int)
{
    __asm {
        __emit 0x8b;
        __emit 0x01;
        __emit 0x3b;
        __emit 0x05;
        __emit 0x24;
        __emit 0x91;
        __emit 0x2d;
        __emit 0x01;
        __emit 0x74;
        __emit 0x07;
        __emit 0x8b;
        __emit 0x4c;
        __emit 0x24;
        __emit 0x04;
        __emit 0x89;
        __emit 0x48;
        __emit 0xfc;
        __emit 0xc2;
        __emit 0x04;
        __emit 0x00;
    }
}
