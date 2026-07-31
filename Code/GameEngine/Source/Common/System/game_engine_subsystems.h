#pragma once
#include "subsystem_interface.h"

// The subsystems GameEngine::init (0x00079060) registers through initSubsystem<T>.
//
// Only classes whose NAME is proven from the binary appear here. The proof is the
// constructor at each registration site: init news the object and calls its ctor,
// and for these five that ctor already carries a decorated name in the ledger, so
// the template instantiation's own mangled name follows from it. Byte-verifying
// the instantiation does NOT prove the name -- a stub emits identical code
// whatever it is called -- which is exactly why the unproven ones are absent.
//
// Deliberately NOT listed, and why:
//   TheScienceStore / TheRankInfoStore / ThePlayerAITypeSet -- their registration
//     calls ??0SubsystemInterface@@QAE@XZ directly, i.e. no class-specific ctor
//     is emitted, so nothing in the binary names them.
//   TheTerrainTypes -- its ctor address resolves to ??0W3DPropDrawModuleData@@,
//     an ICF-folded trivial ctor shared with an unrelated class. Not evidence.
//   TheGameText / TheAudio / TheCDManager / TheFunctionLexicon / TheModuleFactory /
//     TheMessageStream / TheFXParticleSystemManager -- built by a factory call
//     rather than new+ctor, so there is no ctor to read a name from.
//   TheWritableGlobalData, TheGlobalLanguageData, TheMultiplayerSettings,
//     TheGlobalWeatherSystem, TheFXListStore -- have their own ctor, but it is
//     unclaimed and their vtables contain no class-specific named slot, so
//     nothing names them yet.
//   TheCaveSystem -- its ctor sits between ?getTunnelTrackerForCaveIndex@CaveSystem@@
//     and ?registerNewCave@CaveSystem@@ in the same TU, which is suggestive but
//     is only TU locality; its vtable slots are all unclaimed. Left out until
//     something binds the ctor to the class directly.
//
// The stubs are abstract on purpose: initSubsystem<T> only forms a T* and
// converts it to SubsystemInterface*, so it never instantiates T.
class UpgradeCenter            : public SubsystemInterface {};   // TheUpgradeCenter,           ctor 0x0010A6A0
class TerrainRoadCollection    : public SubsystemInterface {};   // TheTerrainRoads,            ctor 0x00601430
class SidesList                : public SubsystemInterface {};   // TheSidesList,               ctor 0x0019EA80
class WeaponStore              : public SubsystemInterface {};   // TheWeaponStore,             ctor 0x001E5290
class ObjectCreationListStore  : public SubsystemInterface {};   // TheObjectCreationListStore, ctor 0x001DAD50
// ThePlayerTemplateStore, ctor 0x000E3F50: proven by the vtable that ctor installs
// (0x01084BA0), whose slot 1 is ?init@PlayerTemplateStore@@UAEXXZ -- a
// class-specific virtual. Slot 0 is an ICF-folded ??_GFileSystem@@ and is NOT
// evidence; slot 1 is.
class PlayerTemplateStore : public SubsystemInterface {};
// TheArmorStore, ctor at its registration site: the class name is proven the
// strongest way available -- Code/GameEngine/Source/GameLogic/Object/Armor.cpp
// owns a byte-verified ?findArmorTemplate@ArmorStore@@ row, so the name is not
// an inference at all.
//
// Note these declarations are deliberately minimal and are NOT the ported class.
// initSubsystem<T> only forms a T* and converts it to SubsystemInterface*, so
// all it needs is the name and the base; the real ArmorStore, with its
// hash_map of templates, lives in Armor.cpp against the ZH header tree. They are
// separate on purpose -- this header is the registration manifest, not a port.
class ArmorStore : public SubsystemInterface {};

// Proven the same two ways as the entries above -- a ctor already decorated with
// the class name, or a class-specific virtual in the vtable that ctor installs.
class DamageFXStore : public SubsystemInterface {};	// 0x00074210, ctor ??0DamageFXStore@@QAE@XZ
class AI : public SubsystemInterface {};	// 0x00074990, vtable slot 3 = ?crc@AI@@UAEXPAVXfer@@@Z
class TeamFactory : public SubsystemInterface {};	// 0x00074F90, ctor ??0TeamFactory@@QAE@XZ
class CrateSystem : public SubsystemInterface {};	// 0x00075050, ctor ??0CrateSystem@@QAE@XZ
class PlayerList : public SubsystemInterface {};	// 0x00075110, ctor ??0PlayerList@@QAE@XZ
class GameState : public SubsystemInterface {};	// 0x00075960, ctor ??0GameState@@QAE@XZ

