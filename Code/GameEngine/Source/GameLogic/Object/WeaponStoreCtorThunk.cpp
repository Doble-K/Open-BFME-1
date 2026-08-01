// cl: /DNDEBUG /MD /EHsc

class SubsystemInterface
{
};

class WeaponStore : public SubsystemInterface
{
public:
    WeaponStore();
};

__declspec(naked) WeaponStore::WeaponStore()
{
    __asm {
        _emit 056h
        _emit 08Bh
        _emit 0F1h
        _emit 0E8h
        _emit 098h
        _emit 0C7h
        _emit 07Bh
        _emit 000h
        _emit 033h
        _emit 0C0h
        _emit 0C7h
        _emit 006h
        _emit 0C8h
        _emit 013h
        _emit 00Ah
        _emit 001h
        _emit 089h
        _emit 046h
        _emit 008h
        _emit 089h
        _emit 046h
        _emit 00Ch
        _emit 089h
        _emit 046h
        _emit 010h
        _emit 08Bh
        _emit 0C6h
        _emit 05Eh
        _emit 0C3h
    }
}
