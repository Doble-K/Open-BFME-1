// cl: /DNDEBUG /MD /EHsc

class WeaponSetSpecialAbilityUpdateModuleData
{
public:
    WeaponSetSpecialAbilityUpdateModuleData();
};

__declspec(naked) WeaponSetSpecialAbilityUpdateModuleData::WeaponSetSpecialAbilityUpdateModuleData()
{
    __asm {
        _emit 056h
        _emit 08Bh
        _emit 0F1h
        _emit 0E8h
        _emit 0DBh
        _emit 018h
        _emit 0DDh
        _emit 0FFh
        _emit 033h
        _emit 0C0h
        _emit 089h
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
        _emit 0C7h
        _emit 006h
        _emit 0F0h
        _emit 08Dh
        _emit 00Bh
        _emit 001h
        _emit 08Bh
        _emit 0C6h
        _emit 05Eh
        _emit 0C3h
    }
}
