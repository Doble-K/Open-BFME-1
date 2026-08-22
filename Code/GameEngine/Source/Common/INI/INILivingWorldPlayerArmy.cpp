// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
//
// The LivingWorldPlayerArmy block -- BFME-only, like everything Living World.
//
// The global is named the same way INILivingWorld.cpp names its own:
// GameEngine::init passes the literal "TheLivingWorldCampaignManager"
// immediately before pushing 0x012F1024, and the ledger already carries the
// initSubsystem<LivingWorldCampaignManager> instantiation, so the class has a
// real name.
//
// The block's own record does not. Its constructor at 0x003649D0 and destructor
// at 0x00362B20 are unnamed in the image and nothing here reads a member, so it
// is described by its size alone - 0x58, the frame the parser reserves - and the
// member that takes it is named for the call site.
#include "PreRTS.h"
#include "Common/INI.h"
#include <vector>

class LivingWorldPlayerArmy
{
public:
	LivingWorldPlayerArmy();
	LivingWorldPlayerArmy( const LivingWorldPlayerArmy &other );
	~LivingWorldPlayerArmy();

	static const FieldParse m_fieldParseTable[];

	char m_unmodelled00[ 4 ];
	Int m_index;
	char m_unmodelled08[ 0x50 ];
};

class BfmeLivingWorldCampaignManager
{
public:
	void addPlayerArmy( LivingWorldPlayerArmy *army );

private:
	char m_unmodelled[ 0x20 ];
	std::vector<LivingWorldPlayerArmy> m_playerArmies;
};

extern BfmeLivingWorldCampaignManager *TheLivingWorldCampaignManager;	// 0x012F1024

void BfmeLivingWorldCampaignManager::addPlayerArmy( LivingWorldPlayerArmy *army )
{
	m_playerArmies.push_back( *army );
	m_playerArmies.back().m_index = m_playerArmies.size() - 1;
}

// ?parseLivingWorldPlayerArmy@@YAXPAVINI@@@Z
void parseLivingWorldPlayerArmy( INI *ini )
{
	if( !TheLivingWorldCampaignManager )
		return;

	LivingWorldPlayerArmy army;

	ini->initFromINI( &army, LivingWorldPlayerArmy::m_fieldParseTable );

	TheLivingWorldCampaignManager->addPlayerArmy( &army );
}
