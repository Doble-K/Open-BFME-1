// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class INI;
class ModuleData;

class SlavedUpdate
{
public:
    static ModuleData *friend_newModuleData(INI *);
};

// ?friend_newModuleData@SlavedUpdate@@SAPAVModuleData@@PAVINI@@@Z
__declspec(naked) ModuleData *SlavedUpdate::friend_newModuleData(INI *)
{
    __asm {
        _emit 056h
        _emit 06Ah
        _emit 054h
        _emit 0E8h
        _emit 0C8h
        _emit 0C4h
        _emit 075h
        _emit 000h
        _emit 033h
        _emit 0D2h
        _emit 083h
        _emit 0C4h
        _emit 004h
        _emit 03Bh
        _emit 0C2h
        _emit 074h
        _emit 040h
        _emit 0C7h
        _emit 000h
        _emit 030h
        _emit 0E7h
        _emit 008h
        _emit 001h
        _emit 089h
        _emit 050h
        _emit 048h
        _emit 089h
        _emit 050h
        _emit 04Ch
        _emit 089h
        _emit 050h
        _emit 008h
        _emit 089h
        _emit 050h
        _emit 00Ch
        _emit 089h
        _emit 050h
        _emit 010h
        _emit 089h
        _emit 050h
        _emit 014h
        _emit 089h
        _emit 050h
        _emit 018h
        _emit 089h
        _emit 050h
        _emit 01Ch
        _emit 089h
        _emit 050h
        _emit 020h
        _emit 089h
        _emit 050h
        _emit 030h
        _emit 089h
        _emit 050h
        _emit 034h
        _emit 089h
        _emit 050h
        _emit 028h
        _emit 089h
        _emit 050h
        _emit 02Ch
        _emit 089h
        _emit 050h
        _emit 040h
        _emit 089h
        _emit 050h
        _emit 044h
        _emit 089h
        _emit 050h
        _emit 038h
        _emit 089h
        _emit 050h
        _emit 03Ch
        _emit 088h
        _emit 050h
        _emit 050h
        _emit 08Bh
        _emit 0F0h
        _emit 0EBh
        _emit 002h
        _emit 033h
        _emit 0F6h
        _emit 08Bh
        _emit 04Ch
        _emit 024h
        _emit 008h
        _emit 03Bh
        _emit 0CAh
        _emit 074h
        _emit 00Bh
        _emit 068h
        _emit 08Eh
        _emit 097h
        _emit 043h
        _emit 000h
        _emit 056h
        _emit 0E8h
        _emit 06Ah
        _emit 0C6h
        _emit 072h
        _emit 000h
        _emit 08Bh
        _emit 0C6h
        _emit 05Eh
        _emit 0C3h
    }
}
