// cl: /DNDEBUG /MD /GX /Od /GZ /GS
// EA's DirtySock ProtoMangle -- the file-static helpers that sit between the
// two bodies protomangle.cpp already names.
//
// WHY THIS IS PROTOMANGLE.  0x00804150 and 0x00804330 are named in the ledger
// because each logs its own name ("ProtoMangleCreate: Server:%s Port:%d
// GameID:%s LKey:%s" / "ProtoMangleDestroy: Shutting down").  Every body here
// is reached only from those two, or from the 2668-byte state machine at
// 0x00804920 whose log lines all start "ProtoMangle: ".  0x008042B0 logs
// "ProtoMangleCreate: buffer=%d bytes" under its caller's name, which is what
// keeps its OWN name unknown -- so the names in this file are address-derived
// and disclaim identity.  The struct is address-derived too; only the member
// OFFSETS and the immediates are evidence.
//
// WHY /Od /GZ.  Every body sets up a frame pointer for code with no register
// pressure, keeps each parameter in its stack slot across statements, writes
// 0xCCCCCCCC over its locals before using them, and ends `cmp ebp,esp / call
// 0x009F7502` -- MSVC 7.1's /GZ run-time checks, which cl rejects on the same
// command line as /O2.  This library was NOT built with the settings the rest
// of the image was.  /GS is on the same line for the sibling TU rows that carry
// the 0x012DBDB0 cookie; it instruments only bodies with a stack buffer, so it
// is inert for all four rows here.

// sprintf is called DIRECTLY (rel32 to the import stub at 0x009F6DE2), not
// through __imp__sprintf, so the translation unit did not see <stdio.h>'s
// dllimport declaration.  Declaring it here is what reproduces that.
extern "C" int sprintf( char *buffer, const char *format, ... );

#include <string.h>

struct Rva008042B0Http;

// ---------------------------------------------------------------- callees
// Addresses read from the REL32 at the call sites below; each name is pinned in
// reverse/symbols.csv and derived from its address, not recovered.
void  Rva007FE780Printf( const char *format, ... );   // 0x007FE780
void *Rva007F0000Alloc( int size );                   // 0x007F0000
void  Rva007F0030Free( void *block );                 // 0x007F0030
void  Rva007FD4E0SocketShutdown( void *socket, int how );  // 0x007FD4E0
void  Rva007FD3F0SocketClose( void *socket );              // 0x007FD3F0
void *Rva007FDFF0Connect( const char *host, int timeout );  // 0x007FDFF0
void  Rva00804920Update( Rva008042B0Http *http );           // 0x00804920
char *Rva007FFB50AddrText( unsigned int addr );             // 0x007FFB50
struct Rva00804440SockAddr;
void  Rva007FE310SocketHost( Rva00804440SockAddr *host, int hostLen,
		Rva00804440SockAddr *dest, int destLen );           // 0x007FE310

// The receiver of 0x008042B0 / 0x008043C0.  ProtoMangleCreate passes
// `ref + 0xC0` with size 0x400, so this is an embedded sub-object, not the
// ProtoMangle module record itself.  Only the four offsets the bodies touch are
// evidence; the padding names nothing.
struct Rva008042B0Http
{
	void        *m_socket;          // +0x000
	void        *m_conn;            // +0x004
	int          m_pad008;
	char         m_host[ 0x100 ];   // +0x00C -- strcpy target, guarded by a strlen < 0x100
	int          m_field10C;        // +0x10C
	int          m_port;            // +0x110
	int          m_state;           // +0x114
	int          m_pad118;
	int          m_field11C;        // +0x11C
	int          m_pad120;
	int          m_field124;        // +0x124
	int          m_pad128;
	int          m_pad12C;
	char        *m_buffer;          // +0x130
	unsigned int m_bufferSize;      // +0x134
	int          m_pad138;
	int          m_pad13C;
	int          m_pad140;
	int          m_field144;        // +0x144
};

