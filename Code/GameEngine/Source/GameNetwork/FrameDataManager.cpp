// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/framedata /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
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


#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "GameNetwork/FrameDataManager.h"
#include "GameNetwork/NetworkUtil.h"

/**
 * Constructor.  isLocal tells it whether its the frame data manager for the local player or not.
 */
// ??0FrameDataManager@@ present-unmatched
FrameDataManager::FrameDataManager(Bool isLocal) {
	m_isLocal = isLocal;
	
	m_frameData = NEW FrameData[FRAME_DATA_LENGTH];

	m_isQuitting = FALSE;
	m_quitFrame = 0;
}

/**
 * destructor.
 */
// ??1FrameDataManager@@ present-unmatched
FrameDataManager::~FrameDataManager() {
	for (Int i = 0; i < FRAME_DATA_LENGTH; ++i) {
		m_frameData[i].reset();
	}

	if (m_frameData)
	{
		delete[] m_frameData;
		m_frameData = NULL;
	}
}

/**
 * Initialize all of the frame datas associated with this manager.
 */
// ?init@FrameDataManager@@ present-unmatched
void FrameDataManager::init() {
	for (Int i = 0; i < FRAME_DATA_LENGTH; ++i) {
		m_frameData[i].init();
		if (m_isLocal) {
			// If this is the local connection, adjust the frame command count.
			m_frameData[i].setFrameCommandCount(m_frameData[i].getCommandCount());
		}
	}

	m_isQuitting = FALSE;
	m_quitFrame = 0;
}

/**
 * Reset the state of all the frames.
 */
// ?reset@FrameDataManager@@ present-unmatched
void FrameDataManager::reset() {
	init();
}

/**
 * update function. Does nothing at this time.
 */
// ?update@FrameDataManager@@ present-unmatched
void FrameDataManager::update() {
}

/**
 * Add a network command to the appropriate frame.
 */
// ?addNetCommandMsg@FrameDataManager@@ present-unmatched
// BFME has no local-player adjustment here; the announced total is stamped by
// the FRAMEINFO path instead. Everything but the call shape matches: retail
// emits call+ret where this compiles to a tail jump, because addCommand's
// NetCommandRef return is discarded and the conventions line up.
void FrameDataManager::addNetCommandMsg(NetCommandMsg *msg) {
	UnsignedInt frame = msg->getExecutionFrame();
	UnsignedInt frameindex = frame % FRAME_DATA_LENGTH;
	m_frameData[frameindex].addCommand(msg);
}

/**
 * Returns true if all the commands for the given frame are ready.
 */
// ?allCommandsReady@FrameDataManager@@ present-unmatched
FrameDataReturnType FrameDataManager::allCommandsReady(UnsignedInt frame, Bool debugSpewage) {
	UnsignedInt frameindex = frame % FRAME_DATA_LENGTH;
	//DEBUG_ASSERTCRASH(m_frameData[frameindex].getFrame() == frame || frame == 256, ("Looking at old commands!"));
	return m_frameData[frameindex].allCommandsReady(debugSpewage);
}

/**
 * Returns the command list for the given frame.
 */
NetCommandList * FrameDataManager::getFrameCommandList(UnsignedInt frame) {
	UnsignedInt frameindex = frame % FRAME_DATA_LENGTH;
	return m_frameData[frameindex].getCommandList();
}

/**
 * Reset the contents of the given frame.
 */
// BFME drops ZH's isAdvancing branch along with m_frame, and passes -1 to
// setFrameCommandCount where ZH re-reads getCommandCount().
void FrameDataManager::resetFrame(UnsignedInt frame, Bool isAdvancing) {
	UnsignedInt frameindex = frame % FRAME_DATA_LENGTH;

	m_frameData[frameindex].reset();

	if (m_isLocal) {
		m_frameData[frameindex].setFrameCommandCount(-1);
	}
}

/**
 * Returns the command count for the given frame.
 */
UnsignedInt FrameDataManager::getCommandCount(UnsignedInt frame) {
	UnsignedInt frameindex = frame % FRAME_DATA_LENGTH;

	return m_frameData[frameindex].getCommandCount();
}

/**
 * Set the frame command count for the given frame.
 */
void FrameDataManager::setFrameCommandCount(UnsignedInt frame, UnsignedInt commandCount) {
	UnsignedInt frameindex = frame % FRAME_DATA_LENGTH;

	m_frameData[frameindex].setFrameCommandCount(commandCount);
}

/**
 *
 */
UnsignedInt FrameDataManager::getFrameCommandCount(UnsignedInt frame) {
	UnsignedInt frameindex = frame % FRAME_DATA_LENGTH;

	return m_frameData[frameindex].getFrameCommandCount();
}

/**
 * Set both the command count and the frame command count to 0 for the given frames.
 */
// ?zeroFrames@FrameDataManager@@ present-unmatched
void FrameDataManager::zeroFrames(UnsignedInt startingFrame, UnsignedInt numFrames) {
	UnsignedInt frameIndex = startingFrame % FRAME_DATA_LENGTH;
	for (UnsignedInt i = 0; i < numFrames; ++i) {
		//DEBUG_LOG(("Calling zeroFrame for frame index %d\n", frameIndex));
		m_frameData[frameIndex].zeroFrame();
		++frameIndex;
		frameIndex = frameIndex % FRAME_DATA_LENGTH;
	}
}

/**
 * Destroy all the commands held by this object.
 */
// ?destroyGameMessages@FrameDataManager@@ present-unmatched
void FrameDataManager::destroyGameMessages() {
	for (Int i = 0; i < FRAME_DATA_LENGTH; ++i) {
		m_frameData[i].destroyGameMessages();
	}
}

/**
 * Sets the quit frame, also sets the isQuitting flag.
 */
// ?setQuitFrame@FrameDataManager@@ present-unmatched
void FrameDataManager::setQuitFrame(UnsignedInt frame) {
	m_isQuitting = TRUE;
	m_quitFrame = frame;
}

/**
 * returns the quit frame.
 */
UnsignedInt FrameDataManager::getQuitFrame() {
	return m_quitFrame;
}

/**
 * returns true if this frame data manager is quitting.
 */
Bool FrameDataManager::getIsQuitting() {
	return m_isQuitting;
}
