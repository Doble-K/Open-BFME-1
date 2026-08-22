// cl: /Od /GZ /MD /DNDEBUG
/* EA DirtySock -- the idle pump for a RING-BUFFERED comm transport.
 *
 * PLACEMENT IS BY ADDRESS NEIGHBOURHOOD ONLY, and is stated rather than
 * implied: these bodies sit inside the span commsrp.cpp already occupies, but
 * they cannot be part of that translation unit, because they are built /Od
 * with /GZ -- local fills of 0xCCCCCCCC and a stack check after every call --
 * and commsrp.cpp is optimised.  Two translation units interleaved in one
 * address range is ordinary; sharing a file with one that has different flags
 * is not possible.  Neither body reaches a string, so nothing here names the
 * module and the file name is address-derived like the symbols.
 *
 * WHAT THE FIELDS ARE, read from the arithmetic rather than assumed.  The two
 * bodies together use +0xB0, +0xB4, +0xB8 and +0xBC as a ring: an offset is
 * advanced by +0xB0 and reduced modulo +0xB4, so +0xB0 is a RECORD SIZE and
 * +0xB4 the buffer size in bytes; the backlog is computed as the distance from
 * +0xBC to +0xB8 taken modulo the buffer size and then DIVIDED BY THE RECORD
 * SIZE, which is what makes the result a count of records rather than bytes.
 * +0xBC is therefore the read cursor and +0xB8 the write cursor.  All the
 * divides are idiv, so every one of these is a signed int.
 */

/* The recursive lock helpers this library uses everywhere; the acquire is a
 * TRY, returning zero when the lock is held elsewhere. */
int Rva007FEB00( void *lock );
void Rva007FECB0( void *lock );

struct Rva00815B50Comm
{
	char m_head[ 0x7C ];
	unsigned int m_socket;          /* +0x7C */
	char m_gap[ 0x30 ];
	int m_recordSize;               /* +0xB0 */
	int m_bufferSize;               /* +0xB4 */
	int m_writeOffset;              /* +0xB8 */
	int m_readOffset;               /* +0xBC */
	/* The ring's BASE POINTER.  0x00815FA0 adds the read offset to it and
	 * dereferences the result, which is what proves the offsets above are
	 * byte offsets into this buffer rather than indices. */
	unsigned char *m_buffer;        /* +0xC0 */
	char m_gap2[ 0x128 ];
	char m_lock[ 4 ];               /* +0x1EC */
};

void Rva00815BB0( struct Rva00815B50Comm *comm );

/* The socket callback.  Its first two arguments -- the handle and the event
 * flags -- are IGNORED; only the ref is used, which is the shape DirtySock
 * installs everywhere.  The lock is TRIED rather than taken, so a callback
 * arriving while the transport is busy is dropped rather than queued.
 */
int Rva00815B50( unsigned int socket, int flags, struct Rva00815B50Comm *ref )
{
	struct Rva00815B50Comm *comm;

	comm = ref;

	if ( Rva007FEB00( comm->m_lock ) != 0 )
	{
		Rva00815BB0( comm );
		Rva007FECB0( comm->m_lock );
	}

	return 0;
}

/* Advance the write cursor by one record, pump the transport through its own
 * callback, and report how many records are outstanding.
 *
 * THE OUT-PARAMETER IS CLEARED AND NEVER WRITTEN AGAIN in this body, so a
 * caller always sees zero from it here; whatever it is for is filled in
 * elsewhere or not at all.  That is retail's, and it is the kind of thing a
 * reader would otherwise assume was an oversight in the conversion.
 *
 * The pump is invoked by CALLING THE CALLBACK DIRECTLY rather than by waiting
 * for the socket to fire it -- same function, same arguments the socket layer
 * would pass, with the handle taken out of the object.
 */
int Rva00815AB0( struct Rva00815B50Comm *comm, int *out )
{
	int iResult;

	*out = 0;

	comm->m_writeOffset = ( comm->m_writeOffset + comm->m_recordSize )
		% comm->m_bufferSize;

	Rva00815B50( comm->m_socket, 0, comm );

	iResult = ( ( comm->m_writeOffset + comm->m_bufferSize
		- comm->m_readOffset ) % comm->m_bufferSize ) / comm->m_recordSize;

	return iResult;
}

/* 0x00815FA0 RETIRES ONE RECORD, but only if the acknowledgement matches.
 *
 * It reads a sequence byte from the incoming packet and one from the record
 * currently at the read cursor, and advances the cursor only when they agree.
 * THE TWO BYTES ARE BIASED DIFFERENTLY -- 0xC0 is subtracted from the packet's
 * and 0x80 from the stored one -- so the two sides carry the same sequence
 * number in different tag spaces, and the constants are what say so.  Reading
 * either byte alone would tell you nothing.
 *
 * A mismatch is silently ignored: no error, no counter, no retransmit here.
 * The record simply stays at the cursor.
 *
 * Both bytes are read with movzx, so the tags are unsigned; the biased results
 * are then compared as ints, which is why an unexpected tag cannot wrap into
 * a false match.
 */
void Rva00815FA0( struct Rva00815B50Comm *comm, const unsigned char *packet )
{
	int iPacketTag;
	int iRecordTag;
	unsigned char *pRecord;

	pRecord = comm->m_buffer + comm->m_readOffset;

	iPacketTag = packet[ 8 ] - 0xC0;
	iRecordTag = pRecord[ 8 ] - 0x80;

	if ( iPacketTag == iRecordTag )
	{
		comm->m_readOffset = ( comm->m_readOffset + comm->m_recordSize )
			% comm->m_bufferSize;
	}
}
