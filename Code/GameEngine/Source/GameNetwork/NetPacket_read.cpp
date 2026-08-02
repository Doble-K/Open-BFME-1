// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// NetPacket's per-type message readers.
//
// Each one allocates the command class for its type and pulls that class's own
// fields out of the packet buffer, advancing the caller's cursor. They are the
// mirror of the FillBufferWith* serialisers.
//
// Every allocation here is a plain ??2@YAPAXI@Z, not a memory pool: BFME
// de-pooled the whole netcode object graph, so the sizes retail pushes are the
// de-pooled ones -- 0x1C for a bare NetCommandMsg where the reference's pooled
// layout would be four bytes larger.
//
// These live outside NetPacket.cpp because that file models the command classes
// through the reference's pooled headers, which put every field four bytes too
// high and route allocation through newInstance().
//
// Naming note: this family is where several ledger rows were misattributed.
// readKeepAliveMessage, readDisconnectKeepAliveMessage, readLoadCompleteMessage,
// readTimeOutGameStartMessage, readPacketRouterQueryMessage and
// readPacketRouterAckMessage were all claimed on one 86-byte body at 0x0006C090,
// which is GameEngine::createMessageStream and constructs nothing of the sort;
// readProgressMessage was claimed on readPlayerLeaveMessage's body; and
// readDisconnectFrameMessage, readDisconnectScreenOffMessage and
// readFrameResendRequestMessage on readDestroyPlayerMessage's. The bodies below
// are the real ones, identified by the constructor each one calls.

#include <string.h>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;

enum { NETCOMMANDTYPE_FRAMEINFO = 3 };

class NetCommandMsg
{
public:
	NetCommandMsg();
	virtual ~NetCommandMsg();

protected:
	UnsignedInt m_timestamp;						// this+0x04
	UnsignedInt m_executionFrame;					// this+0x08
	UnsignedInt m_playerID;							// this+0x0C
	UnsignedShort m_id;								// this+0x10
	Int m_commandType;								// this+0x14
	Int m_referenceCount;							// this+0x18
};

class NetKeepAliveCommandMsg : public NetCommandMsg
{
public:
	NetKeepAliveCommandMsg();
};

class NetDisconnectKeepAliveCommandMsg : public NetCommandMsg
{
public:
	NetDisconnectKeepAliveCommandMsg();
};

class NetAckBothCommandMsg : public NetCommandMsg
{
public:
	NetAckBothCommandMsg();
	void setCommandID(UnsignedShort commandID);
	void setOriginalPlayerID(UnsignedByte originalPlayerID);

	UnsignedShort m_commandID;						// this+0x1C
	UnsignedByte m_originalPlayerID;				// this+0x1E
	UnsignedInt m_originalExecutionFrame;			// this+0x20
};

class NetAckStage1CommandMsg : public NetCommandMsg
{
public:
	NetAckStage1CommandMsg();
	void setCommandID(UnsignedShort commandID);
	void setOriginalPlayerID(UnsignedByte originalPlayerID);

	UnsignedShort m_commandID;						// this+0x1C
	UnsignedByte m_originalPlayerID;				// this+0x1E
	UnsignedInt m_originalExecutionFrame;			// this+0x20
};

class NetAckStage2CommandMsg : public NetCommandMsg
{
public:
	NetAckStage2CommandMsg();
	void setCommandID(UnsignedShort commandID);
	void setOriginalPlayerID(UnsignedByte originalPlayerID);

	UnsignedShort m_commandID;						// this+0x1C
	UnsignedByte m_originalPlayerID;				// this+0x1E
	UnsignedInt m_originalExecutionFrame;			// this+0x20
};

class NetProgressCommandMsg : public NetCommandMsg
{
public:
	NetProgressCommandMsg();
	void setPercentage(UnsignedByte percent);

	UnsignedByte m_percent;							// this+0x1C
};

