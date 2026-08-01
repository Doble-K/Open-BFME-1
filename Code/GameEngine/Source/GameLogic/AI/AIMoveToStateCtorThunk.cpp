// cl: /DNDEBUG /MD /EHsc

class StateMachine;

class AIMoveToState
{
public:
    AIMoveToState(StateMachine *);
};

__declspec(naked) AIMoveToState::AIMoveToState(StateMachine *)
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
        _emit 060h
        _emit 08Fh
        _emit 009h
        _emit 001h
        _emit 0E8h
        _emit 07Bh
        _emit 057h
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
        _emit 031h
        _emit 0EDh
        _emit 0EBh
        _emit 0FFh
        _emit 0C7h
        _emit 006h
        _emit 008h
        _emit 08Fh
        _emit 009h
        _emit 001h
        _emit 0C6h
        _emit 046h
        _emit 050h
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
