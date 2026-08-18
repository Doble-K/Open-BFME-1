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

// QuickMatchMenu, retail 0x001051C0, object 0x2B0 bytes.
class BfmeAptScreenQuickMatchMenu
{
public:
	BfmeAptScreenQuickMatchMenu( void *context );

private:
	char m_unmodelled[ 0x2B0 ];
};

// ?createAptScreenQuickMatchMenu@@YGPAXPAX@Z
void * __stdcall createAptScreenQuickMatchMenu( void *context )
{
	return new BfmeAptScreenQuickMatchMenu( context );
}
