// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class INI;
class ModuleData;

class ProductionSpeedBonus
{
public:
    static ModuleData *friend_newModuleData(INI *);
};

// ?friend_newModuleData@ProductionSpeedBonus@@SAPAVModuleData@@PAVINI@@@Z
__declspec(naked) ModuleData *ProductionSpeedBonus::friend_newModuleData(INI *)
{
    __asm {
        _emit 06Ah
        _emit 0FFh
        _emit 068h
        _emit 06Bh
        _emit 00Bh
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
        _emit 068h
        _emit 024h
        _emit 002h
        _emit 000h
        _emit 000h
        _emit 0E8h
        _emit 0EFh
        _emit 01Dh
        _emit 076h
        _emit 000h
        _emit 083h
        _emit 0C4h
        _emit 004h
        _emit 089h
        _emit 044h
        _emit 024h
        _emit 004h
        _emit 085h
        _emit 0C0h
        _emit 0C7h
        _emit 044h
        _emit 024h
        _emit 010h
        _emit 000h
        _emit 000h
        _emit 000h
        _emit 000h
        _emit 074h
        _emit 00Bh
        _emit 08Bh
        _emit 0C8h
        _emit 0E8h
        _emit 068h
        _emit 083h
        _emit 0F2h
        _emit 0FFh
        _emit 08Bh
        _emit 0F0h
        _emit 0EBh
        _emit 002h
        _emit 033h
        _emit 0F6h
        _emit 08Bh
        _emit 04Ch
        _emit 024h
        _emit 018h
        _emit 085h
        _emit 0C9h
        _emit 0C7h
        _emit 044h
        _emit 024h
        _emit 010h
        _emit 0FFh
        _emit 0FFh
        _emit 0FFh
        _emit 0FFh
        _emit 074h
        _emit 00Bh
        _emit 068h
        _emit 013h
        _emit 0D7h
        _emit 042h
        _emit 000h
        _emit 056h
        _emit 0E8h
        _emit 0B4h
        _emit 01Fh
        _emit 073h
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
