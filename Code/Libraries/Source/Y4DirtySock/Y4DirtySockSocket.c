// cl: /Od /GZ /GS /MD /DNDEBUG

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
	/* TWO LINKS, NOT ONE, and the idle pump at 0x007FD170 is what proves it.
	 * That body walks the list through +0x00, and separately drains a SECOND
	 * list rooted at 0x0130AB5C whose nodes link through +0x04 -- feeding each
	 * one to the same destroyer the socket teardown at 0x007FE210 uses.  So a
	 * socket sits on an active list and a deferred-destroy list at the same
	 * time, through different pointers. */
	struct Rva007FD4E0Socket *m_next;       /* +0x00 */
	struct Rva007FD4E0Socket *m_killNext;   /* +0x04 */
	char m_head[ 0x0E ];            /* +0x08 */
	short m_shutdownFlags;          /* +0x16 */
	unsigned int m_socket;          /* +0x18 */
	char m_gap[ 0x20 ];
	void *m_callback;               /* +0x3C */
	/* THE NEXT FOUR FIELDS ARE RENAMED ON THE STRENGTH OF 0x007FD170, WHICH
	 * REFUTES WHAT THE SETTER AT 0x007FDE80 SUGGESTED.  That setter only
	 * stores, so its parameter order was all the earlier names had to go on.
	 * The pump USES them: +0x40 is compared against a tick count and rewritten
	 * with a fresh one, so it is a timestamp; +0x44 bounds the elapsed delta
	 * with an UNSIGNED compare, so it is a rate; and +0x4C is CALLED, with the
	 * socket, a zero, and +0x48 as its three arguments -- so it is the
	 * callback procedure and +0x48 is its user data.  A field that is called
	 * is not "extra". */
	unsigned int m_lastTick;        /* +0x40 */
	unsigned int m_rate;            /* +0x44 */
	void *m_callbackData;           /* +0x48 */
	void ( __cdecl *m_callbackProc )( struct Rva007FD4E0Socket *socket,
		int reason, void *data );   /* +0x4C */
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