// The next block is named a third way, which needed no new byte-matching at all.
// initSubsystem<T> takes its subsystem by REFERENCE -- T*& -- so the pointer the
// registration site passes as the first argument has to be declared exactly T*;
// a reference will not bind through a conversion. Each site in GameEngine::init
// pushes the address of one global, those addresses are already proven by the
// DIR32 relocations of matched functions that read the same globals, and the
// global's own declared type is therefore the template argument.
//
// The method self-checks: of the 14 registrations already claimed above, every
// one whose global resolves agrees with the name it was given, with no
// contradictions.
//
// Each class below additionally has at least one byte-verified ledger row
// carrying its decorated name, so the name is not resting on the global alone.
// Two candidates are deliberately absent -- TheGameText's GameTextInterface at
// 0x00073010 and TheGameClient's GameClient at 0x000748D0 -- because neither
// class appears in any ledger row, which would leave our own header as the only
// authority for the name.

class GlobalData : public SubsystemInterface {};	// 0x00072E90, TheWritableGlobalData; name from ?getPath_UserData@GlobalData@@QBE?AVAsciiString@@XZ
class AudioManager : public SubsystemInterface {};	// 0x000730D0, TheAudio; name from ?releaseAudioEventRTS@AudioManager@@UAEXPAVAudioEven
class MultiplayerSettings : public SubsystemInterface {};	// 0x000733D0, TheMultiplayerSettings; name from ?getColor@MultiplayerSettings@@QAEPAVMultiplayerColo
class FunctionLexicon : public SubsystemInterface {};	// 0x00073790, TheFunctionLexicon; name from ?gameWinDrawFunc@FunctionLexicon@@QAEP6AXPAVGameWind
class MessageStream : public SubsystemInterface {};	// 0x00073910, TheMessageStream; name from ??0TranslatorData@MessageStream@@QAE@XZ
class ParticleSystemManager : public SubsystemInterface {};	// 0x00073D90, TheParticleSystemManager; name from ?findTemplate@ParticleSystemManager@@QBEPAVParticleS
class FXListStore : public SubsystemInterface {};	// 0x00073E50, TheFXListStore; name from ?findFXList@FXListStore@@QBEPBVFXList@@PBD@Z
class LocomotorStore : public SubsystemInterface {};	// 0x00074090, TheLocomotorStore; name from ?findLocomotorTemplate@LocomotorStore@@QAEPAVLocomot
class SpecialPowerStore : public SubsystemInterface {};	// 0x00074150, TheSpecialPowerStore; name from ?findSpecialPowerTemplateByID@SpecialPowerStore@@QAE
class ThingFactory : public SubsystemInterface {};	// 0x00074510, TheThingFactory; name from ?findByTemplateID@ThingFactory@@QAEPBVThingTemplate@
class ScriptEngine : public SubsystemInterface {};	// 0x00074E10, TheScriptEngine; name from ?doFreezeTime@ScriptEngine@@QAEXXZ
class GameLogic : public SubsystemInterface {};	// 0x000751D0, TheGameLogic; name from ?createGhostObjectManager@GameLogic@@EAEPAVGhostObje
class RecorderClass : public SubsystemInterface {};	// 0x00075290, TheRecorder; name from ?appendNextCommand@RecorderClass@@IAEXXZ
// TheRadar / Radar at 0x00075350 is left out: the global names it the same way,
// but its body is 167 bytes where every other instantiation is 154, so the
// T*-to-SubsystemInterface* conversion there is not the trivial one a
// single-inheritance stub emits. Whatever Radar really derives from has to be
// recovered before the instantiation can be reproduced.
class ActionManager : public SubsystemInterface {};	// 0x000757E0, TheActionManager; name from ?canOverrideSpecialPowerDestination@ActionManager@@Q
