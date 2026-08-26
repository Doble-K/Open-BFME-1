// cl: /Od /GZ /MD /DNDEBUG
/* EA DirtySock -- a second /Od /GZ comm transport, distinguished from the ring
 * one in Y4CommRingIdle.c by its LOCK OFFSET: +0x1E8 here against +0x1EC
 * there.  Four bytes is a whole field, so these are different objects and
 * therefore different transports, and that is the only reason the two files
 * are separate.  Placement of both bodies is by address neighbourhood; neither
 * reaches a string, so nothing names the module.
 */

int Rva007FEB00( void *lock );
void Rva007FECB0( void *lock );

/* The millisecond tick source. */
unsigned int Rva007FEA00( void );

struct Rva00814700Comm
{
	char m_head[ 0x48 ];
	void *m_socketAlias;             /* +0x48 */
	char m_gap4C[ 0x2C ];
	void *m_transport;               /* +0x78 */
	void *m_socket;                  /* +0x7C */
	unsigned char m_endpoint[ 0x08 ]; /* +0x80 */
	unsigned int m_handle;           /* +0x88 */
	char m_gap8C[ 0x04 ];
	int m_state;                     /* +0x90 */
	char m_gap94[ 0x04 ];
	int m_sequence;                  /* +0x98 */
	/* A SECOND RING, distinct from the one in Y4CommRingIdle.c: same shape --
	 * an offset advanced by a record size and reduced modulo a buffer size --
	 * but at +0x9C..+0xA8 rather than +0xB0..+0xBC.  Two rings in two
	 * transports, not one struct seen twice. */
	int m_recordSize;               /* +0x9C */
	int m_bufferSize;               /* +0xA0 */
	int m_readOffset;               /* +0xA4 */
	int m_writeOffset;              /* +0xA8 */
	void *m_allocA;                  /* +0xAC */
	char m_gapB0[ 0x04 ];
	int m_pending;                   /* +0xB4 */
	int m_countA;                   /* +0xB8 */
	int m_countB;                   /* +0xBC */
	int m_countC;                   /* +0xC0 */
	unsigned int m_lastTick;        /* +0xC4 */
	void *m_allocB;                  /* +0xC8 */
	char m_gapCC[ 0x04 ];
	unsigned int m_timeoutTick;     /* +0xD0 */
	char m_gapD4[ 0x04 ];
	int m_status;                   /* +0xD8 */
	char m_gapDC[ 0x10C ];
	char m_lock[ 4 ];               /* +0x1E8 */
	char m_gap1EC[ 0x24 ];
	int m_flags;                    /* +0x210 */
	void *m_value;                  /* +0x214 */
	void ( *m_callback )( struct Rva00814700Comm *, void * ); /* +0x218 */
};

void Rva008142B0( struct Rva00814700Comm *comm, void *socket )
{
	comm->m_socket = socket;
	comm->m_socketAlias = socket;
}

void Rva007FD3F0( void *socket );

int Rva00814400( struct Rva00814700Comm *comm )
{
	if ( comm->m_state == 3 )
		Rva008142B0( comm, 0 );

	if ( comm->m_socket != 0 )
	{
		Rva007FD3F0( comm->m_socket );
		Rva008142B0( comm, 0 );
	}

	comm->m_state = 1;
	return 0;
}

int Rva00814460( struct Rva00814700Comm *comm )
{
	if ( comm->m_state == 3 )
		Rva008142B0( comm, 0 );

	if ( comm->m_socket != 0 )
	{
		Rva007FD3F0( comm->m_socket );
		Rva008142B0( comm, 0 );
	}

	comm->m_state = 1;
	return 0;
}

int CommTCPUnlisten( struct Rva00814700Comm *comm );
void Rva007FEAA0( void *list );
void Rva007F0030( void *block );

void Rva008142D0( struct Rva00814700Comm *comm )
{
	if ( comm->m_state == 4 )
		CommTCPUnlisten( comm );

	if ( comm->m_socket != 0 )
	{
		Rva007FD3F0( comm->m_socket );
		Rva008142B0( comm, 0 );
	}

	Rva007FEAA0( comm->m_lock );
	Rva007F0030( comm->m_allocA );
	Rva007F0030( comm->m_allocB );
	Rva007F0030( comm );
}

void Rva008143A0( struct Rva00814700Comm *comm, void *value )
{
	comm->m_value = value;
	comm->m_flags |= 2;
}

void Rva0081B830( void *transport );

void Rva00813E30( struct Rva00814700Comm *comm )
{
	Rva0081B830( comm->m_transport );
}

int Rva0081BA60( void *transport, const void *payload, int length );

int Rva00814040( struct Rva00814700Comm *comm, const void *payload,
	int length )
{
	return Rva0081BA60( comm->m_transport, payload, length );
}

