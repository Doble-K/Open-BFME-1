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

// Object.h ///////////////////////////////////////////////////////////////////
// Reconstructed BFME (lotrbfme.exe 1.03) Object layout.
//
// This is NOT the ZH Object.h: it is an opaque-padded skeleton that reproduces
// only the field offsets proven from retail accessor bodies, so leaf Object
// members can be byte-matched without disturbing the ~100 rows that compile
// against reference/shims/sweep/GameLogic/Object.h (ZH layout).
//
// Proven retail offsets:
//   0x074 m_id                 setProducer 0x1BE450  mov eax,[eax+0x74]
//   0x078 m_producerID         setProducer 0x1BE450  mov [ecx+0x78],eax
//   0x07c m_builderID          setBuilder  0x1BE470  mov [ecx+0x7c],eax
//   0x080 m_drawable           setDisabledUntil 0x1C81C0  mov eax,[edi+0x80]
//   0x084 m_name               getName     0x05CBA0  lea eax,[ecx+0x84]
//   0x088 m_next / 0x08c m_prev            isInList 0x1BEB40
//   0x090 m_status (2 dwords)  getStatusBits 0x3C6F80
//   0x0a8 m_geometryInfo       (minorRadius read at this+0xbc)
//   0x1a4 m_disabledMask       setDisabledUntil  lea ebp,[edi+0x1a4]
//   0x1a8 m_disabledTillFrame[11]           mov [edi+esi*4+0x1a8],ebx
//   0x1f0 m_behaviors          findSpecialPowerWithOverridableDestinationActive 0x1BF6F0
//   0x204 m_ai                 isUsingAirborneLocomotor 0x1C1770
//   0x224 m_objectUpgradesCompleted (6 dwords)  giveUpgrade 0x1C9F70
//   0x23c m_team               getControllingPlayer 0x1BE3F0
//   0x343 m_scriptStatus (Byte) setScriptStatus 0x1D01D0

#pragma once
#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "Lib/BaseType.h"

class AIUpdateInterface;
class BehaviorModule;
class ContainModuleInterface;
class DockUpdateInterface;
class ProductionUpdateInterface;
class PartitionData;
class SpecialPowerUpdateInterface;
class ThingTemplate;
class UpgradeTemplate;
class CountermeasuresBehaviorInterface;
class ProjectileUpdateInterface;

// BFME UpgradeMaskType is six 32-bit words, not ZH's four: removeUpgrade
// (0x1CA020) builds a 0x18-byte stack temp, and m_objectUpgradesCompleted@0x224
// is followed by m_team@0x23c (getControllingPlayer 0x1BE3F0).
class UpgradeMaskType
{
public:
	enum { NUM_WORDS = 6 };

	enum InitType { kInit };

	UpgradeMaskType() {}
	UpgradeMaskType( InitType, UnsignedInt i )
	{
		for (Int w = 0; w < NUM_WORDS; ++w)
			m_bits[w] = 0;
		m_bits[i >> 5] |= (1 << (i & 31));
	}

	UnsignedInt m_bits[NUM_WORDS];
};

enum SpecialPowerType;

// BFME DISABLED_COUNT is 11, not ZH's 13: setDisabledUntil (0x1C81C0) range-checks
// its type against 0xb, and setScriptStatus (0x1D01D0) passes 9 / 10 for the two
// script-driven types that are the last two entries of the ZH enum.
enum DisabledType
{
	DISABLED_SCRIPT_DISABLED			= 9,
	DISABLED_SCRIPT_UNDERPOWERED	= 10,

	DISABLED_COUNT								= 11,

	DISABLED_ANY									= 65535
};

enum ObjectScriptStatusBit
{
	OBJECT_STATUS_SCRIPT_DISABLED		= 0x01,
	OBJECT_STATUS_SCRIPT_UNPOWERED	= 0x02
};

// ---------------------------------------------------
class Object
{
public:

	SpecialPowerUpdateInterface* findSpecialPowerWithOverridableDestinationActive( SpecialPowerType type ) const;

	Bool isUsingAirborneLocomotor( void ) const;

	void setScriptStatus( ObjectScriptStatusBit bit, Bool set = true );

	void setDisabledUntil( DisabledType type, UnsignedInt frame );
	Bool clearDisabled( DisabledType type );
	void setDisabled( DisabledType type ) { setDisabledUntil( type, FOREVER ); }

	ContainModuleInterface* getContain( void ) const { return m_contain; }

	ProductionUpdateInterface* getProductionUpdateInterface( void );
	DockUpdateInterface* getDockUpdateInterface( void );
	ProjectileUpdateInterface* getProjectileUpdateInterface( void ) const;
	CountermeasuresBehaviorInterface* getCountermeasuresBehaviorInterface( void );
	const CountermeasuresBehaviorInterface* getCountermeasuresBehaviorInterface( void ) const;

	void giveUpgrade( const UpgradeTemplate *upgradeT );
	void removeUpgrade( const UpgradeTemplate *upgradeT );
	void updateUpgradeModules( void );

private:

	enum { FOREVER = 0x3fffffff };

	UnsignedByte							_bfme_vtbl[4];
	const ThingTemplate*			m_template;						///< 0x004 (Thing base)
	UnsignedByte							_bfme_pad_008[0x1e8];
	BehaviorModule**					m_behaviors;					///< 0x1f0
	UnsignedByte							_bfme_pad_1f4[8];
	ContainModuleInterface*		m_contain;						///< 0x1fc
	UnsignedByte							_bfme_pad_200[4];
	AIUpdateInterface*				m_ai;									///< 0x204
	UnsignedByte							_bfme_pad_208[0x1c];
	UpgradeMaskType						m_objectUpgradesCompleted;	///< 0x224
	UnsignedByte							_bfme_pad_23c[0x107];
	UnsignedByte							m_scriptStatus;				///< 0x343
	UnsignedByte							_bfme_pad_344[0x6c];
	PartitionData*						m_partitionData;			///< 0x3b0

};  // end class Object

#endif // _OBJECT_H_
