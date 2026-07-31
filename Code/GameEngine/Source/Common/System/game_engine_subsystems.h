#pragma once
#include "subsystem_interface.h"
#include "subsystem_legend.h"

// Stub subsystem types for the GameEngine::init reconstruction. Each carries the
// exact byte size retail passes to operator new and, where retail has one, a
// constructor declared-but-undefined so the call pins to retail's body. Members
// are NOT ported: the padding exists only so `new` emits retail's size.
//
// CLASS NAMES ARE PROVISIONAL — derived by stripping "The" from the global. They
// are right for the subsystems ZH also has and guesses for the BFME-only ones, so
// the ctor pins keyed on them are inert until a name is confirmed. The evidence
// behind every line here is reverse/gameengine_init_subsystems.tsv.
//
// SubsystemLegend itself is the real class from subsystem_legend.h, not a stub.

// TheSubsystemLegend is declared in subsystem_legend.h

class WritableGlobalData : public SubsystemInterface
{
public:
	WritableGlobalData();
	virtual void init();
	virtual void reset();
	virtual void update();
private:
	char m_unported[4744];		// retail sizeof = 4752
};

extern WritableGlobalData *TheWritableGlobalData;

class GlobalLanguageData : public SubsystemInterface
{
public:
	GlobalLanguageData();
	virtual void init();
	virtual void reset();
	virtual void update();
private:
	char m_unported[304];		// retail sizeof = 312
};

extern GlobalLanguageData *TheGlobalLanguageData;

class GameText : public SubsystemInterface
{
public:
	virtual void init();
	virtual void reset();
	virtual void update();
};
GameText *createGameText();

extern GameText *TheGameText;

class Audio : public SubsystemInterface
{
public:
	virtual void init();
	virtual void reset();
	virtual void update();
};
Audio *createAudio();

extern Audio *TheAudio;

class Eva : public SubsystemInterface
{
public:
	Eva();
	virtual void init();
	virtual void reset();
	virtual void update();
private:
	char m_unported[100];		// retail sizeof = 108
};

extern Eva *TheEva;

class ScienceStore : public SubsystemInterface
{
public:
	// no ctor of its own; retail calls SubsystemInterface::SubsystemInterface
	virtual void init();
	virtual void reset();
	virtual void update();
private:
	char m_unported[12];		// retail sizeof = 20
};

extern ScienceStore *TheScienceStore;

class UpgradeCenter : public SubsystemInterface
{
public:
	UpgradeCenter();
	virtual void init();
	virtual void reset();
	virtual void update();
private:
	char m_unported[12];		// retail sizeof = 20
};

extern UpgradeCenter *TheUpgradeCenter;

class MultiplayerSettings : public SubsystemInterface
{
public:
	MultiplayerSettings();
	virtual void init();
	virtual void reset();
	virtual void update();
private:
	char m_unported[128];		// retail sizeof = 136
};

extern MultiplayerSettings *TheMultiplayerSettings;

class TerrainTypes : public SubsystemInterface
{
public:
	TerrainTypes();
	virtual void init();
	virtual void reset();
	virtual void update();
private:
	char m_unported[4];		// retail sizeof = 12
};

extern TerrainTypes *TheTerrainTypes;

class TerrainRoads : public SubsystemInterface
{
public:
	TerrainRoads();
	virtual void init();
	virtual void reset();
	virtual void update();
private:
	char m_unported[8];		// retail sizeof = 16
};

extern TerrainRoads *TheTerrainRoads;

class CDManager : public SubsystemInterface
{
public:
	virtual void init();
	virtual void reset();
	virtual void update();
};
CDManager *createCDManager();

extern CDManager *TheCDManager;

class GlobalWeatherSystem : public SubsystemInterface
{
public:
	GlobalWeatherSystem();
	virtual void init();
	virtual void reset();
	virtual void update();
private:
	char m_unported[72];		// retail sizeof = 80
};

extern GlobalWeatherSystem *TheGlobalWeatherSystem;

