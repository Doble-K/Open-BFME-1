// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// NetPacket::ConstructNetCommandMsgFromRawData -- the tag loop that turns one
// serialised command back into a NetCommandRef.
//
// The tags are the reference's and in the reference's order: T for the command
// type, R for the relay, P for the player id, C for the command id, F for the
// execution frame, D to hand off to the per-type reader and stop.
//
// The dispatch chain is BFME's, and its order is read straight off the image
// rather than assumed. It differs from the reference's twice over:
//
//   * the types the reference has and BFME does not -- RUNAHEAD,
//     RUNAHEADMETRICS, PACKETROUTERQUERY, PACKETROUTERACK and
//     FRAMERESENDREQUEST -- are simply absent, and
//   * BFME's own six are here: the three ack stages, the GameSpy stats-authkey
//     pair, request-player-leave, inform-player-leave-frame,
//     request-frame-data, and type 22, the per-slot frame ratios.
//
// Type 22 is tested third, right after the frame-info command and well ahead of
// the disconnect types its number sits among. That placement is the giveaway
// that it is per-frame traffic, and it matches: computePlayerFrameRatios is what
// produces it.
//
// Every one of the four setters on the message is inlined here, as is
// NetCommandRef::setRelay -- and that last one writes +0x0C, which independently
// confirms m_relay's offset against the ledger row at 0x003BC6B0 that stores to
// +0x10.

#include <string.h>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;
typedef unsigned char Bool;

enum
{
	NETCOMMANDTYPE_ACKBOTH = 0,
	NETCOMMANDTYPE_ACKSTAGE1 = 1,
	NETCOMMANDTYPE_ACKSTAGE2 = 2,
	NETCOMMANDTYPE_FRAMEINFO = 3,
	NETCOMMANDTYPE_GAMECOMMAND = 4,
	NETCOMMANDTYPE_REQUEST_GAMESPY_STATS_AUTHKEY = 5,
	NETCOMMANDTYPE_GAMESPY_STATS_AUTHKEY = 6,
	NETCOMMANDTYPE_REQUESTPLAYERLEAVE = 7,
	NETCOMMANDTYPE_INFORMPLAYERLEAVEFRAME = 8,
	NETCOMMANDTYPE_REQUESTFRAMEDATA = 9,
	NETCOMMANDTYPE_PLAYERLEAVE = 10,
	NETCOMMANDTYPE_DESTROYPLAYER = 11,
	NETCOMMANDTYPE_KEEPALIVE = 12,
	NETCOMMANDTYPE_DISCONNECTCHAT = 13,
	NETCOMMANDTYPE_CHAT = 14,
	NETCOMMANDTYPE_PROGRESS = 15,
	NETCOMMANDTYPE_LOADCOMPLETE = 16,
	NETCOMMANDTYPE_TIMEOUTSTART = 17,
	NETCOMMANDTYPE_WRAPPER = 18,
	NETCOMMANDTYPE_FILE = 19,
	NETCOMMANDTYPE_FILEANNOUNCE = 20,
	NETCOMMANDTYPE_FILEPROGRESS = 21,
	NETCOMMANDTYPE_PLAYERFRAMERATIOS = 22,
	NETCOMMANDTYPE_DISCONNECTKEEPALIVE = 24,
	NETCOMMANDTYPE_DISCONNECTPLAYER = 25,
	NETCOMMANDTYPE_DISCONNECTVOTE = 26,
	NETCOMMANDTYPE_DISCONNECTFRAME = 27,
	NETCOMMANDTYPE_DISCONNECTSCREENOFF = 28
};

class NetCommandMsg
{
public:
	void detach();

	void setExecutionFrame(UnsignedInt frame) { m_executionFrame = frame; }
	void setID(UnsignedShort id) { m_id = id; }
	void setPlayerID(UnsignedInt playerID) { m_playerID = playerID; }
	void setNetCommandType(Int type) { m_commandType = type; }

	UnsignedInt m_timestamp;						// this+0x04
	UnsignedInt m_executionFrame;					// this+0x08
	UnsignedInt m_playerID;							// this+0x0C
	UnsignedShort m_id;								// this+0x10
	Int m_commandType;								// this+0x14
	Int m_referenceCount;							// this+0x18

private:
	virtual ~NetCommandMsg();
};

class NetCommandRef
{
public:
	NetCommandRef(NetCommandMsg *msg);

	void setRelay(UnsignedByte relay) { m_relay = relay; }

	NetCommandMsg *m_msg;							// this+0x00
	NetCommandRef *m_next;							// this+0x04
	NetCommandRef *m_prev;							// this+0x08
	UnsignedByte m_relay;							// this+0x0C
	UnsignedInt m_timeLastSent;						// this+0x10
};

