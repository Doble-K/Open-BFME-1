// cl: /Od /GZ /MD /DNDEBUG
/* EA DirtySock -- text-to-value scanners, /Od with /GZ.  Both take a default
 * to return when the input is unusable, so neither can fail visibly; a caller
 * that needs to tell "absent" from "parsed" has to pick a default it can
 * recognise.  Placement is by address neighbourhood.
 */

/* 0x007EE8B0 PACKS UP TO FOUR PRINTABLE CHARACTERS INTO AN INT -- the same
 * four-character tags the socket layer dispatches on, 'xmap' and the rest,
 * built from text instead of written as a literal.
 *
 * THE LENGTH LIMIT IS ENFORCED BY THE ACCUMULATOR, not by a counter.  It
 * starts at 0x20202020 -- four spaces -- and the loop runs while it stays
 * below 0x20FFFFFF.  Each character shifts a space out of the top, so after
 * the fourth the leading byte is a printable character, the value exceeds the
 * bound, and the loop stops.  A shorter string leaves the unused leading bytes
 * as SPACES rather than zeros, which is what makes a two-character tag compare
 * equal to the same tag written as a padded literal.
 *
 * The bound is a SIGNED comparison, which is safe only because the accepted
 * range stops at 0x7E: a character with the high bit set would make the
 * accumulator negative and the loop would never stop on its own.  The range
 * check is what protects the bound, not the other way round.
 */
int Rva007EE8B0( const char *text, int defaultValue )
{
	int iValue;

	if ( text == 0 || *text <= ' ' || *text >= 0x7F )
		return defaultValue;

	iValue = 0x20202020;

	while ( iValue < 0x20FFFFFF && *text > ' ' && *text < 0x7F )
	{
		iValue = ( iValue << 8 ) | *text;
		text++;
	}

	return iValue;
}

/* 0x007EE820 PARSES A DOTTED QUAD into a packed address, and it is the same
 * algorithm as the socket unit's parser at 0x007FFDD0 written differently:
 * there the running value's low byte is isolated by subtracting it out and
 * adding it back scaled, here by masking with 0xFFFFFF00 and OR-ing the new
 * byte in.  Same effect, and the two spellings sitting in one image is a
 * useful reminder that a shape match across bodies is not an identity.
 *
 * IT STOPS AT THE FIRST CHARACTER THAT IS NEITHER A DIGIT NOR A DOT and
 * returns what it has, so trailing text is ignored rather than rejected and
 * an empty string yields zero -- not the default, which is reached only by a
 * null pointer.
 *
 * There is no range check on an octet: digits accumulate into a single byte,
 * so "999" wraps rather than failing, exactly as the other parser does.
 */
int Rva007EE820( const char *text, int defaultValue )
{
	int iValue;

	iValue = 0;

	if ( text == 0 )
		return defaultValue;

	for ( iValue = 0; ; text++ )
	{
		if ( *text >= '0' && *text <= '9' )
		{
			iValue = ( iValue & 0xFFFFFF00 )
				| ( ( iValue & 0xFF ) * 10 + ( *text & 0x0F ) );
		}
		else if ( *text == '.' )
		{
			iValue = iValue << 8;
		}
		else
		{
			break;
		}
	}

	return iValue;
}

/* 0x007EE720 PARSES A SIGNED DECIMAL INTEGER, and the two things it does NOT
 * do are the ones worth knowing.
 *
 * IT DOES NOT SKIP LEADING WHITESPACE.  A space before the sign or the digits
 * ends the parse immediately and yields zero -- not the default, which only a
 * null pointer reaches.  Anything handing it text straight out of a
 * configuration line has to trim first.
 *
 * AND IT DOES NOT DETECT OVERFLOW: digits accumulate into an int by multiply
 * and add with no bound, so a long enough run wraps silently.
 *
 * A leading '+' is accepted and skipped, which strtol does but atoi is not
 * required to.  The sign is kept as a multiplier applied at the end rather
 * than by negating the accumulator, so the most negative value is not
 * representable through this path -- it would have to overflow positive first.
 */
int Rva007EE720( const char *text, int defaultValue )
{
	int iSign;
	int iValue;

	if ( text == 0 )
		return defaultValue;

	iSign = 1;

	if ( *text == '+' )
	{
		text++;
	}
	else if ( *text == '-' )
	{
		text++;
		iSign = -1;
	}

	for ( iValue = 0; *text >= '0' && *text <= '9'; text++ )
		iValue = iValue * 10 + ( *text & 0x0F );

	return iSign * iValue;
}

/* A 256-entry translation table, indexed by a SIGNED char -- so a byte with
 * the high bit set reads BEFORE the table's start.  That is what the bytes do;
 * whether anything upstream keeps such bytes out is not visible here. */
extern char g_Rva0112A210Fold[];

/* 0x007EFD00 COMPARES TWO STRINGS THROUGH THAT TABLE, and it is doing three
 * jobs at once rather than one.
 *
 * QUOTES SET A PER-SIDE TERMINATOR.  A leading double quote is consumed and
 * remembered, and thereafter a matching quote ends that side; without one the
 * side instead ends at any character below space.  The two sides are decided
 * INDEPENDENTLY, so a quoted string compares cleanly against an unquoted one
 * -- which is the point, since it lets a configuration value be written either
 * way.
 *
 * The end-of-string test is therefore not a NUL test: a control character ends
 * an unquoted side, and a NUL ends a quoted one only because it is below
 * space... which it is not, in the quoted case.  A quoted string missing its
 * closing quote runs past the terminator.
 *
 * The loop is a DO-WHILE, so both sides always advance at least once; the
 * caller's null and empty-string checks at the top are what make that safe.
 *
 * The result is the difference of the two folded characters, so it orders by
 * the TABLE's ordering rather than by the raw bytes.
 */
