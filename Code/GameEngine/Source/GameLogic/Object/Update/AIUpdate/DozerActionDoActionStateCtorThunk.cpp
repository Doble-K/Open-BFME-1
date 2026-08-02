// cl: /DNDEBUG /MD /EHsc

class StateMachine;
enum DozerTask
{
    DOZER_TASK_DUMMY
};

class DozerActionDoActionState
{
public:
    DozerActionDoActionState(StateMachine *, DozerTask);
};

__declspec(naked) DozerActionDoActionState::DozerActionDoActionState(StateMachine *, DozerTask)
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
        __emit 0x74;
        __emit 0x6e;
        __emit 0x0c;
        __emit 0x01;
        __emit 0xe8;
        __emit 0xcb;
        __emit 0x17;
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
        __emit 0xb1;
        __emit 0xc1;
        __emit 0xd4;
        __emit 0xff;
        __emit 0x8b;
        __emit 0x4c;
        __emit 0x24;
        __emit 0x10;
        __emit 0xc7;
        __emit 0x06;
        __emit 0x20;
        __emit 0x6e;
        __emit 0x0c;
        __emit 0x01;
        __emit 0x89;
        __emit 0x4e;
        __emit 0x24;
        __emit 0xc7;
        __emit 0x46;
        __emit 0x28;
        __emit 0x00;
        __emit 0x00;
        __emit 0x00;
        __emit 0x00;
        __emit 0x8b;
        __emit 0xc6;
        __emit 0x5e;
        __emit 0x59;
        __emit 0xc2;
        __emit 0x08;
        __emit 0x00;
    }
}