// Copy at most size-1 bytes and always terminate.  Note it does NOT stop at a
// NUL in the source: the loop is bounded only by the count, which is why this
// is not strncpy.  A null source yields an empty destination.
void Rva00804250CopyField( char *dst, const char *src, int size )
{
	int i = 0;

	if( src != 0 )
	{
		--size;
		for( ; i < size; ++i )
			dst[ i ] = src[ i ];
	}
	dst[ i ] = 0;
}

// Allocate the sub-object's transfer buffer.  Returns 1 or -1, not 0.
int Rva008042B0HttpCreate( Rva008042B0Http *http, int bufferSize )
{
	http->m_socket = 0;
	http->m_state = 0;
	http->m_bufferSize = bufferSize;
	Rva007FE780Printf( "ProtoMangleCreate: buffer=%d bytes\n", http->m_bufferSize );
	http->m_buffer = (char *)Rva007F0000Alloc( http->m_bufferSize );
	if( http->m_buffer == 0 )
		return -1;
	return 1;
}

// Shut the socket down for both directions, then close it.  Idempotent.
void Rva00804380CloseSocket( Rva008042B0Http *http )
{
	if( http->m_socket != 0 )
	{
		Rva007FD4E0SocketShutdown( http->m_socket, 2 );
		Rva007FD3F0SocketClose( http->m_socket );
	}
	http->m_socket = 0;
}

void Rva008043C0HttpDestroy( Rva008042B0Http *http )
{
	Rva00804380CloseSocket( http );
	Rva007F0030Free( http->m_buffer );
}

// Case-insensitive string compare, folding only A-Z.  The `char` locals are
// signed (movsx at every read), and the loop is a do/while: the terminator is
// compared before the loop can exit, so equal strings return 0.
int Rva00804890StrCaseCmp( const char *left, const char *right )
{
	int diff;
	char cl;
	char cr;

	do
	{
		cl = *left++;
		if( cl >= 'A' && cl <= 'Z' )
			cl ^= 0x20;
		cr = *right++;
		if( cr >= 'A' && cr <= 'Z' )
			cr ^= 0x20;
		diff = cl - cr;
	}
	while( cl != 0 && diff == 0 );

	return diff;
}

// Start one HTTP request.  Reuses the connection only when the host, the port
// and the state all still agree; otherwise it drops the socket and reconnects.
// -1 = host too long for the 0x100-byte field, -2 = request longer than the
// buffer 0x008042B0 allocated.
int Rva008046E0HttpRequest( Rva008042B0Http *http, const char *host, int port,
		const char *request )
{
	if( strlen( host ) >= 0x100 )
		return -1;
	if( strlen( request ) + 1 > http->m_bufferSize )
		return -2;

	if( Rva00804890StrCaseCmp( host, http->m_host ) != 0 || port != http->m_port )
	{
		Rva00804380CloseSocket( http );
		http->m_state = 0;
	}
	if( http->m_state != 7 || http->m_field124 != 0 || http->m_socket == 0 )
	{
		Rva00804380CloseSocket( http );
		http->m_state = 0;
	}

	strcpy( http->m_buffer, request );
	Rva007FE780Printf( "HTTP request:\n%s\n", http->m_buffer );
	http->m_field144 = 3;

	if( http->m_state == 7 && Rva00804890StrCaseCmp( host, http->m_host ) == 0
			&& port == http->m_port )
	{
		http->m_state = 3;
	}
	else
	{
		strcpy( http->m_host, host );
		http->m_port = port;
		http->m_conn = Rva007FDFF0Connect( http->m_host, 0x1E );
		http->m_field10C = 0;
		http->m_state = 1;
	}

	http->m_field11C = 0;
	Rva00804920Update( http );
	return 0;
}

