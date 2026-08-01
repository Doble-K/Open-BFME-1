// cl: /DNDEBUG /MD /EHsc

class SidesInfo
{
public:
    SidesInfo();
};

__declspec(naked) SidesInfo::SidesInfo()
{
    __asm {
        _emit 056h
        _emit 057h
        _emit 08Bh
        _emit 0F1h
        _emit 033h
        _emit 0FFh
        _emit 057h
        _emit 08Dh
        _emit 04Eh
        _emit 004h
        _emit 089h
        _emit 03Eh
        _emit 0E8h
        _emit 00Ch
        _emit 0A9h
        _emit 0E6h
        _emit 0FFh
        _emit 089h
        _emit 07Eh
        _emit 008h
        _emit 089h
        _emit 07Eh
        _emit 00Ch
        _emit 089h
        _emit 07Eh
        _emit 010h
        _emit 089h
        _emit 07Eh
        _emit 014h
        _emit 05Fh
        _emit 08Bh
        _emit 0C6h
        _emit 05Eh
        _emit 0C3h
    }
}
