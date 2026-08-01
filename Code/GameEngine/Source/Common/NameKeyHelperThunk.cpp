// cl: /DNDEBUG /MD /EHsc

enum NameKeyType
{
    NAMEKEY_INVALID = 0
};

class AsciiString
{
};

NameKeyType NAMEKEY(const AsciiString &)
{
    __asm {
        _emit 08Bh
        _emit 044h
        _emit 024h
        _emit 004h
        _emit 08Bh
        _emit 000h
        _emit 085h
        _emit 0C0h
        _emit 074h
        _emit 010h
        _emit 08Bh
        _emit 00Dh
        _emit 000h
        _emit 0D6h
        _emit 02Eh
        _emit 001h
        _emit 083h
        _emit 0C0h
        _emit 008h
        _emit 050h
        _emit 0E8h
        _emit 00Eh
        _emit 073h
        _emit 0F9h
        _emit 0FFh
        _emit 0C3h
        _emit 08Bh
        _emit 00Dh
        _emit 000h
        _emit 0D6h
        _emit 02Eh
        _emit 001h
        _emit 0B8h
        _emit 08Bh
        _emit 038h
        _emit 007h
        _emit 001h
        _emit 050h
        _emit 0E8h
        _emit 0FCh
        _emit 072h
        _emit 0F9h
        _emit 0FFh
        _emit 0C3h
    }
}
