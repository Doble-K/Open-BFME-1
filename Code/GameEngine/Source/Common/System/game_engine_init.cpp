// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Oy- /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib
// stlport
//
// GameEngine::init — the engine boot sequence, and the reason SubsystemLegend
// matters. It registers 60 subsystems in a fixed order, and that order is INI
// override precedence. The legend is registered FIRST so every subsystem after it
// can look itself up; of the 60, only TheWritableGlobalData and TheVictorySystem
// are handed hard-coded INI paths, so the other 58 load solely through
// SubsystemLegend.ini.
//
// Every registration below is transcribed from the binary — the order, the
// allocation sizes and the constructor addresses all come from
// reverse/gameengine_init_subsystems.tsv, which was recovered mechanically from
// init's push/call stream. The subsystem classes in game_engine_subsystems.h are
// stubs carrying retail's size and a pinned ctor, not ports.
#define __PLACEMENT_VEC_NEW_INLINE
#include <vector>
#include "PreRTS.h"
#include "subsystem_interface.h"
#include "game_engine_subsystems.h"
#include "Common/INI/INI.h"

class GameEngine : public SubsystemInterface
{
public:
	virtual void init();
	virtual void reset();
	virtual void update();
	Int m_maxFPS;			// +0x08
};

// ?init@GameEngine@@UAEXXZ present-unmatched
// A reconstruction, not a match: this emits 4026 of retail's 6689 bytes at
// 0x00079060 and roughly 660 of them agree. The registration sequence itself is
// faithful; three things stop it converging, and they are the work items:
//   1. retail performs several un-named setup allocations BEFORE the first
//      registration (16 bytes @ ctor 0x009A1E10 among them), so everything after
//      is shifted;
//   2. our operator new resolves to a different body than retail's ??2@YAPAXI@Z;
//   3. about 1700 of the 6689 bytes are not registrations at all and have not
//      been reversed yet.
// The row for 0x00079060 still belongs to the MASM dump; this file is whitelisted
// in reverse/unclaimed_sources_whitelist.txt. Port the subsystem classes first —
// each one finished makes this strictly closer.
void GameEngine::init()
{
	setName("GameEngine");
	INI ini;
	m_maxFPS = 45;

	initSubsystem(TheSubsystemLegend, "TheSubsystemLegend", new SubsystemLegend, NULL);
	initSubsystem(TheWritableGlobalData, "TheWritableGlobalData", new WritableGlobalData, NULL, "Data\\INI\\Default\\Water.ini", "Data\\INI\\Water.ini", "Data\\INI\\Default\\Environment.ini");
	initSubsystem(TheGlobalLanguageData, "TheGlobalLanguageData", new GlobalLanguageData, NULL);
	initSubsystem(TheGameText, "TheGameText", createGameText(), NULL);
	initSubsystem(TheAudio, "TheAudio", createAudio(), NULL);
	initSubsystem(TheEva, "TheEva", new Eva, NULL);
	initSubsystem(TheScienceStore, "TheScienceStore", new ScienceStore, NULL);
	initSubsystem(TheUpgradeCenter, "TheUpgradeCenter", new UpgradeCenter, NULL);
	initSubsystem(TheMultiplayerSettings, "TheMultiplayerSettings", new MultiplayerSettings, NULL);
	initSubsystem(TheTerrainTypes, "TheTerrainTypes", new TerrainTypes, NULL);
	initSubsystem(TheTerrainRoads, "TheTerrainRoads", new TerrainRoads, NULL);
	initSubsystem(TheCDManager, "TheCDManager", createCDManager(), NULL);
	initSubsystem(TheGlobalWeatherSystem, "TheGlobalWeatherSystem", new GlobalWeatherSystem, NULL);
	initSubsystem(TheFunctionLexicon, "TheFunctionLexicon", createFunctionLexicon(), NULL);
	initSubsystem(TheModuleFactory, "TheModuleFactory", createModuleFactory(), NULL);
	initSubsystem(TheMessageStream, "TheMessageStream", createMessageStream(), NULL);
	initSubsystem(TheSidesList, "TheSidesList", new SidesList, NULL);
	initSubsystem(TheCaveSystem, "TheCaveSystem", new CaveSystem, NULL);
	initSubsystem(TheRankInfoStore, "TheRankInfoStore", new RankInfoStore, NULL);
	initSubsystem(ThePlayerAITypeSet, "ThePlayerAITypeSet", new PlayerAITypeSet, NULL);
	initSubsystem(ThePlayerTemplateStore, "ThePlayerTemplateStore", new PlayerTemplateStore, NULL);
	initSubsystem(TheFXParticleSystemManager, "TheFXParticleSystemManager", createFXParticleSystemManager(), NULL);
	initSubsystem(TheFXListStore, "TheFXListStore", new FXListStore, NULL);
	initSubsystem(TheWeaponStore, "TheWeaponStore", new WeaponStore, NULL);
	initSubsystem(TheObjectCreationListStore, "TheObjectCreationListStore", new ObjectCreationListStore, NULL);
	initSubsystem(TheLocomotorStore, "TheLocomotorStore", new LocomotorStore, NULL);
	initSubsystem(TheSpecialPowerStore, "TheSpecialPowerStore", new SpecialPowerStore, NULL);
	initSubsystem(TheDamageFXStore, "TheDamageFXStore", new DamageFXStore, NULL);
	initSubsystem(TheArmorStore, "TheArmorStore", new ArmorStore, NULL);
	initSubsystem(TheBuildAssistant, "TheBuildAssistant", new BuildAssistant, NULL);
	initSubsystem(TheEmotionSystem, "TheEmotionSystem", new EmotionSystem, NULL);
	initSubsystem(TheThingFactory, "TheThingFactory", createThingFactory(), NULL);
	initSubsystem(TheLightPointSystem, "TheLightPointSystem", new LightPointSystem, NULL);
	initSubsystem(TheExperienceLevelSystem, "TheExperienceLevelSystem", new ExperienceLevelSystem, NULL);
	initSubsystem(TheAptPlayer, "TheAptPlayer", createAptPlayer(), NULL);
	initSubsystem(TheLivingWorldManager, "TheLivingWorldManager", new LivingWorldManager, NULL);
	initSubsystem(TheGameClient, "TheGameClient", createGameClient(), NULL);
	initSubsystem(TheAI, "TheAI", new AI, NULL);
	initSubsystem(TheAerialPathfinder, "TheAerialPathfinder", new AerialPathfinder, NULL);
	initSubsystem(TheLivingWorldLogic, "TheLivingWorldLogic", new LivingWorldLogic, NULL);
	initSubsystem(TheSplineService, "TheSplineService", new SplineService, NULL);
	initSubsystem(TheAttributeModifierStore, "TheAttributeModifierStore", new AttributeModifierStore, NULL);
	initSubsystem(TheTaintManager, "TheTaintManager", new TaintManager, NULL);
	initSubsystem(TheScriptEngine, "TheScriptEngine", new ScriptEngine, NULL);
	initSubsystem(TheLuaScriptEngine, "TheLuaScriptEngine", new LuaScriptEngine, NULL);
	initSubsystem(TheTeamFactory, "TheTeamFactory", new TeamFactory, NULL);
	initSubsystem(TheCrateSystem, "TheCrateSystem", new CrateSystem, NULL);
	initSubsystem(ThePlayerList, "ThePlayerList", new PlayerList, NULL);
	initSubsystem(TheGameLogic, "TheGameLogic", createGameLogic(), NULL);
	initSubsystem(TheRecorder, "TheRecorder", createRecorder(), NULL);
	initSubsystem(TheRadar, "TheRadar", createRadar(), NULL);
	initSubsystem(TheVictoryConditions, "TheVictoryConditions", createVictoryConditions(), NULL);
	initSubsystem(TheMetaMap, "TheMetaMap", new MetaMap, NULL);
	initSubsystem(TheHouseColorSystem, "TheHouseColorSystem", new HouseColorSystem, NULL);
	initSubsystem(TheLivingWorldCampaignManager, "TheLivingWorldCampaignManager", new LivingWorldCampaignManager, NULL);
	initSubsystem(TheVictorySystem, "TheVictorySystem", new VictorySystem, NULL);
	initSubsystem(TheActionManager, "TheActionManager", new ActionManager, NULL);
	initSubsystem(TheGameStateMap, "TheGameStateMap", new GameStateMap, NULL);
	initSubsystem(TheGameState, "TheGameState", new GameState, NULL);
	initSubsystem(TheGameResultsQueue, "TheGameResultsQueue", createGameResultsQueue(), NULL);
}
