// cl: /DNDEBUG /MD /EHsc
// victory_conditions.cpp -- BFME's VictoryConditions subsystem as clean C++.
//
// Retail keeps the whole family in one TU around 0x0035F150-0x0035FED0 with the
// concrete vtable at VA 0x010E8D90 (22 slots). Identity comes from the ZH source
// (GameEngine/Source/GameLogic/System/VictoryConditions.cpp): slot 5 is the
// matched ?update@VictoryConditions@@ body, slot 12 walks ThePlayerList against
// the "FactionCivilian" template exactly like ZH's cachePlayerPtrs, and the
// factory at 0x0035F810 news 0xC4 bytes through the ctor at 0x0035F430.
//
// BFME deltas against ZH, read off the retail bodies:
//  - SubsystemInterface has nine virtual slots (see subsystem_interface.h); the
//    interface virtuals therefore start at slot 9, and BFME appends four new
//    ones (slots 18-21: the ShowEndGame/HideEndGame banner machinery and an
//    m_isDefeated getter).
//  - MAX_PLAYER_COUNT is 32 (every loop runs to 0x20).
//  - Three new members: m_endGameShowing (+0x0C) and m_endGameShowTime (+0x10),
//    zeroed only in the ctor and driven by the banner methods, and a defeat
//    counter at +0xC0 zeroed in reset() and bumped by every true return of
//    hasSinglePlayerBeenDefeated.
//  - reset() picks the victory mask from TheGameLogic's mode word (+0x10C):
//    mode 6 keeps ZH's NOBUILDINGS|NOUNITS, everything else NOBUILDINGS only.
// sizeof(VictoryConditions) == 0xC4, asserted below.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;
#define NULL 0
#define TRUE true
#define FALSE false

// Player as far as this TU touches it. Methods resolve out-of-line through
// reverse/symbols.csv; the two members model the retail offsets areAllies and
// cachePlayerPtrs read inline (getPlayerTemplate at +0x04, getDefaultTeam at
// +0x230).
class Team;
class PlayerTemplate;

enum Relationship
{
	ENEMIES = 0,
	NEUTRAL,
	ALLIES,
};

class Player
{
public:
	const PlayerTemplate *getPlayerTemplate() const { return m_playerTemplate; }
	Team *getDefaultTeam() const { return m_defaultTeam; }
	Relationship getRelationship( const Team *that ) const;
	Bool isPlayerObserver() const;
	Bool isLocalPlayer() const;

private:
	void					*m_vptrPad;								// +0x00 retail vptr
	PlayerTemplate *m_playerTemplate;				// +0x04
	char					 m_pad[ 0x230 - 8 ];
	Team					*m_defaultTeam;						// +0x230
};

// Four-byte stand-in for the AsciiString SubsystemInterface embeds at +4; no
// body here ever touches m_name.
class AsciiString
{
public:
	char *m_data;
};

// BFME's nine-slot subsystem base -- the retail truth this TU dispatches
// against (the shared subsystem_interface.h stops at six slots and keeps
// reset/update one slot early, which these bodies cannot afford: init() must
// tail-jump through [vptr+0x10]).
//   0 ~SubsystemInterface (body 0x009A1A40)   1 init
//   2 loadIniFilesFromLegend (0x009A1A50)     3 unidentified, empty (0x00067930)
//   4 reset                                   5 update
//   6 unidentified Bool(arg){false} (0x00067940)
//   7 unidentified, empty (0x009A16C0)        8 unidentified, empty-with-arg (0x009A16D0)
class SubsystemInterface
{
public:
	SubsystemInterface();
	virtual ~SubsystemInterface();
	virtual void init() = 0;
	virtual Bool loadIniFilesFromLegend();
	virtual void unidentifiedSlot03();
	virtual void reset() = 0;
	virtual void update() = 0;
	virtual Bool unidentifiedSlot06(Int arg);
	virtual void unidentifiedSlot07();
	virtual void unidentifiedSlot08(Int arg);
protected:
	AsciiString m_name;
};

enum VictoryType
{
	VICTORY_NOBUILDINGS = 1,
	VICTORY_NOUNITS = 2,
};

