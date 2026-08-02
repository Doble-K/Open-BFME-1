// cl: /DNDEBUG /MD /EHsc

class WeaponModeSpecialPowerUpdateModuleData
{
public:
    WeaponModeSpecialPowerUpdateModuleData();
};

__declspec(naked) WeaponModeSpecialPowerUpdateModuleData::WeaponModeSpecialPowerUpdateModuleData()
{
    __asm {
        _emit 056h
        _emit 08Bh
        _emit 0F1h
        _emit 0E8h
        _emit 0EFh
        _emit 012h
        _emit 0D7h
        _emit 0FFh
        _emit 033h
        _emit 0C0h
        _emit 0C7h
        _emit 006h
        _emit 010h
        _emit 055h
        _emit 00Ch
        _emit 001h
        _emit 089h
        _emit 086h
        _emit 0D0h
        _emit 001h
        _emit 000h
        _emit 000h
        _emit 089h
        _emit 086h
        _emit 0D4h
        _emit 001h
        _emit 000h
        _emit 000h
        _emit 0C7h
        _emit 086h
        _emit 0D8h
        _emit 001h
        _emit 000h
        _emit 000h
        _emit 003h
        _emit 000h
        _emit 000h
        _emit 000h
        _emit 089h
        _emit 086h
        _emit 0DCh
        _emit 001h
        _emit 000h
        _emit 000h
        _emit 089h
        _emit 086h
        _emit 0DCh
        _emit 001h
        _emit 000h
        _emit 000h
        _emit 08Bh
        _emit 0C6h
        _emit 05Eh
        _emit 0C3h
    }
}

