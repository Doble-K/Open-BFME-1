// cl: /DNDEBUG /MD /EHsc

class DemoTrapUpdateModuleData
{
public:
    DemoTrapUpdateModuleData();
};

__declspec(naked) DemoTrapUpdateModuleData::DemoTrapUpdateModuleData()
{
    __asm {
        _emit 08Bh
        _emit 0C1h
        _emit 0C7h
        _emit 000h
        _emit 0D8h
        _emit 0D7h
        _emit 00Bh
        _emit 001h
        _emit 033h
        _emit 0C9h
        _emit 08Dh
        _emit 050h
        _emit 00Ch
        _emit 089h
        _emit 00Ah
        _emit 089h
        _emit 04Ah
        _emit 004h
        _emit 089h
        _emit 04Ah
        _emit 008h
        _emit 089h
        _emit 04Ah
        _emit 00Ch
        _emit 089h
        _emit 04Ah
        _emit 010h
        _emit 089h
        _emit 04Ah
        _emit 014h
        _emit 088h
        _emit 048h
        _emit 038h
        _emit 088h
        _emit 048h
        _emit 039h
        _emit 089h
        _emit 048h
        _emit 024h
        _emit 089h
        _emit 048h
        _emit 028h
        _emit 089h
        _emit 048h
        _emit 02Ch
        _emit 089h
        _emit 048h
        _emit 030h
        _emit 089h
        _emit 048h
        _emit 034h
        _emit 089h
        _emit 048h
        _emit 008h
        _emit 088h
        _emit 048h
        _emit 03Ah
        _emit 0C3h
    }
}
