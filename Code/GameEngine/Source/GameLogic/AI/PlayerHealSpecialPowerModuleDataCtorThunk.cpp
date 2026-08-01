// cl: /DNDEBUG /MD /EHsc

class PlayerHealSpecialPowerModuleData
{
public:
    PlayerHealSpecialPowerModuleData();
};

__declspec(naked) PlayerHealSpecialPowerModuleData::PlayerHealSpecialPowerModuleData()
{
    __asm {
        _emit 56h
        _emit 8Bh
        _emit 0F1h
        _emit 0E8h
        _emit 5Ch
        _emit 20h
        _emit 0DBh
        _emit 0FFh
        _emit 0C7h
        _emit 06h
        _emit 00h
        _emit 65h
        _emit 0Bh
        _emit 01h
        _emit 8Dh
        _emit 86h
        _emit 18h
        _emit 02h
        _emit 00h
        _emit 00h
        _emit 33h
        _emit 0C9h
        _emit 8Bh
        _emit 0D0h
        _emit 89h
        _emit 0Ah
        _emit 89h
        _emit 4Ah
        _emit 04h
        _emit 89h
        _emit 4Ah
        _emit 08h
        _emit 89h
        _emit 4Ah
        _emit 0Ch
        _emit 89h
        _emit 4Ah
        _emit 10h
        _emit 89h
        _emit 4Ah
        _emit 14h
        _emit 89h
        _emit 8Eh
        _emit 10h
        _emit 02h
        _emit 00h
        _emit 00h
        _emit 0C7h
        _emit 86h
        _emit 14h
        _emit 02h
        _emit 00h
        _emit 00h
        _emit 00h
        _emit 00h
        _emit 0C8h
        _emit 42h
        _emit 33h
        _emit 0D2h
        _emit 89h
        _emit 10h
        _emit 89h
        _emit 50h
        _emit 04h
        _emit 89h
        _emit 50h
        _emit 08h
        _emit 89h
        _emit 50h
        _emit 0Ch
        _emit 89h
        _emit 50h
        _emit 10h
        _emit 89h
        _emit 50h
        _emit 14h
        _emit 89h
        _emit 8Eh
        _emit 30h
        _emit 02h
        _emit 00h
        _emit 00h
        _emit 89h
        _emit 8Eh
        _emit 34h
        _emit 02h
        _emit 00h
        _emit 00h
        _emit 8Bh
        _emit 0C6h
        _emit 5Eh
        _emit 0C3h
    }
}
