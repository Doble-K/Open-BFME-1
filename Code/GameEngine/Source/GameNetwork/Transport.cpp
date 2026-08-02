// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/transport /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
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

#include "GameNetwork/Transport.h"

// ??0Transport@@QAE@XZ present-unmatched
/**
 * BFME does in the constructor what the reference does in init: clear both
 * message rings and every statistics counter. init is left with nothing to do
 * but bind.
 *
 * This compiles to retail's exact length (182B) and to the same instructions,
 * but not yet to the same bytes. Retail strength-reduces the clear loop onto
 * &m_inBuffer[i].length, so the in-buffer's last three stores get displacements
 * 0/+4/+8 and the out buffer is addressed backwards from there; writing the
 * buffers in this order anchors on &m_outBuffer[i].length instead, and writing
 * them the other way round anchors on &m_inBuffer[i].data. Both candidates give
 * three cheap displacements, so the tie-break is not the source order and is
 * still unidentified. Everything else -- field order, the two rep-stosd memsets,
 * the 0x80 downcount, the statistics loop's six stores in declaration order --
 * already matches.
 */
Transport::Transport(void)
{
	m_winsockInit = false;
	m_udpsock = NULL;
	m_statisticsSlot = 0;
	m_lastSecond = 0;
	m_unidentified410E0 = 0;

	Int i;
	for (i=0; i<MAX_MESSAGES; ++i)
	{
		m_inBuffer[i].header.crc = 0;
		memset(m_inBuffer[i].data, 0, MAX_MESSAGE_LEN);
		m_inBuffer[i].length = 0;
		m_inBuffer[i].addr = 0;
		m_inBuffer[i].port = 0;

		m_outBuffer[i].header.crc = 0;
		memset(m_outBuffer[i].data, 0, MAX_MESSAGE_LEN);
		m_outBuffer[i].length = 0;
		m_outBuffer[i].addr = 0;
		m_outBuffer[i].port = 0;
	}

	for (i=0; i<MAX_TRANSPORT_STATISTICS_SECONDS; ++i)
	{
		m_incomingBytes[i] = 0;
		m_unknownBytes[i] = 0;
		m_outgoingBytes[i] = 0;
		m_incomingPackets[i] = 0;
		m_unknownPackets[i] = 0;
		m_outgoingPackets[i] = 0;
	}
}

void Transport::reset( void )
{
	if (m_udpsock)
	{
		delete m_udpsock;
		m_udpsock = NULL;
	}

	if (m_winsockInit)
	{
		WSACleanup();
		m_winsockInit = false;
	}
}

Bool Transport::doSend() {
	if (!m_udpsock)
	{
		return FALSE;
	}

	// Statistics gathering
	UnsignedInt now = timeGetTime();
	if (m_lastSecond + 1000 < now)
	{
		m_lastSecond = now;
		m_statisticsSlot = (m_statisticsSlot + 1) % MAX_TRANSPORT_STATISTICS_SECONDS;
		m_outgoingPackets[m_statisticsSlot] = 0;
		m_outgoingBytes[m_statisticsSlot] = 0;
		m_incomingPackets[m_statisticsSlot] = 0;
		m_incomingBytes[m_statisticsSlot] = 0;
		m_unknownPackets[m_statisticsSlot] = 0;
		m_unknownBytes[m_statisticsSlot] = 0;
	}

	Bool retval = TRUE;

	// Send all messages
	int i;
	for (i=0; i<MAX_MESSAGES; ++i)
	{
		if (m_outBuffer[i].length != 0)
		{
			int bytesSent = 0;
			// Send this message
			if ((bytesSent = m_udpsock->Write((unsigned char *)(&m_outBuffer[i]), m_outBuffer[i].length + sizeof(TransportMessageHeader), m_outBuffer[i].addr, m_outBuffer[i].port)) > 0)
			{
				m_outgoingPackets[m_statisticsSlot]++;
				m_outgoingBytes[m_statisticsSlot] += m_outBuffer[i].length + sizeof(TransportMessageHeader);
				m_outBuffer[i].length = 0;  // Remove from queue
			}
			else
			{
				retval = FALSE;
			}
		}
	} // for (i=0; i<MAX_MESSAGES; ++i)

	return retval;
}
