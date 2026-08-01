// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/ini /Ireference/shims/water /Ireference/shims/iniexception /Ireference/shims/ini_noinline /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it
#define __PLACEMENT_VEC_NEW_INLINE  // always.h/GameMemory.h define array placement-new themselves
// stlport
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

// FILE: INIWater.cpp /////////////////////////////////////////////////////////////////////////////
// Author: Colin Day, December 2001
// Desc:   Water settings 
///////////////////////////////////////////////////////////////////////////////////////////////////

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#define DEFINE_TIME_OF_DAY_NAMES

#include "Common/INI.h"
#include "Common/INIException.h"
#include "Common/GameType.h"

#include "GameClient/TerrainVisual.h"
#include "GameClient/Water.h"

///////////////////////////////////////////////////////////////////////////////////////////////////
// PUBLIC FUNCTIONS ///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------------------------------
/** Water setting, note that this does not support override situations.  As the water
	* system becomes more complex we may want to change this */
//-------------------------------------------------------------------------------------------------
void INI::parseWaterSettingDefinition( INI* ini )
{
	AsciiString name;
	WaterSetting *waterSetting = NULL;

	// read the name
	name = ini->getNextToken();

	// get the water setting we want to load based on name
	char **timeOfDayName = TimeOfDayNames;
	Int timeOfDayIndex = 0;  // TIME_OF_DAY_INVALID
	while( timeOfDayName && *timeOfDayName )
	{

		if( stricmp( *timeOfDayName, name.str() ) == 0 )
		{

			waterSetting = &WaterSettings[ timeOfDayIndex ];
			break;

		}  // end if

		// next name
		timeOfDayName++;
		timeOfDayIndex++;

	}  // end while

	// check for no time of day match
	if( waterSetting == NULL )
		throw INIException( 3, "No water setting found for time of day '%s'", name.str() );

	// parse the data
	ini->initFromINI( waterSetting, waterSetting->getFieldParse() );

}  // end parseWaterSetting

//-------------------------------------------------------------------------------------------------
// ?parseWaterTransparencyDefinition@INI@@SAXPAV1@@Z
// BFME stops after initFromINI. Zero Hour follows it with the skybox-texture
// fix-up that walks the original and the override side by side; retail has no
// trace of that, so it is gone rather than compiled out.
//
// The opening test is the OVERRIDE<T> conversion rather than a raw null check --
// it recurses to the final override first, which is why retail loads the raw
// pointer, tests that, and only then walks the chain.
void INI::parseWaterTransparencyDefinition( INI *ini )
{
	const WaterTransparencySetting *existing = TheWaterTransparency;

	if (existing == NULL) {
		TheWaterTransparency = newInstance(WaterTransparencySetting);
	} else if (ini->getLoadType() == INI_LOAD_CREATE_OVERRIDES) {
		WaterTransparencySetting* wt = (WaterTransparencySetting*) (TheWaterTransparency.getNonOverloadedPointer());
		WaterTransparencySetting* wtOverride = newInstance(WaterTransparencySetting);
		*wtOverride = *wt;

		// Mark that it is an override.
		wtOverride->markAsOverride();

		wt->friend_getFinalOverride()->setNextOverride(wtOverride);
	} else {
		throw INIException(3, "WaterTransparency found twice");
	}

	WaterTransparencySetting* waterTrans = (WaterTransparencySetting*) (TheWaterTransparency.getNonOverloadedPointer());
	waterTrans = (WaterTransparencySetting*) (waterTrans->friend_getFinalOverride());
	// parse the data
	ini->initFromINI( waterTrans, waterTrans->getFieldParse() );
}