class VictoryConditionsInterface : public SubsystemInterface
{
public:
	VictoryConditionsInterface() { m_victoryConditions = 0; }

	virtual Bool hasAchievedVictory(Player *player) = 0;					// slot 9
	virtual Bool hasBeenDefeated(Player *player) = 0;							// slot 10
	virtual Bool hasSinglePlayerBeenDefeated(Player *player) = 0;	// slot 11
	virtual void cachePlayerPtrs( void ) = 0;											// slot 12
	virtual Bool isLocalAlliedVictory( void ) = 0;								// slot 13
	virtual Bool isLocalAlliedDefeat( void ) = 0;									// slot 14
	virtual Bool isLocalDefeat( void ) = 0;												// slot 15
	virtual Bool amIObserver( void ) = 0;													// slot 16
	virtual UnsignedInt getEndFrame( void ) = 0;									// slot 17
	// BFME-only banner machinery; descriptive names from the "ShowEndGame" /
	// "HideEndGame" event literals the retail bodies push (VA 0x010E8E10 /
	// 0x010E8E58), not from any symbol.
	virtual void showEndGame(void *a, void *b, void *c, void *d) = 0;	// slot 18 (0x0035F600)
	virtual void hideEndGame( void ) = 0;													// slot 19 (0x0035F770)
	virtual Bool isPlayerDefeated(Int index) = 0;									// slot 20 (0x0035F4C0)
	virtual void updateEndGame( void ) = 0;												// slot 21 (0x0035F1A0)

protected:
	Int m_victoryConditions;	// +0x08
};

enum { MAX_PLAYER_COUNT = 32 };

// TheGameLogic as far as reset() needs it: the game-mode word retail keeps at
// +0x10C (the same field the matched update body compares against 1/2/5/6).
class GameLogic
{
public:
	Int getGameMode( void ) const { return m_gameMode; }
private:
	char m_pad[ 0x10c ];
	Int m_gameMode;					// +0x10C
};

extern GameLogic *TheGameLogic;			///< retail [0x012F0898]

// TheGameInfo as far as isLocalAlliedVictory needs it: retail queries virtual
// slot 12 ([vptr+0x30]) as a Bool predicate before trusting the local slot.
class GameInfo
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual Bool unidentifiedSlot12() = 0;
};

extern GameInfo *TheGameInfo;				///< retail [0x012F708C]

// hasAchievedVictory reports the winning player index to TheGameLogic through
// the ILT thunk at 0x0000F5FB; the 35-byte body (0x00383C30) bounds the index
// to [0,8) and stamps TheGameLogic's frame counter (+0x3C) into the 0x1C-byte
// per-slot records at +0x1BC. Address-derived shim name, identity open.
class GameLogicShim
{
public:
	void unidentified_0000f5fb(Int playerIndex);
};


class VictoryConditions : public VictoryConditionsInterface
{
public:
	VictoryConditions();
	virtual ~VictoryConditions();

	virtual void init( void );
	virtual void reset( void );
	virtual void update( void );

	virtual Bool hasAchievedVictory(Player *player);
	virtual Bool hasBeenDefeated(Player *player);
	virtual Bool hasSinglePlayerBeenDefeated(Player *player);

	virtual void cachePlayerPtrs( void );

	virtual Bool isLocalAlliedVictory( void );
	virtual Bool isLocalAlliedDefeat( void );
	virtual Bool isLocalDefeat( void );
	virtual Bool amIObserver( void );
	virtual UnsignedInt getEndFrame( void );

	virtual void showEndGame(void *a, void *b, void *c, void *d);
	virtual void hideEndGame( void );
	virtual Bool isPlayerDefeated(Int index);
	virtual void updateEndGame( void );

private:
	Bool					m_endGameShowing;										// +0x0C
	UnsignedInt		m_endGameShowTime;									// +0x10
	Player*				m_players[MAX_PLAYER_COUNT];				// +0x14
	Int						m_localSlotNum;											// +0x94
	UnsignedInt		m_endFrame;													// +0x98
	Bool					m_isDefeated[MAX_PLAYER_COUNT];			// +0x9C
	Bool					m_localPlayerDefeated;							// +0xBC
	Bool					m_singleAllianceRemaining;					// +0xBD
	Bool					m_isObserver;												// +0xBE
	Int						m_defeatCount;											// +0xC0
};

