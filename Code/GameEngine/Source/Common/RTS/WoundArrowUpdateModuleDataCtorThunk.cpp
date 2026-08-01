// cl: /DNDEBUG /MD /EHsc

class WoundArrowUpdateModuleData
{
public:
    WoundArrowUpdateModuleData();
};

__declspec(naked) WoundArrowUpdateModuleData::WoundArrowUpdateModuleData()
{
    __asm {
        _emit 056h
        _emit 08Bh
        _emit 0F1h
        _emit 0E8h
        _emit 0ABh
        _emit 015h
        _emit 0DDh
        _emit 0FFh
        _emit 0C7h
        _emit 006h
        _emit 0B0h
        _emit 08Fh
        _emit 00Bh
        _emit 001h
        _emit 0C7h
        _emit 086h
        _emit 054h
        _emit 002h
        _emit 000h
        _emit 000h
        _emit 000h
        _emit 000h
        _emit 0C8h
        _emit 042h
        _emit 0C7h
        _emit 086h
        _emit 058h
        _emit 002h
        _emit 000h
        _emit 000h
        _emit 000h
        _emit 000h
        _emit 000h
        _emit 000h
        _emit 08Bh
        _emit 0C6h
        _emit 05Eh
        _emit 0C3h
    }
}