class FunctionLexicon : public SubsystemInterface
{
public:
	virtual void init();
	virtual void reset();
	virtual void update();
};
FunctionLexicon *createFunctionLexicon();

extern FunctionLexicon *TheFunctionLexicon;

class ModuleFactory : public SubsystemInterface
{
public:
	virtual void init();
	virtual void reset();
	virtual void update();
};
ModuleFactory *createModuleFactory();

extern ModuleFactory *TheModuleFactory;

class MessageStream : public SubsystemInterface
{
public:
	virtual void init();
	virtual void reset();
	virtual void update();
};
MessageStream *createMessageStream();

extern MessageStream *TheMessageStream;

class SidesList : public SubsystemInterface
{
public:
	SidesList();
	virtual void init();
	virtual void reset();
	virtual void update();
private:
	char m_unported[2532];		// retail sizeof = 2540
};

extern SidesList *TheSidesList;

class CaveSystem : public SubsystemInterface
{
public:
	CaveSystem();
	virtual void init();
	virtual void reset();
	virtual void update();
private:
	char m_unported[16];		// retail sizeof = 24
};

extern CaveSystem *TheCaveSystem;

class RankInfoStore : public SubsystemInterface
{
public:
	// no ctor of its own; retail calls SubsystemInterface::SubsystemInterface
	virtual void init();
	virtual void reset();
	virtual void update();
private:
	char m_unported[12];		// retail sizeof = 20
};

extern RankInfoStore *TheRankInfoStore;

class PlayerAITypeSet : public SubsystemInterface
{
public:
	// no ctor of its own; retail calls SubsystemInterface::SubsystemInterface
	virtual void init();
	virtual void reset();
	virtual void update();
private:
	char m_unported[12];		// retail sizeof = 20
};

extern PlayerAITypeSet *ThePlayerAITypeSet;

class PlayerTemplateStore : public SubsystemInterface
{
public:
	PlayerTemplateStore();
	virtual void init();
	virtual void reset();
	virtual void update();
private:
	char m_unported[12];		// retail sizeof = 20
};

extern PlayerTemplateStore *ThePlayerTemplateStore;

class FXParticleSystemManager : public SubsystemInterface
{
public:
	virtual void init();
	virtual void reset();
	virtual void update();
};
FXParticleSystemManager *createFXParticleSystemManager();

extern FXParticleSystemManager *TheFXParticleSystemManager;

class FXListStore : public SubsystemInterface
{
public:
	FXListStore();
	virtual void init();
	virtual void reset();
	virtual void update();
private:
	char m_unported[20];		// retail sizeof = 28
};

extern FXListStore *TheFXListStore;

class WeaponStore : public SubsystemInterface
{
public:
	WeaponStore();
	virtual void init();
	virtual void reset();
	virtual void update();
private:
	char m_unported[12];		// retail sizeof = 20
};

extern WeaponStore *TheWeaponStore;

class ObjectCreationListStore : public SubsystemInterface
{
public:
	ObjectCreationListStore();
	virtual void init();
	virtual void reset();
	virtual void update();
private:
	char m_unported[24];		// retail sizeof = 32
};

extern ObjectCreationListStore *TheObjectCreationListStore;

class LocomotorStore : public SubsystemInterface
{
public:
	LocomotorStore();
	virtual void init();
	virtual void reset();
	virtual void update();
private:
	char m_unported[12];		// retail sizeof = 20
};

extern LocomotorStore *TheLocomotorStore;

class SpecialPowerStore : public SubsystemInterface
{
public:
	SpecialPowerStore();
	virtual void init();
	virtual void reset();
	virtual void update();
private:
	char m_unported[16];		// retail sizeof = 24
};

extern SpecialPowerStore *TheSpecialPowerStore;

class DamageFXStore : public SubsystemInterface
{
public:
	DamageFXStore();
	virtual void init();
	virtual void reset();
	virtual void update();
private:
	char m_unported[20];		// retail sizeof = 28
};

extern DamageFXStore *TheDamageFXStore;

