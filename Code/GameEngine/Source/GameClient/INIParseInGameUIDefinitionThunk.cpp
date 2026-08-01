// cl: /DNDEBUG /MD /EHsc

class INI
{
public:
    static void parseInGameUIDefinition(INI *);
};

__declspec(naked) void INI::parseInGameUIDefinition(INI *ini)
{
    __asm {
        _emit 08Bh
        _emit 00Dh
        _emit 08Ch
        _emit 014h
        _emit 02Fh
        _emit 001h
        _emit 085h
        _emit 0C9h
        _emit 074h
        _emit 019h
        _emit 08Bh
        _emit 001h
        _emit 0FFh
        _emit 090h
        _emit 058h
        _emit 001h
        _emit 000h
        _emit 000h
        _emit 08Bh
        _emit 00Dh
        _emit 08Ch
        _emit 014h
        _emit 02Fh
        _emit 001h
        _emit 050h
        _emit 051h
        _emit 08Bh
        _emit 04Ch
        _emit 024h
        _emit 00Ch
        _emit 0E8h
        _emit 0DDh
        _emit 075h
        _emit 041h
        _emit 000h
        _emit 0C3h
    }
}
