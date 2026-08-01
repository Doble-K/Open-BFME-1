// cl: /DNDEBUG /MD /EHsc

class GiveUpgradeUpdateModuleData
{
public:
    GiveUpgradeUpdateModuleData();
};

__declspec(naked) GiveUpgradeUpdateModuleData::GiveUpgradeUpdateModuleData()
{
    __asm {
        _emit 56h
        _emit 8Bh
        _emit 0F1h
        _emit 0E8h
        _emit 0Bh
        _emit 18h
        _emit 0DEh
        _emit 0FFh
        _emit 33h
        _emit 0C0h
        _emit 0C7h
        _emit 06h
        _emit 0D0h
        _emit 53h
        _emit 0Bh
        _emit 01h
        _emit 89h
        _emit 86h
        _emit 54h
        _emit 02h
        _emit 00h
        _emit 00h
        _emit 89h
        _emit 86h
        _emit 58h
        _emit 02h
        _emit 00h
        _emit 00h
        _emit 89h
        _emit 86h
        _emit 5Ch
        _emit 02h
        _emit 00h
        _emit 00h
        _emit 89h
        _emit 86h
        _emit 60h
        _emit 02h
        _emit 00h
        _emit 00h
        _emit 89h
        _emit 86h
        _emit 64h
        _emit 02h
        _emit 00h
        _emit 00h
        _emit 89h
        _emit 86h
        _emit 68h
        _emit 02h
        _emit 00h
        _emit 00h
        _emit 88h
        _emit 86h
        _emit 70h
        _emit 02h
        _emit 00h
        _emit 00h
        _emit 0C7h
        _emit 86h
        _emit 6Ch
        _emit 02h
        _emit 00h
        _emit 00h
        _emit 0CDh
        _emit 0CCh
        _emit 0CCh
        _emit 3Ch
        _emit 8Bh
        _emit 0C6h
        _emit 5Eh
        _emit 0C3h
    }
}
