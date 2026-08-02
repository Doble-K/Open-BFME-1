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

// Retail's packet check calls the WWLib CRC through the thunk at 0x0000A984.
extern unsigned long CRC_Memory( const unsigned char *data, unsigned long length, unsigned long crc );


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
	m_badPackets = 0;

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

// This assumes the buf is a multiple of 4 bytes.  Extra is not encrypted.
static inline void decryptBuf( unsigned char *buf, Int len )
{
	UnsignedInt mask = 0x38D9B7D4;

	UnsignedInt *uintPtr = (UnsignedInt *) (buf);

	for (int i=0 ; i<len/4 ; i++) {
		*uintPtr = htonl(*uintPtr);
		*uintPtr = (*uintPtr) ^ mask;
		uintPtr++;
		mask -= 0x7F39C50E;
	}
}

Bool Transport::doRecv()
{
	if (!m_udpsock)
	{
		return FALSE;
	}

	// The reference starts this TRUE and only clears it on a socket error, so it
	// answers "did the socket behave". BFME starts it FALSE and sets it only
	// when a packet actually lands in m_inBuffer, so it answers "did anything
	// arrive" -- and a read error is no longer distinguishable from a quiet
	// socket.
	Bool retval = FALSE;

	sockaddr_in from;
	TransportMessage incomingMessage;

	Int len;
	while ( (len=m_udpsock->Read((unsigned char *)&incomingMessage, sizeof(TransportMessage), &from)) > 0 )
	{
		decryptBuf((unsigned char *)&incomingMessage, len);

		// The reference fills these in on the m_inBuffer slot it picks. BFME
		// fills in the local and copies the whole struct into the slot, which is
		// why the slot store below is an assignment rather than a memcpy.
		incomingMessage.addr = ntohl(from.sin_addr.S_un.S_addr);
		incomingMessage.port = ntohs(from.sin_port);

		UnsignedInt msgLen = len - sizeof(TransportMessageHeader);
		incomingMessage.length = msgLen;

		// Where the reference checks a magic number through isGeneralsPacket,
		// BFME recomputes the CRC over the payload and compares it against the
		// header. That check is the reason BFME's header has no magic field left
		// to check, and it is the only validation an incoming packet gets.
		if (msgLen <= 0 || msgLen > MAX_MESSAGE_LEN ||
				incomingMessage.header.crc != CRC_Memory(incomingMessage.data, msgLen, 0))
		{
			++m_badPackets;
			m_unknownPackets[m_statisticsSlot]++;
			m_unknownBytes[m_statisticsSlot] += len;
			continue;
		}

		m_incomingPackets[m_statisticsSlot]++;
		m_incomingBytes[m_statisticsSlot] += len;

		for (int i=0; i<MAX_MESSAGES; ++i)
		{
			if (m_inBuffer[i].length == 0)
			{
				// Empty slot; use it
				m_inBuffer[i] = incomingMessage;
				retval = TRUE;
				break;
			}
		}
	}

	return retval;
}

// The six bandwidth metrics are the reference's, unchanged, and retail lays
// them out in this order -- each one identified by the statistics array its
// unrolled loop indexes.

Real Transport::getIncomingBytesPerSecond( void )
{
	Real val = 0.0;
	for (int i=0; i<MAX_TRANSPORT_STATISTICS_SECONDS; ++i)
	{
		if (i != m_statisticsSlot)
			val += m_incomingBytes[i];
	}
	return val / (MAX_TRANSPORT_STATISTICS_SECONDS-1);
}

Real Transport::getIncomingPacketsPerSecond( void )
{
	Real val = 0.0;
	for (int i=0; i<MAX_TRANSPORT_STATISTICS_SECONDS; ++i)
	{
		if (i != m_statisticsSlot)
			val += m_incomingPackets[i];
	}
	return val / (MAX_TRANSPORT_STATISTICS_SECONDS-1);
}

Real Transport::getOutgoingBytesPerSecond( void )
{
	Real val = 0.0;
	for (int i=0; i<MAX_TRANSPORT_STATISTICS_SECONDS; ++i)
	{
		if (i != m_statisticsSlot)
			val += m_outgoingBytes[i];
	}
	return val / (MAX_TRANSPORT_STATISTICS_SECONDS-1);
}

Real Transport::getOutgoingPacketsPerSecond( void )
{
	Real val = 0.0;
	for (int i=0; i<MAX_TRANSPORT_STATISTICS_SECONDS; ++i)
	{
		if (i != m_statisticsSlot)
			val += m_outgoingPackets[i];
	}
	return val / (MAX_TRANSPORT_STATISTICS_SECONDS-1);
}

Real Transport::getUnknownBytesPerSecond( void )
{
	Real val = 0.0;
	for (int i=0; i<MAX_TRANSPORT_STATISTICS_SECONDS; ++i)
	{
		if (i != m_statisticsSlot)
			val += m_unknownBytes[i];
	}
	return val / (MAX_TRANSPORT_STATISTICS_SECONDS-1);
}

Real Transport::getUnknownPacketsPerSecond( void )
{
	Real val = 0.0;
	for (int i=0; i<MAX_TRANSPORT_STATISTICS_SECONDS; ++i)
	{
		if (i != m_statisticsSlot)
			val += m_unknownPackets[i];
	}
	return val / (MAX_TRANSPORT_STATISTICS_SECONDS-1);
}
