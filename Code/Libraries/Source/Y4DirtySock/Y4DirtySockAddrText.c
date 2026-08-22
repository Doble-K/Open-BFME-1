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

/* RETURNS the destination, or null on a rejected size.  Nothing at the call
 * site below shows that -- a discarded return costs no bytes -- so the type
 * comes from the definition further down, not from use. */
char *Rva007FF860( const unsigned char *address, char *destination, int size );

char *Rva007FFB50AddrText( unsigned int address )
{
	char sa[ 0x10 ];
	unsigned int uAddress;

	uAddress = address;
	sa[ 7 ] = (char)uAddress;  uAddress >>= 8;
	sa[ 6 ] = (char)uAddress;  uAddress >>= 8;
	sa[ 5 ] = (char)uAddress;  uAddress >>= 8;
	sa[ 4 ] = (char)uAddress;

	Rva007FF860( (const unsigned char *)sa, g_Rva0130ACC8Text, 20 );
	return g_Rva0130ACC8Text;
}

/* 0x007FF860 renders a socket address as a dotted quad, BY HAND -- no CRT call
 * anywhere in it, just idiv by 100 and by 10.  It reads bytes +4..+7 of the
 * address, which is the same big-endian placement the rest of this library
 * uses, and that is why the helper above bothers to fill only those four.
 *
 * THE SIZE CHECK IS TWO CHECKS AND THEY BEHAVE DIFFERENTLY.  A non-positive
 * size returns null and TOUCHES NOTHING -- the destination may not even be
 * writable.  A positive but too-small size also returns null, but first writes
 * a terminator, so the caller is left with an empty string rather than
 * uninitialised bytes.  The threshold is 16, which is the worst case
 * "255.255.255.255" plus its NUL, so the routine never truncates: it either
 * has room for any address or refuses.
 *
 * Each octet is emitted with LEADING zeros suppressed but interior ones kept:
 * the hundreds digit appears only above 99, and the tens digit appears either
 * when the remainder exceeds 9 OR unconditionally once a hundreds digit has
 * been written.  So 10.0.0.1 renders as itself rather than 010.000.000.001,
 * while 205 still renders as 205 rather than 25.  The separator is written
 * after every octet except the last, which is what the `i < 5` guard is doing
 * inside a loop that runs i from 2 to 5.
 *
 * The octet is held in a SIGNED int -- the divides are idiv with cdq and the
 * comparisons are jle -- even though it is loaded with movzx and so can never
 * be negative.  Retail's spelling; an unsigned local would compile to div.
 */
char *Rva007FF860( const unsigned char *address, char *destination, int size )
{
	int i;
	char *p;
	int iOctet;

	p = destination;

	if ( size <= 0 )
		return 0;

	if ( size < 0x10 )
	{
		*p = 0;
		return 0;
	}

	for ( i = 2; i < 6; i++ )
	{
		iOctet = address[ i + 2 ];

		if ( iOctet > 99 )
		{
			*p++ = (char)( iOctet / 100 + '0' );
			iOctet = iOctet % 100;
			/* THE TENS DIGIT IS UNCONDITIONAL HERE, and it has to be: once a
			 * hundreds digit has been written, a zero in the tens place is
			 * significant.  205 renders as 2, 0, 5.  The `> 9` test below
			 * cannot do this job, because 205 %% 100 is 5. */
			*p++ = (char)( iOctet / 10 + '0' );
			iOctet = iOctet % 10;
		}

		if ( iOctet > 9 )
		{
			*p++ = (char)( iOctet / 10 + '0' );
			iOctet = iOctet % 10;
		}

		*p++ = (char)( iOctet + '0' );

		if ( i < 5 )
			*p++ = '.';
	}

	*p = 0;
	return destination;
}

/* 0x007FF990 is a 16-bit byte swap -- network-to-host order, or equally
 * host-to-network, since the operation is its own inverse.  It writes the
 * argument into a two-byte object and reads the two bytes back individually,
 * high one first, which is how you swap without a rotate instruction.
 *
 * Retail's own name for that object, from the /GZ frame descriptor, is `x`,
 * and its declared width there is 2 -- so this is an ARRAY aliased by a 16-bit
 * store, not a short read back through a cast.  The argument is loaded with a
 * 16-bit `mov ax`, so the parameter really is 16 bits wide rather than an int
 * that happens to be small.
 *
 * The result is built with movzx and returned in full 32-bit eax, so the
 * return is int rather than short: a caller gets 0x0000..0xFFFF and never a
 * sign-extended value.
 */
int Rva007FF990( unsigned short value )
{
	unsigned char x[ 2 ];

	*(unsigned short *)x = value;
	return ( x[ 0 ] << 8 ) | x[ 1 ];
}

/* 0x007FF9F0 is the 32-bit companion of the swap above -- retail's frame
 * descriptor names its local `x` and gives its width as 4.  Same idea: store
 * the argument whole, read the bytes back individually most-significant first.
 */
int Rva007FF9F0( unsigned int value )
{
	unsigned char x[ 4 ];

	*(unsigned int *)x = value;
	return ( ( ( ( ( x[ 0 ] << 8 ) | x[ 1 ] ) << 8 ) | x[ 2 ] ) << 8 ) | x[ 3 ];
}

