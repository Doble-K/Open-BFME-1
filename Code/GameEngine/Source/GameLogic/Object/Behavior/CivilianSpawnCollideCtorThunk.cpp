// cl: /DNDEBUG /MD /EHsc

class Thing;
class ModuleData;

class CivilianSpawnCollide
{
public:
    CivilianSpawnCollide(Thing *, const ModuleData *);
};

__declspec(naked) CivilianSpawnCollide::CivilianSpawnCollide(Thing *, const ModuleData *)
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
        _emit 0F0h
        _emit 0FCh
        _emit 0DFh
        _emit 0FFh
        _emit 0C7h
        _emit 046h
        _emit 00Ch
        _emit 0D0h
        _emit 0C9h
        _emit 009h
        _emit 001h
        _emit 0C7h
        _emit 046h
        _emit 010h
        _emit 0E4h
        _emit 01Dh
        _emit 00Ah
        _emit 001h
        _emit 0C7h
        _emit 006h
        _emit 01Ch
        _emit 0A2h
        _emit 00Ah
        _emit 001h
        _emit 0C7h
        _emit 046h
        _emit 00Ch
        _emit 058h
        _emit 0A1h
        _emit 00Ah
        _emit 001h
        _emit 0C7h
        _emit 046h
        _emit 010h
        _emit 03Ch
        _emit 0A1h
        _emit 00Ah
        _emit 001h
        _emit 08Bh
        _emit 0C6h
        _emit 05Eh
        _emit 0C2h
        _emit 008h
        _emit 000h
    }
}

