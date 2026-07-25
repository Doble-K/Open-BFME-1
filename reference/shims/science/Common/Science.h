/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

////////////////////////////////////////////////////////////////////////////////
//																																						//
//  (c) 2001-2003 Electronic Arts Inc.																				//
//																																						//
////////////////////////////////////////////////////////////////////////////////

// FILE: Science.h ////////////////////////////////////////////////////////////////////////////////
// Author: Steven Johnson, Colin Day November 2001
// Desc:   Science descriptoins
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef __SCIENCE_H_
#define __SCIENCE_H_

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////
#include "Common/Overridable.h"
#include "Common/NameKeyGenerator.h"
#include "Common/UnicodeString.h"

class Player;

//-------------------------------------------------------------------------------------------------
enum ScienceType
{
	SCIENCE_INVALID = -1
};

//-------------------------------------------------------------------------------------------------
typedef std::vector<ScienceType> ScienceVec;

//-------------------------------------------------------------------------------------------------
class ScienceInfo : public Overridable
{
	MEMORY_POOL_GLUE_WITH_USERLOOKUP_CREATE( ScienceInfo, "ScienceInfo"  )

	friend class ScienceStore;

private:
	// BFME layout drift (proven from retail lotrbfme.exe against the ZH reference):
	// isScienceGrantable@0xE6DE0 reads m_grantable at [this+0x2c], and
	// playerHasPrereqsForScience@0xE6E50 reads m_prereqSciences begin/end at
	// [this+0x18]/[this+0x1c] (this header's natural, unmodified-order offsets
	// are 0x34 for m_grantable and 0x24 for m_prereqSciences, both proven via
	// an offsetof-equivalent probe: compiling isScienceGrantable unmodified
	// emits offset 0x34, 8 bytes past retail's 0x2c). Retail's
	// getSciencePurchaseCost@0xE6D70 additionally branches on TheGlobalData
	// to pick between [this+0x24] and [this+0x28] before m_grantable@0x2c -
	// i.e. BFME added a second Int-sized cost field between
	// m_sciencePurchasePointCost and m_grantable (semantics unresolved; not
	// needed by the two functions this shim exists to unblock). Net effect:
	// m_prereqSciences moved immediately after m_description (ahead of
	// m_rootSciences), and one opaque Int was inserted before m_grantable.
	// m_rootSciences is moved to the tail: nothing in this TU's *matched*
	// functions reads it by offset, only by name (addRootSciences,
	// friend_getScienceNames, playerHasRootPrereqsForScience - all still
	// present-unmatched), so its exact retail position remains unresolved.
	ScienceType						m_science;
	UnicodeString					m_name;
	UnicodeString					m_description;
	ScienceVec						m_prereqSciences;
	Int										m_sciencePurchasePointCost;
	Int										_bfme_unknownCost28;	///< @0x28 unresolved BFME-only field; getSciencePurchaseCost branches between this and m_sciencePurchasePointCost
	Bool									m_grantable;
	ScienceVec						m_rootSciences;			// this is calced at runtime, NOT read from INI; BFME position unresolved, kept at tail

	ScienceInfo() :
		m_science(SCIENCE_INVALID),
		m_sciencePurchasePointCost(0),	// 0 means "cannot be purchased"
		_bfme_unknownCost28(0),
		m_grantable(true)
	{
	}

	void addRootSciences(ScienceVec& v) const;
};
EMPTY_DTOR(ScienceInfo);

//-------------------------------------------------------------------------------------------------
class ScienceStore : public SubsystemInterface
{
	friend class ScienceInfo;

public:
	virtual ~ScienceStore();

	void init();
	void reset();
	void update() { }

	Bool isValidScience(ScienceType st) const;

	Bool isScienceGrantable(ScienceType st) const;

	Bool getNameAndDescription(ScienceType st, UnicodeString& name, UnicodeString& description) const;

	Bool playerHasPrereqsForScience(const Player* player, ScienceType st) const;

	/**
		this is a subtle call, and should ALMOST NEVER be called by external code...
		this is used to determine if you have the "root" requirements for a given science,
		and thus could *potentially* obtain it if you got extra prereqs.

		Generally, you should call getPurchasableSciences() instead of this!
	*/
	Bool playerHasRootPrereqsForScience(const Player* player, ScienceType st) const;

	Int getSciencePurchaseCost(ScienceType science) const;

	ScienceType getScienceFromInternalName(const AsciiString& name) const;
	AsciiString getInternalNameForScience(ScienceType science) const;

	/** return a list of the sciences the given player can purchase now, and a list he might be able to purchase in the future,
		but currently lacks prereqs or points for. (either might be an empty list) */
	void getPurchasableSciences(const Player* player, ScienceVec& purchasable, ScienceVec& potentiallyPurchasable) const;

	// this is intended ONLY for use by INI::scanScience.
	// Don't use it anywhere else. In particular, never, ever, ever
	// call this with a hardcoded science name. (srj)
	ScienceType friend_lookupScience(const char* scienceName) const;
	static void friend_parseScienceDefinition(INI* ini);

	// return a vector of all the currently-known science names
	// NOTE: this is really only for use by WorldBuilder! Please
	// do not use it in RTS!
	std::vector<AsciiString> friend_getScienceNames() const;


private:

	const ScienceInfo* findScienceInfo(ScienceType st) const;

	typedef std::vector<ScienceInfo*> ScienceInfoVec;
	ScienceInfoVec m_sciences;
};

extern ScienceStore* TheScienceStore;


#endif // __SCIENCE_H_