int Rva0081B9D0( void *transport );
void Rva0081B9B0( void *transport );
int __stdcall Rva0081BDAE( unsigned int handle );

int Rva00813F20( struct Rva00814700Comm *comm )
{
	if ( comm->m_state == 5 || comm->m_state == 8 )
		Rva0081B9B0( comm->m_transport );

	if ( comm->m_state == 3 || comm->m_state == 5 || comm->m_state == 8 )
		Rva0081BDAE( comm->m_handle );

	return 0;
}

int Rva00813F90( struct Rva00814700Comm *comm )
{
	if ( comm->m_state == 3 || comm->m_state == 4 )
		return 2;

	if ( comm->m_state == 2 || comm->m_state == 8 )
		return 1;

	if ( comm->m_state == 7 || comm->m_state == 6 )
		return 3;

	if ( comm->m_state == 5 )
		return Rva0081B9D0( comm->m_transport );

	return 4;
}

int Rva0081BC80( void *transport, void *buffer, int size,
	unsigned int *when );

int Rva00814070( struct Rva00814700Comm *comm, void *buffer, int size,
	unsigned int *when )
{
	return Rva0081BC80( comm->m_transport, buffer, size, when );
}

int Rva0081BD40( void *transport, void *buffer, int size,
	unsigned int *when );

int Rva008140A0( struct Rva00814700Comm *comm, void *buffer, int size,
	unsigned int *when )
{
	return Rva0081BD40( comm->m_transport, buffer, size, when );
}

int Rva008144C0( struct Rva00814700Comm *comm )
{
	if ( comm->m_state == 2 || comm->m_state == 3 )
		return 2;

	if ( comm->m_state == 1 || comm->m_state == 5 )
		return 1;

	if ( comm->m_state == 4 )
		return 3;

	return 4;
}

int Rva00815830( struct Rva00814700Comm *comm )
{
	if ( comm->m_state == 1 || comm->m_state == 2 )
		return 2;

	if ( comm->m_state == 0 || comm->m_state == 4 )
		return 1;

	if ( comm->m_state == 3 )
		return 3;

	return 4;
}

void Rva00816910( struct Rva00814700Comm *comm )
{
	comm->m_countA = 0;
	comm->m_countB = 0;
	comm->m_readOffset = 0;
	comm->m_writeOffset = 0;
	comm->m_lastTick = Rva007FEA00() - 5000;
	comm->m_status = -1;
}

void Rva00815170( struct Rva00814700Comm *comm )
{
	comm->m_countC = 0;
	comm->m_lastTick = 0;
	comm->m_pending = -1;
	comm->m_readOffset = 0;
	comm->m_writeOffset = 0;
	comm->m_sequence = 0;
	comm->m_timeoutTick = Rva007FEA00() - 5000;
}

void Rva008155F0( struct Rva00814700Comm *comm, int status );

void Rva00815C90( struct Rva00814700Comm *comm )
{
	if ( !( ( ( ( ( comm->m_endpoint[ 4 ] << 8 ) | comm->m_endpoint[ 5 ] )
		<< 8 | comm->m_endpoint[ 6 ] ) << 8 | comm->m_endpoint[ 7 ] ) )
		|| !( ( comm->m_endpoint[ 2 ] << 8 ) | comm->m_endpoint[ 3 ] ) )
		return;

	if ( Rva007FEA00() - comm->m_lastTick >= 1000 )
	{
		if ( comm->m_state == 1 )
			Rva008155F0( comm, 16 );
		else if ( comm->m_state == 2 )
			Rva008155F0( comm, 17 );
	}
}

void Rva00815D40( struct Rva00814700Comm *comm )
{
	if ( comm->m_state == 3 && comm->m_countA == comm->m_countB
		&& Rva007FEA00() > comm->m_lastTick + 5000 )
	{
		Rva008155F0( comm, 19 );
	}
}

void Rva00815DA0( struct Rva00814700Comm *comm );
void Rva00816490( struct Rva00814700Comm *comm );

void Rva00815BB0( struct Rva00814700Comm *comm )
{
	if ( comm->m_state == 1 || comm->m_state == 2 )
		Rva00815C90( comm );

	Rva00815DA0( comm );
	Rva00815D40( comm );
	Rva00816490( comm );

	if ( comm->m_flags == 0 && comm->m_value != 0 )
	{
		comm->m_flags++;
		if ( comm->m_callback != 0 )
			comm->m_callback( comm, comm->m_value );
		comm->m_flags--;
		comm->m_value = 0;
	}
}

