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
