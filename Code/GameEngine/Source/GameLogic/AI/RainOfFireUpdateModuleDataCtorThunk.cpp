// cl: /DNDEBUG /MD /EHsc

class RainOfFireUpdateModuleData
{
public:
    RainOfFireUpdateModuleData();
};

__declspec(naked) RainOfFireUpdateModuleData::RainOfFireUpdateModuleData()
{
    __asm {
        _emit 08Bh
        _emit 0C1h
        _emit 033h
        _emit 0C9h
        _emit 0BAh
        _emit 000h
        _emit 000h
        _emit 080h
        _emit 03Fh
        _emit 0C7h
        _emit 000h
        _emit 098h
        _emit 016h
        _emit 00Ch
        _emit 001h
        _emit 0C7h
        _emit 040h
        _emit 008h
        _emit 096h
        _emit 000h
        _emit 000h
        _emit 000h
        _emit 0C7h
        _emit 040h
        _emit 00Ch
        _emit 078h
        _emit 000h
        _emit 000h
        _emit 000h
        _emit 0C7h
        _emit 040h
        _emit 010h
        _emit 000h
        _emit 000h
        _emit 0C8h
        _emit 042h
        _emit 0C7h
        _emit 040h
        _emit 014h
        _emit 000h
        _emit 000h
        _emit 080h
        _emit 03Eh
        _emit 089h
        _emit 048h
        _emit 018h
        _emit 089h
        _emit 050h
        _emit 01Ch
        _emit 089h
        _emit 050h
        _emit 020h
        _emit 089h
        _emit 048h
        _emit 024h
        _emit 089h
        _emit 048h
        _emit 028h
        _emit 089h
        _emit 048h
        _emit 02Ch
        _emit 0C3h
    }
}
