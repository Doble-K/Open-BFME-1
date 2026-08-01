// cl: /DNDEBUG /MD /EHsc

class StateMachine;

class AIBusyState
{
public:
    AIBusyState(StateMachine *);
};

__declspec(naked) AIBusyState::AIBusyState(StateMachine *)
{
    __asm {
        _emit 051h
        _emit 056h
        _emit 051h
        _emit 08Bh
        _emit 0F1h
        _emit 089h
        _emit 064h
        _emit 024h
        _emit 008h
        _emit 08Bh
        _emit 0CCh
        _emit 068h
        _emit 090h
        _emit 07Ah
        _emit 009h
        _emit 001h
        _emit 0E8h
        _emit 0EBh
        _emit 07Bh
        _emit 071h
        _emit 000h
        _emit 08Bh
        _emit 044h
        _emit 024h
        _emit 010h
        _emit 050h
        _emit 08Bh
        _emit 0CEh
        _emit 0E8h
        _emit 0D1h
        _emit 025h
        _emit 0E9h
        _emit 0FFh
        _emit 0C7h
        _emit 006h
        _emit 0A0h
        _emit 07Ah
        _emit 009h
        _emit 001h
        _emit 08Bh
        _emit 0C6h
        _emit 05Eh
        _emit 059h
        _emit 0C2h
        _emit 004h
        _emit 000h
    }
}
