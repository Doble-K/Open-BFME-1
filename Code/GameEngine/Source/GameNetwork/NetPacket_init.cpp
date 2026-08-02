// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// NetPacket::init, 0x00677700, 82 bytes.
//
// Named without guessing: Connection::doSend constructs a NetPacket and then
// calls this, and the reference has two candidates for that slot. reset() is
// ruled out because it deletes m_lastCommand before delegating, and this body
// makes no calls at all -- it is a flat run of stores. So it is init().
//
// The stores also pin BFME's whole NetPacket layout, and it is the reference's
// field set in the reference's init order, with one rearrangement that matters:
//
//   0x000  vptr                (the constructor at 0x00679650 stores one)
//   0x004  m_packet[0x1DC]     0x1DC == 476 == MAX_PACKET_SIZE
//   0x1E0  m_packetLen
//   0x1E4  m_addr        <-- these two are adjacent in BFME and separated in
//   0x1E8  m_port        <-- the reference
//   0x1EC  m_numCommands
//   0x1F0  m_lastCommand
//   0x1F4  m_lastFrame
//   0x1F8  m_lastCommandID     (word)
//   0x1FA  m_lastPlayerID      (byte)
//   0x1FB  m_lastCommandType   (byte)
//   0x1FC  m_lastRelay         (byte)
//
// sizeof is 0x200, which is what doSend hands operator new.
//
// m_addr and m_port sitting adjacent is the confirmation that the six-byte
// { UnsignedInt ip; UnsignedShort port; } inferred from Transport::queueSend is
// real: doSend passes &packet->m_addr as that argument, so the pair IS the
// address struct, embedded in the packet rather than built on the stack.
//
// Declared here rather than through a shim header: any file under
// reference/shims/ forces the full gate, and nothing outside this file needs it.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;

class NetCommandMsg;

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

	UnsignedByte m_packet[0x1DC];					// this+0x004
	Int m_packetLen;								// this+0x1E0
	// Eight bytes, not six: init assigns this as a whole struct (dword at +0x1E4
	// and dword at +0x1E8 out of an eight-byte stack temp), so the trailing two
	// bytes of padding are real and the type is NOT packed. The Transport shim's
	// pack(1) TransportAddress is wrong on that point.
	NetPacketAddress m_dest;						// this+0x1E4 (ip), +0x1E8 (port)
	Int m_numCommands;								// this+0x1EC
	NetCommandMsg *m_lastCommand;					// this+0x1F0
	UnsignedInt m_lastFrame;						// this+0x1F4
	UnsignedShort m_lastCommandID;					// this+0x1F8
	UnsignedByte m_lastPlayerID;					// this+0x1FA
	UnsignedByte m_lastCommandType;					// this+0x1FB
	UnsignedByte m_lastRelay;						// this+0x1FC
};

// The constructor zeroes the address pair field-wise -- dword at +0x1E4 then a
// word at +0x1E8 -- and then inlines init(), which assigns the same pair as a
// whole struct. Both shapes are in retail, one after the other.
// 0x00679650, 103 bytes: retail's length and instructions, but retail
// stores the vptr first and then the two field zeroes, where this source
// hoists the inlined init()'s stack temp above them. Same schedule
// tie-break as the Connection constructor and Transport::queueSend.
// ??0NetPacket@@QAE@XZ present-unmatched
NetPacket::NetPacket() {
	m_dest.ip = 0;
	m_dest.port = 0;
	init();
}

void NetPacket::init() {
	NetPacketAddress dest = { 0, 0 };
	m_dest = dest;
	m_numCommands = 0;
	m_packetLen = 0;
	m_packet[0] = 0;

	m_lastPlayerID = 0;
	m_lastFrame = 0;
	m_lastCommandID = 0;
	m_lastCommandType = 0;
	m_lastRelay = 0;

	m_lastCommand = 0;
}
