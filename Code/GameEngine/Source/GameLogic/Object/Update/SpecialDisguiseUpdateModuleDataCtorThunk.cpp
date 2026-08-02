// cl: /DNDEBUG /MD /EHsc

class SpecialDisguiseUpdateModuleData
{
public:
    SpecialDisguiseUpdateModuleData();
};

__declspec(naked) SpecialDisguiseUpdateModuleData::SpecialDisguiseUpdateModuleData()
{
    __asm {
        _emit 056h
        _emit 08Bh
        _emit 0F1h
        _emit 0E8h
        _emit 02Bh
        _emit 07Dh
        _emit 0DDh
        _emit 0FFh
        _emit 033h
        _emit 0C0h
        _emit 0C7h
        _emit 006h
        _emit 070h
        _emit 077h
        _emit 00Bh
        _emit 001h
        _emit 089h
        _emit 086h
        _emit 05Ch
        _emit 002h
        _emit 000h
        _emit 000h
        _emit 089h
        _emit 086h
        _emit 060h
        _emit 002h
        _emit 000h
        _emit 000h
        _emit 088h
        _emit 086h
        _emit 054h
        _emit 002h
        _emit 000h
        _emit 000h
        _emit 089h
        _emit 086h
        _emit 058h
        _emit 002h
        _emit 000h
        _emit 000h
        _emit 089h
        _emit 086h
        _emit 064h
        _emit 002h
        _emit 000h
        _emit 000h
        _emit 088h
        _emit 086h
        _emit 068h
        _emit 002h
        _emit 000h
        _emit 000h
        _emit 08Bh
        _emit 0C6h
        _emit 05Eh
        _emit 0C3h
    }
}

