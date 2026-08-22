// cl: /DNDEBUG /MD /GX /Od /GZ /GS
// Another module in the 0x00806480..0x00806B10 span, carrying the same /Od /GZ
// signature as the rest of this directory -- a frame pointer for code with no
// register pressure and `cmp ebp,esp` into the stack-check helper at 0x009F7502.
// Nothing in these four bodies names it: there is no string and no selector, so
// the file name and every function name are derived from addresses and assert
// nothing.  What the bodies DO show is that they share one record layout, which
// is why they share a file.

// 0x0080B070, the teardown all three destructors here hand the record's first
// pointer to; address-derived and pinned.
void Rva0080B070Destroy( void *object );

// 0x007F0030, the one-argument release the rest of this directory uses.
void Rva007F0030Free( void *block );

// An import thunk the ledger already names; the C spelling is what this call
// site needs.
extern "C" void Rva0081BDE4( void );

__declspec(dllimport) void __stdcall Rva01358F30Sleep( unsigned int ms );

// The two byte swaps in Y4DirtySock's range and the reset at 0x0080DFC0.
unsigned short Rva007FFA60Swap16( unsigned short value );   // 0x007FFA60
unsigned int   Rva007FFAD0( unsigned int value );           // 0x007FFAD0
// The second argument is a KEY POINTER, not a flag: 0x00806710 passes the
// 0x20-byte Secret it just derived, and 0x00806A90 passes null.
void Rva0080DFC0( void *object, const void *secret );        // 0x0080DFC0
int  Rva0080DF70( const char *key, char *secret, char *ticket ); // 0x0080DF70
extern "C" char *strncpy( char *dest, const char *src, unsigned int count );
extern "C" void *memcpy( void *dest, const void *src, unsigned int count );
extern "C" void *memset( void *dest, int value, unsigned int count );
void *Rva007F0000Alloc( int size );                         // 0x007F0000
unsigned short Rva007FF990Swap16( unsigned short value );   // 0x007FF990
unsigned int   Rva007FF9F0Swap32( unsigned int value );     // 0x007FF9F0
void *Rva0080B000Create( void );                            // 0x0080B000
int   Rva0080B150( void *object, void *addr, int addrLen );  // 0x0080B150
int   Rva0080B460( void *object, int mode );                // 0x0080B460
struct Rva00806580Record;
int   Rva00807370( Rva00806580Record *record, int selector, int flag,
		char *buffer, int bufferSize );                     // 0x00807370
unsigned int Rva007FEA00Tick( void );                       // 0x007FEA00

// The tick this module first ran at, filled in once and never again.
extern unsigned int g_Rva0130ACDCEpoch;

// Declared here rather than included: retail reaches WSAStartup by a direct
// rel32 to the stub at 0x0081BDF6, which a <winsock2.h> declaration's dllimport
// would not produce.  Only the first field is ever read, but the SIZE is
// load-bearing -- 0x190 is what the frame is built around.
struct Rva008064A0WsaData
{
	unsigned short wVersion;
	unsigned short wHighVersion;
	char szDescription[ 257 ];
	char szSystemStatus[ 129 ];
	unsigned short iMaxSockets;
	unsigned short iMaxUdpDg;
	char *lpVendorInfo;
};

extern "C" int __stdcall WSAStartup( unsigned short versionRequested,
		Rva008064A0WsaData *data );

// Only the five offsets these bodies touch are evidence.  +0x00 is a sub-object
// with its own teardown, +0x70 and +0x7C are plain blocks, +0x5C takes a state
// constant and +0x8C a boolean.  Everything between is padding and names nothing.
struct Rva00806580Record
{
	void *m_field00;             // +0x00
	// +0x04..+0x13 IS A SOCKADDR: 0x00806910 memsets exactly 0x10 bytes from
	// +0x04, writes 2 into the first word, and fills the next two fields from
	// its own address and port arguments through the byte swaps.
	short m_family;              // +0x04
	short m_port;                // +0x06 -- 'port', swapped back on the way out
	int   m_addr;                // +0x08 -- 'addr', likewise
	char  m_pad0C[ 0x08 ];
	int   m_localAddr;           // +0x14 -- 'ladr', returned raw
	int   m_localPort;           // +0x18 -- 'lprt', returned raw
	// A 0x3F-byte name with its own terminator: 0x00806710 strncpy's 0x3F bytes
	// here and then writes a zero at +0x5B, which is exactly +0x1C plus 0x3F.
	char  m_name[ 0x40 ];        // +0x1C
	int   m_field5C;             // +0x5C -- 'stat'
	int   m_field60;             // +0x60
	int   m_field64;             // +0x64 -- 'obuf' is +0x64 minus +0x68
	int   m_field68;             // +0x68
	char  m_pad6C[ 0x04 ];
	void *m_field70;             // +0x70
	int   m_field74;             // +0x74 -- 'ibuf' is +0x74 minus +0x78
	int   m_field78;             // +0x78
	void *m_field7C;             // +0x7C -- gates 'ibuf'
	char  m_pad80[ 0x0C ];
	short m_field8C;             // +0x8C -- 'secu', read SIGNED
	short m_field8E;             // +0x8E -- set by 0x00806A90
	char  m_key[ 0x54 ];         // +0x90
	int   m_fieldE4;             // +0xE4 -- 'cryp'; 0x90 + 0x54 lands exactly here
};

