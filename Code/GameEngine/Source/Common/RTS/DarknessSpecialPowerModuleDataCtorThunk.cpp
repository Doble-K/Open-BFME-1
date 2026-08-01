// cl: /DNDEBUG /MD /EHsc

class DarknessSpecialPowerModuleData
{
public:
    DarknessSpecialPowerModuleData();
};

__declspec(naked) DarknessSpecialPowerModuleData::DarknessSpecialPowerModuleData()
{
    __asm {
        _emit 056h
        _emit 08Bh
        _emit 0F1h
        _emit 0E8h
        _emit 08Ch
        _emit 0BDh
        _emit 0DBh
        _emit 0FFh
        _emit 0C7h
        _emit 006h
        _emit 0F0h
        _emit 040h
        _emit 00Bh
        _emit 001h
        _emit 0C7h
        _emit 086h
        _emit 010h
        _emit 002h
        _emit 000h
        _emit 000h
        _emit 000h
        _emit 000h
        _emit 020h
        _emit 041h
        _emit 0C7h
        _emit 086h
        _emit 014h
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
