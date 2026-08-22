// cl: /Od /GZ /MD /DNDEBUG

/* EA DirtySock ("DirtySDK") -- Windows socket layer, dirtynetwin.c.
 *
 * WHAT THIS RANGE IS.  0x007FD080..0x007FEF60 is NOT the FESL/jabba C++ SDK
 * that occupies 0x007F96C0..0x007FCF80; it is a separate C library linked into
 * the same image, and it was built WITHOUT OPTIMISATION.  Three independent
 * tells agree:
 *   - every body opens `push ebp / mov ebp,esp` and fills its locals with
 *     0xCCCCCCCC, and every one that makes a call ends `cmp ebp,esp` followed
 *     by a call to the MSVC 7.1 stack-check helper at 0x009F7502 (__chkesp);
 *     that is /Od plus /GZ, and it is why this file carries its own
 *     `// cl: /Od /GZ /MD` directive instead of the tree default /O2;
 *   - the only string literal reachable from the span is
 *     "dirtynetwin: addr remap %s" at 0x007FD660, which names DirtySock's
 *     Windows socket module by its own source file name;
 *   - 0x007FDEB0 dispatches on the un-relocated imm32s 0x786D6170 and
 *     0x78646E73, i.e. the multi-character literals 'xmap' and 'xdns' -- the
 *     DirtySock SocketControl selector convention.
 * None of that is shape: it is strings, immediates and a compiler-flag
 * signature.
 *
 * The socket object's member OFFSETS below (+0x16, +0x18, +0x3C..+0x4C) are
 * immediates and are hard evidence; the C member names are address-derived.
 * This lane may not add a .h file, so the struct and the two Winsock
 * prototypes are declared here.
 */

int __stdcall shutdown( unsigned int socket, int how );

struct Rva007FD4E0Socket
{
	char m_head[ 0x16 ];
	short m_shutdownFlags;          /* +0x16 */
	unsigned int m_socket;          /* +0x18 */
	char m_gap[ 0x20 ];
	void *m_callback;               /* +0x3C */
	char m_gap2[ 0x04 ];
	void *m_callbackRef;            /* +0x44 */
	void *m_callbackData;           /* +0x48 */
	void *m_callbackExtra;          /* +0x4C */
};

/* The 'xmap' remap table head and the 'xdns' value, both set through
 * 0x007FDEB0 and read back by the remap walk at 0x007D660. */
void *g_Rva0130AB60;
int g_Rva0130AB64;

int Rva007FD4E0( struct Rva007FD4E0Socket *socket, int how )
{
	socket->m_shutdownFlags |= how;
	shutdown( socket->m_socket, how );
	return 0;
}

int Rva007FDE80( struct Rva007FD4E0Socket *socket, void *callback, void *ref,
	void *data, void *extra )
{
	socket->m_callbackRef = ref;
	socket->m_callback = callback;
	socket->m_callbackData = data;
	socket->m_callbackExtra = extra;
	return 0;
}

int Rva007FDEB0( int control, int value, void *pointer )
{
	if( control == 'xmap' )
		g_Rva0130AB60 = pointer;
	if( control == 'xdns' )
		g_Rva0130AB64 = value;
	return -1;
}

int Rva007FE200( const int *p )
{
	return *p;
}

/* Bounded string compare.  A NEGATIVE length selects the unbounded form, which
 * is why there are two separate loops rather than one; both operands are read
 * with `movzx`, so they are UNSIGNED char -- hard evidence, and it is what
 * makes the returned difference non-negative for high-bit bytes. */
int Rva007FE6C0( const char *string1, const char *string2, int length )
{
	int difference;
	const unsigned char *p1;
	const unsigned char *p2;

	p1 = (const unsigned char *)string1;
	p2 = (const unsigned char *)string2;
	if( length < 0 )
	{
		for( ; *p1 != 0; p1++, p2++ )
		{
			if( *p1 != *p2 )
				return *p1 - *p2;
		}
		return 0;
	}
	for( ; length > 0; p1++, p2++, length-- )
	{
		difference = *p1 - *p2;
		if( difference != 0 )
			return difference;
	}
	return 0;
}

/* The idle-callback table: pairs of { function, ref } at 0x0130AB90 with the
 * used count at 0x0130ACB4.  The 8-byte stride is an immediate (`[i*8 + base]`
 * and `[i*8 + base + 4]`) and is hard evidence for the pair layout. */
struct Rva0130AB90Entry
{
	void *m_function;
	void *m_ref;
};

struct Rva0130AB90Entry g_Rva0130AB90[ 64 ];
int g_Rva0130ACB4;

void Rva007FED40( void *function, void *ref )
{
	if( function == 0 || ref == 0 )
		return;
	g_Rva0130AB90[ g_Rva0130ACB4 ].m_function = function;
	g_Rva0130AB90[ g_Rva0130ACB4 ].m_ref = ref;
	g_Rva0130ACB4++;
}

void Rva007FED90( void *function, void *ref )
{
	int index;

	if( function == 0 || ref == 0 )
		return;
	for( index = 0; index < g_Rva0130ACB4; index++ )
	{
		if( g_Rva0130AB90[ index ].m_function == function &&
			g_Rva0130AB90[ index ].m_ref == ref )
		{
			g_Rva0130AB90[ index ].m_function = 0;
			g_Rva0130AB90[ index ].m_ref = 0;
			break;
		}
	}
}

