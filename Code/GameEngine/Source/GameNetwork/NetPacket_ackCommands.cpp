// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source
// BFME's ack message carries the source player at +0x20. Retail passes that
// field as the fourth stack argument to addAckCommand; the ZH declaration
// omits it even though the retail callee cleans four arguments.

typedef bool Bool;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;

class NetCommandMsg;

class NetCommandRef
{
public:
	NetCommandMsg *getCommand(void) { return m_msg; }
	NetCommandMsg *m_msg;
};

class NetAckBothCommandMsg
{
public:
	UnsignedShort getCommandID(void);
	UnsignedByte getOriginalPlayerID(void);
	UnsignedInt getPlayerID(void) { return m_playerID; }
	unsigned char m_prefix[0x1c];
	UnsignedShort m_commandID;
	UnsignedByte m_originalPlayerID;
	unsigned char m_padding;
	UnsignedInt m_playerID;
};

class NetAckStage1CommandMsg
{
public:
	UnsignedShort getCommandID(void);
	UnsignedByte getOriginalPlayerID(void);
	UnsignedInt getPlayerID(void) { return m_playerID; }
	unsigned char m_prefix[0x1c];
	UnsignedShort m_commandID;
	UnsignedByte m_originalPlayerID;
	unsigned char m_padding;
	UnsignedInt m_playerID;
};

class NetAckStage2CommandMsg
{
public:
	UnsignedShort getCommandID(void);
	UnsignedByte getOriginalPlayerID(void);
	UnsignedInt getPlayerID(void) { return m_playerID; }
	unsigned char m_prefix[0x1c];
	UnsignedShort m_commandID;
	UnsignedByte m_originalPlayerID;
	unsigned char m_padding;
	UnsignedInt m_playerID;
};

class NetPacket
{
protected:
	Bool addAckBothCommand(NetCommandRef *msg);
	Bool addAckStage1Command(NetCommandRef *msg);
	Bool addAckStage2Command(NetCommandRef *msg);
	Bool addAckCommand(NetCommandRef *msg, UnsignedShort commandID, UnsignedByte originalPlayerID, UnsignedInt playerID);
};

Bool NetPacket::addAckBothCommand(NetCommandRef *msg)
{
	NetAckBothCommandMsg *ackmsg = (NetAckBothCommandMsg *)msg->getCommand();
	return addAckCommand(msg, ackmsg->getCommandID(), ackmsg->getOriginalPlayerID(), ackmsg->getPlayerID());
}

Bool NetPacket::addAckStage1Command(NetCommandRef *msg)
{
	NetAckStage1CommandMsg *ackmsg = (NetAckStage1CommandMsg *)msg->getCommand();
	return addAckCommand(msg, ackmsg->getCommandID(), ackmsg->getOriginalPlayerID(), ackmsg->getPlayerID());
}

Bool NetPacket::addAckStage2Command(NetCommandRef *msg)
{
	NetAckStage2CommandMsg *ackmsg = (NetAckStage2CommandMsg *)msg->getCommand();
	return addAckCommand(msg, ackmsg->getCommandID(), ackmsg->getOriginalPlayerID(), ackmsg->getPlayerID());
}
