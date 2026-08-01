// cl: /DNDEBUG /MD /EHsc

class StateMachine;

class AIFollowWaypointPathExactState
{
public:
    AIFollowWaypointPathExactState(StateMachine *, bool);
};

__declspec(naked) AIFollowWaypointPathExactState::AIFollowWaypointPathExactState(StateMachine *, bool)
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
        _emit 080h
        _emit 0A8h
        _emit 009h
        _emit 001h
        _emit 0E8h
        _emit 01Bh
        _emit 091h
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
        _emit 0D1h
        _emit 026h
        _emit 0EBh
        _emit 0FFh
        _emit 08Ah
        _emit 04Ch
        _emit 024h
        _emit 010h
        _emit 0C7h
        _emit 006h
        _emit 028h
        _emit 0A8h
        _emit 009h
        _emit 001h
        _emit 0C7h
        _emit 046h
        _emit 050h
        _emit 000h
        _emit 000h
        _emit 000h
        _emit 000h
        _emit 088h
        _emit 04Eh
        _emit 054h
        _emit 08Bh
        _emit 0C6h
        _emit 05Eh
        _emit 059h
        _emit 0C2h
        _emit 008h
        _emit 000h
    }
}