// The ProtoMangle module record ProtoMangleCreate allocates 0x214 bytes for.
// Every field name below is derived from the log line or the format specifier
// the byte is fed to; the OFFSETS are the evidence.
struct Rva00804150ProtoMangleRef
{
	void            *m_socket;          // +0x000
	// THE CALLER'S SOCKET, and 0x008053C0 is what says so: it stores its own
	// socket argument here and then queries THAT for its bound address.  It is
	// also the counterweight ProtoMangleDestroy compares +0x00 against before
	// closing it -- a socket the caller handed in must not be closed on the
	// caller's behalf, which is exactly what that guard buys.
	void            *m_userSocket;      // +0x004
	unsigned int     m_localAddr;       // +0x008
	int              m_myPort;          // +0x00C
	// THE TWO PEER FIELDS, named by the tags 0x00805870 parses into them: it
	// pulls "peerIP" out of a response blob, runs it through the dotted-quad
	// parser and stores the result here, then does the same for "peerPort"
	// through atoi.  The names are retail's own tag spellings.
	unsigned int     m_peerAddr;        // +0x010
	int              m_peerPort;        // +0x014
	char             m_sessID[ 0x20 ];  // +0x018
	char             m_gameID[ 0x20 ];  // +0x038
	char             m_lkey[ 0x40 ];    // +0x058
	char             m_server[ 0x20 ];  // +0x098
	int              m_port;            // +0x0B8
	int              m_pad0BC;
	Rva008042B0Http  m_http;            // +0x0C0
	int              m_pad208;
	int              m_timeout;         // +0x20C
	int              m_field210;        // +0x210
};

// The local address the peer server should see: ask the stack which interface
// reaches 192.168.1.1:79 and read the address back out big-endian.  The two
// byte-at-a-time loops are DirtySock's SockaddrInSetAddr/SockaddrInGetAddr
// macros, which is why the shifts are written into a local rather than kept in
// a register.
struct Rva00804440SockAddr
{
	unsigned short sa_family;
	char           sa_data[ 14 ];
};

unsigned int Rva00804440LocalAddr( void )
{
	Rva00804440SockAddr inet;
	Rva00804440SockAddr host;
	unsigned int work;

	memset( &inet, 0, 16 );
	inet.sa_family = 2;
	inet.sa_data[ 0 ] = 0;
	inet.sa_data[ 1 ] = 0x4F;
	work = 0xC0A80101;
	inet.sa_data[ 5 ] = (char)work; work >>= 8;
	inet.sa_data[ 4 ] = (char)work; work >>= 8;
	inet.sa_data[ 3 ] = (char)work; work >>= 8;
	inet.sa_data[ 2 ] = (char)work;
	memset( &host, 0, 16 );
	Rva007FE310SocketHost( &host, 16, &inet, 16 );
	return ( ( ( ( ( (unsigned char)host.sa_data[ 2 ] << 8 )
			| (unsigned char)host.sa_data[ 3 ] ) << 8 )
			| (unsigned char)host.sa_data[ 4 ] ) << 8 )
			| (unsigned char)host.sa_data[ 5 ];
}

void Rva00804630HttpGet( Rva008042B0Http *http, const char *host, int port,
		const char *url, const char *sessID )
{
	char query[ 0x200 ];

	sprintf( query, "GET %s HTTP/1.1\r\nCookie: sessionID=%s\r\nAccept: */*\r\n"
			"Content-Length: 0\r\nUser-Agent: Custom/1.0\r\nHost: %s\r\n\r\n",
			url, sessID, host );
	Rva008046E0HttpRequest( http, host, port, query );
}

void Rva00804550RequestPeerAddress( Rva00804150ProtoMangleRef *ref )
{
	char strUrl[ 0x100 ];

	sprintf( strUrl, "/getPeerAddress?myIP=%s&myPort=%d&version=1.0",
			Rva007FFB50AddrText( ref->m_localAddr ), ref->m_myPort );
	Rva00804630HttpGet( &ref->m_http, ref->m_server, ref->m_port, strUrl, ref->m_sessID );
	ref->m_field210 = 1;
}

void Rva008043F0Connect( Rva00804150ProtoMangleRef *ref, int myPort, const char *sessID )
{
	ref->m_localAddr = Rva00804440LocalAddr();
	ref->m_myPort = myPort;
	Rva00804250CopyField( ref->m_sessID, sessID, 0x20 );
	Rva00804550RequestPeerAddress( ref );
}

