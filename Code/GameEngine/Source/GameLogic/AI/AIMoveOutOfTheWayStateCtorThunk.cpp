// cl: /DNDEBUG /MD /EHsc

class StateMachine;

class AIMoveOutOfTheWayState
{
public:
    AIMoveOutOfTheWayState(StateMachine *);
};

__declspec(naked) AIMoveOutOfTheWayState::AIMoveOutOfTheWayState(StateMachine *)
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
        _emit 0D0h
        _emit 0A2h
        _emit 009h
        _emit 001h
        _emit 0E8h
        _emit 05Bh
        _emit 098h
        _emit 070h
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
        _emit 02Eh
        _emit 0EBh
        _emit 0FFh
        _emit 0C7h
        _emit 006h
        _emit 078h
        _emit 0A2h
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