// 0x00806580 IS THE FULL TEARDOWN and the sleep in the middle is the whole
// story: it tears the sub-object down, WAITS 50 MILLISECONDS, calls an import,
// and only then frees the two blocks and the record.  A destructor that has to
// pause before releasing memory is waiting for something else to stop touching
// it -- the sub-object almost certainly owns a thread -- and the pause is
// unconditional, taken even when there was no sub-object to tear down.
//
// The record's own pointer is NOT nulled on the way out, unlike in the two
// bodies below; nothing can read it again, because the record is freed.
void Rva00806580( Rva00806580Record *record )
{
	if( record->m_field00 != 0 )
		Rva0080B070Destroy( record->m_field00 );

	Rva01358F30Sleep( 50 );
	Rva0081BDE4();

	if( record->m_field7C != 0 )
		Rva007F0030Free( record->m_field7C );

	if( record->m_field70 != 0 )
		Rva007F0030Free( record->m_field70 );

	Rva007F0030Free( record );
}

// 0x008068B0 and 0x00806A10 ARE BYTE-IDENTICAL apart from the displacements of
// their own two calls, and retail carries both.  That is not identical-code
// folding failing: folding would have left ONE body and two names pointing at
// it, and these are two bodies at two addresses.  So the source really does say
// this twice, and it is written out twice here rather than aliased.
//
// Both are the partial reset the full teardown above is the destructive form of:
// same sub-object, same +0x70 block, but each pointer is NULLED after release
// and the record survives with its state set to 4.
int Rva008068B0( Rva00806580Record *record )
{
	if( record->m_field00 != 0 )
	{
		Rva0080B070Destroy( record->m_field00 );
		record->m_field00 = 0;
	}

	if( record->m_field70 != 0 )
	{
		Rva007F0030Free( record->m_field70 );
		record->m_field70 = 0;
	}

	record->m_field5C = 4;
	return 0;
}

int Rva00806A10( Rva00806580Record *record )
{
	if( record->m_field00 != 0 )
	{
		Rva0080B070Destroy( record->m_field00 );
		record->m_field00 = 0;
	}

	if( record->m_field70 != 0 )
	{
		Rva007F0030Free( record->m_field70 );
		record->m_field70 = 0;
	}

	record->m_field5C = 4;
	return 0;
}

// 0x00806A70 stores a comparison, not its argument: the flag at +0x8C is set
// only when the value handed in is exactly 1, and it is stored SIXTEEN BITS
// WIDE.  Any other value -- including 2 -- clears it.
void Rva00806A70( Rva00806580Record *record, int value )
{
	record->m_field8C = (short)( value == 1 );
}