// 0x007FEA00, the no-argument tick forwarder already converted in
// Y4DirtySockSocket.c; ProtoMangleCreate seeds its timeout from it.
unsigned int Rva007FEA00Tick( void );

// ---------------------------------------------------------------- public
// The two bodies retail names itself, moved here out of protomangle.cpp, where
// they were byte lifts rather than source.  Both were readable all along -- a
// lift reproduces the bytes by construction and converts nothing -- and this
// file already carries every struct and callee they need.
extern "C" {

// THE ARGUMENT LIST COMES OUT OF THE LOG LINE, not out of the frame.  Retail's
// own format is "ProtoMangleCreate: Server:%s Port:%d GameID:%s LKey:%s\n" and
// the four stack slots are pushed in exactly that order, so the names and the
// types are retail's rather than address-derived.  Where each one lands
// afterwards agrees: the server string goes to +0x98, the port to +0xB8, the
// game id to +0x38 and the key to +0x58 with a 0x40 bound, which is the only
// field wide enough to be a key.
//
// THE NULL DEREFERENCE IS RETAIL'S AND IS REPRODUCED.  When the sub-object's
// buffer allocation fails, the record is freed and the local set to null -- and
// the very next statement writes the timeout through that null.  A `return 0`
// in the failure arm would be the obvious fix and it is not what the bytes do:
// there is no branch around the store.  It is left exactly as retail has it.
//
// The initial timeout is `tick % 8000 + 2000`, spelled with an unsigned DIV
// because /Od does no strength reduction and the tick is unsigned.
Rva00804150ProtoMangleRef *ProtoMangleCreate( const char *server, int port,
		const char *gameID, const char *lkey )
{
	Rva00804150ProtoMangleRef *ref;

	Rva007FE780Printf( "ProtoMangleCreate: Server:%s Port:%d GameID:%s LKey:%s\n",
			server, port, gameID, lkey );

	ref = (Rva00804150ProtoMangleRef *)Rva007F0000Alloc( 0x214 );
	memset( ref, 0, 0x214 );

	if( Rva008042B0HttpCreate( &ref->m_http, 0x400 ) <= 0 )
	{
		Rva007F0030Free( ref );
		ref = 0;
	}

	ref->m_timeout = Rva007FEA00Tick() % 8000 + 2000;

	Rva00804250CopyField( ref->m_server, server, 0x20 );
	ref->m_port = port;
	Rva00804250CopyField( ref->m_gameID, gameID, 0x20 );
	Rva00804250CopyField( ref->m_lkey, lkey, 0x40 );

	return ref;
}

// Logs "ProtoMangleDestroy: Shutting down\n", then tears the record down in the
// order the bytes give: the record's own socket first -- and only when the two
// pointers at +0x00 and +0x04 disagree -- then the embedded sub-object, then
// the record itself.  The record is handed to the sub-object's socket closer
// unchanged, which is what says the first two words of both objects have the
// same shape.
void ProtoMangleDestroy( Rva00804150ProtoMangleRef *ref )
{
	Rva007FE780Printf( "ProtoMangleDestroy: Shutting down\n" );

	if( ref->m_socket != ref->m_userSocket )
		Rva00804380CloseSocket( (Rva008042B0Http *)ref );

	Rva008043C0HttpDestroy( &ref->m_http );
	Rva007F0030Free( ref );
}

}

// 0x007FDB60, the DirtySock socket query.  0x008053C0 calls it with the
// selector 0x62696E64 -- 'bind' as a multi-character literal, the same
// convention 0x007FDEB0's 'xmap'/'xdns' pair uses -- and a 0x10-byte buffer,
// which is a sockaddr.  The name is address-derived; the selector is evidence.
void Rva007FDB60SocketInfo( void *socket, int selector, void *buffer,
		int bufferSize );  // 0x007FDB60

