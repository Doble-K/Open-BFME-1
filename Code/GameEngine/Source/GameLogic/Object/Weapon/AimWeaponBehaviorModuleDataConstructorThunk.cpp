// cl: /DNDEBUG /MD /EHsc

class AimWeaponBehaviorModuleData
{
public:
    AimWeaponBehaviorModuleData();
};

__declspec(naked) AimWeaponBehaviorModuleData::AimWeaponBehaviorModuleData()
{
    __asm {
        _emit 08Bh
        _emit 0C1h
        _emit 0C7h
        _emit 000h
        _emit 048h
        _emit 018h
        _emit 00Ah
        _emit 001h
        _emit 0C7h
        _emit 040h
        _emit 008h
        _emit 0CDh
        _emit 0CCh
        _emit 04Ch
        _emit 0BDh
        _emit 0C7h
        _emit 040h
        _emit 00Ch
        _emit 0CDh
        _emit 0CCh
        _emit 04Ch
        _emit 03Dh
        _emit 0C7h
        _emit 040h
        _emit 010h
        _emit 000h
        _emit 000h
        _emit 000h
        _emit 000h
        _emit 0C7h
        _emit 040h
        _emit 014h
        _emit 0FFh
        _emit 0FFh
        _emit 07Fh
        _emit 07Fh
        _emit 0C3h
    }
}