// 0x00806600 IS THE RECORD'S QUERY, and nine multi-character selectors are what
// say so -- 'port', 'addr', 'ladr', 'lprt', 'obuf', 'ibuf', 'stat', 'secu' and
// 'cryp', the same convention 0x007FDEB0's 'xmap'/'xdns' and 0x008053C0's
// 'bind' use.  They also name most of the layout above: two of them come back
// byte-swapped and two do not, which is what separates the wire-order pair at
// +0x06 and +0x08 from the host-order pair at +0x14 and +0x18.
//
// THE TWO BUFFER SELECTORS ARE DIFFERENCES, NOT FIELDS: 'obuf' is +0x64 minus
// +0x68 and 'ibuf' is +0x74 minus +0x78, so each pair is a write cursor and a
// read cursor and the answer is how much is pending.  'ibuf' is additionally
// gated on +0x7C and reports 0 when that is null -- the only arm here that
// needs a local, which is why the frame is four bytes.
//
// IT IS AN IF-CHAIN, NOT A SWITCH.  Each test is followed by its own body and a
// jump to the epilogue before the next test; a switch groups every comparison
// first.  'secu' is read with MOVSX, so that field is a signed short, and an
// unrecognised selector returns 0 rather than an error.
int Rva00806600( Rva00806580Record *record, int selector )
{
	int pending;

	if( selector == 'port' )
		return Rva007FFA60Swap16( record->m_port );
	if( selector == 'addr' )
		return Rva007FFAD0( record->m_addr );
	if( selector == 'ladr' )
		return record->m_localAddr;
	if( selector == 'lprt' )
		return record->m_localPort;
	if( selector == 'obuf' )
		return record->m_field64 - record->m_field68;
	if( selector == 'ibuf' )
	{
		if( record->m_field7C != 0 )
			pending = record->m_field74 - record->m_field78;
		else
			pending = 0;
		return pending;
	}
	if( selector == 'stat' )
		return record->m_field5C;
	if( selector == 'secu' )
		return record->m_field8C;
	if( selector == 'cryp' )
		return record->m_fieldE4;

	return 0;
}

// 0x00806A90 INSTALLS A 0x54-BYTE KEY, and 0x54 is not an arbitrary size: the
// body at 0x00806710 in this same span has /GZ locals named Secret[0x20] and
// Ticket[0x34], and 0x20 + 0x34 is exactly 0x54.  So what lands at +0x90 is
// that pair, and the flag at +0x8E records whether it is there.
//
// THE GUARD IS WRITTEN NEGATIVELY and that is what puts the clearing arm first:
// null, or zero length, or any length that is not 0x54, all take it.  A length
// test that both rejects zero AND demands 0x54 is redundant in its first half,
// and the redundancy is retail's.
//
// The key pointer is copied into a local before the guard runs and the copy is
// what the memcpy reads; and the clearing arm resets the sub-object at +0xE4,
// which is the same field 'cryp' reports, so installing no key tears the
// crypto state down rather than leaving it stale.
void Rva00806A90( Rva00806580Record *record, const void *key, int length )
{
	const void *p;

	p = key;

	if( key == 0 || length == 0 || length != 0x54 )
	{
		record->m_field8E = 0;
		Rva0080DFC0( &record->m_fieldE4, 0 );
	}
	else
	{
		record->m_field8E = 1;
		memcpy( record->m_key, p, 0x54 );
	}
}

// 0x008064A0 MAKES THE RECORD, and it is the counterpart of the teardown at
// 0x00806580: 0x2F0 bytes, zeroed, with the same three fields the resets touch
// set explicitly afterwards.  0x2F0 is also what fixes the layout's tail --
// +0xE4 is well inside it.
//
// WINSOCK IS STARTED FIRST AND ITS FAILURE IS FATAL, before anything is
// allocated, so a caller that gets null back has leaked nothing.  The version
// word it comes back with is DISCARDED here, unlike at 0x007FD080 where the
// same call's answer is byte-swapped and kept -- this module only cares that it
// worked.
//
// The epoch at 0x0130ACDC is stamped only if it is still zero, so the first
// record made in the process fixes it for every later one.
//
// THE THREE EXPLICIT ZEROES ARE REDUNDANT AFTER THE memset and they are
// retail's: +0x00, +0x5C and the 16-bit +0x8E are written again with the values
// the memset already left there.  Dropping them drops three stores.
Rva00806580Record *Rva008064A0( void )
{
	Rva00806580Record *record;
	Rva008064A0WsaData wsadata;

	if( WSAStartup( 2, &wsadata ) != 0 )
		return 0;

	if( g_Rva0130ACDCEpoch == 0 )
		g_Rva0130ACDCEpoch = Rva007FEA00Tick();

	record = (Rva00806580Record *)Rva007F0000Alloc( 0x2F0 );
	if( record != 0 )
	{
		memset( record, 0, 0x2F0 );
		record->m_field00 = 0;
		record->m_field5C = 0;
		record->m_field8E = 0;
	}

	return record;
}