class NetDisconnectFrameCommandMsg : public NetCommandMsg
{
public:
	NetDisconnectFrameCommandMsg();
	void setDisconnectFrame(UnsignedInt frame);

	UnsignedInt m_disconnectFrame;					// this+0x1C
};

class NetDisconnectScreenOffCommandMsg : public NetCommandMsg
{
public:
	NetDisconnectScreenOffCommandMsg();
	void setNewFrame(UnsignedInt frame);

	UnsignedInt m_newFrame;							// this+0x1C
};

class BFMENetInformPlayerLeaveFrameCommandMsg : public NetCommandMsg
{
public:
	BFMENetInformPlayerLeaveFrameCommandMsg();
	void setLeaveFrame(UnsignedInt frame);
	void setLeavingPlayerID(Int playerID);

	Int m_leavingPlayerID;							// this+0x1C
	UnsignedInt m_leaveFrame;						// this+0x20
};

class BFMENetRequestFrameDataCommandMsg : public NetCommandMsg
{
public:
	BFMENetRequestFrameDataCommandMsg();
	void setRequestedPlayerID(Int playerID);
	void setRequestedFrame(UnsignedInt frame);

	Int m_requestedPlayerID;						// this+0x1C
	UnsignedInt m_requestedFrame;					// this+0x20
};

// Type 3, the frame-info command, and the only one whose constructor retail
// inlines into its reader -- so the constructor is written inline here too.
// FINDINGS pins what the three fields carry: sendFrameInfo stamps the sender's
// TheGameLogic->getFrame() at +0x1C and the frame's total command count at
// +0x24, and the receiving half copies +0x20 into the per-player dword array at
// ConnectionManager+0x120A0. Nothing names that third value, so it keeps its
// offset. The count starting at -1 is the same "not yet known" sentinel the base
// uses for m_executionFrame.
class NetFrameCommandMsg : public NetCommandMsg
{
public:
	NetFrameCommandMsg()
	{
		m_frame = 0;
		m_field20 = 0;
		m_commandCount = -1;
		m_commandType = NETCOMMANDTYPE_FRAMEINFO;
	}

	UnsignedInt m_frame;							// this+0x1C
	UnsignedInt m_field20;							// this+0x20
	UnsignedInt m_commandCount;						// this+0x24
};

class BFMENetRequestPlayerLeaveCommandMsg : public NetCommandMsg
{
public:
	BFMENetRequestPlayerLeaveCommandMsg();
	void setRequestedPlayerID(Int playerID);

	Int m_requestedPlayerID;						// this+0x1C
};

class NetPacket
{
protected:
	static NetCommandMsg *readFrameMessage(UnsignedByte *data, Int &i);
	static NetCommandMsg *readRequestPlayerLeaveMessage(UnsignedByte *data, Int &i);
	static NetCommandMsg *readAckBothMessage(UnsignedByte *data, Int &i);
	static NetCommandMsg *readAckStage1Message(UnsignedByte *data, Int &i);
	static NetCommandMsg *readAckStage2Message(UnsignedByte *data, Int &i);
	static NetCommandMsg *readKeepAliveMessage(UnsignedByte *data, Int &i);
	static NetCommandMsg *readDisconnectKeepAliveMessage(UnsignedByte *data, Int &i);
	static NetCommandMsg *readProgressMessage(UnsignedByte *data, Int &i);
	static NetCommandMsg *readLoadCompleteMessage(UnsignedByte *data, Int &i);
	static NetCommandMsg *readTimeOutGameStartMessage(UnsignedByte *data, Int &i);
	static NetCommandMsg *readDisconnectFrameMessage(UnsignedByte *data, Int &i);
	static NetCommandMsg *readDisconnectScreenOffMessage(UnsignedByte *data, Int &i);
	static NetCommandMsg *readInformPlayerLeaveFrameMessage(UnsignedByte *data, Int &i);
	static NetCommandMsg *readRequestFrameDataMessage(UnsignedByte *data, Int &i);
};

