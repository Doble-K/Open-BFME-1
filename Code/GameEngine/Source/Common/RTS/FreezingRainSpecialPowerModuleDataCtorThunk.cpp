// cl: /DNDEBUG /MD /EHsc

class FreezingRainSpecialPowerModuleData
{
public:
    FreezingRainSpecialPowerModuleData();
};

__declspec(naked) FreezingRainSpecialPowerModuleData::FreezingRainSpecialPowerModuleData()
{
    __asm {
        _emit 056h
        _emit 08Bh
        _emit 0F1h
        _emit 0E8h
        _emit 07Ch
        _emit 083h
        _emit 0DBh
        _emit 0FFh
        _emit 0C7h
        _emit 006h
        _emit 028h
        _emit 051h
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
