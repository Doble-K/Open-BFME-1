// cl: /DNDEBUG /MD /EHsc /ICode/GameEngine/Include/Precompiled

#include "PreRTS.h"

class StatsCollectorAsciiString
{
public:
	StatsCollectorAsciiString() : m_data( 0 ) {}

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

class StatsCollector
{
public:
	StatsCollector();

private:
	StatsCollectorAsciiString m_statsFileName;
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
