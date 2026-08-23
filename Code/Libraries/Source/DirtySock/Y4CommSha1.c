// cl: /Od /GZ /MD /DNDEBUG
/* EA DirtySock -- a SHA-1 implementation, /Od with /GZ.  Separate from the MD5
 * in Y4CommDigest.c: different context layout, different transform, and the
 * two are not related by anything but sitting in the same address range.
 */

/* THE ALGORITHM IS EVIDENCED, not inferred from the shape.  The transform at
 * 0x00811310 contains all four SHA-1 round constants, its state is five words
 * rather than four, and retail's own name for its message schedule -- from the
 * /GZ frame descriptor -- is W, 0x140 bytes, which is eighty words: SHA-1's
 * notation and its expanded schedule exactly. */
struct Rva008111D0Context
{
	unsigned int m_count;			/* +0x00, bytes already hashed */
	unsigned int m_fill;			/* +0x04, bytes waiting in the block */
	unsigned int m_state[ 5 ];		/* +0x08 */
	unsigned char m_block[ 0x40 ];		/* +0x1C */
};

/* The block transform.  Pinned for now; 891 bytes and worth its own tick. */
void Rva00811310( struct Rva008111D0Context *context, const char *block );

void * __cdecl memcpy( void *dest, const void *src, unsigned int count );

/* 0x008111D0 FEEDS BYTES INTO THE SHA-1 STATE.  Where the MD5 update in
 * Y4CommDigest.c copies ONE BYTE AT A TIME through a masked cursor, this one
 * is written the other way round: top up the partial block with memcpy,
 * transform whole blocks straight out of the caller's buffer, then stash the
 * remainder.  Two digests in one library, two entirely different update
 * strategies.
 *
 * THE MIDDLE LOOP NEVER COPIES.  Full blocks are hashed in place from the
 * caller's memory, so a large call touches the context's own block buffer only
 * at the two ends.  That is the reason the transform takes a block POINTER
 * here while MD5's took only the context.
 *
 * THE FILL FIELD IS STORED, NOT DERIVED.  MD5 recovers its position by masking
 * the running count; this keeps a separate counter, so the two fields can in
 * principle disagree -- and the count is advanced only in units of 0x40, never
 * by the partial remainder, which is what makes that safe.
 *
 * THE TOP-UP BRANCH DOES NOT FALL THROUGH TO THE FLUSH.  If the partial block
 * is completed exactly it transforms and resets; otherwise it just advances
 * the fill and the whole call ends with the block still partial.  Both paths
 * then reach the same middle loop, which does nothing when the input was
 * short.
 */
void Rva008111D0( struct Rva008111D0Context *context, const char *data,
	unsigned int length )
{
	unsigned int uRoom;
	unsigned int uCopied;

	if ( context->m_fill != 0 )
	{
		uRoom = 0x40 - context->m_fill;
		uCopied = ( uRoom > length ) ? length : uRoom;

		memcpy( context->m_block + context->m_fill, data, uCopied );

		data += uCopied;
		length -= uCopied;

		if ( uCopied == uRoom )
		{
			Rva00811310( context, ( const char * )context->m_block );
			context->m_count += 0x40;
			context->m_fill = 0;
		}
		else
		{
			context->m_fill += uCopied;
		}
	}

	while ( length >= 0x40 )
	{
		Rva00811310( context, data );
		context->m_count += 0x40;
		length -= 0x40;
		data += 0x40;
	}

	if ( length != 0 )
	{
		memcpy( context->m_block + context->m_fill, data, length );
		context->m_fill += length;
	}
}
