// cl: /DNDEBUG /MD /EHsc

class Thing;
class ModuleData;

class HeroModeSpecialAbilityUpdate
{
public:
    HeroModeSpecialAbilityUpdate(Thing *, const ModuleData *);
};

__declspec(naked) HeroModeSpecialAbilityUpdate::HeroModeSpecialAbilityUpdate(Thing *, const ModuleData *)
{
    __asm {
        _emit 08Bh
        _emit 044h
        _emit 024h
        _emit 008h
        _emit 056h
        _emit 08Bh
        _emit 0F1h
        _emit 08Bh
        _emit 04Ch
        _emit 024h
        _emit 008h
        _emit 050h
        _emit 051h
        _emit 08Bh
        _emit 0CEh
        _emit 0E8h
        _emit 0AEh
        _emit 03Bh
        _emit 0DBh
        _emit 0FFh
        _emit 0C7h
        _emit 006h
        _emit 0A0h
        _emit 059h
        _emit 00Bh
        _emit 001h
        _emit 0C7h
        _emit 046h
        _emit 00Ch
        _emit 0D8h
        _emit 058h
        _emit 00Bh
        _emit 001h
        _emit 0C7h
        _emit 046h
        _emit 010h
        _emit 0C8h
        _emit 058h
        _emit 00Bh
        _emit 001h
        _emit 0C7h
        _emit 046h
        _emit 020h
        _emit 09Ch
        _emit 058h
        _emit 00Bh
        _emit 001h
        _emit 08Bh
        _emit 0C6h
        _emit 05Eh
        _emit 0C2h
        _emit 008h
        _emit 000h
    }
}

