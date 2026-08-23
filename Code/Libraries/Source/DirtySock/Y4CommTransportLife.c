// cl: /Od /GZ /MD /DNDEBUG
/* EA DirtySock -- the construct/destroy pair for a THIRD comm transport,
 * distinct again from the two in Y4CommRingIdle.c and Y4CommTickIdle.c.  Its
 * lock sits at +0x1F4 where theirs are at +0x1EC and +0x1E8, and its object is
 * 0x224 bytes where theirs are smaller; the constructor's own allocation size
 * settles that.
 *
 * WHAT THE OBJECT IS.  Its first fourteen words are a table of FUNCTION
 * POINTERS, filled in one by one, and the first two entries are this file's
 * own two bodies -- construct at +0x00 and destroy at +0x04.  That is
 * DirtySock's usual shape for a transport: a plain C struct whose leading
 * fields are the operations, so a caller holds one pointer and reaches
 * everything through it.  The other twelve land in the address range
 * commudp.cpp already occupies, which is what places this pair.
 *
 * The remaining pointer operands are declared address-derived and asserted to
 * be nothing more: they are DIR32 sites, so the gate fills them from retail
 * and the names below never reach the bytes.
 */

void *Rva007F0000Alloc( int size );
void Rva007F0030( void *object );
void *__cdecl memset( void *destination, int value, unsigned int count );
char *__cdecl strcpy( char *destination, const char *source );

/* Lock construct and destruct; the acquire and release live in the socket
 * unit and are already named there. */
void Rva007FEA20( void *lock );
void Rva007FEAA0( void *lock );

void Rva00817210Op( void );
void Rva00817230Op( void );
void Rva00818D90Op( void );
void Rva00817240Op( void );
void Rva00819300Op( void );
void Rva008172C0Op( void );
void Rva008171C0Op( void );
void Rva00817340Op( void );
void Rva008173A0Op( void );
void Rva008173C0Op( void );
void Rva00818BF0Op( void );
void Rva00818D20Op( void );

struct Rva00816BF0Comm
{
	/* +0x00..+0x34, and the first two are this file's own bodies. */
	void *m_op[ 14 ];
	char m_gap0[ 0x14 ];
	char m_name[ 0x2C ];            /* +0x4C */
	struct Rva00816BF0Comm *m_next; /* +0x78 */
	/* The socket OBJECT, not a handle: the destructor hands it straight to the
	 * socket destroy at 0x007FD3F0. */
	struct Rva007FD4E0Socket *m_socket;     /* +0x7C */
	char m_peer[ 0x10 ];            /* +0x80 */
	int m_state;                    /* +0x90 */
	int m_reserved94;               /* +0x94 */
	int m_recvRecordSize;           /* +0x98 */
	int m_recvBufferSize;           /* +0x9C */
	char m_gap1[ 0x08 ];
	unsigned char *m_recvBuffer;    /* +0xA8 */
	char m_gap2[ 0x0C ];
	int m_sendRecordSize;           /* +0xB8 */
	int m_sendBufferSize;           /* +0xBC */
	char m_gap3[ 0x0C ];
	unsigned char *m_sendBuffer;    /* +0xCC */
	char m_gap4[ 0x124 ];
	char m_lock[ 4 ];               /* +0x1F4 */
	char m_tail[ 0x2C ];
};

struct Rva007FD4E0Socket;
int Rva007FD3F0( struct Rva007FD4E0Socket *socket );

extern char g_Rva012C4F88Name[];
extern struct Rva00816BF0Comm *g_Rva0130B188List;

struct Rva00816BF0Comm *Rva00816BF0( int maxPacket, int recvCount,
	int sendCount );
void Rva00816E70( struct Rva00816BF0Comm *comm );
void Rva00816DF0( struct Rva00816BF0Comm *comm, int flag );
void Rva00816E10( struct Rva00816BF0Comm *comm );
void Rva00816F60( struct Rva00816BF0Comm *comm );
void Rva00817100( struct Rva00816BF0Comm *comm, int timeout );
void Rva00817140( struct Rva00816BF0Comm *comm );

