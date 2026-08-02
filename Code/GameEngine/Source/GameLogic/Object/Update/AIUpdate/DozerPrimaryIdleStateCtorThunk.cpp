// cl: /DNDEBUG /MD /EHsc

class StateMachine;

class DozerPrimaryIdleState
{
public:
    DozerPrimaryIdleState(StateMachine *);
};

__declspec(naked) DozerPrimaryIdleState::DozerPrimaryIdleState(StateMachine *)
{
    __asm {
        __emit 0x51;
        __emit 0x56;
        __emit 0x51;
        __emit 0x8b;
        __emit 0xf1;
        __emit 0x89;
        __emit 0x64;
        __emit 0x24;
        __emit 0x08;
        __emit 0x8b;
        __emit 0xcc;
        __emit 0x68;
        __emit 0x54;
        __emit 0x6f;
        __emit 0x0c;
        __emit 0x01;
        __emit 0xe8;
        __emit 0x2b;
        __emit 0x15;
        __emit 0x5d;
        __emit 0x00;
        __emit 0x8b;
        __emit 0x44;
        __emit 0x24;
        __emit 0x10;
        __emit 0x50;
        __emit 0x8b;
        __emit 0xce;
        __emit 0xe8;
        __emit 0x11;
        __emit 0xbf;
        __emit 0xd4;
        __emit 0xff;
        __emit 0x33;
        __emit 0xc0;
        __emit 0x89;
        __emit 0x46;
        __emit 0x24;
        __emit 0x89;
        __emit 0x46;
        __emit 0x28;
        __emit 0x88;
        __emit 0x46;
        __emit 0x2c;
        __emit 0xc7;
        __emit 0x06;
        __emit 0x00;
        __emit 0x6f;
        __emit 0x0c;
        __emit 0x01;
        __emit 0x8b;
        __emit 0xc6;
        __emit 0x5e;
        __emit 0x59;
        __emit 0xc2;
        __emit 0x04;
        __emit 0x00;
    }
}