/* Winsock wrappers.  Both hand the raw return straight to the shared error
 * translator at 0x007FD540, which is why the call is nested rather than
 * sequenced -- there is no intermediate store. */
int __stdcall bind( unsigned int socket, const void *address, int addressLength );
int __stdcall listen( unsigned int socket, int backlog );

int Rva007FD540( int result );

int Rva007FD510( struct Rva007FD4E0Socket *socket, const void *address,
	int addressLength )
{
	return Rva007FD540( bind( socket->m_socket, address, addressLength ) );
}

int Rva007FD7A0( struct Rva007FD4E0Socket *socket, int backlog )
{
	return Rva007FD540( listen( socket->m_socket, backlog ) );
}

/* Idle-list teardown: the same global list head is handed to both halves. */
extern int g_Rva0130AC90;

void Rva007FEBD0( void *list );
void Rva007FECB0( void *list );

void Rva007FEE10( void )
{
	Rva007FEBD0( &g_Rva0130AC90 );
	Rva007FECB0( &g_Rva0130AC90 );
}

long __cdecl time( long *destination );

void Rva007FEF60( void )
{
	time( 0 );
}

/* Module shutdown at 0x007FD270.  The first call takes a FUNCTION POINTER:
 * the pushed immediate 0x00BFD170 is a virtual address, and its RVA is
 * 0x007FD170 -- the per-socket destroy helper called directly further down.
 * So the module registers its own destroyer, drains the list head until it is
 * empty, then tears the head down itself.  The trailing call is an import
 * thunk the ledger already names.  Every name here is address-derived. */
extern void *g_Rva0130AB58Head;

void Rva007FD3F0( void *socket );
void Rva007FD170( void *head );
void Rva007FE670( void );
void Rva0081BDE4( void );

void Rva007FD270( void )
{
	Rva007FED90( (void *)Rva007FD170, &g_Rva0130AB58Head );
	Rva007FEE10();

	while ( g_Rva0130AB58Head != 0 )
		Rva007FD3F0( g_Rva0130AB58Head );

	Rva007FD170( &g_Rva0130AB58Head );
	Rva007FE670();
	Rva0081BDE4();
}

/* Winsock error translation at 0x007FD540, already forward-declared above and
 * called by the bind and listen wrappers.  A negative return means the Winsock
 * call failed, so the real code is fetched and mapped onto this library's own
 * small negative vocabulary.  THE IMMEDIATES ARE THE EVIDENCE: 0x2733 10035
 * WSAEWOULDBLOCK, 0x2746 10054 WSAECONNRESET, 0x2743 10051 WSAENETUNREACH,
 * 0x2751 10065 WSAEHOSTUNREACH, 0x2749 10057 WSAENOTCONN and 0x274D 10061
 * WSAECONNREFUSED -- a contiguous run of the WSAE* block, which is what says
 * this is an errno mapper rather than an ordinary switch.  The pairs that share
 * a result share an `if`: would-block and connection-reset both report success,
 * which is this library's convention rather than anything the bytes explain. */
int Rva0081BE08( void );

int Rva007FD540( int result )
{
	if ( result < 0 )
	{
		result = Rva0081BE08();

		if ( result == 10035 || result == 10054 )
			result = 0;
		else if ( result == 10051 || result == 10065 )
			result = -5;
		else if ( result == 10057 )
			result = -2;
		else if ( result == 10061 )
			result = -6;
		else
			result = -7;
	}

	return result;
}

/* 0x007FE210.  The call is `ff 15` through an IAT slot, i.e. a __declspec
 * (dllimport) __stdcall taking two arguments -- nothing is popped afterwards.
 * THE IMPORT'S NAME NEVER REACHES THESE BYTES: an IAT call site is a DIR32
 * relocation and the gate fills those four bytes from retail, so the name below
 * is address-derived on purpose and asserts nothing about which API this is.
 * What the bytes do fix is the shape: a two-argument stdcall probe over a
 * sub-object at +0x54 that, when it reports non-zero, hands the whole object to
 * a one-argument cdecl helper. */
__declspec(dllimport) int __stdcall Rva01358E58Probe( void *object, int flag );

void Rva007F0030( void *object );

void Rva007FE210( void *object )
{
	if ( Rva01358E58Probe( (char *)object + 0x54, 1 ) )
		Rva007F0030( object );
}

/* 0x007FEA00: a bare forwarder onto a no-argument stdcall import.  Nothing but
 * the /GZ esp check surrounds it. */
__declspec(dllimport) void __stdcall Rva01358E0CImport( void );

void Rva007FEA00( void )
{
	Rva01358E0CImport();
}

/* 0x007FE620: the shutdown drain.  A flag is raised, the worker is pumped until
 * a second flag clears, and the first flag is lowered again.  The 0x32 pushed
 * to the one-argument stdcall import is a 50-unit wait -- a poll interval,
 * which is what makes this a drain rather than a single hand-off.  Both globals
 * and the import are address-derived; the import name never reaches the bytes,
 * since an IAT call site is a DIR32 the gate fills from retail. */
extern int g_Rva012C3CDCDraining;
extern int g_Rva0130ACB8Pending;

__declspec(dllimport) void __stdcall Rva01358F30Wait( int interval );

void Rva007FEE40( void );

void Rva007FE620( void )
{
	g_Rva012C3CDCDraining = 1;

	while ( g_Rva0130ACB8Pending != 0 )
	{
		Rva007FEE40();
		Rva01358F30Wait( 0x32 );
	}

	g_Rva012C3CDCDraining = 0;
}