/* THE TWO QUEUE SIZINGS ARE THE INTERESTING PART, and they are identical:
 * a record is the caller's maximum packet plus 0x10 of per-record header --
 * which is where the timestamp at +0x00, the length at +0x04 and the leading
 * data byte come from -- then rounded UP to a multiple of four.
 *
 * The rounding is `(n + 3) & 0x7FFC`, an AND rather than a modulo, and the
 * mask does two jobs: it clears the low two bits for the alignment and it also
 * clears everything above 0x7FFC.  So a maximum packet larger than about 32KB
 * does not fail, it WRAPS to a small record size.  That is a real limit of
 * this constructor and nothing here checks for it.
 *
 * Neither buffer allocation is checked either, though the object's own is.
 */
struct Rva00816BF0Comm *Rva00816BF0( int maxPacket, int recvCount,
	int sendCount )
{
	struct Rva00816BF0Comm *comm;

	comm = (struct Rva00816BF0Comm *)Rva007F0000Alloc( 0x224 );
	if ( comm == 0 )
		return 0;

	memset( comm, 0, 0x224 );

	comm->m_op[  0 ] = (void *)Rva00816BF0;
	comm->m_op[  1 ] = (void *)Rva00816E70;
	comm->m_op[  2 ] = (void *)Rva00817210Op;
	comm->m_op[  3 ] = (void *)Rva00817230Op;
	comm->m_op[  4 ] = (void *)Rva00818D90Op;
	comm->m_op[  5 ] = (void *)Rva00817240Op;
	comm->m_op[  6 ] = (void *)Rva00819300Op;
	comm->m_op[  7 ] = (void *)Rva008172C0Op;
	comm->m_op[  8 ] = (void *)Rva008171C0Op;
	comm->m_op[  9 ] = (void *)Rva00817340Op;
	comm->m_op[ 10 ] = (void *)Rva008173A0Op;
	comm->m_op[ 11 ] = (void *)Rva008173C0Op;
	comm->m_op[ 12 ] = (void *)Rva00818BF0Op;
	comm->m_op[ 13 ] = (void *)Rva00818D20Op;

	strcpy( comm->m_name, g_Rva012C4F88Name );
	Rva007FEA20( comm->m_lock );

	comm->m_recvRecordSize = maxPacket + 0x10;
	comm->m_recvRecordSize = ( comm->m_recvRecordSize + 3 ) & 0x7FFC;
	comm->m_recvBufferSize = comm->m_recvRecordSize * recvCount;
	comm->m_recvBuffer = (unsigned char *)
		Rva007F0000Alloc( comm->m_recvBufferSize );

	comm->m_sendRecordSize = maxPacket + 0x10;
	comm->m_sendRecordSize = ( comm->m_sendRecordSize + 3 ) & 0x7FFC;
	comm->m_sendBufferSize = comm->m_sendRecordSize * sendCount;
	comm->m_sendBuffer = (unsigned char *)
		Rva007F0000Alloc( comm->m_sendBufferSize );

	Rva00816DF0( comm, 0 );

	memset( comm->m_peer, 0, 0x10 );
	comm->m_state = 1;
	comm->m_reserved94 = 0;

	Rva00816E10( comm );
	return comm;
}

/* THE SOCKET IS SHARED, AND THIS IS WHERE THAT SHOWS.  Before destroying it
 * the body walks the global list of transports looking for ANOTHER one using
 * the same socket, and destroys it only if none is found.  That is a
 * reference count done by search rather than by counter -- cheap when the list
 * is short, and it means the socket outlives whichever transport happens to be
 * torn down first.
 *
 * The scan relies on this object already being unlinked from that list; the
 * unlink is one of the two calls made before it.
 *
 * The three frees at the end are in allocation order -- receive buffer, send
 * buffer, then the object -- and none of them is null-checked, which is
 * consistent with the constructor never checking the two buffer allocations
 * either.
 */
void Rva00816E70( struct Rva00816BF0Comm *comm )
{
	struct Rva00816BF0Comm *p;

	Rva00817100( comm, 0xC8 );
	Rva00817140( comm );

	if ( comm->m_state == 4 )
		Rva00816F60( comm );

	if ( comm->m_socket != 0 )
	{
		for ( p = g_Rva0130B188List; p != 0; p = p->m_next )
		{
			if ( p->m_socket == comm->m_socket )
				break;
		}

		if ( p == 0 )
		{
			Rva007FD3F0( comm->m_socket );
			Rva00816DF0( comm, 0 );
		}
	}

	Rva007FEAA0( comm->m_lock );
	Rva007F0030( comm->m_recvBuffer );
	Rva007F0030( comm->m_sendBuffer );
	Rva007F0030( comm );
}
