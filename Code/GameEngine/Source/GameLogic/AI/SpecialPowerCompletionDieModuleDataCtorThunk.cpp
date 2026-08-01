// cl: /DNDEBUG /MD /EHsc

class SpecialPowerCompletionDieModuleData
{
public:
    SpecialPowerCompletionDieModuleData();
};

__declspec(naked) SpecialPowerCompletionDieModuleData::SpecialPowerCompletionDieModuleData()
{
    __asm {
        _emit 6Ah
        _emit 0FFh
        _emit 68h
        _emit 0E8h
        _emit 13h
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
        _emit 8Dh
        _emit 4Eh
        _emit 08h
        _emit 0C7h
        _emit 44h
        _emit 24h
        _emit 10h
        _emit 00h
        _emit 00h
        _emit 00h
        _emit 00h
        _emit 0C7h
        _emit 06h
        _emit 78h
        _emit 0AFh
        _emit 08h
        _emit 01h
        _emit 0E8h
        _emit 91h
        _emit 3Bh
        _emit 0EEh
        _emit 0FFh
        _emit 8Bh
        _emit 4Ch
        _emit 24h
        _emit 08h
        _emit 0C7h
        _emit 06h
        _emit 08h
        _emit 0B8h
        _emit 08h
        _emit 01h
        _emit 0C7h
        _emit 46h
        _emit 34h
        _emit 00h
        _emit 00h
        _emit 00h
        _emit 00h
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

