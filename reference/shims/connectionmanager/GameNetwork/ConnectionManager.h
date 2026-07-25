#pragma once
// TU-scoped stand-in for the real GameNetwork/ConnectionManager.h (whose
// ZH-reference field layout does not match BFME's -- proven by three
// thunk-dump accessor bodies: retail getLocalPlayerID/isPacketRouter read
// this+0x12028/this+0x1202c for m_localSlot/m_packetRouterSlot, 0x12004
// bytes past the end of the this+4 m_connections pointer array the ZH
// header places right after the vptr. Whatever grew BFME's ConnectionManager
// between those two points is opaque padding here -- nothing in this TU
// touches it.
//
// Scoped to this TU via a private /Ireference/shims/connectionmanager
// include -- every other TU still resolves GameNetwork/ConnectionManager.h
// to the real header.

class NetProgressCommandMsg;

// Only the one dword retail's isPlayerConnected reads (this+0, compared to
// -1) is modeled; the rest of the real Connection object is irrelevant here.
class Connection
{
public:
	Int m_openSentinel;
};

class ConnectionManager
{
public:
	// The real class declares virtual init/reset/update/etc, giving it a
	// vptr at this+0; a dummy virtual here reproduces that so m_connections
	// lands at this+4 like retail.
	virtual ~ConnectionManager() {}

	Connection *m_connections[8];					// this+4 .. this+0x24
	char m_padBeforeLocalSlot[0x12028 - 0x24];		// unpinned; not touched by this TU
	UnsignedInt m_localSlot;						// this+0x12028
	UnsignedInt m_packetRouterSlot;				// this+0x1202c

	UnsignedInt getLocalPlayerID();
	Bool isPacketRouter( void );
	Bool isPlayerConnected( Int playerID );

private:
	void processProgress( NetProgressCommandMsg *msg );
};
