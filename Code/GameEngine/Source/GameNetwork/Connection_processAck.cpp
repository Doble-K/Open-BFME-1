// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// Connection::processAck(NetCommandMsg *), 0x00662270, 91 bytes.
//
// The reference's shape: dispatch on the ack stage, cast, and forward. What
// BFME adds is a third argument -- the original execution frame the ack carries
// at +0x20, which the reference's ack classes do not have at all. It is read
// straight off the field; there is no getter for it anywhere in the image.
//
// The reference routes each stage through a one-line overload taking the
// concrete ack class; retail inlines those, so only the three-argument form
// survives as a call.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;

enum
{
	NETCOMMANDTYPE_ACKBOTH = 0,
	NETCOMMANDTYPE_ACKSTAGE1 = 1
};

class NetCommandRef;

class NetCommandMsg
{
public:
	Int getNetCommandType() { return m_commandType; }

	void *m_vptr;
	UnsignedInt m_timestamp;						// this+0x04
	UnsignedInt m_executionFrame;					// this+0x08
	UnsignedInt m_playerID;							// this+0x0C
	UnsignedShort m_id;								// this+0x10
	Int m_commandType;								// this+0x14
	Int m_referenceCount;							// this+0x18
};

class NetAckStage1CommandMsg : public NetCommandMsg
{
public:
	UnsignedShort getCommandID();
	UnsignedByte getOriginalPlayerID();

	UnsignedShort m_commandID;						// this+0x1C
	UnsignedByte m_originalPlayerID;				// this+0x1E
	UnsignedInt m_originalExecutionFrame;			// this+0x20
};

class NetAckBothCommandMsg : public NetCommandMsg
{
public:
	UnsignedShort getCommandID();
	UnsignedByte getOriginalPlayerID();

	UnsignedShort m_commandID;						// this+0x1C
	UnsignedByte m_originalPlayerID;				// this+0x1E
	UnsignedInt m_originalExecutionFrame;			// this+0x20
};

class Connection
{
public:
	NetCommandRef *processAck(NetCommandMsg *msg);
	NetCommandRef *processAck(UnsignedShort commandID, UnsignedByte originalPlayerID, UnsignedInt originalExecutionFrame);
};

NetCommandRef *Connection::processAck(NetCommandMsg *msg) {
	if (msg->getNetCommandType() == NETCOMMANDTYPE_ACKSTAGE1) {
		NetAckStage1CommandMsg *ackmsg = (NetAckStage1CommandMsg *)msg;
		return processAck(ackmsg->getCommandID(), ackmsg->getOriginalPlayerID(), ackmsg->m_originalExecutionFrame);
	}

	if (msg->getNetCommandType() == NETCOMMANDTYPE_ACKBOTH) {
		NetAckBothCommandMsg *ackmsg = (NetAckBothCommandMsg *)msg;
		UnsignedInt originalExecutionFrame = ackmsg->m_originalExecutionFrame;
		return processAck(ackmsg->getCommandID(), ackmsg->getOriginalPlayerID(), originalExecutionFrame);
	}

	return 0;
}
