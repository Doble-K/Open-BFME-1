// cl: /DNDEBUG /MD /EHsc

class UnicodeString
{
};

class DisplayString
{
public:
    virtual UnicodeString getText();
};

__declspec(naked) UnicodeString DisplayString::getText()
{
    __asm {
        _emit 051h
        _emit 056h
        _emit 08Bh
        _emit 074h
        _emit 024h
        _emit 00Ch
        _emit 083h
        _emit 0C1h
        _emit 004h
        _emit 051h
        _emit 08Bh
        _emit 0CEh
        _emit 0C7h
        _emit 044h
        _emit 024h
        _emit 008h
        _emit 000h
        _emit 000h
        _emit 000h
        _emit 000h
        _emit 0E8h
        _emit 067h
        _emit 083h
        _emit 047h
        _emit 000h
        _emit 08Bh
        _emit 0C6h
        _emit 05Eh
        _emit 059h
        _emit 0C2h
        _emit 004h
        _emit 000h
    }
}
