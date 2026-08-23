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
	char m_head[ 0xD4 ];
	int m_recordSize;               /* +0xD4 */
	int m_bufferSize;               /* +0xD8 */
	char m_gap[ 0x04 ];
	int m_offset;                   /* +0xE0 */
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
 * fourth.  Nothing here inspects the four arguments, so their types are not
 * recoverable and they are declared as plain words -- converting 0x0081BC80
 * is what would settle them.
 */
int Rva0081BC80( struct Rva0081BD40Comm *comm, int a, int b, int c );

int Rva0081BD40( struct Rva0081BD40Comm *comm, int a, int b, int c )
{
	int iResult;

	iResult = Rva0081BC80( comm, a, b, c );

	if ( iResult >= 0 )
		comm->m_offset = ( comm->m_offset + comm->m_recordSize )
			% comm->m_bufferSize;

	return iResult;
}
