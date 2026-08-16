// cl: /DNDEBUG /MD /EHs-c-
// Open-BFME5: PlayerList::setLocalPlayer, retail 0x000DF3C0, 97 bytes,
// converted out of Code/gen_asm/d_000d6fb0.asm. zh_sweep packet 000df3c0
// carries the earlier investigation; this finishes it.
//
// Zero Hour's body covers the first 45 bytes exactly and stops there. BFME
// appends 52 bytes that notify two subsystems, each with a function pointer,
// and the second notification is a tail call with the incoming argument slot
// overwritten. Both are outside the `player != m_local` guard -- retail's
// `je 0x000DF3ED` jumps past the swap and lands on the first of them -- so they
// run on every call, not only when the local player actually changes.
//
// What the two globals are:
//
//   0x012ED5BC  TheShroudManager. The engine-init block at 0x0038A2AC stores
//               the freshly constructed object here and then sets its name from
//               the literal "TheShroudManager" at 0x010EB3E0, the same
//               constructor-tag evidence that named TheRadar. Its neighbours
//               agree: 0x012ED5C4 takes "TheCollisionManager" twenty bytes
//               later in the same block.
//
//   0x012ED5C0  unnamed. Nothing in .text stores to it -- 25 reads, no write --
//               so whatever constructs it does so through a pointer, and the
//               init block skips straight from 0x012ED5BC to 0x012ED5C4. It
//               keeps an address-derived name until something proves one.
//
// The two methods are forwarders of the same shape, `mov ecx,[ecx+0x0C]; jmp`,
// which is why they are named for their addresses rather than guessed at: the
// body behind 0x008F7380 stores its two arguments at +0x64 and +0x6C of the
// object hanging off +0x0C, and nothing here says what those fields mean.
//
// The two function pointers are the ledger's own d_001072A0 and d_001072F0,
// 58-byte siblings 0x50 apart that each notify TheDisplay through vtable slot
// 0x10C/0x118 and TheRadar through 0x24/0x2C. Their addresses are relocation
// sites, so the byte gate does not depend on which one is which -- but the
// shapes match the two calls, and taking their address is what retail does.

typedef int Int;

class AsciiString;
class Team;

class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();

private:
	void *m_name;
};

class Snapshot
{
public:
	~Snapshot() {}
	virtual void crc() = 0;
	virtual void xfer() = 0;
	virtual void loadPostProcess() = 0;
};

class Player
{
public:
	void becomingLocalPlayer( bool becoming );

	unsigned char m_unreconstructed_00[0x24];
	Int m_playerRefreshTag;									///< +0x24, handed to the shroud manager
};

// The ledger's names for the two callbacks; see the header comment. The first
// is now real C++ in SubsystemRefreshCallbacks.cpp and takes its three
// arguments, so its decoration moved with it; the second is still a byte dump
// under the no-argument name.
void d_001072a0( Int a1, Int a2, Int a3 );
void d_001072f0( void );

typedef void (*SubsystemRefreshProc3)( Int, Int, Int );
typedef void (*SubsystemRefreshProc)( void );

class ShroudManager
{
public:
	void m_008F7380( Int tag, SubsystemRefreshProc3 refresh );
};

class Gen_012ED5C0
{
public:
	void m_00880E10( SubsystemRefreshProc refresh );
};

extern ShroudManager *TheShroudManager;
extern Gen_012ED5C0 *g_012ED5C0;

class PlayerList : public SubsystemInterface, public Snapshot
{
public:
	void setLocalPlayer( Player *player );
	Player *getNeutralPlayer( void ) { return m_players[0]; }

private:
	Player *m_local;										///< +0x0C
	int m_playerCount;										///< +0x10
	Player *m_players[32];									///< +0x14
};

//-----------------------------------------------------------------------------
// ?setLocalPlayer@PlayerList@@QAEXPAVPlayer@@@Z
void PlayerList::setLocalPlayer( Player *player )
{
	if (player == 0)
		player = getNeutralPlayer();

	if (player != m_local)
	{
		if (m_local)
			m_local->becomingLocalPlayer(false);
		m_local = player;
		player->becomingLocalPlayer(true);
	}

	if (TheShroudManager)
		TheShroudManager->m_008F7380(player->m_playerRefreshTag, d_001072a0);

	if (g_012ED5C0)
		g_012ED5C0->m_00880E10(d_001072f0);
}