/* 0x007FFA60 swaps sixteen bits too, but SPELLED THE OTHER WAY ROUND, and the
 * pair is worth keeping distinct rather than collapsing.  0x007FF990 stores a
 * short and reads two bytes out; this one writes two bytes in and reads a
 * short back.  The two are functionally identical and compile to different
 * code, so which one a call site uses is evidence about which direction the
 * original source meant -- host-to-network here, network-to-host there.
 *
 * It also shifts the PARAMETER rather than a local, and shifts it as sixteen
 * bits: the emitted `shr cx, 8` is a 16-bit operation writing back to the
 * argument slot.  A 32-bit temporary would compile to `shr eax, 8`.
 *
 * The return is a 16-bit `mov ax`, so this one returns unsigned short where
 * its counterpart returns int.
 */
unsigned short Rva007FFA60( unsigned short value )
{
	unsigned char x[ 2 ];

	x[ 1 ] = (unsigned char)value;
	value >>= 8;
	x[ 0 ] = (unsigned char)value;

	return *(unsigned short *)x;
}

/* 0x007FF720 COMPARES TWO SOCKET ADDRESSES, and the interesting part is that
 * it compares a different NUMBER OF BYTES depending on the family.
 *
 * The family words are checked first and, when they differ, their difference
 * is returned directly -- so the ordering between two different families is by
 * family number, not by content.  When they agree the rest is handed to the
 * bounded compare in the socket unit, over 6 bytes for AF_INET and 14
 * otherwise.  Six is exactly the port plus the address, which means THE
 * TRAILING EIGHT BYTES OF AN AF_INET ADDRESS ARE DELIBERATELY IGNORED -- and
 * those are the same eight the receive path stamps an arrival timestamp into.
 * Two datagrams from one peer therefore compare equal despite differing
 * bytes, which is plainly the point.
 *
 * 14 is the default rather than 16, so the family itself is never re-compared;
 * it has already been established equal by the time the length is used.
 */
struct Rva007FF720SockAddr
{
	unsigned short m_family;        /* +0x00 */
	char m_data[ 14 ];              /* +0x02 */
};

int Rva007FE6C0( const char *string1, const char *string2, int length );

int Rva007FF720( const struct Rva007FF720SockAddr *a,
	const struct Rva007FF720SockAddr *b )
{
	int iLength;

	iLength = 14;

	if ( a->m_family != b->m_family )
		return a->m_family - b->m_family;

	if ( a->m_family == 2 )
		iLength = 6;

	return Rva007FE6C0( a->m_data, b->m_data, iLength );
}

/* 0x007FFC10 is the inverse of the text helper at the top of this file: it
 * runs the parser at 0x007FF790 over whatever it is handed, then lifts the
 * four address bytes out of the resulting socket address in the same
 * big-endian order everything else here uses.  So the parser fills a whole
 * socket address and this discards all of it except the address itself.
 */
/* Returns 0 or -1; the extractor above ignores that, which is why the type
 * comes from the definition below rather than from this call site. */
int Rva007FF790( char *sa, const char *text );

int Rva007FFC10( const char *source )
{
	char sa[ 0x10 ];
	unsigned int uAddress;

	Rva007FF790( sa, source );

	uAddress = ( ( ( ( (unsigned char *)sa )[ 4 ] << 8
		| ( (unsigned char *)sa )[ 5 ] ) << 8
		| ( (unsigned char *)sa )[ 6 ] ) << 8 )
		| ( (unsigned char *)sa )[ 7 ];

	return uAddress;
}

/* 0x007FF790 PARSES a dotted quad straight into bytes +4..+7 of a socket
 * address -- the inverse of the formatter above, and the two agree on where
 * the address lives.
 *
 * THE SEPARATOR EXPECTED AFTER EACH OCTET IS COMPUTED, NOT BRANCHED ON: after
 * the first three it is a dot, after the fourth it is the terminator, and the
 * two cases are folded into one comparison.  So a trailing dot is rejected and
 * so is a missing one -- the same test does both.
 *
 * There is NO RANGE CHECK on an octet.  Digits are accumulated into a single
 * byte with `p[i] = p[i] * 10 + digit`, so the multiply and add wrap silently:
 * "999" parses as 231 rather than failing.  Only the punctuation is validated.
 *
 * On failure all four bytes are cleared, and the ORDER of those stores is
 * evidence about the source: 1, 0, 3, 2, which is two chained pair
 * assignments rather than one four-way chain or four separate statements.
 *
 * The digit conversion masks with 0x0F rather than subtracting '0'.  The two
 * agree for actual digits, which the loop has already established.
 */
int Rva007FF790( char *sa, const char *text )
{
	int i;
	unsigned char *p;

	p = (unsigned char *)sa + 4;

	for ( i = 0; i < 4; i++, text++ )
	{
		p[ i ] = 0;

		while ( *text >= '0' && *text <= '9' )
		{
			p[ i ] = (unsigned char)( p[ i ] * 10 + ( *text & 0x0F ) );
			text++;
		}

		if ( *text != ( i < 3 ? '.' : 0 ) )
		{
			p[ 0 ] = p[ 1 ] = 0;
			p[ 2 ] = p[ 3 ] = 0;
			return -1;
		}
	}

	return 0;
}
