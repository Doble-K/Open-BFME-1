// cl: /Od /GZ /MD /DNDEBUG
/* EA DirtySock -- a fourth /Od /GZ comm object, past the range the three
 * already converted occupy.  Its ring sits at +0xD4..+0xE0, where the others
 * are at +0x98, +0xB0 and +0xB8, so it is a distinct object again; nothing
 * here identifies the module, and both bodies are placed by address
 * neighbourhood.
 *
 * Only the fields these two bodies actually touch are declared.  The gaps are
 * left as gaps rather than filled with plausible names.
 */

struct Rva0081BD40Comm
{
	char m_head[ 0xCC ];
	/* A STATE.  0x0081B790 and 0x0081B910 both require it to be 1 before
	 * doing anything, and both convert a 5 into their own result -- 3 and 2
	 * respectively.  Nothing converted so far shows what sets it to 5. */
	int m_state;                    /* +0xCC */
	char m_gapCC[ 0x04 ];
	int m_recordSize;               /* +0xD4 */
	int m_bufferSize;               /* +0xD8 */
	int m_writeOffset;              /* +0xDC */
	int m_readOffset;               /* +0xE0 */
	unsigned char *m_buffer;        /* +0xE4 */
	char m_gap[ 0x1838 ];
	/* A CRITICAL SECTION, and its SIZE is the evidence: the two bodies that
	 * take it pass +0x1920 to a pair of one-argument stdcall imports, and the
	 * busy flag below starts exactly 0x18 bytes later -- which is sizeof
	 * CRITICAL_SECTION on x86.  The import names never reach the bytes, so
	 * the declarations below are address-derived. */
	char m_lock[ 0x18 ];            /* +0x1920 */
	/* A BUSY FLAG the dequeue SPINS on.  Its offset also makes this object at
	 * least 0x193C bytes -- an order of magnitude larger than the three
	 * transports converted so far, which are 0x224 and smaller. */
	int m_busy;                     /* +0x1938 */
};

/* The one-argument stdcall import the socket unit already reaches with a 50
 * for a poll interval; here it is called with zero, which is a yield rather
 * than a wait.  The name is address-derived: an IAT call site is a DIR32 and
 * the gate fills it from retail, so nothing here asserts which API it is. */
__declspec(dllimport) void __stdcall Rva01358F30Wait( int interval );

/* A QUEUED RECORD.  Length at +0x00, tick at +0x04, payload at +0x10 -- the
 * same header the third transport uses, and again with no header byte inside
 * the payload. */
struct Rva0081BC80Record
{
	int m_length;                   /* +0x00 */
	unsigned int m_tick;            /* +0x04 */
	char m_reserved[ 0x08 ];
	unsigned char m_data[ 4 ];      /* +0x10 */
};

/* 0x0081A360 is a 16-BIT HASH, and every part of that is in the bytes: the
 * accumulator is written and read back as a WORD, the multiply is by 13, and
 * the result is returned in ax rather than eax -- so the caller gets
 * 0x0000..0xFFFF and the upper half of the register is not part of the answer.
 *
 * The input byte is read with movzx, so the data is unsigned; the length is
 * compared with `jle`, so it is SIGNED and a negative length hashes nothing
 * rather than running away.
 *
 * Both parameters are walked in place rather than through locals, which is
 * why the frame holds only the accumulator.
 */
unsigned short Rva0081A360( const unsigned char *data, int length )
{
	unsigned short uHash;

	uHash = 0;

	while ( length > 0 )
	{
		uHash = (unsigned short)( uHash * 13 + *data );
		data++;
		length--;
	}

	return uHash;
}

/* 0x0081BD40 forwards four arguments and advances the ring cursor only when
 * the inner call reports success, so a failure leaves the slot to be retried.
 * The same shape appears once per transport in this library; this is the
 * fourth.
 */
/* Settled by converting it: a buffer, a size and an optional out-pointer. */
int Rva0081BC80( struct Rva0081BD40Comm *comm, void *buffer, int size,
	unsigned int *when );

