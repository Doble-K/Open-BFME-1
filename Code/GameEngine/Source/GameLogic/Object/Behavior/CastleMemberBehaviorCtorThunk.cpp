// cl: /DNDEBUG /MD /EHsc

class Thing;
class ModuleData;

class CastleMemberBehavior
{
public:
    CastleMemberBehavior(Thing *, const ModuleData *);
};

__declspec(naked) CastleMemberBehavior::CastleMemberBehavior(Thing *, const ModuleData *)
{
    __asm {
        _emit 08Bh
        _emit 0C1h
        _emit 0B9h
        _emit 0FEh
        _emit 0FFh
        _emit 0FFh
        _emit 0FFh
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
        _emit 033h
        _emit 0C9h
        _emit 0C7h
        _emit 000h
        _emit 0C8h
        _emit 097h
        _emit 00Eh
        _emit 001h
        _emit 0C7h
        _emit 040h
        _emit 018h
        _emit 00Bh
        _emit 000h
        _emit 000h
        _emit 000h
        _emit 0C7h
        _emit 040h
        _emit 01Ch
        _emit 00Ch
        _emit 000h
        _emit 000h
        _emit 000h
        _emit 0C7h
        _emit 040h
        _emit 020h
        _emit 00Ah
        _emit 000h
        _emit 000h
        _emit 000h
        _emit 089h
        _emit 048h
        _emit 024h
        _emit 088h
        _emit 048h
        _emit 028h
        _emit 088h
        _emit 048h
        _emit 029h
        _emit 0C3h
    }
}