class NetPacket
{
public:
	static NetCommandRef *ConstructNetCommandMsgFromRawData(UnsignedByte *data, UnsignedShort dataLength);

protected:
	static NetCommandMsg *readGameMessage(UnsignedByte *data, Int &i);
	static NetCommandMsg *readAckBothMessage(UnsignedByte *data, Int &i);
	static NetCommandMsg *readAckStage1Message(UnsignedByte *data, Int &i);
	static NetCommandMsg *readAckStage2Message(UnsignedByte *data, Int &i);
	static NetCommandMsg *readFrameMessage(UnsignedByte *data, Int &i);
	static NetCommandMsg *readPlayerFrameRatiosMessage(UnsignedByte *data, Int &i);
	static NetCommandMsg *readPlayerLeaveMessage(UnsignedByte *data, Int &i);
	static NetCommandMsg *readDestroyPlayerMessage(UnsignedByte *data, Int &i);
	static NetCommandMsg *readKeepAliveMessage(UnsignedByte *data, Int &i);
	static NetCommandMsg *readDisconnectKeepAliveMessage(UnsignedByte *data, Int &i);
	static NetCommandMsg *readDisconnectPlayerMessage(UnsignedByte *data, Int &i);
	static NetCommandMsg *readDisconnectChatMessage(UnsignedByte *data, Int &i);
	static NetCommandMsg *readDisconnectVoteMessage(UnsignedByte *data, Int &i);
	static NetCommandMsg *readChatMessage(UnsignedByte *data, Int &i);
	static NetCommandMsg *readProgressMessage(UnsignedByte *data, Int &i);
	static NetCommandMsg *readLoadCompleteMessage(UnsignedByte *data, Int &i);
	static NetCommandMsg *readTimeOutGameStartMessage(UnsignedByte *data, Int &i);
	static NetCommandMsg *readWrapperMessage(UnsignedByte *data, Int &i);
	static NetCommandMsg *readFileMessage(UnsignedByte *data, Int &i);
	static NetCommandMsg *readFileAnnounceMessage(UnsignedByte *data, Int &i);
	static NetCommandMsg *readFileProgressMessage(UnsignedByte *data, Int &i);
	static NetCommandMsg *readInformPlayerLeaveFrameMessage(UnsignedByte *data, Int &i);
	static NetCommandMsg *readRequestPlayerLeaveMessage(UnsignedByte *data, Int &i);
	static NetCommandMsg *readRequestFrameDataMessage(UnsignedByte *data, Int &i);
	static NetCommandMsg *readDisconnectFrameMessage(UnsignedByte *data, Int &i);
	static NetCommandMsg *readDisconnectScreenOffMessage(UnsignedByte *data, Int &i);
	static NetCommandMsg *readRequestGameSpyStatsAuthKeyMessage(UnsignedByte *data, Int &i);
	static NetCommandMsg *readGameSpyStatsAuthKeyMessage(UnsignedByte *data, Int &i);
};

