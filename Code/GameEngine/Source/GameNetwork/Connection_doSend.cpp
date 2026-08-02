// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// Connection::doSend, 0x00661F10, 581 bytes -- the egress path.
//
// The reference's shape survives, with four BFME changes:
//
//  * a clock-wrap guard at the top that the reference has no counterpart for:
//    if the clock has gone backwards, m_lastTimeSent is pulled back to it so the
//    frame-grouping gate below cannot lock the connection out for 49 days.
//
//  * the quit test reads a -1 sentinel out of a dword at +0 rather than a
//    separate Bool, but is otherwise the reference's.
//
//  * the destination address comes off the Connection itself rather than
//    through a user object, and goes into the packet as a struct.
//
//  * and the interesting one: an ack-pending command is not retried forever.
//    After the retry bookkeeping, retail reads the command's frame -- the frame
//    field for a FRAMEINFO command, the execution frame for anything else -- and
//    if that frame plus TheWritableGlobalData+0xCB4 is already behind
//    TheGameLogic's current frame, the command is dropped from the queue instead
//    of being kept for another round.
//
// +0xCB4 is NetworkRunAheadSlack, not NetworkKeepAliveDelay: the INI offset
// table puts KeepAliveDelay at +0xCB8 and RunAheadSlack at +0xCB4, and
// RunAheadSlack is the one with reads. So the same staleness horizon that makes
// hasPacketRouterFrameStall declare a router stall also decides when a queued
// command is too old to keep retrying -- which makes RunAheadSlack a send-path
// knob as well as a stall tolerance.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;
typedef bool Bool;
typedef unsigned int time_t;

#define NULL 0
#define TRUE 1
#define FALSE 0

enum { NETCOMMANDTYPE_FRAMEINFO = 3 };
enum { MaxQuitFlushTime = 30000 };

extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime(void);

void __cdecl operator delete(void *block) throw();

class NetCommandMsg
{
public:
	Int getNetCommandType() { return m_commandType; }
	UnsignedInt getExecutionFrame() { return m_executionFrame; }

	void *m_vptr;
	UnsignedInt m_timestamp;						// this+0x04
	UnsignedInt m_executionFrame;					// this+0x08
	UnsignedInt m_playerID;							// this+0x0C
	UnsignedShort m_id;								// this+0x10
	Int m_commandType;								// this+0x14
};

// Type 3 keeps the frame it announces at +0x1C rather than in the base's
// execution frame, which is why the drop test has to branch on the type.
class NetFrameCommandMsg : public NetCommandMsg
{
public:
	UnsignedInt m_frame;							// this+0x1C
};

class NetCommandRef
{
public:
	~NetCommandRef();

	NetCommandMsg *getCommand() { return m_msg; }
	NetCommandRef *getNext() { return m_next; }
	UnsignedInt getTimeLastSent() { return m_timeLastSent; }
	void setTimeLastSent(UnsignedInt t) { m_timeLastSent = t; }

	NetCommandMsg *m_msg;							// this+0x00
	NetCommandRef *m_next;							// this+0x04
	NetCommandRef *m_prev;							// this+0x08
	UnsignedByte m_relay;							// this+0x0C
	UnsignedInt m_timeLastSent;						// this+0x10
};

class NetCommandList
{
public:
	NetCommandRef *getFirstMessage() { return m_first; }
	void reset();
	void removeMessage(NetCommandRef *msg);

	void *m_vptr;
	NetCommandRef *m_first;							// this+0x04
};

struct NetPacketAddress
{
	UnsignedInt ip;
	UnsignedShort port;
};

class NetPacket
{
public:
	virtual ~NetPacket();

	NetPacket();
	void init();
	Bool addCommand(NetCommandRef *msg);

	UnsignedByte m_packet[0x1DC];					// this+0x004
	Int m_packetLen;								// this+0x1E0
	NetPacketAddress m_dest;						// this+0x1E4
	Int m_numCommands;								// this+0x1EC
	NetCommandRef *m_lastCommand;					// this+0x1F0
	UnsignedInt m_lastFrame;						// this+0x1F4
	UnsignedShort m_lastCommandID;					// this+0x1F8
	UnsignedByte m_lastPlayerID;					// this+0x1FA
	UnsignedByte m_lastCommandType;					// this+0x1FB
	UnsignedByte m_lastRelay;						// this+0x1FC
};

class Transport
{
public:
	Bool queueSend(NetPacketAddress *addr, const UnsignedByte *data, Int len);
};

class GlobalData
{
public:
	char m_padToRunAheadSlack[0xCB4];
	Int m_networkRunAheadSlack;						// this+0xCB4
};

class GameLogic
{
public:
	UnsignedInt getFrame() { return m_frame; }

	char m_padToFrame[0x3C];
	UnsignedInt m_frame;							// this+0x3C
};

extern GlobalData *TheWritableGlobalData;
extern GameLogic *TheGameLogic;

