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
	char m_head[ 0x1E8 ];
	char m_lock[ 4 ];               /* +0x1E8 */
};

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
int __stdcall Rva0081BDAE( unsigned int handle );

int Rva00813780( unsigned int handle )
{
	int iResult;

	if ( handle != 0xFFFFFFFF )
		iResult = Rva0081BDAE( handle );
	else
		iResult = 0x8000002B;

	return iResult;
}
