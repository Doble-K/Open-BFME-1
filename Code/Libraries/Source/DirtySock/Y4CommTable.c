// cl: /Od /GZ /GS /MD /DNDEBUG
/* EA DirtySock -- the comm layer's entry table and its lookup, /Od with /GZ.
 * Placement is by address neighbourhood within the 0x00810000 group.
 */

/* One table entry, 0x1A4 bytes.  Only the fields the lookup touches are named;
 * the rest is gap, because nothing here reads it and guessing would be worse
 * than admitting the gap. */
struct Rva00812220Entry
{
	char m_gap0[ 0x08 ];
	char m_nameA[ 0x20 ];			/* +0x08 */
	char m_nameB[ 0x16C ];			/* +0x28, empty means a free slot */
	int m_value;				/* +0x194, zero means not ready */
	int m_extra;				/* +0x198 */
	int m_pending;				/* +0x19C, non-zero means skip */
	char m_gap1A0[ 4 ];
};

struct Rva00812220Table
{
	char m_gap0[ 0x28 ];
	struct Rva00812220Entry *m_first;	/* +0x28 */
	struct Rva00812220Entry *m_end;		/* +0x2C */
};

/* 0x00811CE0 COMPARES TWO STRINGS IGNORING ASCII CASE, folding with XOR 0x20
 * on the range 'A'..'Z' only -- so it is ASCII case-insensitive and nothing
 * more; no table, no locale, and bytes above 0x7F are compared exactly.
 *
 * IT IS A DO-WHILE, so it always reads and folds ONE CHARACTER FROM EACH SIDE
 * before testing anything.  Two empty strings therefore still cost a full
 * iteration, and -- more to the point -- BOTH pointers are advanced past their
 * terminators before the loop can end.  The caller never sees that, since the
 * pointers are its own copies, but it means neither string may be at the very
 * end of a mapped page.
 */
int Rva00811CE0( const char *a, const char *b )
{
	int iDiff;
	char cA;
	char cB;

	do
	{
		cA = *a;
		a++;

		if ( cA >= 'A' && cA <= 'Z' )
		{
			cA ^= 0x20;
		}

		cB = *b;
		b++;

		if ( cB >= 'A' && cB <= 'Z' )
		{
			cB ^= 0x20;
		}

		iDiff = cA - cB;
	}
	while ( cA != 0 && iDiff == 0 );

	return iDiff;
}

/* 0x00812220 FINDS AN ENTRY MATCHING UP TO TWO NAMES and returns its value,
 * or the caller's default if nothing matches.
 *
 * EITHER NAME MAY BE OMITTED, and omitted means "matches anything" rather than
 * "matches empty": a null or empty argument skips that comparison entirely.
 * With both omitted this returns the first ready entry, which makes the same
 * function a lookup and a "give me any" query depending only on its arguments.
 *
 * THE TWO COMPARISONS PASS THEIR ARGUMENTS IN OPPOSITE ORDERS -- the first as
 * (key, entry) and the second as (entry, key).  It cannot matter to the result
 * because the comparator is symmetric about zero and only the zero case is
 * tested, but the asymmetry is real and is in the bytes.
 *
 * FOUR SEPARATE CONDITIONS SKIP AN ENTRY and they are not interchangeable: an
 * empty second name means the slot is free, a non-zero pending flag means it
 * is in flight, a zero value means it is not ready, and a name mismatch means
 * it is someone else's.  All four continue silently, so a caller that gets the
 * default back cannot tell which of the four applied -- or that the table was
 * null, which returns the default too.
 */
int Rva00812220( struct Rva00812220Table *table, const char *keyA,
	const char *keyB, int *pExtra, int iDefault )
{
	struct Rva00812220Entry *p;

	if ( table == 0 )
	{
		return iDefault;
	}

	for ( p = table->m_first; p != table->m_end; p++ )
	{
		if ( p->m_nameB[ 0 ] == 0 )
		{
			continue;
		}

		if ( p->m_pending != 0 )
		{
			continue;
		}

		if ( keyA != 0 && *keyA != 0 && Rva00811CE0( keyA, p->m_nameA ) != 0 )
		{
			continue;
		}

		if ( keyB != 0 && *keyB != 0 && Rva00811CE0( p->m_nameB, keyB ) != 0 )
		{
			continue;
		}

		if ( p->m_value == 0 )
		{
			continue;
		}

		if ( pExtra != 0 )
		{
			*pExtra = p->m_extra;
		}

		iDefault = p->m_value;
		break;
	}

	return iDefault;
}

