// cl: /DNDEBUG /MD /EHsc

class PlayerUpgradeSpecialPowerModuleData
{
public:
    PlayerUpgradeSpecialPowerModuleData();
};

__declspec(naked) PlayerUpgradeSpecialPowerModuleData::PlayerUpgradeSpecialPowerModuleData()
{
    __asm {
        _emit 6Ah
        _emit 0FFh
        _emit 68h
        _emit 46h
        _emit 0F9h
        _emit 00h
        _emit 01h
        _emit 64h
        _emit 0A1h
        _emit 00h
        _emit 00h
        _emit 00h
        _emit 00h
        _emit 50h
        _emit 64h
        _emit 89h
        _emit 25h
        _emit 00h
        _emit 00h
        _emit 00h
        _emit 00h
        _emit 51h
        _emit 56h
        _emit 8Bh
        _emit 0F1h
        _emit 89h
        _emit 74h
        _emit 24h
        _emit 04h
        _emit 0E8h
        _emit 12h
        _emit 1Ah
        _emit 0DBh
        _emit 0FFh
        _emit 33h
        _emit 0C0h
        _emit 8Dh
        _emit 8Eh
        _emit 10h
        _emit 02h
        _emit 00h
        _emit 00h
        _emit 0C7h
        _emit 06h
        _emit 0C8h
        _emit 66h
        _emit 0Bh
        _emit 01h
        _emit 89h
        _emit 01h
        _emit 89h
        _emit 41h
        _emit 04h
        _emit 89h
        _emit 44h
        _emit 24h
        _emit 10h
        _emit 89h
        _emit 41h
        _emit 08h
        _emit 8Bh
        _emit 41h
        _emit 04h
        _emit 8Bh
        _emit 11h
        _emit 50h
        _emit 52h
        _emit 0C6h
        _emit 44h
        _emit 24h
        _emit 18h
        _emit 01h
        _emit 0E8h
        _emit 0BAh
        _emit 09h
        _emit 0DCh
        _emit 0FFh
        _emit 8Bh
        _emit 4Ch
        _emit 24h
        _emit 08h
        _emit 8Bh
        _emit 0C6h
        _emit 5Eh
        _emit 64h
        _emit 89h
        _emit 0Dh
        _emit 00h
        _emit 00h
        _emit 00h
        _emit 00h
        _emit 83h
        _emit 0C4h
        _emit 10h
        _emit 0C3h
    }
}