// 0x008053C0 is the CONNECT entry, and it logs itself: "protomangle: connecting
// with sockref 0x%08x\n".  What it does with that sockref is what names +0x04 --
// it stores the caller's socket there and immediately asks THAT socket for its
// bound address, so the record keeps the caller's socket separately from its
// own.  ProtoMangleDestroy's otherwise puzzling +0x00 versus +0x04 comparison is
// an ownership test once that is known.
//
// THE PORT IS BIG-ENDIAN AND IS READ AS TWO BYTES, not as a swapped short:
// bytes 2 and 3 of the sockaddr are each widened with movzx and folded with a
// shift and an or.  That is the same SockaddrInGetPort spelling 0x00804440 uses
// for the address, and reading it as a short and swapping does not reproduce it.
//
// The frame is 0x1C: cookie, guard, the 0x10 buffer /GZ names `SockAddr`,
// guard.  Nothing else is on the stack.
void Rva008053C0Connect( Rva00804150ProtoMangleRef *ref, void *socket,
		const char *sessID )
{
	char SockAddr[ 0x10 ];

	Rva007FE780Printf( "protomangle: connecting with sockref 0x%08x\n", socket );

	ref->m_localAddr = Rva00804440LocalAddr();
	ref->m_userSocket = socket;

	Rva007FDB60SocketInfo( ref->m_userSocket, 'bind', SockAddr, 0x10 );
	ref->m_myPort = ( (unsigned char)SockAddr[ 2 ] << 8 )
			| (unsigned char)SockAddr[ 3 ];

	Rva00804250CopyField( ref->m_sessID, sessID, 0x20 );
	Rva00804550RequestPeerAddress( ref );
}

// A one-line reader for the sub-object's +0x11C, reached through the record at
// +0x1DC -- 0xC0 + 0x11C, which is what ties the two structs together here.  It
// takes no frame beyond ebp and makes no call, so /GZ leaves it alone; the name
// is address-derived because the field's meaning is not settled anywhere.
int Rva00805610HttpField11C( Rva00804150ProtoMangleRef *ref )
{
	return ref->m_http.m_field11C;
}

// The two callees 0x00805870 needs, both address-derived and both pinned.
// 0x00805710 copies one named tag out of a text blob into a bounded buffer and
// returns negative when the tag is absent; 0x007FFC10 turns a dotted quad into
// an address.
int  Rva00805710TagFieldGet( char *dest, int destSize, const char *text,
		const char *tag, int flags );          // 0x00805710
unsigned int Rva007FFC10TextAddr( const char *text );  // 0x007FFC10

// Called directly through the import stub at 0x009F6DEE rather than through
// __imp__atoi, so this TU did not see <stdlib.h> either.
extern "C" int atoi( const char *text );

// 0x00805870 PARSES THE PEER OUT OF A RESPONSE, and its two tag strings name
// the fields it fills: "peerIP" through the dotted-quad parser into +0x10, and
// "peerPort" through atoi into +0x14.  Neither field had a name before this
// body; both now have retail's own.
//
// THE RETURN IS AN ALL-OR-NOTHING TEST, not a count.  Retail counts the two
// successes into a local and then returns `count == 2` through a sete -- so a
// response carrying only one of the two tags reports failure, and the caller
// cannot tell which half arrived.  A blank address is treated as absent even
// when the tag parsed, which is why the first arm counts only after checking
// the stored value; the port arm has no such check and counts unconditionally.
//
// The frame is 0x30: cookie, guard, the 0x20 buffer /GZ names `strParm`, guard,
// the counter.  strParm is declared first; the other order moves the guarded
// pair and every offset with it.
int Rva00805870ParsePeer( Rva00804150ProtoMangleRef *ref, const char *text )
{
	char strParm[ 0x20 ];
	int count;

	count = 0;

	if( Rva00805710TagFieldGet( strParm, 0x20, text, "peerIP", 0 ) >= 0 )
	{
		ref->m_peerAddr = Rva007FFC10TextAddr( strParm );
		if( ref->m_peerAddr != 0 )
			++count;
	}

	if( Rva00805710TagFieldGet( strParm, 0x20, text, "peerPort", 0 ) >= 0 )
	{
		ref->m_peerPort = atoi( strParm );
		++count;
	}

	return count == 2;
}