class ArmorStore : public SubsystemInterface
{
public:
	ArmorStore();
	virtual void init();
	virtual void reset();
	virtual void update();
private:
	char m_unported[20];		// retail sizeof = 28
};

extern ArmorStore *TheArmorStore;

class BuildAssistant : public SubsystemInterface
{
public:
	BuildAssistant();
	virtual void init();
	virtual void reset();
	virtual void update();
private:
	char m_unported[12];		// retail sizeof = 20
};

extern BuildAssistant *TheBuildAssistant;

class EmotionSystem : public SubsystemInterface
{
public:
	EmotionSystem();
	virtual void init();
	virtual void reset();
	virtual void update();
private:
	char m_unported[24];		// retail sizeof = 32
};

extern EmotionSystem *TheEmotionSystem;

class ThingFactory : public SubsystemInterface
{
public:
	virtual void init();
	virtual void reset();
	virtual void update();
};
ThingFactory *createThingFactory();

extern ThingFactory *TheThingFactory;

class LightPointSystem : public SubsystemInterface
{
public:
	LightPointSystem();
	virtual void init();
	virtual void reset();
	virtual void update();
private:
	char m_unported[12];		// retail sizeof = 20
};

extern LightPointSystem *TheLightPointSystem;

class ExperienceLevelSystem : public SubsystemInterface
{
public:
	ExperienceLevelSystem();
	virtual void init();
	virtual void reset();
	virtual void update();
private:
	char m_unported[40];		// retail sizeof = 48
};

extern ExperienceLevelSystem *TheExperienceLevelSystem;

class AptPlayer : public SubsystemInterface
{
public:
	virtual void init();
	virtual void reset();
	virtual void update();
};
AptPlayer *createAptPlayer();

extern AptPlayer *TheAptPlayer;

class LivingWorldManager : public SubsystemInterface
{
public:
	LivingWorldManager();
	virtual void init();
	virtual void reset();
	virtual void update();
private:
	char m_unported[668];		// retail sizeof = 676
};

extern LivingWorldManager *TheLivingWorldManager;

class GameClient : public SubsystemInterface
{
public:
	virtual void init();
	virtual void reset();
	virtual void update();
};
GameClient *createGameClient();

extern GameClient *TheGameClient;

class AI : public SubsystemInterface
{
public:
	AI();
	virtual void init();
	virtual void reset();
	virtual void update();
private:
	char m_unported[24];		// retail sizeof = 32
};

extern AI *TheAI;

class AerialPathfinder : public SubsystemInterface
{
public:
	AerialPathfinder();
	virtual void init();
	virtual void reset();
	virtual void update();
private:
	char m_unported[8];		// retail sizeof = 16
};

extern AerialPathfinder *TheAerialPathfinder;

class LivingWorldLogic : public SubsystemInterface
{
public:
	LivingWorldLogic();
	virtual void init();
	virtual void reset();
	virtual void update();
private:
	char m_unported[212];		// retail sizeof = 220
};

extern LivingWorldLogic *TheLivingWorldLogic;

class SplineService : public SubsystemInterface
{
public:
	// no ctor of its own; retail calls SubsystemInterface::SubsystemInterface
	virtual void init();
	virtual void reset();
	virtual void update();
};

extern SplineService *TheSplineService;

class AttributeModifierStore : public SubsystemInterface
{
public:
	// no ctor of its own; retail calls SubsystemInterface::SubsystemInterface
	virtual void init();
	virtual void reset();
	virtual void update();
private:
	char m_unported[12];		// retail sizeof = 20
};

extern AttributeModifierStore *TheAttributeModifierStore;

class TaintManager : public SubsystemInterface
{
public:
	TaintManager();
	virtual void init();
	virtual void reset();
	virtual void update();
private:
	char m_unported[8];		// retail sizeof = 16
};

extern TaintManager *TheTaintManager;

class ScriptEngine : public SubsystemInterface
{
public:
	ScriptEngine();
	virtual void init();
	virtual void reset();
	virtual void update();
private:
	char m_unported[95832];		// retail sizeof = 95840
};

