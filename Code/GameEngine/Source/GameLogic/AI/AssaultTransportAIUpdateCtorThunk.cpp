// cl: /DNDEBUG /MD /EHsc

class Thing;
class ModuleData;

class AssaultTransportAIUpdate
{
public:
    AssaultTransportAIUpdate(Thing *, const ModuleData *);
};

__declspec(naked) AssaultTransportAIUpdate::AssaultTransportAIUpdate(Thing *, const ModuleData *)
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
        _emit 09Fh
        _emit 04Bh
        _emit 0D7h
        _emit 0FFh
        _emit 0C7h
        _emit 086h
        _emit 040h
        _emit 003h
        _emit 000h
        _emit 000h
        _emit 024h
        _emit 060h
        _emit 00Ch
        _emit 001h
        _emit 08Bh
        _emit 0CEh
        _emit 0C7h
        _emit 006h
        _emit 020h
        _emit 061h
        _emit 00Ch
        _emit 001h
        _emit 0C7h
        _emit 046h
        _emit 00Ch
        _emit 058h
        _emit 060h
        _emit 00Ch
        _emit 001h
        _emit 0C7h
        _emit 046h
        _emit 010h
        _emit 04Ch
        _emit 060h
        _emit 00Ch
        _emit 001h
        _emit 0C7h
        _emit 046h
        _emit 020h
        _emit 048h
        _emit 060h
        _emit 00Ch
        _emit 001h
        _emit 0C7h
        _emit 046h
        _emit 024h
        _emit 02Ch
        _emit 060h
        _emit 00Ch
        _emit 001h
        _emit 0C7h
        _emit 086h
        _emit 040h
        _emit 003h
        _emit 000h
        _emit 000h
        _emit 028h
        _emit 060h
        _emit 00Ch
        _emit 001h
        _emit 0C7h
        _emit 086h
        _emit 098h
        _emit 003h
        _emit 000h
        _emit 000h
        _emit 00Ah
        _emit 000h
        _emit 000h
        _emit 000h
        _emit 0E8h
        _emit 012h
        _emit 0C9h
        _emit 0D6h
        _emit 0FFh
        _emit 08Bh
        _emit 0C6h
        _emit 05Eh
        _emit 0C2h
        _emit 008h
        _emit 000h
    }
}