// This function assumes that all of the fields are either of default value or are
// present in the raw data.
//
// 0x0067EE40, 937 bytes. Every instruction is retail's and in retail's order;
// what differs is which registers hold three of the locals. Retail keeps offset
// in esi and notDone in cl, and reads dataLength into eax; this source gets
// offset in eax and notDone in dl with dataLength in ecx, which shifts the whole
// frame layout by eight bytes because esi is then pushed after the local stores
// rather than before them.
//
// Two source-level facts were pinned getting this far and are worth keeping even
// while the body is unclaimed: the byte-into-Int memcpy for the T tag is what
// forces commandType through a stack slot rather than staying in a register, and
// dropping the reference's `msg = NULL` initialiser is what removes the sixth
// prologue store. Both were derived from the target, not guessed.
//
// The ledger's existing claim for this name is at 0x00682FF0, from a MASM dump.
// That body is 515 bytes, dispatches on a value being 3 and allocates 0x18 --
// it parses no tags, calls no reader and builds no NetCommandRef, so the name
// does not belong to it. Repointing is left until this body is byte-clean.
// ?ConstructNetCommandMsgFromRawData@NetPacket@@SAPAVNetCommandRef@@PAEG@Z present-unmatched
NetCommandRef *NetPacket::ConstructNetCommandMsgFromRawData(UnsignedByte *data, UnsignedShort dataLength)
{
	// Zero, not GAMECOMMAND: BFME changed the default the reference starts from.
	// Zero is ACKBOTH in this enum, but nothing depends on that -- a well-formed
	// command always carries its own T tag before the D that reads it.
	Int commandType = 0;
	UnsignedShort commandID = 0;
	UnsignedInt frame = 0;
	UnsignedByte playerID = 0;
	UnsignedByte relay = 0;

	Int offset = 0;
	Bool notDone = 1;
	NetCommandRef *ref = 0;
	NetCommandMsg *msg;

	while ((offset < (Int)dataLength) && notDone) {
		if (data[offset] == 'T') {
			++offset;
			memcpy(&commandType, data + offset, sizeof(UnsignedByte));
			offset += sizeof(UnsignedByte);
		} else if (data[offset] == 'R') {
			++offset;
			memcpy(&relay, data + offset, sizeof(UnsignedByte));
			offset += sizeof(UnsignedByte);
		} else if (data[offset] == 'P') {
			++offset;
			memcpy(&playerID, data + offset, sizeof(UnsignedByte));
			offset += sizeof(UnsignedByte);
		} else if (data[offset] == 'C') {
			++offset;
			memcpy(&commandID, data + offset, sizeof(UnsignedShort));
			offset += sizeof(UnsignedShort);
		} else if (data[offset] == 'F') {
			++offset;
			memcpy(&frame, data + offset, sizeof(UnsignedInt));
			offset += sizeof(UnsignedInt);
		} else if (data[offset] == 'D') {
			++offset;
			if (commandType == NETCOMMANDTYPE_GAMECOMMAND) {
				msg = readGameMessage(data, offset);
			} else if (commandType == NETCOMMANDTYPE_ACKBOTH) {
				msg = readAckBothMessage(data, offset);
			} else if (commandType == NETCOMMANDTYPE_ACKSTAGE1) {
				msg = readAckStage1Message(data, offset);
			} else if (commandType == NETCOMMANDTYPE_ACKSTAGE2) {
				msg = readAckStage2Message(data, offset);
			} else if (commandType == NETCOMMANDTYPE_FRAMEINFO) {
				msg = readFrameMessage(data, offset);
			} else if (commandType == NETCOMMANDTYPE_PLAYERFRAMERATIOS) {
				msg = readPlayerFrameRatiosMessage(data, offset);
			} else if (commandType == NETCOMMANDTYPE_PLAYERLEAVE) {
				msg = readPlayerLeaveMessage(data, offset);
			} else if (commandType == NETCOMMANDTYPE_DESTROYPLAYER) {
				msg = readDestroyPlayerMessage(data, offset);
			} else if (commandType == NETCOMMANDTYPE_KEEPALIVE) {
				msg = readKeepAliveMessage(data, offset);
			} else if (commandType == NETCOMMANDTYPE_DISCONNECTKEEPALIVE) {
				msg = readDisconnectKeepAliveMessage(data, offset);
			} else if (commandType == NETCOMMANDTYPE_DISCONNECTPLAYER) {
				msg = readDisconnectPlayerMessage(data, offset);
			} else if (commandType == NETCOMMANDTYPE_DISCONNECTCHAT) {
				msg = readDisconnectChatMessage(data, offset);
			} else if (commandType == NETCOMMANDTYPE_DISCONNECTVOTE) {
				msg = readDisconnectVoteMessage(data, offset);
			} else if (commandType == NETCOMMANDTYPE_CHAT) {
				msg = readChatMessage(data, offset);
			} else if (commandType == NETCOMMANDTYPE_PROGRESS) {
				msg = readProgressMessage(data, offset);
			} else if (commandType == NETCOMMANDTYPE_LOADCOMPLETE) {
				msg = readLoadCompleteMessage(data, offset);
			} else if (commandType == NETCOMMANDTYPE_TIMEOUTSTART) {
				msg = readTimeOutGameStartMessage(data, offset);
			} else if (commandType == NETCOMMANDTYPE_WRAPPER) {
				msg = readWrapperMessage(data, offset);
			} else if (commandType == NETCOMMANDTYPE_FILE) {
				msg = readFileMessage(data, offset);
			} else if (commandType == NETCOMMANDTYPE_FILEANNOUNCE) {
				msg = readFileAnnounceMessage(data, offset);
			} else if (commandType == NETCOMMANDTYPE_FILEPROGRESS) {
				msg = readFileProgressMessage(data, offset);
			} else if (commandType == NETCOMMANDTYPE_INFORMPLAYERLEAVEFRAME) {
				msg = readInformPlayerLeaveFrameMessage(data, offset);
			} else if (commandType == NETCOMMANDTYPE_REQUESTPLAYERLEAVE) {
				msg = readRequestPlayerLeaveMessage(data, offset);
			} else if (commandType == NETCOMMANDTYPE_REQUESTFRAMEDATA) {
				msg = readRequestFrameDataMessage(data, offset);
			} else if (commandType == NETCOMMANDTYPE_DISCONNECTFRAME) {
				msg = readDisconnectFrameMessage(data, offset);
			} else if (commandType == NETCOMMANDTYPE_DISCONNECTSCREENOFF) {
				msg = readDisconnectScreenOffMessage(data, offset);
			} else if (commandType == NETCOMMANDTYPE_REQUEST_GAMESPY_STATS_AUTHKEY) {
				msg = readRequestGameSpyStatsAuthKeyMessage(data, offset);
			} else if (commandType == NETCOMMANDTYPE_GAMESPY_STATS_AUTHKEY) {
				msg = readGameSpyStatsAuthKeyMessage(data, offset);
			}

			msg->setExecutionFrame(frame);
			msg->setID(commandID);
			msg->setPlayerID(playerID);
			msg->setNetCommandType(commandType);

			ref = new NetCommandRef(msg);

			ref->setRelay(relay);

			msg->detach();
			msg = 0;

			notDone = 0;
		}
	}

	return ref;
}
