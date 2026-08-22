// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// FILE: AptScreenFactories.cpp ///////////////////////////////////////////////
//
// BFME-only. Fifteen ninety-eight-byte factories sit between 0x00104AC0 and
// 0x001051C0, one per .apt screen, and a table in .data pairs each with its
// screen name. Each is the same three lines: new a screen object of a fixed
// size, hand the argument to its constructor, return the pointer or null if the
// allocation failed.
//
// The table gives the screen, not the function, so the C++ names here are ours.
// The sizes and the constructor addresses are read off the retail bodies, and
// each object is described only by its size - nothing in these bodies touches a
// member, so there is no layout to recover and none is invented.
//
// Objectives.apt and PlayerStatus.apt share one factory at 0x00104F40; the two
// table entries point at the same body.
//
///////////////////////////////////////////////////////////////////////////////

// LoadScreen.apt, retail 0x00104AC0, object 0x258 bytes.
class BfmeAptScreenLoadScreen
{
public:
	BfmeAptScreenLoadScreen( void *context );

private:
	char m_unmodelled[ 0x258 ];
};

// ?createAptScreenLoadScreen@@YGPAXPAX@Z
void * __stdcall createAptScreenLoadScreen( void *context )
{
	return new BfmeAptScreenLoadScreen( context );
}

// LanLobby.apt, retail 0x00104B40, object 0x3DC bytes.
class BfmeAptScreenLanLobby
{
public:
	BfmeAptScreenLanLobby( void *context );

private:
	char m_unmodelled[ 0x3DC ];
};

// ?createAptScreenLanLobby@@YGPAXPAX@Z
void * __stdcall createAptScreenLanLobby( void *context )
{
	return new BfmeAptScreenLanLobby( context );
}

// MainMenu.apt, retail 0x00104BC0, object 0x280 bytes.
class BfmeAptScreenMainMenu
{
public:
	BfmeAptScreenMainMenu( void *context );

private:
	char m_unmodelled[ 0x280 ];
};

// ?createAptScreenMainMenu@@YGPAXPAX@Z
void * __stdcall createAptScreenMainMenu( void *context )
{
	return new BfmeAptScreenMainMenu( context );
}

// OnlineShell.apt, retail 0x00104C40, object 0x280 bytes.
class BfmeAptScreenOnlineShell
{
public:
	BfmeAptScreenOnlineShell( void *context );

private:
	char m_unmodelled[ 0x280 ];
};

// ?createAptScreenOnlineShell@@YGPAXPAX@Z
void * __stdcall createAptScreenOnlineShell( void *context )
{
	return new BfmeAptScreenOnlineShell( context );
}

// Options.apt, retail 0x00104CC0, object 0x310 bytes.
class BfmeAptScreenOptions
{
public:
	BfmeAptScreenOptions( void *context );

private:
	char m_unmodelled[ 0x310 ];
};

// ?createAptScreenOptions@@YGPAXPAX@Z
void * __stdcall createAptScreenOptions( void *context )
{
	return new BfmeAptScreenOptions( context );
}

// DisconnectScreen.apt, retail 0x00104D40, object 0x26C bytes.
class BfmeAptScreenDisconnectScreen
{
public:
	BfmeAptScreenDisconnectScreen( void *context );

private:
	char m_unmodelled[ 0x26C ];
};

// ?createAptScreenDisconnectScreen@@YGPAXPAX@Z
void * __stdcall createAptScreenDisconnectScreen( void *context )
{
	return new BfmeAptScreenDisconnectScreen( context );
}

// SaveLoad.apt, retail 0x00104DC0, object 0x288 bytes.
class BfmeAptScreenSaveLoad
{
public:
	BfmeAptScreenSaveLoad( void *context );

private:
	char m_unmodelled[ 0x288 ];
};

// ?createAptScreenSaveLoad@@YGPAXPAX@Z
void * __stdcall createAptScreenSaveLoad( void *context )
{
	return new BfmeAptScreenSaveLoad( context );
}

// Skirmish.apt, retail 0x00104E40, object 0x43C bytes.
class BfmeAptScreenSkirmish
{
public:
	BfmeAptScreenSkirmish( void *context );

private:
	char m_unmodelled[ 0x43C ];
};

// ?createAptScreenSkirmish@@YGPAXPAX@Z
void * __stdcall createAptScreenSkirmish( void *context )
{
	return new BfmeAptScreenSkirmish( context );
}

// QuitMenu.apt, retail 0x00104EC0, object 0x260 bytes.
class BfmeAptScreenQuitMenu
{
public:
	BfmeAptScreenQuitMenu( void *context );

private:
	char m_unmodelled[ 0x260 ];
};

// ?createAptScreenQuitMenu@@YGPAXPAX@Z
void * __stdcall createAptScreenQuitMenu( void *context )
{
	return new BfmeAptScreenQuitMenu( context );
}

