// cl: /DNDEBUG /MD /EHsc

class GrabPassengerSpecialPowerModuleData
{
public:
    GrabPassengerSpecialPowerModuleData();
};

__declspec(naked) GrabPassengerSpecialPowerModuleData::GrabPassengerSpecialPowerModuleData()
{
    __asm {
        _emit 056h
        _emit 08Bh
        _emit 0F1h
        _emit 0E8h
        _emit 0DCh
        _emit 069h
        _emit 0DBh
        _emit 0FFh
        _emit 0C7h
        _emit 006h
        _emit 048h
        _emit 058h
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
        _emit 000h
        _emit 000h
        _emit 0C6h
        _emit 086h
        _emit 014h
        _emit 002h
        _emit 000h
        _emit 000h
        _emit 001h
        _emit 08Bh
        _emit 0C6h
        _emit 05Eh
        _emit 0C3h
    }
}
