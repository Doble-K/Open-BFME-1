// cl: /DNDEBUG /MD /EHsc

class StateMachine;

class AIAttackAimAtTargetState
{
public:
    AIAttackAimAtTargetState(StateMachine *, bool, bool);
};

__declspec(naked) AIAttackAimAtTargetState::AIAttackAimAtTargetState(StateMachine *, bool, bool)
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
        _emit 0B4h
        _emit 07Ch
        _emit 009h
        _emit 001h
        _emit 0E8h
        _emit 02Bh
        _emit 07Ah
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
        _emit 011h
        _emit 024h
        _emit 0E9h
        _emit 0FFh
        _emit 08Ah
        _emit 04Ch
        _emit 024h
        _emit 010h
        _emit 08Ah
        _emit 054h
        _emit 024h
        _emit 014h
        _emit 032h
        _emit 0C0h
        _emit 088h
        _emit 046h
        _emit 025h
        _emit 088h
        _emit 046h
        _emit 026h
        _emit 0C7h
        _emit 006h
        _emit 060h
        _emit 07Ch
        _emit 009h
        _emit 001h
        _emit 088h
        _emit 04Eh
        _emit 024h
        _emit 088h
        _emit 056h
        _emit 027h
        _emit 08Bh
        _emit 0C6h
        _emit 05Eh
        _emit 059h
        _emit 0C2h
        _emit 00Ch
        _emit 000h
    }
}
