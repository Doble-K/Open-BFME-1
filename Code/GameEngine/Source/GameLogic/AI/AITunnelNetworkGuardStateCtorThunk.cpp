// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class StateMachine;

class AITunnelNetworkGuardState
{
public:
    AITunnelNetworkGuardState(StateMachine *machine);
};

// ??0AITunnelNetworkGuardState@@QAE@PAVStateMachine@@@Z
__declspec(naked) AITunnelNetworkGuardState::AITunnelNetworkGuardState(StateMachine *machine)
{
    __asm {
        __emit 0x51
        __emit 0x56
        __emit 0x51
        __emit 0x8b
        __emit 0xf1
        __emit 0x89
        __emit 0x64
        __emit 0x24
        __emit 0x08
        __emit 0x8b
        __emit 0xcc
        __emit 0x68
        __emit 0x0c
        __emit 0x83
        __emit 0x09
        __emit 0x01
        __emit 0xe8
        __emit 0xfb
        __emit 0x73
        __emit 0x71
        __emit 0x00
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x10
        __emit 0x50
        __emit 0x8b
        __emit 0xce
        __emit 0xe8
        __emit 0xe1
        __emit 0x1d
        __emit 0xe9
        __emit 0xff
        __emit 0xc7
        __emit 0x06
        __emit 0xb8
        __emit 0x82
        __emit 0x09
        __emit 0x01
        __emit 0xc7
        __emit 0x46
        __emit 0x24
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x8b
        __emit 0xc6
        __emit 0x5e
        __emit 0x59
        __emit 0xc2
        __emit 0x04
        __emit 0x00
    }
}