// 0x00806910 IS THE OPEN, and the pairing is what reads it: it builds the
// sockaddr in the record, makes the sub-object with 0x0080B000 -- the
// constructor matching the 0x0080B070 teardown the three destructors above all
// call -- and then configures it twice before declaring the record ready.
//
// IT REFUSES TO RUN TWICE.  A record that already has a sub-object is rejected
// outright, so this is an open and not a reconnect; the reset at 0x008068B0 is
// what has to run in between.
//
// The address and port arrive in host order and are swapped in, which is the
// mirror of 'addr' and 'port' swapping them back out at 0x00806600 -- the
// record stores them the way the wire wants them.  The port argument is loaded
// SIXTEEN BITS WIDE at the call, so it is a short parameter and not a
// truncated int.
//
// EVERY FAILURE RETURNS -1 AND LEAVES THE SUB-OBJECT IN PLACE.  Neither
// configuration failure tears down what 0x0080B000 just built, so the caller
// must run a reset before trying again -- and the second attempt would then hit
// the refusal at the top if it did not.
int Rva00806910( Rva00806580Record *record, unsigned int addr,
		unsigned short port )
{
	if( record->m_field00 != 0 )
		return -1;

	if( record->m_field7C != 0 )
	{
		Rva007F0030Free( record->m_field7C );
		record->m_field7C = 0;
	}

	memset( &record->m_family, 0, 0x10 );
	record->m_family = 2;
	record->m_addr = Rva007FF9F0Swap32( addr );
	record->m_port = Rva007FF990Swap16( port );

	record->m_field00 = Rva0080B000Create();
	if( record->m_field00 == 0 )
		return -1;

	if( Rva0080B150( record->m_field00, &record->m_family, 0x10 ) < 0 )
		return -1;

	if( Rva0080B460( record->m_field00, 2 ) < 0 )
		return -1;

	record->m_field5C = 1;
	record->m_field60 = 0;
	record->m_field8E = 0;
	return 0;
}

// 0x00806710 IS THE SECURE OPEN, and it is 0x00806910 with a key step bolted
// on: the same refusal when a sub-object already exists, the same +0x7C
// release, the same 0x10-byte sockaddr built from swapped arguments.  What it
// adds is a name and, when a key was installed, a derivation.
//
// THE NAME FIELD SIZES ITSELF: 0x3F bytes are copied to +0x1C and a zero is
// then written at +0x5B, which is exactly +0x1C plus 0x3F.  strncpy does not
// terminate when it fills, so that store is the terminator and the field is
// 0x40 wide.  A null name is skipped entirely, terminator included, which
// leaves whatever was there before.
//
// THE KEY STEP IS GATED ON THE FLAG 0x00806A90 SETS, read with MOVSX from
// +0x8E.  It derives a 0x20-byte Secret and a 0x34-byte Ticket from the stored
// key -- 0x20 plus 0x34 is the 0x54 that key is -- then hands the Ticket to the
// selector 0x3F746963, '?tic', and the Secret to the crypto sub-object at
// +0xE4.  A derivation that does not report a positive result clears the flag,
// so the record falls back to unsecured rather than failing the open.
//
// Unlike 0x00806910 this body never makes a sub-object of its own: it requires
// one to be absent and then leaves it absent, which is what separates the two.
int Rva00806710( Rva00806580Record *record, const char *name, unsigned int addr,
		unsigned short port )
{
	char Secret[ 0x20 ];
	char Ticket[ 0x34 ];

	if( record->m_field00 != 0 )
		return -1;

	if( record->m_field7C != 0 )
	{
		Rva007F0030Free( record->m_field7C );
		record->m_field7C = 0;
	}

	memset( &record->m_family, 0, 0x10 );
	record->m_family = 2;
	record->m_addr = Rva007FF9F0Swap32( addr );
	record->m_port = Rva007FF990Swap16( port );

	if( name != 0 )
	{
		strncpy( record->m_name, name, 0x3F );
		record->m_name[ 0x3F ] = 0;
	}

	record->m_field5C = 2;
	record->m_field60 = 0;
	record->m_field8C = 0;

	if( record->m_field8E != 0 )
	{
		if( Rva0080DF70( record->m_key, Secret, Ticket ) > 0 )
		{
			Rva00807370( record, '?tic', 0, Ticket, 0x34 );
			Rva0080DFC0( &record->m_fieldE4, Secret );
		}
		else
		{
			record->m_field8E = 0;
		}
	}

	return 0;
}
