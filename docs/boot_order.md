# BFME 1.03 engine boot order

Read straight out of `GameEngine::init` at 0x00079060. This is the order the engine brings
its subsystems up in, so it is also the order a mod's overrides take
effect in: anything parsed later wins.

Two things worth knowing before reading it.

Zero Hour hands each subsystem its INI files through `initSubsystem`'s
three trailing `const char *` arguments. BFME passes NULL for all three
at all 60 sites and calls `INI::load` separately instead, so the loads
below are their own statements sitting between the registrations, not
properties of the subsystem above them.

Only 5 INI files are loaded here. Every other INI in the game is loaded
later, by the subsystem's own `init()` -- `Eva::init` reaches for
`Data\INI\Eva.ini` itself, for instance. So this is the boot order, not
the full INI load order.

| # | step | detail |
|--:|:--|:--|
| 1 | `initSubsystem` | **TheSubsystemLegend** |
| 2 | `INI::load` | `Data\INI\Default\SubsystemLegend.ini` — INI_LOAD_OVERWRITE |
| 3 | `initSubsystem` | **TheWritableGlobalData** |
| 4 | `INI::load` | `Data\INI\Default\Water.ini` — INI_LOAD_OVERWRITE |
| 5 | `INI::load` | `Data\INI\Water.ini` — INI_LOAD_OVERWRITE |
| 6 | `INI::load` | `Data\INI\Default\Environment.ini` — INI_LOAD_OVERWRITE |
| 7 | `INI::load` | `Data\INI\Environment.ini` — INI_LOAD_OVERWRITE |
| 8 | `initSubsystem` | **TheGlobalLanguageData** |
| 9 | `initSubsystem` | **TheGameText** |
| 10 | `initSubsystem` | **TheAudio** |
| 11 | `initSubsystem` | **TheEva** |
| 12 | `initSubsystem` | **TheScienceStore** |
| 13 | `initSubsystem` | **TheUpgradeCenter** |
| 14 | `initSubsystem` | **TheMultiplayerSettings** |
| 15 | `initSubsystem` | **TheTerrainTypes** |
| 16 | `initSubsystem` | **TheTerrainRoads** |
| 17 | `initSubsystem` | **TheCDManager** |
| 18 | `initSubsystem` | **TheGlobalWeatherSystem** |
| 19 | `initSubsystem` | **TheFunctionLexicon** |
| 20 | `initSubsystem` | **TheModuleFactory** |
| 21 | `initSubsystem` | **TheMessageStream** |
| 22 | `initSubsystem` | **TheSidesList** |
| 23 | `initSubsystem` | **TheCaveSystem** |
| 24 | `initSubsystem` | **TheRankInfoStore** |
| 25 | `initSubsystem` | **ThePlayerAITypeSet** |
| 26 | `initSubsystem` | **ThePlayerTemplateStore** |
| 27 | `initSubsystem` | **TheFXParticleSystemManager** |
| 28 | `initSubsystem` | **TheFXListStore** |
| 29 | `initSubsystem` | **TheWeaponStore** |
| 30 | `initSubsystem` | **TheObjectCreationListStore** |
| 31 | `initSubsystem` | **TheLocomotorStore** |
| 32 | `initSubsystem` | **TheSpecialPowerStore** |
| 33 | `initSubsystem` | **TheDamageFXStore** |
| 34 | `initSubsystem` | **TheArmorStore** |
| 35 | `initSubsystem` | **TheBuildAssistant** |
| 36 | `initSubsystem` | **TheEmotionSystem** |
| 37 | `initSubsystem` | **TheThingFactory** |
| 38 | `initSubsystem` | **TheLightPointSystem** |
| 39 | `initSubsystem` | **TheExperienceLevelSystem** |
| 40 | `initSubsystem` | **TheAptPlayer** |
| 41 | `initSubsystem` | **TheLivingWorldManager** |
| 42 | `initSubsystem` | **TheGameClient** |
| 43 | `initSubsystem` | **TheAI** |
| 44 | `initSubsystem` | **TheAerialPathfinder** |
| 45 | `initSubsystem` | **TheLivingWorldLogic** |
| 46 | `initSubsystem` | **TheSplineService** |
| 47 | `initSubsystem` | **TheAttributeModifierStore** |
| 48 | `initSubsystem` | **TheTaintManager** |
| 49 | `initSubsystem` | **TheScriptEngine** |
| 50 | `initSubsystem` | **TheLuaScriptEngine** |
| 51 | `initSubsystem` | **TheTeamFactory** |
| 52 | `initSubsystem` | **TheCrateSystem** |
| 53 | `initSubsystem` | **ThePlayerList** |
| 54 | `initSubsystem` | **TheGameLogic** |
| 55 | `initSubsystem` | **TheRecorder** |
| 56 | `initSubsystem` | **TheRadar** |
| 57 | `initSubsystem` | **TheVictoryConditions** |
| 58 | `initSubsystem` | **TheMetaMap** |
| 59 | `initSubsystem` | **TheHouseColorSystem** |
| 60 | `initSubsystem` | **TheLivingWorldCampaignManager** |
| 61 | `initSubsystem` | **TheVictorySystem** |
| 62 | `initSubsystem` | **TheActionManager** |
| 63 | `initSubsystem` | **TheGameStateMap** |
| 64 | `initSubsystem` | **TheGameState** |
| 65 | `initSubsystem` | **TheGameResultsQueue** |
