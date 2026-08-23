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
	char m_head[ 0x38 ];
	/* THE SEND CALLBACK, called by 0x0081A8C0 just before each record goes out
	 * with the transport, the payload, its length and a zero.  Null means
	 * nobody is watching; it does not stop the send. */
	void ( __cdecl *m_sendProc )( struct Rva0081BD40Comm *comm,
		const void *payload, int length, int reserved );  /* +0x38 */
	char m_head2[ 0x90 ];
	/* A STATE.  0x0081B790 and 0x0081B910 both require it to be 1 before
	 * doing anything, and both convert a 5 into their own result -- 3 and 2
	 * respectively.  Nothing converted so far shows what sets it to 5. */
	int m_state;                    /* +0xCC */
	char m_gapCC[ 0x04 ];
	int m_recvRecordSize;               /* +0xD4 */
	int m_recvBufferSize;               /* +0xD8 */
	int m_recvWriteOffset;              /* +0xDC */
	int m_recvReadOffset;               /* +0xE0 */
	unsigned char *m_recvBuffer;        /* +0xE4 */
	/* THE EXPECTED RECEIVE SEQUENCE.  0x0081A8C0 stamps one less than this
	 * into every outgoing record's ack field, which is the "I want N next"
	 * convention the acknowledgement handler above decodes. */
	int m_recvSequence;             /* +0xE8 */
	/* THE SEND RING, the same five fields plus an ack cursor that the third
	 * transport has at +0xB0..+0xC8.  0x0081AA20 is the same acknowledgement
	 * handler that transport has at 0x008186C0, walking these instead. */
	int m_sendRecordSize;           /* +0xEC */
	int m_sendBufferSize;           /* +0xF0 */
	int m_sendWriteOffset;          /* +0xF4 */
	int m_sendReadOffset;           /* +0xF8 */
	int m_sendAckOffset;            /* +0xFC */
	unsigned char *m_sendBuffer;    /* +0x100 */
	char m_gap[ 0x181C ];
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
		comm->m_recvReadOffset = ( comm->m_recvReadOffset + comm->m_recvRecordSize )
			% comm->m_recvBufferSize;

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

	if ( comm->m_recvReadOffset == comm->m_recvWriteOffset )
		return -7;

	while ( comm->m_busy != 0 )
		Rva01358F30Wait( 0 );

	record = (struct Rva0081BC80Record *)( comm->m_recvBuffer
		+ comm->m_recvReadOffset );

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

/* The control message: a code at +0x08 and a value at +0x0C, the same header
 * the other transports use. */
struct Rva0081AA20Message
{
	int m_length;                   /* +0x00 */
	unsigned int m_tick;            /* +0x04 */
	int m_code;                     /* +0x08 */
	int m_value;                    /* +0x0C */
};

/* A queued send record carries its sequence at +0x08.  Only that is
 * established here. */
struct Rva0081AA20SendRecord
{
	int m_length;                   /* +0x00 */
	unsigned int m_tick;            /* +0x04 */
	unsigned int m_sequence;        /* +0x08, this record's own */
	int m_ack;                      /* +0x0C, piggybacked acknowledgement */
	unsigned char m_data[ 4 ];      /* +0x10 */
};

void Rva0081A8C0( struct Rva0081BD40Comm *comm );

/* 0x0081AA20 IS THE ACKNOWLEDGEMENT HANDLER, and it is the SAME BODY the third
 * transport has at 0x008186C0 -- same off-by-one for code 4, same
 * drag-the-ack-cursor loop, same rewind and kick -- walking this object's ring
 * at +0xEC..+0x100 instead of that one's at +0xB0..+0xC8.
 *
 * Because that one is already converted and explained, the reading here is not
 * a fresh inference: code 4 means "I want sequence N next" so everything BELOW
 * N is retired, anything else means "I have N" so N itself goes too, and the
 * comparison is unsigned so a wrapped sequence space still retires correctly.
 * Code 4 additionally snaps the transmit cursor back and kicks the sender,
 * which is what makes it a retransmit request.
 *
 * Duplicated code rather than shared: the two bodies differ only in field
 * offsets and which kick they call.
 */
