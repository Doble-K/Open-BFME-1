// cl: /DNDEBUG /MD /EHsc

class Thing;
class ModuleData;

class HorseHordeContain
{
public:
    HorseHordeContain(Thing *, const ModuleData *);
};

__declspec(naked) HorseHordeContain::HorseHordeContain(Thing *, const ModuleData *)
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
        _emit 0CBh
        _emit 0D6h
        _emit 0DEh
        _emit 0FFh
        _emit 0C7h
        _emit 006h
        _emit 050h
        _emit 00Dh
        _emit 00Bh
        _emit 001h
        _emit 0C7h
        _emit 046h
        _emit 00Ch
        _emit 088h
        _emit 00Ch
        _emit 00Bh
        _emit 001h
        _emit 0C7h
        _emit 046h
        _emit 010h
        _emit 078h
        _emit 00Ch
        _emit 00Bh
        _emit 001h
        _emit 0C7h
        _emit 046h
        _emit 020h
        _emit 0D0h
        _emit 00Ah
        _emit 00Bh
        _emit 001h
        _emit 0C7h
        _emit 046h
        _emit 024h
        _emit 0B0h
        _emit 00Ah
        _emit 00Bh
        _emit 001h
        _emit 0C7h
        _emit 046h
        _emit 028h
        _emit 0ACh
        _emit 00Ah
        _emit 00Bh
        _emit 001h
        _emit 0C7h
        _emit 046h
        _emit 02Ch
        _emit 09Ch
        _emit 00Ah
        _emit 00Bh
        _emit 001h
        _emit 0C7h
        _emit 046h
        _emit 030h
        _emit 060h
        _emit 00Ah
        _emit 00Bh
        _emit 001h
        _emit 0C7h
        _emit 046h
        _emit 034h
        _emit 050h
        _emit 00Ah
        _emit 00Bh
        _emit 001h
        _emit 0C7h
        _emit 086h
        _emit 0D4h
        _emit 000h
        _emit 000h
        _emit 000h
        _emit 04Ch
        _emit 00Ah
        _emit 00Bh
        _emit 001h
        _emit 0C7h
        _emit 086h
        _emit 0E4h
        _emit 000h
        _emit 000h
        _emit 000h
        _emit 0E0h
        _emit 007h
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
