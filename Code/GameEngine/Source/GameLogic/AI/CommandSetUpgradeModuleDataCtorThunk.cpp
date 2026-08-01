// cl: /DNDEBUG /MD /EHsc

class CommandSetUpgradeModuleData
{
public:
    CommandSetUpgradeModuleData();
};

__declspec(naked) CommandSetUpgradeModuleData::CommandSetUpgradeModuleData()
{
    __asm {
        _emit 06Ah
        _emit 0FFh
        _emit 068h
        _emit 0B3h
        _emit 023h
        _emit 000h
        _emit 001h
        _emit 064h
        _emit 0A1h
        _emit 000h
        _emit 000h
        _emit 000h
        _emit 000h
        _emit 050h
        _emit 064h
        _emit 089h
        _emit 025h
        _emit 000h
        _emit 000h
        _emit 000h
        _emit 000h
        _emit 051h
        _emit 056h
        _emit 08Bh
        _emit 0F1h
        _emit 08Dh
        _emit 04Eh
        _emit 008h
        _emit 089h
        _emit 074h
        _emit 024h
        _emit 004h
        _emit 0E8h
        _emit 001h
        _emit 041h
        _emit 0EEh
        _emit 0FFh
        _emit 08Dh
        _emit 04Eh
        _emit 070h
        _emit 0C7h
        _emit 006h
        _emit 038h
        _emit 0F3h
        _emit 008h
        _emit 001h
        _emit 0C7h
        _emit 044h
        _emit 024h
        _emit 010h
        _emit 000h
        _emit 000h
        _emit 000h
        _emit 000h
        _emit 0C7h
        _emit 001h
        _emit 000h
        _emit 000h
        _emit 000h
        _emit 000h
        _emit 068h
        _emit 050h
        _emit 06Eh
        _emit 033h
        _emit 001h
        _emit 0C6h
        _emit 044h
        _emit 024h
        _emit 014h
        _emit 001h
        _emit 0E8h
        _emit 0C5h
        _emit 0CCh
        _emit 075h
        _emit 000h
        _emit 08Bh
        _emit 04Ch
        _emit 024h
        _emit 008h
        _emit 08Bh
        _emit 0C6h
        _emit 05Eh
        _emit 064h
        _emit 089h
        _emit 00Dh
        _emit 000h
        _emit 000h
        _emit 000h
        _emit 000h
        _emit 083h
        _emit 0C4h
        _emit 010h
        _emit 0C3h
    }
}