struct Rva007FD4E0Socket;

/* The module's owning object, 0x50 bytes.  Only the fields this file touches
 * are named; the first 0x28 stay gap because nothing here reads them.  THE
 * TABLE THE LOOKUP WALKS IS THIS OBJECT -- 0x00812220 takes the same pointer
 * and reads the same two fields, so the "table" and the "module" are one
 * allocation and the split is only in how each function names it. */
struct Rva00812320Module
{
	char m_gap0[ 0x28 ];
	struct Rva00812220Entry *m_first;	/* +0x28 */
	struct Rva00812220Entry *m_end;		/* +0x2C */
	int m_ready;				/* +0x30 */
	char m_gap34[ 4 ];
	struct Rva007FD4E0Socket *m_socket;	/* +0x38 */
	char m_peer[ 0x10 ];			/* +0x3C */
	int m_active;				/* +0x4C */
};

int Rva007FD920( struct Rva007FD4E0Socket *socket, const char *buffer,
	int length, int flags, void *to, int toLength );
void * __cdecl memset( void *dest, int c, unsigned int count );
void * __cdecl memcpy( void *dest, const void *src, unsigned int count );

/* "gEA\0" repeated.  THE TAG IS READ ONE CHARACTER AT A TIME FROM THREE
 * DIFFERENT OFFSETS -- 0, 5 and 10 -- which land on the 'g' of the first copy,
 * the 'E' of the second and the 'A' of the third.  The assembled result spells
 * the same three characters the run already contains contiguously, so this
 * buys nothing against a strings dump; it only makes the literal invisible to
 * a reader of the code. */
extern char g_Rva012C499CTag[];

/* 0x008125C0 SENDS THE MODULE'S ANNOUNCE PACKET.  Retail's own name for the
 * buffer, from the /GZ frame descriptor, is Packet.
 *
 * THE PACKET IS 0x180 BYTES AND ALL BUT FOUR OF THEM ARE ZERO -- three tag
 * characters at the front and one byte at offset 8.  The whole 0x180 is sent
 * regardless, so the wire cost is fixed and does not depend on content; a
 * reader looking for a length field will not find one.
 *
 * THE DESTINATION IS THE CONTEXT'S OWN STORED ADDRESS, passed by pointer with
 * a fixed length of 0x10, so this always goes to the same place and takes no
 * argument saying where.
 */
int Rva008125C0( struct Rva00812320Module *context )
{
	char Packet[ 0x180 ];

	memset( Packet, 0, sizeof( Packet ) );

	Packet[ 0 ] = g_Rva012C499CTag[ 0 ];
	Packet[ 1 ] = g_Rva012C499CTag[ 5 ];
	Packet[ 2 ] = g_Rva012C499CTag[ 10 ];
	Packet[ 8 ] = 0x3F;

	return Rva007FD920( context->m_socket, Packet, sizeof( Packet ), 0,
		context->m_peer, 0x10 );
}

/* The FESL allocator pair at 0x007F0000 and 0x007F0030 -- vtable slots 2 and 3
 * of the same lazily-fetched global.  Optimised code, so both are pinned
 * rather than converted. */
void *Rva007F0000( unsigned int size );
void Rva007F0030( void *block );

struct Rva0130AB68List;

struct Rva007FD4E0Socket *Rva007FD2D0( int family, int type, int protocol );
int Rva007FD510( struct Rva007FD4E0Socket *socket, const void *address,
	int addressLength );
int Rva007FDE80( struct Rva007FD4E0Socket *socket, void *callback,
	unsigned int rate, void *data,
	void ( __cdecl *proc )( struct Rva007FD4E0Socket *, int, void * ) );
void Rva007FEA20( struct Rva0130AB68List *list );
void Rva007FEBD0( void *list );
void Rva007FECB0( void *list );
void __cdecl Rva00812690( struct Rva007FD4E0Socket *socket, int reason,
	void *data );

extern struct Rva00812320Module *g_Rva0130AD00Module;
extern int g_Rva0130ACFCRefCount;

