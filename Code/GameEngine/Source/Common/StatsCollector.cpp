// cl: /DNDEBUG /MD /EHsc /ICode/GameEngine/Include/Precompiled

#include "PreRTS.h"
#include <time.h>

class AsciiString
{
public:
	AsciiString() : m_data( 0 ) {}
	const char *str() const { return m_data ? m_data + 8 : ""; }

private:
	char *m_data;
};

class GameLogic
{
public:
	UnsignedInt getFrame() const { return m_frame; }

private:
	unsigned char m_unmodelled00[ 0x3C ];
	UnsignedInt m_frame;
};

extern GameLogic *TheGameLogic;

class GlobalData
{
public:
	unsigned char m_unmodelled00[ 8 ];
	AsciiString m_mapName;
};

extern GlobalData *TheWritableGlobalData;

class Player
{
public:
	const AsciiString &getSide() const { return m_side; }

private:
	unsigned char m_unmodelled00[ 0x28 ];
	AsciiString m_side;
};

class PlayerList
{
public:
	Player *getLocalPlayer() const { return m_localPlayer; }

private:
	unsigned char m_unmodelled00[ 0x0C ];
	Player *m_localPlayer;
};

extern PlayerList *ThePlayerList;

class StatsCollector
{
public:
	StatsCollector();

private:
	void writeInitialFileInfo();
	AsciiString m_statsFileName;
	UnsignedInt m_moneyDeposited;
	UnsignedInt m_moneyWithdrawn;
	UnsignedInt m_buildCommands;
	UnsignedInt m_moveCommands;
	UnsignedInt m_attackCommands;
	UnsignedInt m_scrollMapCommands;
	UnsignedInt m_aiUnits;
	UnsignedInt m_playerUnits;
	UnsignedInt m_alliesKilled;
	UnsignedInt m_enemiesKilled;
	UnsignedInt m_neutralsKilled;
	UnsignedInt m_scoreKeeperBuildingsLost;
	UnsignedInt m_scoreKeeperBuildingsBuilt;
	UnsignedInt m_scoreKeeperBuildingsDestroyed;
	UnsignedInt m_scoreKeeperUnitsLost;
	UnsignedInt m_scoreKeeperUnitsBuilt;
	UnsignedInt m_scoreKeeperUnitsDestroyed;
	UnsignedInt m_scoreKeeperMoneyEarned;
	UnsignedInt m_scoreKeeperMoneySpent;
	UnsignedInt m_scrollBeginTime;
	UnsignedInt m_scrollTime;
	Bool m_isScrolling;
	Int m_timeCount;
	Int m_lastUpdate;
	Int m_startFrame;
};

StatsCollector::StatsCollector()
{
	m_moneyDeposited = 0;
	m_moneyWithdrawn = 0;
	m_buildCommands = 0;
	m_moveCommands = 0;
	m_attackCommands = 0;
	m_scrollMapCommands = 0;
	m_aiUnits = 0;
	m_playerUnits = 0;
	m_alliesKilled = 0;
	m_enemiesKilled = 0;
	m_neutralsKilled = 0;
	m_scoreKeeperBuildingsLost = 0;
	m_scoreKeeperBuildingsBuilt = 0;
	m_scoreKeeperBuildingsDestroyed = 0;
	m_scoreKeeperUnitsLost = 0;
	m_scoreKeeperUnitsBuilt = 0;
	m_scoreKeeperUnitsDestroyed = 0;
	m_scoreKeeperMoneyEarned = 0;
	m_scoreKeeperMoneySpent = 0;
	m_scrollBeginTime = 0;
	m_scrollTime = 0;
	m_isScrolling = FALSE;
	m_timeCount = 0;
	m_lastUpdate = 0;
	m_startFrame = TheGameLogic->getFrame();
}

void StatsCollector::writeInitialFileInfo()
{
	FILE *f = fopen( m_statsFileName.str(), "w" );
	if( !f )
		return;

	fprintf( f, "---------------------------------------------------\n" );
	time_t aclock;
	time( &aclock );
	struct tm *newTime = localtime( &aclock );
	fprintf( f, "Date:\t%s", asctime( newTime ) );
	fprintf( f, "Map:\t%s\n", TheWritableGlobalData->m_mapName.str() );
	fprintf( f, "Side:\t%s\n", ThePlayerList->getLocalPlayer()->getSide().str() );
	fprintf( f, "---------------------------------------------------\n\n" );

	fprintf( f, "Time*\t" );
	fprintf( f, "Instant_Average_FPS\t" );
	fprintf( f, "Instant_Net_FPS\t" );
	fprintf( f, "Build_Commands\t" );
	fprintf( f, "Move_Commands\t" );
	fprintf( f, "Attack_Commands\t" );
	fprintf( f, "Scroll_Map_Commands\t" );
	fprintf( f, "Scroll_Time_in_Seconds\t" );
	fprintf( f, "Other_Commands_(N/A)\t" );
	fprintf( f, "Player_Money_Amount\t" );
	fprintf( f, "Player_Money_Withdrawn\t" );
	fprintf( f, "Player_Money_Deposited\t" );
	fprintf( f, "Player_Units\t" );
	fprintf( f, "AI_Units\t" );
	fprintf( f, "Allies_Killed\t" );
	fprintf( f, "Enemies_Killed\t" );
	fprintf( f, "Neutrals_Killed\t" );
	fprintf( f, "ScoreKeeper_MoneySpent\t" );
	fprintf( f, "ScoreKeeper_MoneyEarned\t" );
	fprintf( f, "ScoreKeeper_UnitsDestroyed\t" );
	fprintf( f, "ScoreKeeper_UnitsBuilt\t" );
	fprintf( f, "ScoreKeeper_UnitsLost\t" );
	fprintf( f, "ScoreKeeper_BuildingsDestroyed\t" );
	fprintf( f, "ScoreKeeper_BuildingsBuilt\t" );
	fprintf( f, "ScoreKeeper_BuildingsLost\t" );
	fprintf( f, "\n" );

	fclose( f );
}
