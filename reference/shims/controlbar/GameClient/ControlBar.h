// TU-scoped BFME ControlBar layout shim.
//
// The ZH reference ControlBar.h (which BFME's ControlBar.cpp TU still uses,
// unshimmed) mismatches retail's true field offsets: BFME dropped/changed a
// swath of ZH-only fields (purchase-science UI, upgrade cameo rows, etc.)
// that don't exist in this LOTR-era build. Full reconstruction of that
// interior layout has not been done yet. Only the boundaries proven so far
// (each from a retail accessor body's disassembly) are represented, via
// padding blobs between them:
//
//   m_specialPowerShortcutButtons[10] @ this+0xCC (retail RVA 0x4A07D0,
//     ControlBar::showSpecialPowerShortcut: `lea ebx,[esi+0xCC]` array base,
//     4-byte stride confirmed by the loop's `add ebx,4`; element count from
//     the proven 0xCC..0xF4 gap (0x28 bytes / 4 = 10) — not independently
//     confirmed, just the only size consistent with both boundaries)
//   m_currentlyUsedSpecialPowersButtons @ this+0xF4 (same body:
//     `mov eax,[esi+0xF4]` loop bound)
//   m_specialPowerShortcutParent @ this+0xFC (retail RVA 0x49D4A0,
//     ControlBar::hideSpecialPowerShortcut: `mov ecx,[ecx+0xFC]`; also read
//     at +0xFC in showSpecialPowerShortcut)
//   m_commandButtons @ this+0x2c (retail RVA 0x4A0270,
//     ControlBar::findNonConstCommandButton: `mov eax,[ecx+0x2c]`; ZH header
//     has it at this+0x28)
//
// showSpecialPowerShortcut itself does NOT verify yet with this layout: its
// body also calls TheScriptEngine->isGameEnding() (retail reads the field at
// TheScriptEngine+0x17080; the current ScriptEngine reference header puts it
// at +0x10AA4 — ScriptEngine has its own BFME layout drift, out of this
// track) and Player::hasAnyShortcutSpecialPower() (retail's caller does a
// 32-bit `test eax,eax` on the result; the reference Player.h declares it
// returning `Bool`/bool, which compiles to an 8-bit `test al,al` here — the
// real BFME declaration is evidently a wider return type). Both are
// out-of-track class drifts; only land showSpecialPowerShortcut once they
// are separately fixed. Retail's body also omits the ZH source's
// `&& !hasAnyShortcutSelection()` clause entirely — don't port that back in.
//
// findNonConstCommandButton itself (the body that proves m_commandButtons)
// does NOT byte-verify: it's 8 bytes short of retail's 126B body in two
// register-allocation/CSE spots no source rewrite reproduced. See the
// present-unmatched block above its definition in ControlBarFields.cpp and
// reverse/re_attempts.log before re-attempting.
//
// This header intentionally declares nothing else — it exists only for the
// small set of ControlBar member functions ported into ControlBarFields.cpp
// that touch fields at or before this proven boundary. Do NOT #include this
// from ControlBar.cpp itself: that TU has 40+ already-matched functions
// compiled against the (also wrong, but load-bearing) ZH header layout for
// fields before this boundary, and swapping headers there would need the
// full interior reconstructed first.

#pragma once

#ifndef __CONTROLBAR_H_
#define __CONTROLBAR_H_

#include "Common/SubsystemInterface.h"
#include "Common/AsciiString.h"

class GameWindow;

// StringBase<char>::Header layout mirrored here (see
// Code/Libraries/Source/WWVegas/WWLib/string_base.h) so findNonConstCommandButton
// can reproduce retail's inlined length-prefixed compare: the retail body (RVA
// 0x4A0270) reads a CommandButton's name header directly ([ecx+0xc], length at
// +0x4, char data at +0x8) and never calls AsciiString::compare()/operator==
// (both real out-of-line functions elsewhere in this codebase, matched from
// __declspec(naked) bodies in string_base.cpp) -- there is no CALL instruction
// in the whole 126B body for the comparison itself. AsciiString's only member
// (ascii_string.h's m_text) is that same Header* despite the name.
struct BFMEStringHeader
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
	char data[1];
};

// CommandButton's leading fields, reconstructed only as far as
// findNonConstCommandButton's retail body (RVA 0x4A0270) proves them:
//   m_name @ this+0xc  -- matches what ZH's declared inheritance
//     (Overridable : MemoryPoolObject, vtable + m_nextOverride + m_isOverride
//     = 0xc bytes with this codebase's 4-byte Bool) would already put there;
//     no drift before m_name.
//   m_next @ this+0x60 -- ZH has it at +0x14 right after m_name/m_command;
//     BFME's interior grew by 0x4C bytes of LOTR-only fields between them
//     (unreconstructed; same kind of drift as ControlBar's own interior).
class CommandButton
{

public:

	const AsciiString &getName( void ) const { return m_name; }
	CommandButton *friend_getNext( void ) { return m_next; }
	const CommandButton *getNext( void ) const { return m_next; }

private:

	unsigned char m_unreconstructed_00[0xc];					///< vtable + Overridable (unchanged from ZH)

	AsciiString m_name;										///< retail this+0xc

	unsigned char m_unreconstructed_10[0x60 - 0xc - sizeof(AsciiString)];	///< unreconstructed BFME-only interior

	CommandButton *m_next;										///< retail this+0x60

};

//-------------------------------------------------------------------------------------------------
class ControlBar : public SubsystemInterface
{

public:

	ControlBar( void );
	virtual ~ControlBar( void );

	void hideSpecialPowerShortcut( void );

protected:

	CommandButton *findNonConstCommandButton( const AsciiString &name );	///< IAE-mangled (protected) to match ZH's access level

private:

	// Unreconstructed interior: SubsystemInterface's vtable ptr + AsciiString
	// m_name (8 bytes total, sizeof(SubsystemInterface)) plus not-yet-pinned
	// ControlBar fields, padded so the next proven field lands at its real
	// offset. Do not read individual bytes out of this blob.
	unsigned char m_unreconstructed_08[0x2c - sizeof(SubsystemInterface)];

	CommandButton *m_commandButtons;							///< retail this+0x2c (ZH header has this+0x28; ControlBar::findNonConstCommandButton RVA 0x4A0270: `mov eax,[ecx+0x2c]`)

	unsigned char m_unreconstructed_30[0xCC - 0x2c - 4];

	GameWindow *m_specialPowerShortcutButtons[10];			///< retail this+0xCC (ZH header has this+0x1A0, MAX_SPECIAL_POWER_SHORTCUTS=11 there); array fills the whole 0xCC..0xF4 gap, no padding needed

	int m_currentlyUsedSpecialPowersButtons;				///< retail this+0xF4

	unsigned char m_unreconstructed_F8[0xFC - 0xF4 - sizeof(int)];	///< ZH has m_specialPowerLayout (WindowLayout*) here; not touched by any function ported so far

	GameWindow *m_specialPowerShortcutParent;			///< retail this+0xFC (ZH header has this+0x184)

};

#endif // __CONTROLBAR_H_
