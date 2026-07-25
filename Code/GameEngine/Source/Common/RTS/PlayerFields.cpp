// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /DZH_EMIT_POOL_GLUE /Ireference/shims/player /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it
//
// Player radar-cluster field accessors, byte-matched against the reconstructed
// BFME Player layout (reference/shims/player/Common/Player.h). disableRadar
// (retail 0xCC1C0, behind thunk 0x3C2BD) reads m_radarDisabled at [this+0x60],
// m_disableProofRadarCount at [this+0x5c] and m_radarCount at [this+0x58] --
// this header's natural (ZH-derived) layout puts them at 0x4c/0x48/0x44, a
// uniform +0x14 (5 dwords) inserted somewhere between m_playerIndex (proven
// UNSHIFTED at [this+0x24] via the matched getPlayerMask@Player) and
// m_radarCount. See the shim header for the full offset writeup.
//
// hasRadar's own standalone body (0xC9A80, immediately after
// okToPlayRadarEdgeSound's body at 0xC9A20 in the same retail compiland) is a
// pure field read with no external calls, so it lands cleanly. disableRadar/
// enableRadar/addRadar/removeRadar all ALSO call through TheAudio->
// getMiscAudio(), which retail dispatches virtually ([vtbl+0x124]) while the
// current (unshimmed) AudioManager header still declares it as a plain
// non-virtual member -- an AudioManager-side vtable drift outside this
// track's scope (Player-side field reads were proven byte-identical up to
// that point; see reverse/re_attempts.log). Left unconverted rather than
// landed with an unresolved call.
//
// This lives here rather than in Common/RTS/Player.cpp because that TU
// resolves Common/Player.h to the ZH-layout reference header (m_radarDisabled
// @0x4c); the private /Ireference/shims/player above makes only this TU see
// the true BFME offsets, so converting this leaf does not disturb Player.cpp
// (83 matches).
#include "PreRTS.h"
#include "Common/Player.h"

// ?hasRadar@Player@@QBE_NXZ
Bool Player::hasRadar() const
{
	if( m_radarDisabled  && (m_disableProofRadarCount == 0) )
		return FALSE;// Nope, no matter how many you have, if I say no, you don't have it

	// Otherwise, check if I actually do have it.
	return m_radarCount > 0;
}
