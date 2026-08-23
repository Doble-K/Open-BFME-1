// cl: /Od /GZ /MD /DNDEBUG
/* EA DirtySock -- the comm layer's message digest, /Od with /GZ.  Placement is
 * by address neighbourhood within the 0x00810000 group.
 */

/* The digest state.  THE SHAPE IS THE ONLY EVIDENCE FOR WHAT IT IS: a running
 * BYTE count at the front, sixteen bytes of chaining state, and a 64-byte
 * block that is flushed whenever it fills.  Four state words with a 64-byte
 * block is MD5's shape, but nothing here proves the algorithm -- that is in
 * the transform at 0x00810120, which is not converted yet -- so the fields are
 * named for what this function does with them and not for what they probably
 * are.  Note the count is in BYTES, where MD5 conventionally keeps bits. */
struct Rva00810060Context
{
	unsigned int m_count;			/* +0x00 */
	char m_state[ 0x10 ];			/* +0x04 */
	unsigned char m_block[ 0x40 ];		/* +0x14 */
};

/* The block transform.  Pinned rather than converted for now -- it is 3765
 * bytes and wants a tick of its own; this declaration is what lets the update
 * land ahead of it. */
void Rva00810120( struct Rva00810060Context *context );

/* 0x00810060 FEEDS BYTES INTO THE DIGEST, flushing whenever the block fills.
 *
 * A NEGATIVE LENGTH MEANS "NUL-TERMINATED", and the measuring loop runs before
 * anything else -- so the same entry point takes a counted buffer or a C
 * string, chosen by the sign of an argument rather than by a separate
 * function.  A length of zero is not the same as a negative one: zero feeds
 * nothing, negative measures.
 *
 * THE FILL POSITION IS RECOVERED FROM THE COUNT rather than stored, by masking
 * the running total with 0x3F.  So the context carries no separate cursor and
 * the two can never disagree -- but it also means the count and the block
 * position are the same field, and anything that adjusts one moves the other.
 *
 * THE FLUSH TEST IS AN EQUALITY, not a bound.  It fires only on exactly 0x40,
 * which is safe because the position is masked on entry and advanced one byte
 * at a time -- an invariant of this loop rather than anything checked here.
 */
void Rva00810060( struct Rva00810060Context *context, const unsigned char *data,
	int length )
{
	int iFill;
	const unsigned char *p;

	p = data;

	if ( length < 0 )
	{
		for ( length = 0; p[ length ] != 0; length++ )
		{
		}
	}

	iFill = context->m_count & 0x3F;

	for ( ; length > 0; length-- )
	{
		context->m_block[ iFill ] = *p;
		iFill++;
		p++;
		context->m_count++;

		if ( iFill == 0x40 )
		{
			Rva00810120( context );
			iFill = 0;
		}
	}
}