extern ScriptEngine *TheScriptEngine;

class LuaScriptEngine : public SubsystemInterface
{
public:
	LuaScriptEngine();
	virtual void init();
	virtual void reset();
	virtual void update();
private:
	char m_unported[180];		// retail sizeof = 188
};

extern LuaScriptEngine *TheLuaScriptEngine;

class TeamFactory : public SubsystemInterface
{
public:
	TeamFactory();
	virtual void init();
	virtual void reset();
	virtual void update();
private:
	char m_unported[24];		// retail sizeof = 32
};

extern TeamFactory *TheTeamFactory;

class CrateSystem : public SubsystemInterface
{
public:
	CrateSystem();
	virtual void init();
	virtual void reset();
	virtual void update();
private:
	char m_unported[12];		// retail sizeof = 20
};

extern CrateSystem *TheCrateSystem;

class PlayerList : public SubsystemInterface
{
public:
	PlayerList();
	virtual void init();
	virtual void reset();
	virtual void update();
private:
	char m_unported[140];		// retail sizeof = 148
};

extern PlayerList *ThePlayerList;

class GameLogic : public SubsystemInterface
{
public:
	virtual void init();
	virtual void reset();
	virtual void update();
};
GameLogic *createGameLogic();

extern GameLogic *TheGameLogic;

class Recorder : public SubsystemInterface
{
public:
	virtual void init();
	virtual void reset();
	virtual void update();
};
Recorder *createRecorder();

extern Recorder *TheRecorder;

class Radar : public SubsystemInterface
{
public:
	virtual void init();
	virtual void reset();
	virtual void update();
};
Radar *createRadar();

extern Radar *TheRadar;

class VictoryConditions : public SubsystemInterface
{
public:
	virtual void init();
	virtual void reset();
	virtual void update();
};
VictoryConditions *createVictoryConditions();

extern VictoryConditions *TheVictoryConditions;

class MetaMap : public SubsystemInterface
{
public:
	MetaMap();
	virtual void init();
	virtual void reset();
	virtual void update();
private:
	char m_unported[4];		// retail sizeof = 12
};

extern MetaMap *TheMetaMap;

class HouseColorSystem : public SubsystemInterface
{
public:
	// no ctor of its own; retail calls SubsystemInterface::SubsystemInterface
	virtual void init();
	virtual void reset();
	virtual void update();
private:
	char m_unported[8];		// retail sizeof = 16
};

extern HouseColorSystem *TheHouseColorSystem;

class LivingWorldCampaignManager : public SubsystemInterface
{
public:
	LivingWorldCampaignManager();
	virtual void init();
	virtual void reset();
	virtual void update();
private:
	char m_unported[36];		// retail sizeof = 44
};

extern LivingWorldCampaignManager *TheLivingWorldCampaignManager;

class VictorySystem : public SubsystemInterface
{
public:
	VictorySystem();
	virtual void init();
	virtual void reset();
	virtual void update();
private:
	char m_unported[260];		// retail sizeof = 268
};

extern VictorySystem *TheVictorySystem;

class ActionManager : public SubsystemInterface
{
public:
	ActionManager();
	virtual void init();
	virtual void reset();
	virtual void update();
};

extern ActionManager *TheActionManager;

class GameStateMap : public SubsystemInterface
{
public:
	GameStateMap();
	virtual void init();
	virtual void reset();
	virtual void update();
private:
	char m_unported[4];		// retail sizeof = 12
};

extern GameStateMap *TheGameStateMap;

class GameState : public SubsystemInterface
{
public:
	GameState();
	virtual void init();
	virtual void reset();
	virtual void update();
private:
	char m_unported[80];		// retail sizeof = 88
};

extern GameState *TheGameState;

class GameResultsQueue : public SubsystemInterface
{
public:
	virtual void init();
	virtual void reset();
	virtual void update();
};
GameResultsQueue *createGameResultsQueue();

extern GameResultsQueue *TheGameResultsQueue;

