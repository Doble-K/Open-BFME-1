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
