// cl: /DNDEBUG /MD /EHsc /Ireference/shims/sweep /Ireference/shims/campaignmanagerascii /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWLib

#include "Common/AsciiString.h"

class StateMachine;

class State
{
public:
	State(StateMachine *machine, AsciiString name);

	virtual ~State();

private:
	unsigned char m_head[0x20];
};

class AITunnelNetworkGuardState : public State
{
public:
	AITunnelNetworkGuardState(StateMachine *machine);

private:
	void *m_guardMachine;
};

// ??0AITunnelNetworkGuardState@@QAE@PAVStateMachine@@@Z
AITunnelNetworkGuardState::AITunnelNetworkGuardState(StateMachine *machine) :
	State(machine, "AITunnelNetworkGuardState"),
	m_guardMachine(0)
{
}
