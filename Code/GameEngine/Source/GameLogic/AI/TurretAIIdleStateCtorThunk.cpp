// cl: /DNDEBUG /MD /EHsc

class TurretStateMachine;

class TurretAIIdleState
{
public:
    TurretAIIdleState(TurretStateMachine *);
};

__declspec(naked) TurretAIIdleState::TurretAIIdleState(TurretStateMachine *)
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
        _emit 0C4h
        _emit 0BCh
        _emit 009h
        _emit 001h
        _emit 0E8h
        _emit 07Bh
        _emit 0B2h
        _emit 06Fh
        _emit 000h
        _emit 08Bh
        _emit 044h
        _emit 024h
        _emit 010h
        _emit 050h
        _emit 08Bh
        _emit 0CEh
        _emit 0E8h
        _emit 006h
        _emit 061h
        _emit 0E8h
        _emit 0FFh
        _emit 0C7h
        _emit 006h
        _emit 070h
        _emit 0BCh
        _emit 009h
        _emit 001h
        _emit 0C7h
        _emit 046h
        _emit 024h
        _emit 000h
        _emit 000h
        _emit 000h
        _emit 000h
        _emit 08Bh
        _emit 0C6h
        _emit 05Eh
        _emit 059h
        _emit 0C2h
        _emit 004h
        _emit 000h
    }
}