int Rva0081BD40( struct Rva0081BD40Comm *comm, void *buffer, int size,
	unsigned int *when )
{
	int iResult;

	iResult = Rva0081BC80( comm, buffer, size, when );

	if ( iResult >= 0 )
		comm->m_readOffset = ( comm->m_readOffset + comm->m_recordSize )
			% comm->m_bufferSize;

	return iResult;
}

void *__cdecl memcpy( void *destination, const void *source,
	unsigned int count );

/* 0x0081BC80 DEQUEUES ONE RECORD, and it is the only one of these four that
 * BLOCKS.
 *
 * After finding the queue non-empty it spins while a flag at +0x1938 is set,
 * yielding the timeslice on each pass rather than sleeping for an interval --
 * the same import the socket unit calls with 50, called here with zero.  So a
 * reader can be held off indefinitely by whoever owns that flag, with no
 * timeout and no failure return for it; the only exits are an empty queue and
 * a successful read.
 *
 * Note the order: EMPTINESS IS TESTED BEFORE THE SPIN.  An empty queue returns
 * -7 immediately rather than waiting for a writer, so this blocks on the flag
 * and not on data.
 *
 * The rest matches its counterparts: the copy is clamped to the caller's size
 * while the RETURN IS THE FULL RECORD LENGTH, so comparing the two is the only
 * way to detect truncation, and the optional out-pointer receives the arrival
 * tick.
 */
int Rva0081BC80( struct Rva0081BD40Comm *comm, void *buffer, int size,
	unsigned int *when )
{
	struct Rva0081BC80Record *record;
	int iCopy;

	if ( comm->m_readOffset == comm->m_writeOffset )
		return -7;

	while ( comm->m_busy != 0 )
		Rva01358F30Wait( 0 );

	record = (struct Rva0081BC80Record *)( comm->m_buffer
		+ comm->m_readOffset );

	if ( record->m_length < size )
		iCopy = record->m_length;
	else
		iCopy = size;

	memcpy( buffer, record->m_data, iCopy );

	if ( when != 0 )
		*when = record->m_tick;

	return record->m_length;
}

__declspec(dllimport) void __stdcall Rva01358D18Enter( void *lock );
__declspec(dllimport) void __stdcall Rva01358E74Leave( void *lock );

int Rva0081B010( struct Rva0081BD40Comm *comm, void *argument );

/* 0x0081B790 and 0x0081B910 ARE THE SAME BODY BUT FOR ONE CONSTANT: both
 * refuse unless the argument is non-null and the state is 1, both take the
 * critical section, both call the same worker, and both convert a state of 5
 * into their own -- 3 for the first, 2 for the second -- before releasing.
 *
 * The pair is what makes 5 legible as a TRANSIENT the worker can leave behind:
 * neither body sets it, both check for it, and each replaces it with a
 * different settled value.  So the worker signals "decide what I became" and
 * the caller's identity is what decides.  Either body alone would just look
 * like an unexplained magic number.
 *
 * The refusal is an early return with an ||, which is legible in the jumps: a
 * null argument jumps straight to the return, while a state of 1 jumps PAST
 * it.  An && wrapping the body sends both operands to the same place instead.
 *
 * The worker's result is returned unchanged, and it is captured BEFORE the
 * state fixup -- so the fixup cannot affect what the caller sees.
 */
int Rva0081B790( struct Rva0081BD40Comm *comm, void *argument )
{
	int iResult;

	if ( argument == 0 || comm->m_state != 1 )
		return -2;

	Rva01358D18Enter( comm->m_lock );

	iResult = Rva0081B010( comm, argument );

	if ( comm->m_state == 5 )
		comm->m_state = 3;

	Rva01358E74Leave( comm->m_lock );
	return iResult;
}

int Rva0081B910( struct Rva0081BD40Comm *comm, void *argument )
{
	int iResult;

	if ( argument == 0 || comm->m_state != 1 )
		return -2;

	Rva01358D18Enter( comm->m_lock );

	iResult = Rva0081B010( comm, argument );

	if ( comm->m_state == 5 )
		comm->m_state = 2;

	Rva01358E74Leave( comm->m_lock );
	return iResult;
}