NetCommandMsg *NetPacket::readFrameMessage(UnsignedByte *data, Int &i)
{
	NetFrameCommandMsg *msg = new NetFrameCommandMsg;

	UnsignedInt frame = 0;
	memcpy(&frame, data + i, sizeof(frame));
	i += sizeof(frame);
	msg->m_frame = frame;

	UnsignedInt field20 = 0;
	memcpy(&field20, data + i, sizeof(field20));
	i += sizeof(field20);
	msg->m_field20 = field20;

	UnsignedInt commandCount = 0;
	memcpy(&commandCount, data + i, sizeof(commandCount));
	i += sizeof(commandCount);
	msg->m_commandCount = commandCount;

	return msg;
}

NetCommandMsg *NetPacket::readRequestPlayerLeaveMessage(UnsignedByte *data, Int &i)
{
	BFMENetRequestPlayerLeaveCommandMsg *msg = new BFMENetRequestPlayerLeaveCommandMsg;

	Int playerID = 0;
	memcpy(&playerID, data + i, sizeof(playerID));
	i += sizeof(playerID);
	msg->setRequestedPlayerID(playerID);

	return msg;
}

NetCommandMsg *NetPacket::readAckBothMessage(UnsignedByte *data, Int &i)
{
	NetAckBothCommandMsg *msg = new NetAckBothCommandMsg;

	UnsignedShort cmdID = 0;
	memcpy(&cmdID, data + i, sizeof(UnsignedShort));
	i += sizeof(UnsignedShort);
	msg->setCommandID(cmdID);

	UnsignedByte origPlayerID = 0;
	memcpy(&origPlayerID, data + i, sizeof(UnsignedByte));
	i += sizeof(UnsignedByte);
	msg->setOriginalPlayerID(origPlayerID);

	// BFME-only, and written through the field rather than a setter -- there is
	// no setOriginalExecutionFrame anywhere in the image.
	UnsignedInt origExecFrame = 0;
	memcpy(&origExecFrame, data + i, sizeof(origExecFrame));
	i += sizeof(origExecFrame);
	msg->m_originalExecutionFrame = origExecFrame;

	return msg;
}

NetCommandMsg *NetPacket::readAckStage1Message(UnsignedByte *data, Int &i)
{
	NetAckStage1CommandMsg *msg = new NetAckStage1CommandMsg;

	UnsignedShort cmdID = 0;
	memcpy(&cmdID, data + i, sizeof(UnsignedShort));
	i += sizeof(UnsignedShort);
	msg->setCommandID(cmdID);

	UnsignedByte origPlayerID = 0;
	memcpy(&origPlayerID, data + i, sizeof(UnsignedByte));
	i += sizeof(UnsignedByte);
	msg->setOriginalPlayerID(origPlayerID);

	// BFME-only, and written through the field rather than a setter -- there is
	// no setOriginalExecutionFrame anywhere in the image.
	UnsignedInt origExecFrame = 0;
	memcpy(&origExecFrame, data + i, sizeof(origExecFrame));
	i += sizeof(origExecFrame);
	msg->m_originalExecutionFrame = origExecFrame;

	return msg;
}

NetCommandMsg *NetPacket::readAckStage2Message(UnsignedByte *data, Int &i)
{
	NetAckStage2CommandMsg *msg = new NetAckStage2CommandMsg;

	UnsignedShort cmdID = 0;
	memcpy(&cmdID, data + i, sizeof(UnsignedShort));
	i += sizeof(UnsignedShort);
	msg->setCommandID(cmdID);

	UnsignedByte origPlayerID = 0;
	memcpy(&origPlayerID, data + i, sizeof(UnsignedByte));
	i += sizeof(UnsignedByte);
	msg->setOriginalPlayerID(origPlayerID);

	// BFME-only, and written through the field rather than a setter -- there is
	// no setOriginalExecutionFrame anywhere in the image.
	UnsignedInt origExecFrame = 0;
	memcpy(&origExecFrame, data + i, sizeof(origExecFrame));
	i += sizeof(origExecFrame);
	msg->m_originalExecutionFrame = origExecFrame;

	return msg;
}