/* 0x00812320 CREATES THE MODULE, OR SHARES THE ONE THAT EXISTS.  Retail's own
 * names for the two address buffers, from the /GZ frame descriptor, are
 * bindaddr and peeraddr.
 *
 * IT IS A REFCOUNTED SINGLETON WITH NO LOCK.  The existing-instance test, the
 * count increment and the global store are three separate unsynchronised
 * accesses, so two threads arriving together can both allocate and one result
 * is leaked with a count of one.  Nothing here is guarded.
 *
 * THE ENTRY COUNT IS RAISED TO FOUR AND NEVER CAPPED, so a caller asking for
 * one gets four and a caller asking for a million gets a million times 0x1A4
 * handed straight to the allocator.
 *
 * THE TWO ALLOCATION FAILURES ARE HANDLED DIFFERENTLY AND BOTH ARE DEAD.  The
 * first returns null without freeing anything; the second frees the module
 * first.  Neither can run, because the allocator prints and then faults rather
 * than returning null -- so this is failure handling written against a
 * contract the allocator does not keep.
 *
 * THE SOCKET FAILURE PATH LEAKS THE ENTRY TABLE.  It frees the module but not
 * the block hung off +0x28, which was allocated separately.  That path IS
 * reachable, unlike the two above.
 *
 * BOTH ADDRESSES ARE BUILT BYTE BY BYTE, port 0x270F and, for the peer, an
 * all-ones address shifted out one byte at a time from low to high into
 * descending offsets -- a big-endian store of the broadcast address written as
 * a loop that was unrolled by hand.
 */
struct Rva00812320Module *Rva00812320( int iEntries )
{
	struct Rva007FD4E0Socket *pSocket;
	char bindaddr[ 0x10 ];
	char peeraddr[ 0x10 ];
	struct Rva00812320Module *pModule;
	unsigned int uAddr;

	if ( g_Rva0130AD00Module != 0 )
	{
		g_Rva0130ACFCRefCount++;
		return g_Rva0130AD00Module;
	}

	pModule = Rva007F0000( 0x50 );

	if ( pModule == 0 )
	{
		return 0;
	}

	memset( pModule, 0, 0x50 );

	if ( iEntries < 4 )
	{
		iEntries = 4;
	}

	pModule->m_first = Rva007F0000( iEntries * 0x1A4 );

	if ( pModule->m_first == 0 )
	{
		Rva007F0030( pModule );
		return 0;
	}

	pModule->m_end = pModule->m_first + iEntries;

	memset( pModule->m_first, 0,
		( char * )pModule->m_end - ( char * )pModule->m_first );

	pModule->m_active = 1;

	pSocket = Rva007FD2D0( 2, 2, 0 );

	if ( pSocket == 0 )
	{
		Rva007F0030( pModule );
		return 0;
	}

	g_Rva0130AD00Module = pModule;
	g_Rva0130ACFCRefCount = 1;

	Rva007FEA20( ( struct Rva0130AB68List * )pModule );
	Rva007FEBD0( pModule );

	*( short * )&bindaddr[ 0 ] = 2;
	*( short * )&bindaddr[ 2 ] = 0;
	*( int * )&bindaddr[ 4 ] = 0;
	*( int * )&bindaddr[ 8 ] = 0;
	*( int * )&bindaddr[ 12 ] = 0;
	bindaddr[ 2 ] = 0x27;
	bindaddr[ 3 ] = 0x0F;

	Rva007FD510( pSocket, bindaddr, 0x10 );

	*( short * )&peeraddr[ 0 ] = 2;
	*( short * )&peeraddr[ 2 ] = 0;
	*( int * )&peeraddr[ 4 ] = 0;
	*( int * )&peeraddr[ 8 ] = 0;
	*( int * )&peeraddr[ 12 ] = 0;
	peeraddr[ 2 ] = 0x27;
	peeraddr[ 3 ] = 0x0F;

	uAddr = 0xFFFFFFFF;
	peeraddr[ 7 ] = ( char )uAddr;
	uAddr >>= 8;
	peeraddr[ 6 ] = ( char )uAddr;
	uAddr >>= 8;
	peeraddr[ 5 ] = ( char )uAddr;
	uAddr >>= 8;
	peeraddr[ 4 ] = ( char )uAddr;

	memcpy( pModule->m_peer, peeraddr, 0x10 );

	pModule->m_ready = 1;
	pModule->m_socket = pSocket;

	Rva007FDE80( pModule->m_socket, ( void * )2, 0x64, pModule,
		Rva00812690 );

	Rva007FECB0( pModule );
	Rva008125C0( pModule );

	return pModule;
}
