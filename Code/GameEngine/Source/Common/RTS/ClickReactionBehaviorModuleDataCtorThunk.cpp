// cl: /DNDEBUG /MD /EHsc

class ClickReactionBehaviorModuleData
{
public:
    ClickReactionBehaviorModuleData();
};

__declspec(naked) ClickReactionBehaviorModuleData::ClickReactionBehaviorModuleData()
{
    __asm {
        _emit 08Bh
        _emit 0C1h
        _emit 033h
        _emit 0C9h
        _emit 0C7h
        _emit 000h
        _emit 010h
        _emit 04Ah
        _emit 00Ah
        _emit 001h
        _emit 088h
        _emit 048h
        _emit 020h
        _emit 088h
        _emit 048h
        _emit 021h
        _emit 0BAh
        _emit 0FFh
        _emit 0FFh
        _emit 07Fh
        _emit 07Fh
        _emit 089h
        _emit 048h
        _emit 008h
        _emit 089h
        _emit 050h
        _emit 014h
        _emit 089h
        _emit 048h
        _emit 00Ch
        _emit 089h
        _emit 050h
        _emit 018h
        _emit 089h
        _emit 048h
        _emit 010h
        _emit 089h
        _emit 050h
        _emit 01Ch
        _emit 0C3h
    }
}
