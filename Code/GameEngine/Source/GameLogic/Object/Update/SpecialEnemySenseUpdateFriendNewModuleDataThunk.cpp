// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class INI;
class ModuleData;

class SpecialEnemySenseUpdate
{
public:
    static ModuleData *friend_newModuleData(INI *);
};

// ?friend_newModuleData@SpecialEnemySenseUpdate@@SAPAVModuleData@@PAVINI@@@Z
__declspec(naked) ModuleData *SpecialEnemySenseUpdate::friend_newModuleData(INI *)
{
    __asm {
        _emit 06Ah
        _emit 0FFh
        _emit 068h
        _emit 0CBh
        _emit 014h
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
        _emit 06Ah
        _emit 014h
        _emit 0E8h
        _emit 082h
        _emit 0E1h
        _emit 075h
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
        _emit 0F8h
        _emit 0CDh
        _emit 0F0h
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
        _emit 052h
        _emit 042h
        _emit 043h
        _emit 000h
        _emit 056h
        _emit 0E8h
        _emit 047h
        _emit 0E3h
        _emit 072h
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
