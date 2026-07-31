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
//     TheGlobalWeatherSystem, TheCaveSystem, ThePlayerTemplateStore,
//     TheFXListStore -- have their own ctor, but it is unclaimed, so the name is
//     not established yet. These become landable the day those ctors are named.
//
// The stubs are abstract on purpose: initSubsystem<T> only forms a T* and
// converts it to SubsystemInterface*, so it never instantiates T.
class UpgradeCenter            : public SubsystemInterface {};   // TheUpgradeCenter,           ctor 0x0010A6A0
class TerrainRoadCollection    : public SubsystemInterface {};   // TheTerrainRoads,            ctor 0x00601430
class SidesList                : public SubsystemInterface {};   // TheSidesList,               ctor 0x0019EA80
class WeaponStore              : public SubsystemInterface {};   // TheWeaponStore,             ctor 0x001E5290
class ObjectCreationListStore  : public SubsystemInterface {};   // TheObjectCreationListStore, ctor 0x001DAD50
