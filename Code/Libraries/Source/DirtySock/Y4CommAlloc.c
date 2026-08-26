// cl: /Od /GZ /MD /DNDEBUG
/* EA DirtySock -- allocation helpers for the comm layer, /Od with /GZ.  The
 * first of the 0x00800000..0x00820000 group to be converted; placement is by
 * address neighbourhood and by which allocator each body calls.
 */

/* The FESL allocator entry point at 0x007F0000.  It is OPTIMISED code -- no
 * frame pointer, a lazy global and a virtual call -- so it is pinned rather
 * than converted here; it takes a size cdecl and returns the block.  If no
 * allocator has been installed it prints "no FESL allocator defined" and then
 * dereferences the null anyway, so a missing allocator is a crash with a
 * message rather than a null return. */
void *Rva007F0000( unsigned int size );

void * __cdecl memset( void *dest, int c, unsigned int count );

/* 0x0080B000 ALLOCATES AND ZEROES A 0x124-BYTE OBJECT.  The size is a literal
 * in two places -- once for the allocation and once for the clear -- so the
 * two cannot disagree at run time but nothing ties them together either.
 *
 * THE ZEROING IS CONDITIONAL AND THE RETURN IS NOT.  A failed allocation
 * skips the clear and returns null, which is correct; but the allocator this
 * calls does not return null on failure, it crashes, so the guard is
 * unreachable in practice and only the shape of it survives.
 */
void *Rva0080B000( void )
{
	void *pObject;

	pObject = Rva007F0000( 0x124 );

	if ( pObject != 0 )
	{
		memset( pObject, 0, 0x124 );
	}

	return pObject;
}

void Rva0080ADE0( void *object, int releaseState );
void Rva007F0030( void *object );

void Rva0080B050( void *object )
{
	Rva0080ADE0( object, 0 );
}

void Rva0080B070( void *object )
{
	Rva0080ADE0( object, 0 );
	Rva007F0030( object );
}

struct Rva0080B000Comm
{
	void *m_socket;
};

void *Rva007FD2D0( int family, int type, int protocol );
void Rva007FD3F0( void *socket );
int Rva007FD510( void *socket, const void *address, int addressLength );

int Rva0080B150( struct Rva0080B000Comm *comm, const void *address,
	int addressLength )
{
	if ( comm->m_socket != 0 )
	{
		Rva007FD3F0( comm->m_socket );
	}

	comm->m_socket = Rva007FD2D0( 2, 1, 0 );
	if ( comm->m_socket == 0 )
	{
		return -7;
	}

	return Rva007FD510( comm->m_socket, address, addressLength );
}

struct Rva00812320Module;

struct Rva00812320Module *Rva00812320( int iEntries );
int Rva00812220( struct Rva00812320Module *module, const char *keyA,
	const char *keyB, int *pExtra, int iDefault );
int Rva00811E20( struct Rva00812320Module *module, const char *keyA,
	const char *keyB, char *out, int outSize, int bIncludePending );

/* Uninitialised data.  Whatever filter string this holds is written at run
 * time, so it is not recoverable from the image; it sits two bytes below the
 * module's reference count, which is why the group of globals reads as one
 * small block rather than three unrelated addresses. */
extern char g_Rva0130ACFAFilter[];

/* The caller's own object.  Only the two fields these wrappers touch are
 * named -- a default key at +0x04 and the module pointer at +0x64. */
struct Rva0080F100Object
{
	char m_gap0[ 4 ];
	char m_defaultKey[ 0x60 ];		/* +0x04 */
	struct Rva00812320Module *m_module;	/* +0x64 */
};

/* 0x0080F100 AND 0x0080F180 ARE THE SAME WRAPPER TWICE, differing only in
 * which of the two table functions they end in -- the value lookup or the
 * text listing.  Both CREATE THE MODULE ON FIRST USE, both substitute the
 * object's own key when the caller passes none, and both then re-test the
 * module pointer.
 *
 * THAT SECOND TEST IS NOT REDUNDANT-LOOKING BY ACCIDENT.  The constructor can
 * fail and return null, so the field may still be null after the first branch
 * assigned it -- the code reads as a doubled check and is really a
 * create-then-verify.  The failure result is 0, which the lookup also returns
 * for "no match", so a caller cannot tell a construction failure from an empty
 * table.
 *
 * SIXTEEN ENTRIES IS HARDCODED at both sites rather than passed in, so the
 * table size is decided by whichever of these two happens to run first and
 * neither caller can influence it.
 */
int Rva0080F100( struct Rva0080F100Object *object, const char *keyA,
	const char *keyB )
{
	int iResult;

	if ( object->m_module == 0 )
	{
		object->m_module = Rva00812320( 0x10 );
	}

	if ( keyA == 0 )
	{
		keyA = object->m_defaultKey;
	}

	if ( object->m_module == 0 )
	{
		iResult = 0;
	}
	else
	{
		iResult = Rva00812220( object->m_module, keyA, keyB, 0, 0 );
	}

	return iResult;
}

int Rva0080F180( struct Rva0080F100Object *object, const char *keyA,
	char *out, int outSize )
{
	int iResult;

	if ( object->m_module == 0 )
	{
		object->m_module = Rva00812320( 0x10 );
	}

	if ( keyA == 0 )
	{
		keyA = object->m_defaultKey;
	}

	if ( object->m_module == 0 )
	{
		iResult = 0;
	}
	else
	{
		iResult = Rva00811E20( object->m_module, keyA, g_Rva0130ACFAFilter,
			out, outSize, 0 );
	}

	return iResult;
}