// Objectives.apt and PlayerStatus.apt, retail 0x00104F40, object 0x290 bytes.
class BfmeAptScreenObjectives
{
public:
	BfmeAptScreenObjectives( void *context );

private:
	char m_unmodelled[ 0x290 ];
};

// ?createAptScreenObjectives@@YGPAXPAX@Z
void * __stdcall createAptScreenObjectives( void *context )
{
	return new BfmeAptScreenObjectives( context );
}

// ScoreScreen.apt, retail 0x00104FC0, object 0x334 bytes.
class BfmeAptScreenScoreScreen
{
public:
	BfmeAptScreenScoreScreen( void *context );

private:
	char m_unmodelled[ 0x334 ];
};

// ?createAptScreenScoreScreen@@YGPAXPAX@Z
void * __stdcall createAptScreenScoreScreen( void *context )
{
	return new BfmeAptScreenScoreScreen( context );
}

// CampaignReview.apt, retail 0x00105040, object 0x258 bytes.
class BfmeAptScreenCampaignReview
{
public:
	BfmeAptScreenCampaignReview( void *context );

private:
	char m_unmodelled[ 0x258 ];
};

// ?createAptScreenCampaignReview@@YGPAXPAX@Z
void * __stdcall createAptScreenCampaignReview( void *context )
{
	return new BfmeAptScreenCampaignReview( context );
}

// InGameChat.apt, retail 0x001050C0, object 0x2A4 bytes.
class BfmeAptScreenInGameChat
{
public:
	BfmeAptScreenInGameChat( void *context );

private:
	char m_unmodelled[ 0x2A4 ];
};

// ?createAptScreenInGameChat@@YGPAXPAX@Z
void * __stdcall createAptScreenInGameChat( void *context )
{
	return new BfmeAptScreenInGameChat( context );
}

// SpellStore.apt, retail 0x00105140, object 0x2D4 bytes.
class BfmeAptScreenSpellStore
{
public:
	BfmeAptScreenSpellStore( void *context );

private:
	char m_unmodelled[ 0x2D4 ];
};

// ?createAptScreenSpellStore@@YGPAXPAX@Z
void * __stdcall createAptScreenSpellStore( void *context )
{
	return new BfmeAptScreenSpellStore( context );
}

class NameKeyGenerator
{
public:
	int nameToKey( const char *name );
};

extern NameKeyGenerator *TheNameKeyGenerator;

class BfmeAptScreenBase
{
public:
	BfmeAptScreenBase( void *context );
	~BfmeAptScreenBase();
	virtual void slot0();

private:
	char m_unmodelled[ 0x214 ];
};

// QuickMatchMenu, retail 0x001051C0, object 0x2B0 bytes.
class BfmeAptScreenQuickMatchMenu : public BfmeAptScreenBase
{
public:
	BfmeAptScreenQuickMatchMenu( void *context );
	virtual void slot0();

private:
	bool m_isMatching;
	char m_pad219[ 3 ];
	int m_matchingLevel;
	bool m_isStopping;
	char m_pad221[ 3 ];
	int m_selectedMap;
	int m_parentOptionsKey;
	void *m_parentOptions;
	int m_maxPingKey;
	void *m_maxPing;
	int m_numPlayersKey;
	void *m_numPlayers;
	int m_ladderKey;
	void *m_ladder;
	int m_maxDisconnectsKey;
	void *m_maxDisconnects;
	int m_sideKey;
	void *m_side;
	int m_colorKey;
	void *m_color;
	int m_backKey;
	void *m_back;
	int m_startKey;
	void *m_start;
	int m_currentMatchingLevelKey;
	void *m_currentMatchingLevel;
	int m_personalInfoKey;
	void *m_personalInfo;
	int m_mapSelectKey;
	void *m_mapSelect;
	int m_parentProgressKey;
	void *m_parentProgress;
	int m_quickMatchListKey;
	void *m_quickMatchList;
	int m_widenKey;
	void *m_widen;
	int m_stopKey;
	void *m_stop;
	int m_parentStatsKey;
	void *m_parentStats;
};

