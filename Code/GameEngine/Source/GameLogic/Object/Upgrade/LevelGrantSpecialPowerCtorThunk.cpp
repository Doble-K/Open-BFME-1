// cl: /DNDEBUG /MD /EHsc

class Thing;
class ModuleData;

class LevelGrantSpecialPower
{
public:
    LevelGrantSpecialPower(Thing *, const ModuleData *);
};

__declspec(naked) LevelGrantSpecialPower::LevelGrantSpecialPower(Thing *, const ModuleData *)
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
        _emit 02Eh
        _emit 037h
        _emit 0DBh
        _emit 0FFh
        _emit 0C7h
        _emit 006h
        _emit 070h
        _emit 05Ch
        _emit 00Bh
        _emit 001h
        _emit 0C7h
        _emit 046h
        _emit 00Ch
        _emit 0A8h
        _emit 05Bh
        _emit 00Bh
        _emit 001h
        _emit 0C7h
        _emit 046h
        _emit 010h
        _emit 098h
        _emit 05Bh
        _emit 00Bh
        _emit 001h
        _emit 0C7h
        _emit 046h
        _emit 020h
        _emit 06Ch
        _emit 05Bh
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

