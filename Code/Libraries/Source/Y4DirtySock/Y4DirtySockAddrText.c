// cl: /Od /GZ /GS /MD /DNDEBUG
/* EA DirtySock -- address-to-text helper, a separate translation unit from the
 * socket layer at 0x007FD080..0x007FEF60 because it sits in a different block
 * of .text entirely, past the socket module's last body.
 *
 * 0x007FFB50 renders a 32-bit address as text.  It builds a bare socket
 * address whose FOUR ADDRESS BYTES ARE ALL IT FILLS IN -- the family and port
 * are left as whatever the /GZ fill put there -- and hands it to the formatter
 * at 0x007FF860 with a 20-byte destination.  So the formatter reads only
 * +4..+7, and this is address-only rendering rather than address-and-port.
 *
 * Retail's own name for the local, from the /GZ frame descriptor, is `sa`, and
 * its width is 0x10.  The byte placement is the same big-endian one used
 * throughout this library: the value is shifted right eight bits at a time
 * with the low byte written to the highest offset first.
 *
 * THE RESULT IS A SHARED STATIC BUFFER, NOT AN ALLOCATION -- the same address
 * is both the formatter's destination and the return value.  So the caller
 * does not own it and a second call clobbers the first; the remap lookup at
 * 0x007FD660 calls this twice in one printf-style argument list, which is
 * exactly the pattern that would break if it were per-call storage.  It gets
 * away with it because each result is consumed by a separate call.
 */

/* Twenty bytes: the size is the formatter's third argument, an immediate. */
extern char g_Rva0130ACC8Text[ 20 ];

void Rva007FF860( const void *address, char *destination, int size );

char *Rva007FFB50AddrText( unsigned int address )
{
	char sa[ 0x10 ];
	unsigned int uAddress;

	uAddress = address;
	sa[ 7 ] = (char)uAddress;  uAddress >>= 8;
	sa[ 6 ] = (char)uAddress;  uAddress >>= 8;
	sa[ 5 ] = (char)uAddress;  uAddress >>= 8;
	sa[ 4 ] = (char)uAddress;

	Rva007FF860( sa, g_Rva0130ACC8Text, 20 );
	return g_Rva0130ACC8Text;
}