void Rva0081AA20( struct Rva0081BD40Comm *comm,
	struct Rva0081AA20Message *message )
{
	int bRewind;
	unsigned int uAcked;
	struct Rva0081AA20SendRecord *record;
	int iAcked;

	bRewind = ( message->m_code == 4 );

	if ( bRewind )
		iAcked = message->m_value - 1;
	else
		iAcked = message->m_value;

	uAcked = iAcked;

	while ( comm->m_sendReadOffset != comm->m_sendWriteOffset )
	{
		record = (struct Rva0081AA20SendRecord *)( comm->m_sendBuffer
			+ comm->m_sendReadOffset );

		if ( uAcked < record->m_sequence )
			break;

		if ( comm->m_sendAckOffset == comm->m_sendReadOffset )
		{
			comm->m_sendAckOffset = ( comm->m_sendAckOffset
				+ comm->m_sendRecordSize ) % comm->m_sendBufferSize;
		}

		comm->m_sendReadOffset = ( comm->m_sendReadOffset
			+ comm->m_sendRecordSize ) % comm->m_sendBufferSize;
	}

	if ( bRewind )
	{
		comm->m_sendAckOffset = comm->m_sendReadOffset;
		Rva0081A8C0( comm );
	}
}

int Rva0081A3B0( struct Rva0081BD40Comm *comm,
	struct Rva0081AA20SendRecord *record );

/* 0x0081A8C0 IS A WINDOWED SENDER: it transmits queued records while a
 * BYTE BUDGET lasts, and the budget is 0x800 -- 2048 bytes in flight.
 *
 * It computes the budget by walking everything ALREADY IN FLIGHT -- from the
 * read cursor up to the transmit cursor -- and subtracting each record's
 * length from 0x800.  So the window counts bytes outstanding, not packets, and
 * a few large records close it as effectively as many small ones.
 *
 * THE FIRST RECORD ALWAYS GOES OUT REGARDLESS OF THE BUDGET.  The stop test is
 * "transmit cursor is not at the read cursor AND this record is bigger than
 * what is left", so when nothing is in flight the size check is skipped
 * entirely.  Without that exception a record larger than 2048 bytes could
 * never be sent at all -- the window would never open wide enough -- and the
 * connection would wedge.  Reading the test as a plain budget check misses
 * that completely.
 *
 * Every record is stamped with one less than the expected receive sequence on
 * its way out, which is how acknowledgements ride along with data.
 *
 * The optional send callback fires BEFORE the transmit and its result is not
 * consulted; a failed transmit breaks the loop and leaves the transmit cursor
 * where it was, so the record is retried rather than skipped.
 */
void Rva0081A8C0( struct Rva0081BD40Comm *comm )
{
	int iOffset;
	int iBudget;
	struct Rva0081AA20SendRecord *p;
	struct Rva0081AA20SendRecord *record;

	iBudget = 0x800;

	for ( iOffset = comm->m_sendReadOffset;
		iOffset != comm->m_sendAckOffset;
		iOffset = ( iOffset + comm->m_sendRecordSize )
			% comm->m_sendBufferSize )
	{
		p = (struct Rva0081AA20SendRecord *)( comm->m_sendBuffer + iOffset );
		iBudget = iBudget - p->m_length;
	}

	while ( comm->m_sendAckOffset != comm->m_sendWriteOffset )
	{
		record = (struct Rva0081AA20SendRecord *)( comm->m_sendBuffer
			+ comm->m_sendAckOffset );

		if ( comm->m_sendAckOffset != comm->m_sendReadOffset
			&& record->m_length > iBudget )
			break;

		iBudget = iBudget - record->m_length;
		record->m_ack = comm->m_recvSequence - 1;

		if ( comm->m_sendProc != 0 )
		{
			comm->m_sendProc( comm, (char *)record + 0x10, record->m_length,
				0 );
		}

		if ( Rva0081A3B0( comm, record ) < 0 )
			break;

		comm->m_sendAckOffset = ( comm->m_sendAckOffset
			+ comm->m_sendRecordSize ) % comm->m_sendBufferSize;
	}
}