int Rva007FDE80( struct Rva007FD4E0Socket *socket, void *callback,
	unsigned int rate, void *data,
	void ( __cdecl *proc )( struct Rva007FD4E0Socket *, int, void * ) )
{
	socket->m_rate = rate;
	socket->m_callback = callback;
	socket->m_callbackData = data;
	socket->m_callbackProc = proc;
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
__declspec(dllimport) unsigned int __stdcall Rva01358E0CImport( void );

/* RETURNS ITS RESULT.  Nothing in this body shows that -- a forwarder that
 * drops the value and one that returns it compile to the same bytes, because
 * eax already holds it.  The pump at 0x007FD170 is what settles it: it stores
 * this call's eax and then uses it as a tick count, so the forwarder is
 * typed from its CALLER rather than from itself. */
unsigned int Rva007FEA00( void )
{
	return Rva01358E0CImport();
}

/* 0x007FE620: the shutdown drain.  A flag is raised, the worker is pumped until
 * a second flag clears, and the first flag is lowered again.  The 0x32 pushed
 * to the one-argument stdcall import is a 50-unit wait -- a poll interval,
 * which is what makes this a drain rather than a single hand-off.  Both globals
 * and the import are address-derived; the import name never reaches the bytes,
 * since an IAT call site is a DIR32 the gate fills from retail. */
extern int g_Rva012C3CDCDraining;
/* Holds the worker THREAD HANDLE: the startup at 0x007FE520 stores
 * CreateThread's return here, and the drain loops treat non-zero as
 * "worker still running". It is set to 1 first and then overwritten
 * with the handle, so the same word doubles as the running flag. */
extern int g_Rva0130ACB8Thread;

__declspec(dllimport) void __stdcall Rva01358F30Wait( int interval );

void Rva007FEE40( void );

void Rva007FE620( void )
{
	g_Rva012C3CDCDraining = 1;

	while ( g_Rva0130ACB8Thread != 0 )
	{
		Rva007FEE40();
		Rva01358F30Wait( 0x32 );
	}

	g_Rva012C3CDCDraining = 0;
}

/* 0x007FEAA0: reset one list, defaulting to the module's own when handed a null
 * pointer.  TWO stack slots hold what reads as one value because /Od
 * materialises a ternary into a temporary and then assigns it -- the second
 * slot is the compiler's, not a second variable in the source.  The trailing
 * one-argument stdcall import is handed the sub-object at +0xC. */
struct Rva0130AB68List
{
	/* A RECURSIVE LOCK, and the acquire at 0x007FEB00 is what proves each
	 * field. It compares +0x00 against the return of a no-argument import and,
	 * on a match, bumps +0x04 and succeeds without locking anything -- that is
	 * an owner-thread check guarding a recursion count. +0x08 is handed to the
	 * same two-argument probe the socket body at 0x007FE210 uses, and +0x0C to
	 * the enter/init/destroy slots. The release tests +0x04 with an UNSIGNED
	 * `cmp ..,1 / jbe`, so the depth is unsigned. */
	unsigned int m_ownerThread;     /* +0x00 */
	unsigned int m_depth;           /* +0x04 */
	int m_state;                    /* +0x08 */
	char m_body[ 4 ];               /* +0x0C */
};

extern struct Rva0130AB68List g_Rva0130AB68Default;

__declspec(dllimport) void __stdcall Rva01358D0CReset( void *body );

void Rva007FEAA0( struct Rva0130AB68List *list )
{
	struct Rva0130AB68List *node = list ? list : &g_Rva0130AB68Default;

	node->m_state = 0;
	Rva01358D0CReset( node->m_body );
}

/* 0x007FE670: the other half of the shutdown handshake at 0x007FE620.  That one
 * raises the draining flag and pumps while work is pending; this one clears the
 * pending flag and waits for the drain COUNT to fall to zero -- `jle` is a
 * SIGNED test, so the flag at 0x012C3CDC is a count rather than a boolean --
 * before resetting both lists.  Passing null to the reset selects the module's
 * own list, which is why one call has no argument of its own. */
void Rva007FE670( void )
{
	g_Rva0130ACB8Thread = 0;

	while ( g_Rva012C3CDCDraining > 0 )
		Rva01358F30Wait( 1 );

	Rva007FEAA0( 0 );
	Rva007FEAA0( (struct Rva0130AB68List *)&g_Rva0130AC90 );
}

/* 0x007FEA20: the initialiser counterpart of the reset at 0x007FEAA0 -- same
 * null-defaulting selection, but it clears all three head words rather than the
 * count alone, and hands the +0xC sub-object to a DIFFERENT import slot.  One
 * slot initialising what the other tears down is the usual pairing for an
 * embedded lock, though the bytes fix only that the two slots differ. */
__declspec(dllimport) void __stdcall Rva01358E4CInit( void *body );

void Rva007FEA20( struct Rva0130AB68List *list )
{
	struct Rva0130AB68List *node = list ? list : &g_Rva0130AB68Default;

	node->m_ownerThread = 0;
	node->m_depth = 0;
	node->m_state = 0;
	Rva01358E4CInit( node->m_body );
}

/* 0x007FECB0: release one reference.  Above one, the count simply drops; at one
 * or zero the object is cleared and its +0xC sub-object handed to a THIRD
 * import slot -- distinct from both the initialiser's and the reset's, which is
 * what says these bodies touch one embedded object through its own entry
 * points rather than sharing one call.
 *
 * CORRECTION, from the blocking acquire at 0x007FEBD0: that body calls THIS
 * SAME SLOT to give the section back after its probe reports busy, which a
 * destroy could not be.  The slot is a LEAVE, so the last release here is
 * `clear the ownership words and leave`, not `tear the object down`. */
__declspec(dllimport) void __stdcall Rva01358E74Leave( void *body );

void Rva007FECB0( struct Rva0130AB68List *list )
{
	struct Rva0130AB68List *node = list ? list : &g_Rva0130AB68Default;

	if ( node->m_depth > 1 )
	{
		node->m_depth = node->m_depth - 1;
	}
	else
	{
		node->m_ownerThread = 0;
		node->m_depth = 0;
		node->m_state = 0;
		Rva01358E74Leave( node->m_body );
	}
}

/* 0x007FEB00: acquire, and the body that fixes the whole layout.  If the caller
 * already owns the lock the depth simply rises and no locking happens -- that
 * early return is what makes this recursive.  Otherwise the state word is
 * probed through the SAME two-argument import the socket body at 0x007FE210
 * uses, a non-zero answer meaning busy, and only then is the critical section
 * entered and ownership recorded.  Note the owner is re-read from the import
 * AFTER entering rather than reused from the first call: the compiler was given
 * no licence to cache it across the lock. */
__declspec(dllimport) unsigned int __stdcall Rva01358D7CCurrentId( void );
__declspec(dllimport) void __stdcall Rva01358D18Enter( void *body );

int Rva007FEB00( struct Rva0130AB68List *list )
{
	struct Rva0130AB68List *node = list ? list : &g_Rva0130AB68Default;

	if ( node->m_ownerThread == Rva01358D7CCurrentId() )
	{
		node->m_depth = node->m_depth + 1;
		return 1;
	}

	if ( Rva01358E58Probe( &node->m_state, 1 ) )
		return 0;

	Rva01358D18Enter( node->m_body );

	node->m_ownerThread = Rva01358D7CCurrentId();
	node->m_depth = node->m_depth + 1;
	return 1;
}

/* 0x007FEBD0: the blocking acquire built on the try-acquire above.  Each round
 * first attempts the cheap path, then takes the section, and only claims
 * ownership if the state word is still clear; if it is not, the section is
 * given straight back and the thread waits before trying again.  That
 * give-it-back call is what proves slot 0x1358E74 is a leave.
 *
 * One source detail the bytes fix: the try-acquire is called with the RAW
 * PARAMETER, not with the already-defaulted local -- so a null argument is
 * re-defaulted inside the callee on every round, and the loop re-enters at the
 * call rather than at the selection. */
void Rva007FEBD0( struct Rva0130AB68List *list )
{
	struct Rva0130AB68List *node = list ? list : &g_Rva0130AB68Default;

	while ( !Rva007FEB00( list ) )
	{
		Rva01358D18Enter( node->m_body );

		if ( !Rva01358E58Probe( &node->m_state, 1 ) )
		{
			node->m_ownerThread = Rva01358D7CCurrentId();
			node->m_depth = node->m_depth + 1;
			return;
		}

		Rva01358E74Leave( node->m_body );
		Rva01358F30Wait( 1 );
	}
}


/* 0x007FE250: name resolution.  The hostname buffer lives at +0x10 of the
 * request and is handed to a stdcall lookup; on success the FOUR BYTES at
 * offset +0x0C of the returned record are assembled MOST SIGNIFICANT FIRST
 * ((b[0]<<24)|(b[1]<<16)|(b[2]<<8)|b[3]) and stored at +0x04.  That
 * byte-at-a-time big-endian assembly, rather than a dword load, is what says
 * the source is reading a network-order address out of a pointer-to-list at
 * +0x0C -- a dword load would have been one instruction.  Status is 1 on
 * success and -1 on failure, and the tail is the same probe-then-helper pair
 * the socket body at 0x007FE210 ends with. */
struct Rva0081BDEAHostRecord
{
	char m_head[ 0x0C ];
	unsigned char **m_addressList;  /* +0x0C */
};

struct Rva007FE250Request
{
	int m_status;                   /* +0x00, 1 resolved, -1 failed */
	unsigned int m_address;         /* +0x04, host byte order */
	char m_gap[ 8 ];
	char m_hostname[ 0x44 ];        /* +0x10 */
	int m_state;                    /* +0x54, probed like the lock's */
};

struct Rva0081BDEAHostRecord * __stdcall Rva0081BDEA( const char *name );

int Rva007FE250( struct Rva007FE250Request *request )
{
	/* DECLARATION ORDER IS LOAD-BEARING: /Od hands the first-declared local
	 * the slot nearest the frame pointer, and retail puts the byte pointer
	 * there, so it was declared first. */
	unsigned char *bytes;
	struct Rva0081BDEAHostRecord *record;

	record = Rva0081BDEA( request->m_hostname );

	if ( record != 0 )
	{
		bytes = *record->m_addressList;
		request->m_address = ( bytes[ 0 ] << 24 ) | ( bytes[ 1 ] << 16 )
		                   | ( bytes[ 2 ] << 8 ) | bytes[ 3 ];
		request->m_status = 1;
	}
	else
	{
		request->m_status = -1;
	}

	if ( Rva01358E58Probe( &request->m_state, 1 ) )
		Rva007F0030( request );

	return 0;
}

/* 0x007FE520: module startup.  The fifth argument pushed to the six-argument
 * stdcall creator is 0x00BFE620 -- a VIRTUAL address whose RVA is 0x007FE620,
 * the drain loop already converted above -- so this is thread creation and that
 * loop is the worker body.  The frame descriptor /GZ left after this function
 * names the sixth argument's local `pid`, which is retail's own name.
 *
 * The tail is DEAD CODE: `xor ecx,ecx` immediately followed by `je` always
 * jumps, so the call it skips can never run.  That is what a debug print looks
 * like once its guard has folded to a constant zero, and it is reproduced here
 * rather than dropped because the bytes carry it. */
__declspec(dllimport) int __stdcall Rva01358D00CreateWorker(
	void *security, unsigned int stackSize, void *start, void *parameter,
	unsigned int flags, unsigned int *identifier );
__declspec(dllimport) void __stdcall Rva01358F20SetPriority( int thread, int priority );
__declspec(dllimport) void __stdcall Rva01358CCCRelease( int thread );

extern int g_Rva0130ACB4;

void Rva007FE780( void *text );

void Rva007FE520( int priority )
{
	unsigned int pid;

	g_Rva0130ACB4 = 0;
	g_Rva012C3CDCDraining = -1;

	Rva007FEA20( 0 );
	Rva007FEA20( (struct Rva0130AB68List *)&g_Rva0130AC90 );

	g_Rva0130ACB8Thread = 1;
	g_Rva0130ACB8Thread = Rva01358D00CreateWorker( 0, 0, (void *)Rva007FE620,
	                                               0, 0, &pid );

	if ( g_Rva0130ACB8Thread != 0 )
	{
		Rva01358F20SetPriority( g_Rva0130ACB8Thread, priority );
		Rva01358CCCRelease( g_Rva0130ACB8Thread );
	}

	if ( 0 )
		Rva007FE780( (void *)0x12c3ce0 );
}

/* A ROTATING-XOR STRING HASH, and every part of it is legible in the bytes
 * rather than inferred.  Per character: the top five bits of the accumulator
 * are saved off, the accumulator is shifted left by five, the saved bits are
 * brought back in at the bottom by an ARITHMETIC shift right of 27 -- which is
 * what makes the accumulator a SIGNED int rather than unsigned, since a
 * logical shift would have been shr -- and the character is folded in last.
 *
 * The character is read with movsx, so the text is plain `char` and not
 * `unsigned char`; that distinction is visible and therefore not a guess.
 *
 * THE THIRD LOCAL IS REAL, NOT A COMPILER TEMPORARY.  The saved-bits value at
 * -0x0C is written and then read back on the next instruction, which a /Od
 * temporary would also do -- so the frame size is what settles it: three
 * declared locals give exactly the 0x0C frame retail has.
 *
 * The loop is MSVC's ordinary /Od `for` layout: initialisers, a jump forward
 * to the test, the increment sitting BEFORE the test in address order, and the
 * body jumping back to it.  Writing it as a while loop puts the increment
 * after the body instead and does not reproduce these bytes.
 */
int __cdecl Rva007FF080( const char *pText )
{
	int i;
	int uHash;
	int uCarry;

	for ( i = 0, uHash = 0; pText[ i ] != 0; i++ )
	{
		uCarry = uHash & 0xF8000000;
		uHash = uHash << 5;
		uHash = ( uCarry >> 27 ) ^ uHash;
		uHash = pText[ i ] ^ uHash;
	}
	return uHash;
}

/* 0x007FD5C0 is the CONNECT wrapper, and it is the same family as the bind and
 * listen ones above: hand the raw Winsock result to the error translator.  Two
 * things make it longer than its siblings.
 *
 * First, the address is TRANSLATED rather than passed through -- the helper at
 * 0x007FD660 fills a 16-byte scratch buffer and returns a pointer to it, which
 * is what connect actually receives.  Retail's own name for that buffer, taken
 * from the /GZ frame descriptor, is `temp`, and its declared width there is
 * 0x10; neither is a name or a size I chose.
 *
 * Second, a byte at +0x14 is cleared first.  It sits in the same head region
 * the shutdown-flag word occupies, and nothing in THIS body says what it means,
 * so it is left as a byte store into the existing head array rather than given
 * an invented field name.
 *
 * The whole outer expression is one statement: MSVC evaluates arguments
 * right-to-left, so the length is pushed BEFORE the translation helper runs,
 * and the helper's own two arguments are cleaned with `add esp,8` in the middle
 * of connect's argument list.  That interleaving is what the bytes show, and
 * splitting the call across statements does not reproduce it.
 */
int __stdcall connect( unsigned int socket, const void *address,
	int addressLength );

void *Rva007FD660( char *temp, const void *address );

int Rva007FD5C0( struct Rva007FD4E0Socket *socket, const void *address,
	int addressLength )
{
	char temp[ 0x10 ];

	socket->m_head[ 0x14 - 0x08 ] = 0;
	return Rva007FD540( connect( socket->m_socket,
		Rva007FD660( temp, address ), addressLength ) );
}

/* 0x007FDEE0 is a SELF-TEST of the address translator at 0x007FE310, and it
 * says so in constants rather than in shape.  It builds one socket address for
 * 192.168.1.1 port 79 -- 0xC0A80101 is the dotted quad written out, and the
 * port bytes are the folded halves of 0x004F -- pushes it through the
 * translator, and reads the address back out of the result.  Nothing else in
 * the body varies, so the returned value is only interesting when compared
 * against the value that went in.
 *
 * BOTH FRAME NAMES ARE RETAIL'S OWN, from the /GZ descriptor: `inet` and
 * `host`, each 0x10 bytes.  The pair of names is itself the clue to what the
 * translator does -- one side is the network form, the other the library's own.
 *
 * THE BYTE ORDER IS THE EVIDENCE FOR THE LAYOUT.  The address is stored into a
 * local and then shifted right eight bits at a time, LOW byte written to the
 * HIGHEST offset first, which is big-endian placement at +4..+7; the read-back
 * at the end reassembles from +4 down to +7 with movzx, so those bytes are
 * unsigned.  The port at +2..+3 is written high half first and needs no
 * temporary because both halves of a constant fold at compile time.  That
 * difference in spelling between the port and the address is visible in the
 * bytes and is reproduced here rather than tidied up.
 */
struct Rva007FDEE0Addr
{
	short m_family;                 /* +0x00 */
	unsigned char m_data[ 14 ];     /* +0x02 */
};

void *__cdecl memset( void *destination, int value, unsigned int count );

int Rva007FE310( void *host, int hostLength, const void *inet, int inetLength );

int Rva007FDEE0( void )
{
	struct Rva007FDEE0Addr inet;
	struct Rva007FDEE0Addr host;
	unsigned int uAddress;

	memset( &inet, 0, sizeof inet );
	inet.m_family = 2;
	inet.m_data[ 0 ] = (unsigned char)( 0x004F >> 8 );
	inet.m_data[ 1 ] = (unsigned char)0x004F;

	uAddress = 0xC0A80101;
	inet.m_data[ 5 ] = (unsigned char)uAddress;  uAddress >>= 8;
	inet.m_data[ 4 ] = (unsigned char)uAddress;  uAddress >>= 8;
	inet.m_data[ 3 ] = (unsigned char)uAddress;  uAddress >>= 8;
	inet.m_data[ 2 ] = (unsigned char)uAddress;

	memset( &host, 0, sizeof host );
	Rva007FE310( &host, sizeof host, &inet, sizeof inet );

	return ( ( ( ( host.m_data[ 2 ] << 8 ) | host.m_data[ 3 ] ) << 8
		| host.m_data[ 4 ] ) << 8 ) | host.m_data[ 5 ];
}

/* 0x007FD170 is the IDLE PUMP, and it is the body that gave the socket struct
 * above its real field names.  It does three things under one lock: fire any
 * socket whose callback is due, drain the deferred-destroy list, unlock.
 *
 * A callback is due only if all four guards pass, and each is a separate fact
 * about the object: a rate is set, a procedure is installed, the timestamp is
 * not the in-progress sentinel -1, and the elapsed time exceeds the rate.  The
 * elapsed comparison is `jbe`, i.e. UNSIGNED, which is what makes the
 * subtraction wrap correctly across a tick-counter rollover -- so the tick
 * source and both fields are unsigned, and that is read from the bytes.
 *
 * THE SENTINEL IS THE INTERESTING PART.  The timestamp is set to -1 BEFORE the
 * callback runs and to a FRESH tick count after, not to the tick count taken at
 * the top.  Both details are load-bearing: -1 makes the entry ineligible for
 * the duration of the call, which is what keeps a re-entrant pump from firing
 * the same socket twice, and re-reading the clock afterwards means the rate
 * measures the gap BETWEEN calls rather than including the call itself.
 *
 * The second loop links through +0x04 rather than +0x00 and hands each node to
 * the same destroyer the socket teardown uses -- a deferred-free list, drained
 * inside the lock so nothing can be resurrected while it empties.
 */
extern struct Rva007FD4E0Socket *g_Rva0130AB5CKillList;

void Rva007FD170( struct Rva007FD4E0Socket *head )
{
	struct Rva007FD4E0Socket *pSocket;
	struct Rva007FD4E0Socket *pList;
	unsigned int uTick;

	pList = head;
	uTick = Rva007FEA00();
	Rva007FEBD0( 0 );

	for ( pSocket = pList->m_next; pSocket != 0; pSocket = pSocket->m_next )
	{
		if ( pSocket->m_rate != 0 && pSocket->m_callbackProc != 0
			&& pSocket->m_lastTick != 0xFFFFFFFF
			&& uTick - pSocket->m_lastTick > pSocket->m_rate )
		{
			pSocket->m_lastTick = 0xFFFFFFFF;
			pSocket->m_callbackProc( pSocket, 0, pSocket->m_callbackData );
			uTick = Rva007FEA00();
			pSocket->m_lastTick = uTick;
		}
	}

	while ( ( pSocket = g_Rva0130AB5CKillList ) != 0 )
	{
		g_Rva0130AB5CKillList = pSocket->m_killNext;
		Rva007F0030( pSocket );
	}

	Rva007FECB0( 0 );
}