typedef char BFMERetailVictoryConditionsSizeCheck[ sizeof( VictoryConditions ) == 0xc4 ? 1 : -1 ];

// The constructor, destructor and createVictoryConditions live in
// victory_conditions_create.cpp: their retail bodies carry EH frames, which
// MSVC only emits while their callees (reset, hideEndGame) stay undefined in
// the calling TU -- defined here, they are provably nothrow and the frame
// vanishes.

//-------------------------------------------------------------------------------------------------
// Compiles as a TU-local helper with MSVC's custom register convention
// (p1 in eax, p2 in caller's esi), exactly the 53-byte body at 0x0035F150.
inline static Bool areAllies(const Player *p1, const Player *p2)
{
	if (p1 != p2 &&
		p1->getRelationship(p2->getDefaultTeam()) == ALLIES &&
		p2->getRelationship(p1->getDefaultTeam()) == ALLIES)
		return true;

	return false;
}

//-------------------------------------------------------------------------------------------------
Bool VictoryConditions::hasAchievedVictory(Player *player)
{
	if (!player)
		return false;
	if (player->isPlayerObserver())
		return false;

	if (m_singleAllianceRemaining && m_defeatCount > 0)
	{
		for (Int i=0; i<MAX_PLAYER_COUNT; ++i)
		{
			if ( m_players[i] && !hasSinglePlayerBeenDefeated(m_players[i]) &&
				(player == m_players[i] || areAllies(m_players[i], player)) )
			{
				((GameLogicShim *)TheGameLogic)->unidentified_0000f5fb(i);
				return true;
			}
		}
	}

	return false;
}

//-------------------------------------------------------------------------------------------------
Bool VictoryConditions::isLocalAlliedVictory( void )
{
	if (!m_isObserver)
	{
		GameInfo *info = TheGameInfo;
		if (!info || !info->unidentifiedSlot12())
			return (hasAchievedVictory(m_players[m_localSlotNum]));
	}

	return false;
}

//-------------------------------------------------------------------------------------------------
Bool VictoryConditions::hasBeenDefeated(Player *player)
{
	if (!player)
		return false;
	if (player->isPlayerObserver())
		return false;

	if (m_singleAllianceRemaining && m_defeatCount > 0 && !hasAchievedVictory(player))
		return true;

	return false;
}

//-------------------------------------------------------------------------------------------------
Bool VictoryConditions::isLocalAlliedDefeat( void )
{
	if (m_isObserver)
	{
		if (m_defeatCount > 0)
			return m_singleAllianceRemaining;
		return false;
	}

	return (hasBeenDefeated(m_players[m_localSlotNum]));
}

//-------------------------------------------------------------------------------------------------
Bool VictoryConditions::isLocalDefeat( void )
{
	if (m_isObserver)
		return FALSE;

	return (m_localPlayerDefeated);
}

//-------------------------------------------------------------------------------------------------
Bool VictoryConditions::amIObserver( void )
{
	return m_isObserver;
}

//-------------------------------------------------------------------------------------------------
UnsignedInt VictoryConditions::getEndFrame( void )
{
	return m_endFrame;
}

//-------------------------------------------------------------------------------------------------
Bool VictoryConditions::isPlayerDefeated(Int index)
{
	return m_isDefeated[index];
}

//-------------------------------------------------------------------------------------------------
void VictoryConditions::init( void )
{
	reset();
}

//-------------------------------------------------------------------------------------------------
void VictoryConditions::reset( void )
{
	for (Int i=0; i<MAX_PLAYER_COUNT; ++i)
	{
		m_players[i] = NULL;
		m_isDefeated[i] = false;
	}
	m_localPlayerDefeated = false;
	m_singleAllianceRemaining = false;
	m_isObserver = false;
	m_endFrame = 0;
	m_defeatCount = 0;
	m_localSlotNum = -1;

	m_victoryConditions = (TheGameLogic->getGameMode() == 6)
		? (VICTORY_NOBUILDINGS | VICTORY_NOUNITS)
		: VICTORY_NOBUILDINGS;
}