int Rva007EFD00( const char *a, const char *b )
{
	unsigned char cTermA;
	unsigned char cTermB;
	unsigned char cA;
	unsigned char cB;

	if ( a == 0 || *a == 0 )
		return -1;

	cTermA = ( *a == '"' ) ? *a++ : 0;
	cTermB = ( *b == '"' ) ? *b++ : 0;

	do
	{
		cA = g_Rva0112A210Fold[ *a ];
		a++;
		if ( cA == cTermA || ( cA < ' ' && cTermA == 0 ) )
			cA = 0;

		cB = g_Rva0112A210Fold[ *b ];
		b++;
		if ( cB == cTermB || ( cB < ' ' && cTermB == 0 ) )
			cB = 0;
	}
	while ( cA == cB && cA != 0 && cB != 0 );

	return cA - cB;
}

/* A separator character and a suffix string, both in writable data rather than
 * among the literals, so both are configurable at run time.  The separator is
 * a plain char -- read with movsx where the buffer's own bytes are read with
 * movzx, which is what types the two differently. */
extern char g_Rva012C391CSeparator;
extern char g_Rva012C392CSuffix[];

/* 0x007EC4D0 APPENDS THE SUFFIX TO A BUFFER, inserting the separator first if
 * the buffer needs one, and returns 0 or -1 for "did not fit".
 *
 * THE SEPARATOR IS ONLY ADDED WHEN IT IS ACTUALLY MISSING.  Three conditions
 * all have to hold: the buffer is non-empty, its last character is not a
 * control character, and it is not already the separator.  So calling this
 * twice does not double the separator, and appending to text that already ends
 * in one leaves it alone -- which is what makes the operation repeatable.
 *
 * THE TWO LENGTH CHECKS ARE DIFFERENT AND BOTH MATTER.  The separator needs
 * one free byte and is checked against size - 1; the suffix is checked with a
 * FIXED MARGIN OF FOUR rather than against its own length, so a suffix longer
 * than three characters plus its terminator would overrun.  Nothing here reads
 * the suffix's length, so that margin is an assumption about the data rather
 * than a bound derived from it.
 *
 * A buffer too small for the suffix is left with the separator already
 * appended -- the failure is not atomic, and -1 does not mean "unchanged".
 */
int Rva007EC4D0( unsigned char *buffer, int size )
{
	int i;
	int iResult;
	char *pSuffix;
	unsigned char *pBuffer;

	iResult = -1;
	pSuffix = g_Rva012C392CSuffix;
	pBuffer = buffer;

	for ( i = 0; pBuffer[ i ] != 0; i++ )
	{
	}

	if ( i > 0 && pBuffer[ i - 1 ] >= ' '
		&& pBuffer[ i - 1 ] != g_Rva012C391CSeparator
		&& i < size - 1 )
	{
		pBuffer[ i ] = g_Rva012C391CSeparator;
		i++;
		pBuffer[ i ] = 0;
	}

	if ( i + 4 < size )
	{
		while ( *pSuffix != 0 )
		{
			pBuffer[ i ] = *pSuffix;
			i++;
			pSuffix++;
		}

		pBuffer[ i ] = 0;
		iResult = 0;
	}

	return iResult;
}

/* 0x007EC3F0 REPLACES THE VALUE OF A ONE-FIELD RECORD IN PLACE, rewriting the
 * buffer as "key=\nvalue" and returning 0, or -1 if there is not enough room.
 *
 * THE SCAN AT THE TOP DEFINES THE RECORD FORMAT more precisely than any of the
 * parsers in this file do.  A delimiter is '=' OR ':' FOLLOWED BY A CONTROL
 * CHARACTER -- neither punctuation mark alone ends the key, so a key may
 * contain either as long as ordinary text follows it.  What is written back is
 * always '=' and 0x0A, so ':' is accepted on input and never produced.
 * Finding no delimiter is not an error: the scan then stops at the terminator
 * and the whole existing string is taken as the key.
 *
 * A NULL VALUE MEANS "TRUNCATE", NOT "NO CHANGE", and it returns success.  The
 * key's terminator is written BEFORE the value is examined, so by the time the
 * null test runs the old value is already gone -- and the same is true of the
 * -1 path below, which leaves a truncated buffer behind.  NEITHER FAILURE NOR
 * THE NULL CASE IS A NO-OP.
 *
 * THE MARGIN OF FIVE IS NOT A FIT CHECK.  The copy stops at the last byte of
 * the buffer and the terminator always lands there, so two bytes past the key
 * would be enough to write an empty value.  Requiring five means the caller
 * gets -1 rather than a record whose value was cut to almost nothing: the
 * check is about the result being worth writing, not about it fitting.
 */
int Rva007EC3F0( unsigned char *buffer, int size, const char *value )
{
	unsigned char *p;
	unsigned char *pEnd;

	for ( p = buffer; *p != 0; p++ )
	{
		if ( ( *p == '=' || *p == ':' ) && p[ 1 ] < ' ' )
		{
			break;
		}
	}

	*p = 0;

	if ( value == 0 )
	{
		return 0;
	}

	pEnd = buffer + size - 1;

	if ( pEnd - p < 5 )
	{
		return -1;
	}

	*p = '=';
	p++;
	*p = '\n';
	p++;

	while ( *value != 0 && p != pEnd )
	{
		*p = *value;
		p++;
		value++;
	}

	*p = 0;
	return 0;
}