BfmeAptScreenQuickMatchMenu::BfmeAptScreenQuickMatchMenu( void *context )
	: BfmeAptScreenBase( context )
{
	m_isMatching = false;
	m_matchingLevel = 0;
	m_isStopping = false;
	m_selectedMap = 0;
	m_parentOptionsKey = TheNameKeyGenerator->nameToKey( "WOLQuickMatchMenu.wnd:ParentOptions" );
	m_parentOptions = 0;
	m_maxPingKey = TheNameKeyGenerator->nameToKey( "WOLQuickMatchMenu.wnd:ComboBoxMaxPing" );
	m_maxPing = 0;
	m_numPlayersKey = TheNameKeyGenerator->nameToKey( "WOLQuickMatchMenu.wnd:ComboBoxNumPlayers" );
	m_numPlayers = 0;
	m_ladderKey = TheNameKeyGenerator->nameToKey( "WOLQuickMatchMenu.wnd:ComboBoxLadder" );
	m_ladder = 0;
	m_maxDisconnectsKey = TheNameKeyGenerator->nameToKey( "WOLQuickMatchMenu.wnd:ComboBoxMaxDisconnects" );
	m_maxDisconnects = 0;
	m_sideKey = TheNameKeyGenerator->nameToKey( "WOLQuickMatchMenu.wnd:ComboBoxSide" );
	m_side = 0;
	m_colorKey = TheNameKeyGenerator->nameToKey( "WOLQuickMatchMenu.wnd:ComboBoxColor" );
	m_color = 0;
	m_backKey = TheNameKeyGenerator->nameToKey( "WOLQuickMatchMenu.wnd:ButtonBack" );
	m_back = 0;
	m_startKey = TheNameKeyGenerator->nameToKey( "WOLQuickMatchMenu.wnd:ButtonStart" );
	m_start = 0;
	m_currentMatchingLevelKey = TheNameKeyGenerator->nameToKey( "WOLQuickMatchMenu.wnd:currentMatchingLevel" );
	m_currentMatchingLevel = 0;
	m_personalInfoKey = TheNameKeyGenerator->nameToKey( "WOLQuickMatchMenu.wnd:PersonalInfo" );
	m_personalInfo = 0;
	m_mapSelectKey = TheNameKeyGenerator->nameToKey( "WOLQuickMatchMenu.wnd:ListBoxMapSelect" );
	m_mapSelect = 0;
	m_parentProgressKey = TheNameKeyGenerator->nameToKey( "WOLQuickMatchMenu.wnd:ParentProgress" );
	m_parentProgress = 0;
	m_quickMatchListKey = TheNameKeyGenerator->nameToKey( "WOLQuickMatchMenu.wnd:ListboxQuickMatch" );
	m_quickMatchList = 0;
	m_widenKey = TheNameKeyGenerator->nameToKey( "WOLQuickMatchMenu.wnd:ButtonWiden" );
	m_widen = 0;
	m_stopKey = TheNameKeyGenerator->nameToKey( "WOLQuickMatchMenu.wnd:ButtonStop" );
	m_stop = 0;
	m_parentStatsKey = TheNameKeyGenerator->nameToKey( "WOLQuickMatchMenu.wnd:ParentStats" );
	m_parentStats = 0;
}

// ?createAptScreenQuickMatchMenu@@YGPAXPAX@Z
void * __stdcall createAptScreenQuickMatchMenu( void *context )
{
	return new BfmeAptScreenQuickMatchMenu( context );
}

// WOLQuickMatchMenu, retail 0x00506040, object 0x28 bytes. The odd one out: its
// constructor is inlined rather than called, so the factory runs the base
// constructor at 0x00470620, stores its own vtable, zeroes the member at +0x24,
// and then clears the singleton at 0x012F4820 before returning. Only the base
// class is polymorphic-and-separate here; everything else is this one call site.
class BfmeQuickMatchScreenBase
{
public:
	BfmeQuickMatchScreenBase( void *context );
	virtual void slot0();

private:
	char m_unmodelled[ 0x20 ];
};

class BfmeQuickMatchScreen : public BfmeQuickMatchScreenBase
{
public:
	BfmeQuickMatchScreen( void *context );
	virtual void slot0();

private:
	int m_fieldAt24;
};

extern void *TheBfmeQuickMatchScreenSlot;   // 0x012F4820

inline BfmeQuickMatchScreen::BfmeQuickMatchScreen( void *context )
	: BfmeQuickMatchScreenBase( context )
{
	m_fieldAt24 = 0;
	TheBfmeQuickMatchScreenSlot = 0;
}

// ?createAptScreenWOLQuickMatchMenu@@YGPAXPAX@Z
void * __stdcall createAptScreenWOLQuickMatchMenu( void *context )
{
	return new BfmeQuickMatchScreen( context );
}

// OnlineProfile, retail 0x0055BBA0, object 0x3C bytes. Two departures from the
// rest: it is __cdecl rather than __stdcall - retail returns with a bare ret -
// and it refuses to build a second one, returning null when the singleton at
// 0x012F4AB4 is already set.
class BfmeOnlineProfileScreen
{
public:
	BfmeOnlineProfileScreen( void *context );

private:
	char m_unmodelled[ 0x3C ];
};

extern void *TheBfmeOnlineProfileSlot;   // 0x012F4AB4

// ?createAptScreenOnlineProfile@@YAPAXPAX@Z
void *createAptScreenOnlineProfile( void *context )
{
	if( TheBfmeOnlineProfileSlot )
		return 0;

	return new BfmeOnlineProfileScreen( context );
}
