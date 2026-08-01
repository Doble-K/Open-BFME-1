// cl: /DNDEBUG /MD /EHsc

class HealContainModuleData
{
public:
    HealContainModuleData();
};

__declspec(naked) HealContainModuleData::HealContainModuleData()
{
    __asm {
        _emit 08Bh
        _emit 0C1h
        _emit 033h
        _emit 0C9h
        _emit 0C7h
        _emit 000h
        _emit 0B0h
        _emit 0D1h
        _emit 00Bh
        _emit 001h
        _emit 089h
        _emit 048h
        _emit 008h
        _emit 089h
        _emit 048h
        _emit 00Ch
        _emit 089h
        _emit 048h
        _emit 010h
        _emit 089h
        _emit 048h
        _emit 014h
        _emit 089h
        _emit 048h
        _emit 018h
        _emit 089h
        _emit 048h
        _emit 01Ch
        _emit 089h
        _emit 048h
        _emit 020h
        _emit 0C3h
    }
}