NetCommandMsg *NetPacket::readKeepAliveMessage(UnsignedByte *data, Int &i)
{
	NetKeepAliveCommandMsg *msg = new NetKeepAliveCommandMsg;

	return msg;
}

NetCommandMsg *NetPacket::readDisconnectKeepAliveMessage(UnsignedByte *data, Int &i)
{
	NetDisconnectKeepAliveCommandMsg *msg = new NetDisconnectKeepAliveCommandMsg;

	return msg;
}

NetCommandMsg *NetPacket::readProgressMessage(UnsignedByte *data, Int &i)
{
	NetProgressCommandMsg *msg = new NetProgressCommandMsg;

	UnsignedByte percentage = 0;
	memcpy(&percentage, data + i, sizeof(UnsignedByte));
	i += sizeof(UnsignedByte);
	msg->setPercentage(percentage);

	return msg;
}

// Both carry no payload at all, so both are a bare NetCommandMsg whose type the
// caller stamps. They are two separate 86-byte bodies rather than one folded
// copy only because each encodes its own SEH scope-table pointer.
NetCommandMsg *NetPacket::readLoadCompleteMessage(UnsignedByte *data, Int &i)
{
	NetCommandMsg *msg = new NetCommandMsg;

	return msg;
}

NetCommandMsg *NetPacket::readTimeOutGameStartMessage(UnsignedByte *data, Int &i)
{
	NetCommandMsg *msg = new NetCommandMsg;

	return msg;
}

NetCommandMsg *NetPacket::readDisconnectFrameMessage(UnsignedByte *data, Int &i)
{
	NetDisconnectFrameCommandMsg *msg = new NetDisconnectFrameCommandMsg;

	UnsignedInt disconnectFrame = 0;
	memcpy(&disconnectFrame, data + i, sizeof(disconnectFrame));
	i += sizeof(disconnectFrame);
	msg->setDisconnectFrame(disconnectFrame);

	return msg;
}

NetCommandMsg *NetPacket::readDisconnectScreenOffMessage(UnsignedByte *data, Int &i)
{
	NetDisconnectScreenOffCommandMsg *msg = new NetDisconnectScreenOffCommandMsg;

	UnsignedInt newFrame = 0;
	memcpy(&newFrame, data + i, sizeof(newFrame));
	i += sizeof(newFrame);
	msg->setNewFrame(newFrame);

	return msg;
}

NetCommandMsg *NetPacket::readInformPlayerLeaveFrameMessage(UnsignedByte *data, Int &i)
{
	BFMENetInformPlayerLeaveFrameCommandMsg *msg = new BFMENetInformPlayerLeaveFrameCommandMsg;

	UnsignedInt leaveFrame = 0;
	memcpy(&leaveFrame, data + i, sizeof(leaveFrame));
	i += sizeof(leaveFrame);
	msg->setLeaveFrame(leaveFrame);

	Int playerID = 0;
	memcpy(&playerID, data + i, sizeof(playerID));
	i += sizeof(playerID);
	msg->setLeavingPlayerID(playerID);

	return msg;
}

NetCommandMsg *NetPacket::readRequestFrameDataMessage(UnsignedByte *data, Int &i)
{
	BFMENetRequestFrameDataCommandMsg *msg = new BFMENetRequestFrameDataCommandMsg;

	Int playerID = 0;
	memcpy(&playerID, data + i, sizeof(playerID));
	i += sizeof(playerID);
	msg->setRequestedPlayerID(playerID);

	UnsignedInt frame = 0;
	memcpy(&frame, data + i, sizeof(frame));
	i += sizeof(frame);
	msg->setRequestedFrame(frame);

	return msg;
}
