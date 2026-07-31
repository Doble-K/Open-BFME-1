// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/framedata /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it
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


#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "GameNetwork/FrameData.h"
#include "GameNetwork/NetworkUtil.h"

// BFME's FrameData has no m_frame -- the ring index is the frame -- so the
// ZH getFrame/setFrame pair and every assignment to it are gone. See
// reference/shims/framedata/GameNetwork/FrameData.h for the offset evidence.

/**
 * Initialize this thing.
 */
// ?init@FrameData@@ present-unmatched
void FrameData::init()
{
	if (m_commandList == NULL) {
		m_commandList = newInstance(NetCommandList);
		m_commandList->init();
	}
	m_commandList->reset();

	m_frameCommandCount = -1;
	m_commandCount = 0;
	m_lastFailedCC = -2;
	m_lastFailedFrameCC = -2;
}

/**
 * Set the command count for this frame
 */
void FrameData::setFrameCommandCount(UnsignedInt frameCommandCount) {
	m_frameCommandCount = frameCommandCount;
}

/**
 * Get the command count for this frame.
 */
UnsignedInt FrameData::getFrameCommandCount() {
	return m_frameCommandCount;
}

/**
 * return the number of commands received so far.
 */
UnsignedInt FrameData::getCommandCount() {
	return m_commandCount;
}

/**
 * Add a command to this frame
 */
// ?addCommand@FrameData@@ present-unmatched
void FrameData::addCommand(NetCommandMsg *msg) {
	// need to add the message in order of command ID
	if (m_commandList == NULL) {
		init();
	}

	// We don't need to worry about setting the relay since its not getting sent anywhere.
	if (m_commandList->findMessage(msg) != NULL) {
		// We don't want to add the same command twice.
		return;
	}
	m_commandList->addMessage(msg);

	++m_commandCount;
}

/**
 * Return the list of commands for this frame
 */
NetCommandList * FrameData::getCommandList() {
	return m_commandList;
}

/**
 * destroy all the commands in this frame.
 */
// ?destroyGameMessages@FrameData@@ present-unmatched
void FrameData::destroyGameMessages() {
	if (m_commandList == NULL) {
		return;
	}

	m_commandList->reset();
	m_commandCount = 0;
}