struct Rva00815510Comm
{
	char m_head[ 0x7C ];
	void *m_socket;                  /* +0x7C */
	char m_gap80[ 0x10 ];
	int m_state;                     /* +0x90 */
	char m_gap94[ 0x18 ];
	void *m_allocA;                  /* +0xAC */
	char m_gapB0[ 0x10 ];
	void *m_allocB;                  /* +0xC0 */
	char m_gapC4[ 0x128 ];
	char m_lock[ 4 ];                /* +0x1EC */
};

int Rva008155A0( struct Rva00815510Comm *comm );
void Rva008154F0( struct Rva00815510Comm *comm, void *socket );

void Rva00815510( struct Rva00815510Comm *comm )
{
	if ( comm->m_state == 3 )
		Rva008155A0( comm );

	if ( comm->m_socket != 0 )
	{
		Rva007FD3F0( comm->m_socket );
		Rva008154F0( comm, 0 );
	}

	Rva007FEAA0( comm->m_lock );
	Rva007F0030( comm->m_allocA );
	Rva007F0030( comm->m_allocB );
	Rva007F0030( comm );
}

struct Rva00813E50Comm
{
	char m_head[ 0x7C ];
	int m_port;                      /* +0x7C */
	char m_gap80[ 0x10 ];
	int m_state;                     /* +0x90 */
	char m_gap94[ 0x04 ];
	char m_host[ 1 ];                /* +0x98 */
};

char *strchr( const char *text, int value );
char *strcpy( char *dest, const char *source );
void __stdcall Rva00813100( int port, int kind, struct Rva00813E50Comm *comm,
	int size, int a, int b );

int Rva00813E50( struct Rva00813E50Comm *comm, char *text )
{
	if ( comm->m_state != 2 )
		return -2;

	comm->m_port = 0;
	for ( ; *text >= '0' && *text <= '9'; text++ )
	{
		comm->m_port = comm->m_port * 10 + ( *text & 15 );
	}

	text = strchr( text, ':' );
	if ( text == 0 )
		return -3;

	strcpy( comm->m_host, text + 1 );
	comm->m_state = 3;
	Rva00813100( comm->m_port, 2, comm, 0x4000, 0, 0 );
	return 0;
}

void Rva00814770( struct Rva00814700Comm *comm, unsigned int tick );

/* The socket callback.  Same shape as the ring transport's -- handle and event
 * flags ignored, only the ref used, lock TRIED rather than taken -- with one
 * addition: it READS THE CLOCK ITSELF and hands the tick to the pump, rather
 * than letting the pump read it.  So every record the pump processes in one
 * call is stamped with a single consistent time, which it could not be if the
 * pump sampled per record.
 */
int Rva00814700( unsigned int socket, int flags, struct Rva00814700Comm *ref )
{
	struct Rva00814700Comm *comm;
	unsigned int uTick;

	comm = ref;

	if ( Rva007FEB00( comm->m_lock ) != 0 )
	{
		uTick = Rva007FEA00();
		Rva00814770( comm, uTick );
		Rva007FECB0( comm->m_lock );
	}

	return 0;
}

/* 0x00813780 guards a one-argument import behind an INVALID-HANDLE CHECK,
 * returning 0x8000002B instead of calling when the handle is -1.  The high bit
 * makes that a negative value, so callers testing for failure see it without
 * knowing the code.
 *
 * The import is not named: its thunk lands in an IAT slot the ledger has no
 * name for, so the declaration below is address-derived and asserts nothing
 * about which API it is.  What the bytes do fix is the shape -- one argument,
 * nothing cleaned at the call site, so __stdcall -- and that its result is
 * returned unchanged.
 */
int Rva00813780( unsigned int handle )
{
	int iResult;

	if ( handle != 0xFFFFFFFF )
		iResult = Rva0081BDAE( handle );
	else
		iResult = 0x8000002B;

	return iResult;
}

/* 0x00814F70 forwards four arguments unchanged and then ADVANCES THE RING ONLY
 * ON SUCCESS -- the cursor moves when the inner call returns a non-negative
 * result and stays put otherwise.  So a failed operation leaves the slot
 * available to be retried rather than consuming it, which is the whole reason
 * this wrapper exists separately from the body it calls.
 *
 * The test is `jl`, i.e. SIGNED: the inner call's negative returns are error
 * codes and its non-negative ones are counts.
 *
 * The four forwarded arguments are all 4-byte pushes and this body does not
 * look inside any of them, so their types are not recoverable here; they are
 * declared as plain words rather than guessed at.
 */
int Rva00814EA0( struct Rva00814700Comm *comm, int a, int b, int c );

int Rva00814F70( struct Rva00814700Comm *comm, int a, int b, int c )
{
	int iResult;

	iResult = Rva00814EA0( comm, a, b, c );

	if ( iResult >= 0 )
	{
		comm->m_writeOffset = ( comm->m_writeOffset + comm->m_recordSize )
			% comm->m_bufferSize;
	}

	return iResult;
}