GlobalData *TheWritableGlobalData;
GameLogic *TheGameLogic;

// The definition sets the whole register, but every caller tests al -- so the
// declaration callers see returns Bool, and only the definition widens.
Bool CommandRequiresAck(NetCommandMsg *msg);

class Connection
{
public:
	// Takes an argument the reference's does not: with it set, the loop stops
	// after five packets rather than draining the queue.
	UnsignedInt doSend(Bool limitBurst);

protected:
	void doRetryMetrics();

	// -1 when the connection is not quitting; the reference keeps a separate
	// Bool for this.
	Int m_quitFrame;								// this+0x000
	UnsignedInt m_quitTime;							// this+0x004
	Transport *m_transport;							// this+0x008
	// Assigned into the packet as a whole struct -- retail moves two dwords, so
	// the padding after the port travels with it.
	NetPacketAddress m_dest;						// this+0x00C
	char m_padToCommandList[0x18 - 0x14];			// unpinned
	NetCommandList *m_netCommandList;		// this+0x018
	UnsignedInt m_retryTime;						// this+0x01C
	char m_padToFrameGrouping[0x344 - 0x20];		// unpinned
	UnsignedInt m_frameGrouping;					// this+0x344
	UnsignedInt m_lastTimeSent;						// this+0x348
	char m_padToRetryMetrics[0x350 - 0x34C];		// unpinned
	Int m_numRetries;								// this+0x350
	UnsignedInt m_retryMetricsTime;					// this+0x354
};

// Matched from Connection.cpp; defined here too because retail inlines it into
// doSend and the static it owns has to be the same object.
// ?doRetryMetrics@Connection@@IAEXXZ present-unmatched
void Connection::doRetryMetrics() {
	static Int numSeconds = 0;
	time_t curTime = timeGetTime();

	if ((curTime - m_retryMetricsTime) > 10000) {
		m_retryMetricsTime = curTime;
		++numSeconds;
		m_numRetries = 0;
	}
}

// Instruction for instruction retail's, including every branch, every field
// offset and every callee. What is left is the frame allocator: retail puts
// curtime at +0x0C, numpackets at +0x10 and next at +0x14, and this source gets
// next lowest instead. Reordering the declarations does not move them, and
// hoisting next out of the inner scope does not either.
// ?doSend@Connection@@QAEI_N@Z present-unmatched
UnsignedInt Connection::doSend(Bool limitBurst) {
	Int numpackets = 0;
	time_t curtime = timeGetTime();
	Bool couldQueue = TRUE;

	if (curtime < m_lastTimeSent) {
		m_lastTimeSent = curtime;
	}

	// Do this check first, since it's an important fail-safe
	if ((m_quitFrame != -1) && (curtime > m_quitTime + MaxQuitFlushTime)) {
		m_netCommandList->reset();
		return 0;
	}

	if ((curtime - m_lastTimeSent) < m_frameGrouping) {
		return 0;
	}

	// iterate through all the messages and put them into a packet(s).
	NetCommandRef *msg = m_netCommandList->getFirstMessage();
	NetCommandRef *next;

	while ((msg != NULL) && couldQueue) {
		NetPacket *packet = new NetPacket;
		packet->init();
		packet->m_dest = m_dest;

		Bool notDone = TRUE;

		// add the command messages until either we run out of messages or the packet is full.
		while ((msg != NULL) && notDone) {
			next = msg->getNext(); // Need this since msg could be deleted

			time_t timeLastSent = msg->getTimeLastSent();

			if (((curtime - timeLastSent) > m_retryTime) || (timeLastSent == -1)) {
				notDone = packet->addCommand(msg);
				if (notDone) {
					// the msg command was added to the packet.
					if (CommandRequiresAck(msg->getCommand())) {
						if (timeLastSent != -1) {
							++m_numRetries;
						}
						doRetryMetrics();
						msg->setTimeLastSent(curtime);

						NetCommandMsg *command = msg->getCommand();
						UnsignedInt frame = (command->getNetCommandType() == NETCOMMANDTYPE_FRAMEINFO)
								? ((NetFrameCommandMsg *)command)->m_frame
								: command->getExecutionFrame();

						if (frame == -1) {
							msg = next;
							continue;
						}

						if ((TheWritableGlobalData->m_networkRunAheadSlack + frame) >= TheGameLogic->getFrame()) {
							msg = next;
							continue;
						}
					}

					m_netCommandList->removeMessage(msg);
					delete msg;
				}
			}
			msg = next;
		}

		++numpackets;

		if ((numpackets > 5) && limitBurst) {
			couldQueue = FALSE;
		}

		if (packet->m_numCommands > 0) {
			// If the packet actually has any information to give, give it to the transport object
			// for transmission.
			couldQueue = m_transport->queueSend(&packet->m_dest, packet->m_packet, packet->m_packetLen);
			m_lastTimeSent = curtime;
		}

		delete packet;
	}

	return numpackets;
}
